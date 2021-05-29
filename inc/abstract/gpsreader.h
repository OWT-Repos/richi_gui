#pragma once

#include <QObject>
#include <random>

// Abstract class for gps acquisition
class GPSReader : public QObject {
    Q_OBJECT
   public:
    // Device descriptor
    int fd;
    // Vector to store time data
    double latValue;
    // Vector to store converted data
    double lngValue;
    // Vector to store time data
    double gpsTime;
    // Vector to store converted data
    double gpsSV;
    // Loop boolean control
    bool running = true;
    // Class constructor
    explicit GPSReader(QObject *parent = 0) : QObject(parent){};
    // Class destructor
    virtual ~GPSReader(){};
   signals:
    // Qt Signal used to transfer data to DataProcessor thread
    virtual void dataReady(double const &latitude, double const &longitude);
   public slots:
    // Qt Slot used to
    virtual void run() = 0;
    void quit() {
        running = false;
    };
};