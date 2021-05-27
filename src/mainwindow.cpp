#include "mainwindow.h"

#include <fftw3.h>

#include <QObject>
#include <QPushButton>
#include <QThread>
#include <QVector>
#include <QtCore>
#include <cmath>
#include <iterator>
#include <random>

#include "dataprocessor.h"
#include "qcustomplot.h"
#include "ui_mainwindow.h"

int N_size = 4096;
double sampleFrequency = 44100.0;

void MainWindow::updateData(QVector<double> const &xSeries, QVector<double> const &ySeries) {
    ui->leftPlot->graph(0)->setData(xSeries, ySeries);
}

void MainWindow::updateFFT(QVector<double> const &xSeries, QVector<double> const &ySeries) {
    ui->rightPlot->graph(0)->setData(xSeries, ySeries);
}

void MainWindow::updateOnePeak(double freq, double power) {
    ui->peakOneFreqValue->setText(QString::number(freq));
    ui->peakOnePowerValue->setText(QString::number(power));

    QVector<double> peakOneLineX = {freq, freq};
    QVector<double> peakOneLineY = {-140, 4};
    ui->rightPlot->graph(1)->setData(peakOneLineX, peakOneLineY);
}

void MainWindow::updateTwoPeak(double freq, double power) {
    ui->peakTwoFreqValue->setText(QString::number(freq));
    ui->peakTwoPowerValue->setText(QString::number(power));

    QVector<double> peakOneLineX = {freq, freq};
    QVector<double> peakOneLineY = {-140, 4};
    ui->rightPlot->graph(2)->setData(peakOneLineX, peakOneLineY);
}

void MainWindow::updateThreePeak(double freq, double power) {
    ui->peakThreeFreqValue->setText(QString::number(freq));
    ui->peakThreePowerValue->setText(QString::number(power));

    QVector<double> peakOneLineX = {freq, freq};
    QVector<double> peakOneLineY = {-140, 4};
    ui->rightPlot->graph(3)->setData(peakOneLineX, peakOneLineY);
}

void MainWindow::updatePlots() {
    ui->rightPlot->replot();
    ui->leftPlot->replot();
}

void MainWindow::startThreads() {
    connect(this, &MainWindow::peripheralsReady, this, &MainWindow::updateThreePeak, Qt::QueuedConnection);
    StateMachine::getInstance()->startingPeripherals();
    ui->statusLabel->setText(QCoreApplication::translate("MainWindow", "Status: Inicializando periféricos", nullptr));

    dataLogging.setObjectName("logging thread");
    dataAcquiring.setObjectName("acquiring thread");
    dataProcessing.setObjectName("processor thread");

    dataLogger = DataLogger::getInstance();
    dataProcessor = new DataProcessor(N_size, sampleFrequency);
    dataAcquisition = new USBADC(N_size, sampleFrequency);

    dataLogger->moveToThread(&dataLogging);
    dataProcessor->moveToThread(&dataProcessing);
    dataAcquisition->moveToThread(&dataAcquiring);

    connect(&dataProcessing, &QThread::finished, dataProcessor, &QObject::deleteLater);
    connect(&dataAcquiring, &QThread::finished, dataAcquisition, &QObject::deleteLater);
    connect(&dataLogging, &QThread::finished, dataLogger, &QObject::deleteLater);
    //TODO Possible Queue infinitely increment
    connect(dataAcquisition, &DataReader::dataReady, dataProcessor, &DataProcessor::processData, Qt::QueuedConnection);
    connect(dataProcessor, &DataProcessor::dataReady, this, &MainWindow::updateData, Qt::QueuedConnection);
    connect(dataProcessor, &DataProcessor::fftReady, this, &MainWindow::updateFFT, Qt::QueuedConnection);
    connect(dataProcessor, &DataProcessor::plotData, this, &MainWindow::updatePlots, Qt::QueuedConnection);
    connect(dataProcessor, &DataProcessor::peakOneReady, this, &MainWindow::updateOnePeak, Qt::QueuedConnection);
    connect(dataProcessor, &DataProcessor::peakTwoReady, this, &MainWindow::updateTwoPeak, Qt::QueuedConnection);
    connect(dataProcessor, &DataProcessor::peakThreeReady, this, &MainWindow::updateThreePeak, Qt::QueuedConnection);

    connect(dataProcessor, &DataProcessor::logConfiguration, dataLogger, &DataLogger::insertConfiguration, Qt::QueuedConnection);
    connect(dataProcessor, &DataProcessor::logBeacon, dataLogger, &DataLogger::insertBeaconData, Qt::QueuedConnection);
    connect(dataProcessor, &DataProcessor::logTimestamp, dataLogger, &DataLogger::insertTimeData, Qt::QueuedConnection);
    connect(dataProcessor, &DataProcessor::logPeaks, dataLogger, &DataLogger::insertPeaksData, Qt::QueuedConnection);
    connect(dataProcessor, &DataProcessor::logSpectrum, dataLogger, &DataLogger::insertSpectrumData, Qt::QueuedConnection);

    connect(this, &MainWindow::logConfiguration, dataLogger, &DataLogger::insertConfiguration, Qt::QueuedConnection);
    connect(this, &MainWindow::logBeacon, dataLogger, &DataLogger::insertBeaconData, Qt::QueuedConnection);
    connect(this, &MainWindow::logTimestamp, dataLogger, &DataLogger::insertTimeData, Qt::QueuedConnection);
    connect(this, &MainWindow::logPeaks, dataLogger, &DataLogger::insertPeaksData, Qt::QueuedConnection);
    connect(this, &MainWindow::logSpectrum, dataLogger, &DataLogger::insertSpectrumData, Qt::QueuedConnection);

    connect(this, &MainWindow::setPeakTimeserie, dataProcessor, &DataProcessor::setPeakToDisplay, Qt::QueuedConnection);

    StateMachine::getInstance()->peripheralsReady();
    ui->statusLabel->setText(QCoreApplication::translate("MainWindow", "Status: Periféricos listos", nullptr));
    emit peripheralsReady(1.1, 1.2);
}

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    startPeripherals = new std::thread(&MainWindow::startThreads, this);

    connectButtons();

    dataAcquiring.start();
    dataProcessing.start();
    dataLogging.start();
}

void MainWindow::openBeaconInput() {
    if (!ui->inputBeaconWidget->dialogWidget->isVisible()) {
        ui->inputBeaconWidget->dialogWidget->setVisible(true);
        ui->inputBeaconWidget->inputBeaconWidget->setVisible(true);
        ui->inputBeaconWidget->keyboardWidget->setVisible(true);
        ui->inputBeaconWidget->inputBeaconWidget->activateWindow();
        ui->inputBeaconWidget->inputBeaconWidget->setFocus(Qt::ActiveWindowFocusReason);
    }
}

void MainWindow::beaconAccept() {
    if (ui->inputBeaconWidget->dialogWidget->isVisible()) {
        ui->inputBeaconWidget->dialogWidget->setVisible(false);
        ui->inputBeaconWidget->inputBeaconWidget->setVisible(false);
        ui->inputBeaconWidget->keyboardWidget->setVisible(false);
    }
}

void MainWindow::beaconCancel() {
    if (ui->inputBeaconWidget->dialogWidget->isVisible()) {
        ui->inputBeaconWidget->dialogWidget->setVisible(false);
        ui->inputBeaconWidget->inputBeaconWidget->setVisible(false);
        ui->inputBeaconWidget->keyboardWidget->setVisible(false);
    }
}

void MainWindow::dispFrequencyOne() {
    emit setPeakTimeserie(0);
    ui->selectOneFreq->setStyleSheet("background-color: rgba(46, 204, 113, 0.4); border: none;");
    ui->selectTwoFreq->setStyleSheet("background-color: rgba(204, 46, 113, 0.4); border: none;");
    ui->selectThreeFreq->setStyleSheet("background-color: rgba(204, 46, 113, 0.4); border: none;");
}

void MainWindow::dispFrequencyTwo() {
    emit setPeakTimeserie(1);
    ui->selectOneFreq->setStyleSheet("background-color: rgba(204, 46, 113, 0.4); border: none;");
    ui->selectTwoFreq->setStyleSheet("background-color: rgba(46, 204, 113, 0.4); border: none;");
    ui->selectThreeFreq->setStyleSheet("background-color: rgba(204, 46, 113, 0.4); border: none;");
}

void MainWindow::dispFrequencyThree() {
    emit setPeakTimeserie(2);
    ui->selectOneFreq->setStyleSheet("background-color: rgba(204, 46, 113, 0.4); border: none;");
    ui->selectTwoFreq->setStyleSheet("background-color: rgba(204, 46, 113, 0.4); border: none;");
    ui->selectThreeFreq->setStyleSheet("background-color: rgba(46, 204, 113, 0.4); border: none;");
}

void MainWindow::startNewLog() {
    DataLogger::Configuration conf = {N_size, sampleFrequency};
    emit logConfiguration(conf);
    StateMachine::getInstance()->newLog();
    ui->statusLabel->setText(QCoreApplication::translate("MainWindow", "Status: Nuevo registro configurado", nullptr));
}

void MainWindow::startNewPreblastLog() {
    StateMachine::getInstance()->preblastLog();
    ui->statusLabel->setText(QCoreApplication::translate("MainWindow", "Status: Nuevo registro pre-estallido empezado", nullptr));
}

void MainWindow::startNewPostblastLog() {
    StateMachine::getInstance()->postblastLog();
    ui->statusLabel->setText(QCoreApplication::translate("MainWindow", "Status: Nuevo registro post-estallido empezado", nullptr));
}

void MainWindow::connectButtons() {
    // Close and Shutdown button
    connect(ui->closeShutdown, &QPushButton::released, this, &QMainWindow::close);
    connect(ui->selectBeacon, &QPushButton::released, this, &MainWindow::openBeaconInput);
    connect(ui->selectOneFreq, &QPushButton::released, this, &MainWindow::dispFrequencyOne);
    connect(ui->selectTwoFreq, &QPushButton::released, this, &MainWindow::dispFrequencyTwo);
    connect(ui->selectThreeFreq, &QPushButton::released, this, &MainWindow::dispFrequencyThree);

    connect(ui->startLog, &QPushButton::released, this, &MainWindow::startNewLog);
    connect(ui->preblastLog, &QPushButton::released, this, &MainWindow::startNewPreblastLog);
    connect(ui->postblastLog, &QPushButton::released, this, &MainWindow::startNewPostblastLog);

    connect(ui->inputBeaconWidget->inputBeaconAccept, &QPushButton::released, this, &MainWindow::beaconAccept);
    connect(ui->inputBeaconWidget->inputBeaconCancel, &QPushButton::released, this, &MainWindow::beaconCancel);
}

MainWindow::~MainWindow() {
    dataAcquiring.quit();
    dataProcessing.quit();
    dataLogging.quit();
    dataAcquiring.wait();
    dataProcessing.wait();
    dataLogging.wait();
    delete ui;
}

void MainWindow::setupGUI() {
    QFont pfont("Newyork", 8);
    pfont.setStyleHint(QFont::SansSerif);
    pfont.setPointSize(8);

    ui->centralWidget->setCursor(Qt::BlankCursor);

    ui->rightPlot->setBackground(QBrush(QColor(0xDD, 0xDD, 0xDD), Qt::SolidPattern));
    ui->rightPlot->addGraph();
    ui->rightPlot->addGraph();
    ui->rightPlot->addGraph();
    ui->rightPlot->addGraph();
    ui->rightPlot->xAxis->setLabel("Frequency");
    ui->rightPlot->yAxis->setLabel("Power");
    // ui->rightPlot->xAxis->setTickLabelFont(pfont);
    // ui->rightPlot->yAxis->setTickLabelFont(pfont);
    // ui->rightPlot->xAxis->setLabelFont(pfont);
    // ui->rightPlot->yAxis->setLabelFont(pfont);
    ui->rightPlot->xAxis->setRange(0, sampleFrequency / 2);
    ui->rightPlot->yAxis->setRange(-140, 4);
    ui->rightPlot->graph(0)->setPen(QPen(Qt::blue));
    ui->rightPlot->graph(1)->setPen(QPen(Qt::black, 1.0, Qt::DashLine));
    ui->rightPlot->graph(2)->setPen(QPen(Qt::black, 1.0, Qt::DashLine));
    ui->rightPlot->graph(3)->setPen(QPen(Qt::black, 1.0, Qt::DashLine));

    ui->textLabel = new QCPItemText(ui->rightPlot);
    ui->textLabel->setPositionAlignment(Qt::AlignTop | Qt::AlignHCenter);
    ui->textLabel->setPadding(QMargins(5, 5, 5, 5));
    ui->textLabel->position->setType(QCPItemPosition::ptAxisRectRatio);
    ui->textLabel->position->setCoords(0.85, 0);
    ui->textLabel->setFont(QFont(font().family(), 12));
    ui->textLabel->setPen(QPen(Qt::black));
    ui->textLabel->setBrush(QBrush(Qt::white));
    ui->textLabel->setText("Window Hanning \nN = 4096\nFs = 44100.0");

    ui->leftPlot->setBackground(QBrush(QColor(0xDD, 0xDD, 0xDD)));
    ui->leftPlot->addGraph();
    ui->leftPlot->addGraph();
    ui->leftPlot->xAxis->setLabel("Time");
    ui->leftPlot->yAxis->setLabel("Amplitude");
    ui->leftPlot->xAxis->setRange(0, (double)(N_size / 2.0 / sampleFrequency));
    ui->leftPlot->yAxis->setRange(-140, 4);
    ui->leftPlot->graph(0)->setPen(QPen(Qt::blue));

    ui->selectOneFreq->setStyleSheet("background-color: rgba(46, 204, 113, 0.4); border: none;");
    ui->selectTwoFreq->setStyleSheet("background-color: rgba(204, 46, 113, 0.4); border: none;");
    ui->selectThreeFreq->setStyleSheet("background-color: rgba(204, 46, 113, 0.4); border: none;");
}
