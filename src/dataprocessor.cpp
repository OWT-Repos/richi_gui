#include "dataprocessor.h"

DataProcessor::~DataProcessor() {
    std::cout << "Closing DataProcessor instance" << std::endl;
    dataAcquiring->quit();
    dataAcquiring->wait();
    emit gpsQuit();
    gpsAcquiring->quit();
    gpsAcquiring->wait();
}

// Function to calculate the FFT of a time serie
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

// Function to calculate the average FFT of the accumulator
std::vector<std::vector<double>> DataProcessor::fftAverage(std::vector<std::vector<double>> data) {
    std::vector<std::vector<double>> out = {
        std::vector<double>(dataSize / 2, 0),
        std::vector<double>(dataSize / 2, 0)};
    for (int i = 0; i < dataSize / 2; i++) {
        for (int j = 0; j < accumulatorSize; j++) out[0][i] += data[j][i];
        out[0][i] = (out[0][i] / accumulatorSize);
        out[1][i] = 20.0 * log10(out[0][i]);
    }

    return out;
}

// Function to get the peaks of the instantaneous FFT
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
        // Peak peakData = getWeightedFrequency(fft, max_index);
        Peak peakData = {max_index * sampleFrequency / dataSize, max_val, max_index};
        out.push_back(peakData);
    }
    return out;
}

// Function to get the weighted frequency of the peak
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

// Function to calculate the entropy of the FFT - Unused right now
double DataProcessor::calculateEntropy(std::vector<std::vector<double>> data) {
    double out = 0.0;
    double normalizeData = 0.0;
    for (int i = 0; i < dataSize / 2; i++) normalizeData += data[0][i];
    for (int i = 0; i < dataSize / 2; i++) out -= data[0][i] / normalizeData * log2(data[0][i] / normalizeData);
    return out;
}

// Function to calculate noise floor of the FFT
double DataProcessor::calculateNoiseFloor(std::vector<double> data) {
    double out = 0.0;
    FrequencyIndex freqRange = {(int)floor(dataSize * (8000.0) / sampleFrequency),
                                (int)ceil(dataSize * (10000.0) / sampleFrequency)};
    for (int i = freqRange.begin; i < freqRange.end; i++)
        out += data[i];

    return out / (freqRange.end - freqRange.begin);
}

// Qt Slot used to receive the data from DataAcquisition
void DataProcessor::processData(std::vector<double> amplitudeData) {
    // Apply Hanning Window to data
    for (unsigned int i = 0; i < amplitudeData.size(); ++i) amplitudeData[i] *= dataWindow[i];

    // Calculate FFT
    std::vector<std::vector<double>> dataFFT = fftCalculation(amplitudeData);
    // Accumulate FFT
    fftAccumulator[accumulatorPointer] = dataFFT[0];
    accumulatorPointer = (++accumulatorPointer) % accumulatorSize;
    // Average FFT
    averageFFT = fftAverage(fftAccumulator);

    // Cast FFT from std::vector to QVector. Necessary to plot data on QCustomPlot
    QVector<double> Qoutx = QVector<double>::fromStdVector(frequencyDomain);
    QVector<double> Qouty = QVector<double>::fromStdVector(averageFFT[1]);
    // Emit signal to MainWindow to update frequency data
    emit fftReady(Qoutx, Qouty);

    // Calculate peaks on FFT
    peaksData = getPeaks(averageFFT);
    double noiseFloor = calculateNoiseFloor(averageFFT[0]);

    // Emit signal to MainWindow to update peak frequency and power
    emit setNoiseFloor(20.0 * log10(noiseFloor));
    emit peakOneReady(peaksData[0].frequency, 20.0 * log10(peaksData[0].power));
    emit peakTwoReady(peaksData[1].frequency, 20.0 * log10(peaksData[1].power));
    emit peakThreeReady(peaksData[2].frequency, 20.0 * log10(peaksData[2].power));
    // Emit signal to update plots
    emit plotData();
}

// Qt Slot used to update processor parameters
void DataProcessor::updateParameters(int sampleSizeArg, int sampleFrequencyArg, int accumulatorSizeArg, int windowOptionArg,
                                     float beaconAArg, float beaconBArg, float beaconCArg) {
    sampleFrequency = sampleFrequencyArg;
    dataSize = sampleSizeArg;
    accumulatorSize = accumulatorSizeArg;
    windowOption = windowOptionArg;
    beaconA = beaconAArg * 1000.0;
    beaconB = beaconBArg * 1000.0;
    beaconC = beaconCArg * 1000.0;

    // Initialize data processing window
    dataWindow = DataWindow::createWindow(dataSize, windowOption);
    // Initialize vector for frequency domain X-axis plot in FFT
    frequencyDomain = std::vector<double>(dataSize / 2, 0);
    // Initialize time domain and frequency domain X-axis
    for (int i = 0; i < dataSize; i++) {
        if (i < dataSize / 2) frequencyDomain[i] = (double)sampleFrequency * i / dataSize;
    }

    // Initialize frequency bins to look for peaks
    frequencyBins.clear();
    frequencyBins.push_back(FrequencyIndex{(int)floor(dataSize * (beaconA - 125.0) / sampleFrequency),
                                           (int)ceil(dataSize * (beaconA + 125.0) / sampleFrequency)});
    frequencyBins.push_back(FrequencyIndex{(int)floor(dataSize * (beaconB - 125.0) / sampleFrequency),
                                           (int)ceil(dataSize * (beaconB + 125.0) / sampleFrequency)});
    frequencyBins.push_back(FrequencyIndex{(int)floor(dataSize * (beaconC - 125.0) / sampleFrequency),
                                           (int)ceil(dataSize * (beaconC + 125.0) / sampleFrequency)});

    // Initialize FFT accumulator with zeroes
    fftAccumulator.clear();
    for (int i = 0; i < accumulatorSize; i++) fftAccumulator.push_back(std::vector<double>(dataSize, 0));

    timeDomain = std::vector<double>(peakSerieSize, 0);
    distanceDomain = std::vector<double>(peakSerieSize, 0);

    dataAcquiring->quit();
    while (!dataAcquiring->isFinished())
        ;
    dataAcquisition = new USBADC(dataSize, sampleFrequency);
    dataAcquisition->moveToThread(dataAcquiring);

    connect(dataAcquiring, &QThread::finished, dataAcquisition, &QObject::deleteLater);
    connect(dataAcquiring, &QThread::started, dataAcquisition, &DataReader::startStream);
    connect(dataAcquisition, &DataReader::dataReady, this, &DataProcessor::processData, Qt::QueuedConnection);
    dataAcquiring->start();
}

// Function to initialize the vector members
void DataProcessor::initialize() {
    // Initialize data processing window
    dataWindow = DataWindow::createWindow(dataSize, windowOption);
    // Initialize vector for frequency domain X-axis plot in FFT
    frequencyDomain = std::vector<double>(dataSize / 2, 0);
    // Initialize time domain and frequency domain X-axis
    for (int i = 0; i < dataSize; i++) {
        if (i < dataSize / 2) frequencyDomain[i] = (double)sampleFrequency * i / dataSize;
    }

    // Initialize frequency bins to look for peaks
    frequencyBins.push_back(FrequencyIndex{(int)floor(dataSize * (beaconA - 125.0) / sampleFrequency),
                                           (int)ceil(dataSize * (beaconA + 125.0) / sampleFrequency)});
    frequencyBins.push_back(FrequencyIndex{(int)floor(dataSize * (beaconB - 125.0) / sampleFrequency),
                                           (int)ceil(dataSize * (beaconB + 125.0) / sampleFrequency)});
    frequencyBins.push_back(FrequencyIndex{(int)floor(dataSize * (beaconC - 125.0) / sampleFrequency),
                                           (int)ceil(dataSize * (beaconC + 125.0) / sampleFrequency)});

    // Initialize FFT accumulator with zeroes
    for (int i = 0; i < accumulatorSize; i++) fftAccumulator.push_back(std::vector<double>(dataSize, 0));

    timeDomain = std::vector<double>(peakSerieSize, 0);
    distanceDomain = std::vector<double>(peakSerieSize, 0);

    beepPlaying = new QThread();
    beepPlaying->setObjectName("playing thread");
    beepWav = new QSound("qrc:/censor-beep-1.wav");
    beepWav->moveToThread(beepPlaying);
    beepTimer = new QTimer;
    beepTimer->moveToThread(beepPlaying);
    connect(beepPlaying, &QThread::finished, beepWav, &QObject::deleteLater);
    connect(beepPlaying, &QThread::finished, beepTimer, &QObject::deleteLater);
    connect(this, &DataProcessor::beepStart, beepTimer, static_cast<void (QTimer::*)(int)>(&QTimer::start));
    connect(this, &DataProcessor::beepStop, beepTimer, &QTimer::stop);
    connect(beepTimer, &QTimer::timeout, beepWav, static_cast<void (QSound::*)()>(&QSound::play));
    beepPlaying->start();

    dataAcquiring = new QThread();
    dataAcquiring->setObjectName("acquiring thread");
    dataAcquisition = new USBADC(dataSize, sampleFrequency);
    dataAcquisition->moveToThread(dataAcquiring);

    connect(dataAcquiring, &QThread::finished, dataAcquisition, &QObject::deleteLater);
    connect(dataAcquiring, &QThread::started, dataAcquisition, &DataReader::startStream);
    connect(dataAcquisition, &DataReader::dataReady, this, &DataProcessor::processData, Qt::QueuedConnection);
    dataAcquiring->start();

    stateInstance = StateMachine::getInstance();

    gpsStatus = new QThread();
    gpsStatus->setObjectName("gps status thread");
    gpsTimer = new QTimer;
    gpsTimer->moveToThread(gpsStatus);
    connect(gpsStatus, &QThread::finished, gpsTimer, &QObject::deleteLater);
    connect(gpsTimer, &QTimer::timeout, this, &DataProcessor::reconnectGPS);
    connect(this, &DataProcessor::gpsStatusStart, gpsTimer, static_cast<void (QTimer::*)(int)>(&QTimer::start));
    gpsStatus->start();

    // Initialize GPS instance
    gpsAcquiring = new QThread();
    gpsAcquiring->setObjectName("gps thread");
    try {
        gpsType = 1;
        gpsAcquisition = new EMLIDGPS();
    } catch (...) {
        gpsType = 0;
        gpsAcquisition = new FakeGPS();
    }
    gpsAcquisition->moveToThread(gpsAcquiring);
    // Connect this object with GPS instance to receive new position data. DirectConnection since it is high priority
    connect(gpsAcquiring, &QThread::started, gpsAcquisition, &GPSReader::run);
    connect(gpsAcquiring, &QThread::finished, gpsAcquisition, &QObject::deleteLater);
    connect(gpsAcquisition, &GPSReader::dataReady, this, &DataProcessor::processGPS, Qt::QueuedConnection);
    connect(this, &DataProcessor::gpsQuit, gpsAcquisition, &GPSReader::quit, Qt::DirectConnection);
    // Start GPS thread
    gpsAcquiring->start();

    if (gpsType > 0) emit gpsStatusStart(5000);
}

// Qt Slot used to select peak timeserie to display
void DataProcessor::setPeakToDisplay(int disp) {
    peakToDisplay = disp;
}

// Qt Slot used to select peak timeserie to display
void DataProcessor::setViewAxis(int axis) {
    timeDistance = axis;
}

// Qt Slot used to receive the data from GPSReader
void DataProcessor::processGPS(
    double const &latitude,
    double const &longitude,
    double const &height,
    std::string const &name,
    unsigned char const &type,
    unsigned char const &status,
    unsigned char const &hor,
    unsigned char const &ver) {
    gpsLatitude = latitude;
    gpsLongitude = longitude;
    gpsHeight = height;

    emit updateGPSInfo(latitude, longitude, height, name, type, status, hor, ver);

    if (gpsType > 0) emit gpsStatusStart(5000);

    if (!startingAxisPosition) {
        startingAxisPosition = true;
        // Initialize peak timeserie low value
        peakTimeserie.push_back(std::vector<double>(peakSerieSize, 20.0 * log10(peaksData[0].power)));
        peakTimeserie.push_back(std::vector<double>(peakSerieSize, 20.0 * log10(peaksData[1].power)));
        peakTimeserie.push_back(std::vector<double>(peakSerieSize, 20.0 * log10(peaksData[2].power)));
        currentPositionLatitude = gpsLatitude;
        currentPositionLongitude = gpsLongitude;
        currentPositionHeight = gpsHeight;
        currentTime = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
    }

    // Get timestamp in milliseconds from system
    unsigned long long int timeNow = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();

    if (stateInstance->getState() == PREBLAST || stateInstance->getState() == POSTBLAST) {
        double currentPower = 20.0 * log10(peaksData[peakToDisplay].power);
        signed int nextBeepLevel = 0;
        if (currentPower < -100.0)
            nextBeepLevel = -120;
        else if (-100.0 <= currentPower && currentPower < -93.33)
            nextBeepLevel = -100;
        else if (-93.33 <= currentPower && currentPower < -86.67)
            nextBeepLevel = -93;
        else if (-86.67 <= currentPower && currentPower < -80.00)
            nextBeepLevel = -86;
        else if (-80.00 <= currentPower && currentPower < -73.33)
            nextBeepLevel = -80;
        else if (-73.33 <= currentPower && currentPower < -66.67)
            nextBeepLevel = -73;
        else if (-66.67 <= currentPower && currentPower < -60.00)
            nextBeepLevel = -66;
        else if (-60.00 <= currentPower && currentPower < -53.33)
            nextBeepLevel = -60;
        else if (-53.33 <= currentPower && currentPower < -46.67)
            nextBeepLevel = -53;
        else if (-46.67 <= currentPower && currentPower < -40.00)
            nextBeepLevel = -46;
        else if (-40.0 < currentPower)
            nextBeepLevel = -40;

        if (nextBeepLevel != currentBeepLevel) {
            currentBeepLevel = nextBeepLevel;
            switch (currentBeepLevel) {
                case -120:
                    emit beepStop();
                    break;
                case -100:
                    emit beepStart(5000);
                    break;
                case -93:
                    emit beepStart(1833);
                    break;
                case -86:
                    emit beepStart(1666);
                    break;
                case -80:
                    emit beepStart(1500);
                    break;
                case -73:
                    emit beepStart(1333);
                    break;
                case -66:
                    emit beepStart(1166);
                    break;
                case -60:
                    emit beepStart(1000);
                    break;
                case -53:
                    emit beepStart(833);
                    break;
                case -46:
                    emit beepStart(666);
                    break;
                case -40:
                    emit beepStart(500);
                    break;
            }
        }
    } else if (stateInstance->getState() == IDLE) {
        if (currentBeepLevel != -120) {
            currentBeepLevel = -120;
            emit beepStop();
        }
    }

    if (stateInstance->getState() == POSTBLAST) {
        // Save data in an struct
        DataLogger::TimeData timestamp = {timeNow, gpsLatitude, gpsLongitude, gpsHeight};
        // Log timestamp data
        emit logTimestamp(timestamp);
        // Log spectrum in logarithm scale
        DataLogger::SpectrumData spectrum = {averageFFT[1]};
        if (logSpectrumOption) emit logSpectrum(spectrum);
        // Log each peak data in logarithm scale
        for (unsigned char i = 0; i < 3; i++) {
            DataLogger::PeaksData peak = {i, peaksData[i].frequency, 20.0 * log10(peaksData[i].power)};
            emit logPeaks(peak);
        }
    }

    timeDomain[peakPointer] = (double)sampleCount++;
    double prevData = 0.0;
    if (peakPointer == 0)
        prevData = distanceDomain[peakSerieSize - 1];
    else
        prevData = distanceDomain[peakPointer - 1];
    distanceDomain[peakPointer] = measureDistance(gpsLatitude, gpsLongitude, currentPositionLatitude, currentPositionLongitude) + prevData;
    currentPositionLatitude = gpsLatitude;
    currentPositionLongitude = gpsLongitude;
    currentPositionHeight = gpsHeight;
    // Update values of peak timeserie
    peakTimeserie[0][peakPointer] = 20.0 * log10(peaksData[0].power);
    peakTimeserie[1][peakPointer] = 20.0 * log10(peaksData[1].power);
    peakTimeserie[2][peakPointer] = 20.0 * log10(peaksData[2].power);
    peakPointer = (++peakPointer) % peakSerieSize;

    // Cast data from std::vector to QVector. Necessary to plot data on QCustomPlot
    QVector<double> Qoutx;
    if (timeDistance == 0)
        Qoutx = QVector<double>::fromStdVector(timeDomain);
    else if (timeDistance == 1)
        Qoutx = QVector<double>::fromStdVector(distanceDomain);
    QVector<double> Qouty = QVector<double>::fromStdVector(peakTimeserie[peakToDisplay]);
    // Emit signal to MainWindow to update time data
    emit dataReady(Qoutx, Qouty);
}

void DataProcessor::saveBeacon(double distance, double id, int beaconType) {
    unsigned long long int timeNow = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
    // Save data in an struct
    DataLogger::TimeData timestamp = {timeNow, gpsLatitude, gpsLongitude, gpsHeight};
    // Log timestamp data
    emit logTimestamp(timestamp);
    if (stateInstance->getState() == PREBLAST) {
        DataLogger::BeaconData beacon = {0, 0, beaconType, distance, peaksData[beaconType].frequency, peaksData[beaconType].power};
        emit logBeacon(beacon);
    } else if (stateInstance->getState() == POSTBLAST) {
        if (distance == -1) {
            DataLogger::BeaconData beacon = {0, 1, peakToDisplay, distance, id, id};
            emit logBeacon(beacon);
        } else {
            DataLogger::BeaconData beacon = {0, 1, peakToDisplay, distance, peaksData[peakToDisplay].frequency, peaksData[peakToDisplay].power};
            emit logBeacon(beacon);
        }
    }
}

void DataProcessor::reconnectGPS() {
    emit gpsDisconnected();
    emit gpsQuit();
    gpsAcquiring->quit();
    gpsAcquiring->wait();

    // Initialize GPS instance
    gpsAcquiring = new QThread();
    gpsAcquiring->setObjectName("gps thread");
    switch (gpsType) {
        case 1:
            try {
                gpsAcquisition = new EMLIDGPS();
            } catch (...) {
                std::cout << "Not connected GPS" << std::endl;
                emit gpsStatusStart(2000);
                return;
            }
            break;
        default:
            break;
    }
    gpsAcquisition->moveToThread(gpsAcquiring);
    // Connect this object with GPS instance to receive new position data. DirectConnection since it is high priority
    connect(gpsAcquiring, &QThread::started, gpsAcquisition, &GPSReader::run);
    connect(gpsAcquiring, &QThread::finished, gpsAcquisition, &QObject::deleteLater);
    connect(gpsAcquisition, &GPSReader::dataReady, this, &DataProcessor::processGPS, Qt::QueuedConnection);
    connect(this, &DataProcessor::gpsQuit, gpsAcquisition, &GPSReader::quit, Qt::DirectConnection);
    // Start GPS thread
    gpsAcquiring->start();

    emit gpsReconnected();

    if (gpsType > 0) emit gpsStatusStart(5000);
}