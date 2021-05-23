#include "dataprocessor.h"

std::vector<std::vector<double>> DataProcessor::fftCalculation(std::vector<double> data) {
    std::vector<std::vector<double>> out = {
        std::vector<double>(dataSize / 2),
        std::vector<double>(dataSize / 2)};
    std::vector<fftw_complex> fft_out(dataSize);
    fftw_plan p = fftw_plan_dft_r2c_1d(dataSize, data.data(), fft_out.data(), FFTW_ESTIMATE);
    fftw_execute(p);
    for (auto i = 0; i < dataSize / 2; i++) {
        out[0][i] = pow(10, -processGain / 10.0) / dataSize * (std::sqrt(pow(fft_out[i][0], 2.0) + pow(fft_out[i][1], 2.0)));
        out[1][i] = 20.0 * log10(out[0][i]);
    }
    fftw_destroy_plan(p);
    fftw_cleanup();
    return out;
}

std::vector<double> DataProcessor::fftAverage(std::vector<std::vector<double>> data) {
    std::vector<double> out(dataSize / 2, 0);
    for (int i = 0; i < dataSize / 2; i++) {
        for (int j = 0; j < accumulatorSize; j++) out[i] += data[j][i];
        out[i] = 20.0 * log10(out[i] / accumulatorSize);
    }

    return out;
}

std::vector<DataProcessor::Peak> DataProcessor::getPeaks(std::vector<std::vector<double>> fft) {
    std::vector<Peak> out;

    for (auto &freqBin : frequencyBins) {
        int max_index = 0;
        double max_val = -__DBL_MAX__;
        for (int i = freqBin.begin; i < freqBin.end; i++) {
            if (fft[0][i] > max_val) {
                max_index = i;
                max_val = fft[0][i];
            }
        }
        Peak peakData = getWeightedFrequency(fft, max_index);
        out.push_back(peakData);
    }
    return out;
}

DataProcessor::Peak DataProcessor::getWeightedFrequency(std::vector<std::vector<double>> fft, int index) {
    double weightedFrequency = 0.0;
    double powerIntegral = 0.0;
    for (int i = -21; i <= 21; i++) {
        if (index + i >= 0 && index + i < dataSize) {
            powerIntegral += fft[0][index + i];
            weightedFrequency += fft[0][index + i] * frequencyDomain[index + i];
        }
    }

    Peak out = {weightedFrequency / powerIntegral, powerIntegral, index};
    return out;
}

double DataProcessor::calculateEntropy(std::vector<std::vector<double>> data) {
    double out = 0.0;
    double normalizeData = 0.0;
    for (int i = 0; i < dataSize / 2; i++) normalizeData += data[0][i];
    for (int i = 0; i < dataSize / 2; i++) out -= data[0][i] / normalizeData * log2(data[0][i] / normalizeData);
    return out;
}

void DataProcessor::processData(std::vector<double> amplitudeData) {
    auto timeNow = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
    DataLogger::TimeData timestamp = {timeNow, 0.0, 0.0};
    emit logTimestamp(timestamp);
    // Cast data from std::vector to QVector. Necessary to plot data on QCustomPlot
    QVector<double> Qoutx = QVector<double>(timeDomain.begin(), timeDomain.end());
    QVector<double> Qouty = QVector<double>(amplitudeData.begin(), amplitudeData.end());
    // Emit signal to MainWindow to plot time data
    emit dataReady(Qoutx, Qouty);

    // Apply Hanning Window to data
    for (unsigned int i = 0; i < amplitudeData.size(); ++i) amplitudeData[i] *= dataWindow[i];

    // Calculate FFT
    std::vector<std::vector<double>> dataFFT = fftCalculation(amplitudeData);
    // Accumulate FFT
    fftAccumulator[accumulatorPointer] = dataFFT[0];
    accumulatorPointer = (++accumulatorPointer) % accumulatorSize;
    // Average FFT
    std::vector<double> averageFFT = fftAverage(fftAccumulator);
    if (accumulatorPointer == 0) {
        DataLogger::SpectrumData spectrum = {averageFFT};
        emit logSpectrum(spectrum);
    }

    // Cast FFT from std::vector to QVector. Necessary to plot data on QCustomPlot
    Qoutx = QVector<double>(frequencyDomain.begin(), frequencyDomain.end());
    Qouty = QVector<double>(averageFFT.begin(), averageFFT.end());
    // Emit signal to MainWindow to plot frequency data
    emit fftReady(Qoutx, Qouty);

    // Calculate peaks on FFT
    std::vector<Peak> peaksData = getPeaks(dataFFT);
    DataLogger::PeaksData peak = {peaksData[0].frequency, peaksData[0].value};
    emit logPeaks(peak);
    // Emit signal to MainWindow to update peak frequency and power
    emit peakOneReady(peaksData[0].frequency, 20.0 * log10(peaksData[0].value));
    emit peakTwoReady(peaksData[1].frequency, 20.0 * log10(peaksData[1].value));
    emit peakThreeReady(peaksData[2].frequency, 20.0 * log10(peaksData[2].value));
    emit plotData();
    //Sleep(500);
}

void DataProcessor::initialize() {
    dataWindow = DataWindow::CreateWindow(dataSize, DataWindow::NUTALL);
    timeDomain = std::vector<double>(dataSize, 0);
    frequencyDomain = std::vector<double>(dataSize / 2, 0);
    for (int i = 0; i < dataSize; i++) {
        timeDomain[i] = (double)i / (double)sampleFrequency;
        if (i < dataSize / 2) frequencyDomain[i] = (double)sampleFrequency * i / dataSize;
    }

    frequencyBins = std::vector<FrequencyIndex>(3);
    frequencyBins[0] = {(int)floor(dataSize * 10500.0 / sampleFrequency), (int)ceil(dataSize * 11500.0 / sampleFrequency)};
    frequencyBins[1] = {(int)floor(dataSize * 11500.0 / sampleFrequency), (int)ceil(dataSize * 12500.0 / sampleFrequency)};
    frequencyBins[2] = {(int)floor(dataSize * 12500.0 / sampleFrequency), (int)ceil(dataSize * 13500.0 / sampleFrequency)};

    for (int i = 0; i < accumulatorSize; i++) fftAccumulator.push_back(std::vector<double>(dataSize, 0));
}