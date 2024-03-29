#pragma once

#include <QQmlApplicationEngine>
#include <QQuickWidget>
#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

#include "dialogs.h"
#include "dialogs/beacontable.h"
#include "mainwindow.h"
#include "qcustomplot.h"
#include "stylesheetdefines.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow {
   public:
    bool simpleView = false;
    unsigned int timeDistance = 0;

    QTranslator *translator_es;
    QTranslator *translator_en;

    QVector<double> ticks;
    QVector<QString> labels;

    QCPItemText *textLabel;
    QCPAxisRect *wideAxisOne;
    QCPAxisRect *wideAxisTwo;
    QCPAxisRect *wideAxisThree;
    QCPGraph *mainGraphOne;
    QCPGraph *mainGraphTwo;
    QCPGraph *mainGraphThree;
    QCustomPlot *barsPlot;
    QCPBars *peaksBars;

    QQuickWidget *keyboardInputWidget;

    BeaconInputDialog *inputBeaconWidget;
    BeaconFoundDialog *foundBeaconWidget;
    WarningDialog *warningWidget;
    GPSStatus *gpsWidget;
    BeaconTable *beaconTable;
    NameInputDialog *nameInputDialog;
    AdjustSpectrum *adjustSpectrum;

    QWidget *centralWidget;
    QFrame *statusLine;
    QLabel *statusLabel;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *plotsLayout;
    QCustomPlot *rightPlot;
    QCustomPlot *leftPlot;
    QHBoxLayout *panelLayout;
    QVBoxLayout *dataLayout;
    QHBoxLayout *miscLayout;
    QHBoxLayout *peaksViewLayout;
    QVBoxLayout *peaksLayout;
    QLabel *peaksTitle;
    QGridLayout *peaksData;
    QHBoxLayout *peakOneFreq;
    QLabel *peakOneFreqValue;
    QLabel *peakOneFreqUnit;
    QHBoxLayout *peakTwoFreq;
    QLabel *peakTwoFreqValue;
    QLabel *peakTwoFreqUnit;
    QHBoxLayout *peakThreeFreq;
    QLabel *peakThreeFreqValue;
    QLabel *peakThreeFreqUnit;
    QHBoxLayout *peakOnePower;
    QLabel *peakOnePowerValue;
    QLabel *peakOnePowerUnit;
    QHBoxLayout *peakTwoPower;
    QLabel *peakTwoPowerValue;
    QLabel *peakTwoPowerUnit;
    QHBoxLayout *peakThreePower;
    QLabel *peakThreePowerValue;
    QLabel *peakThreePowerUnit;
    QVBoxLayout *beaconLayout;
    QPushButton *selectTimeAxis;
    QPushButton *selectBeacon;

    QPushButton *beaconFound;
    QVBoxLayout *logLayout;
    QHBoxLayout *freqSelectLayout;
    QHBoxLayout *axisSelectLayout;
    QHBoxLayout *preblastLayout;
    QHBoxLayout *postblastLayout;
    QHBoxLayout *standbyLayout;
    QPushButton *selectDistanceAxis;
    QPushButton *preblastLog;
    QPushButton *postblastLog;
    QPushButton *standbyLog;
    QPushButton *tableLog;
    QHBoxLayout *saveLayout;
    QPushButton *switchLanguage;
    QPushButton *adjustButton;
    QPushButton *startLog;
    QPushButton *saveLog;
    QPushButton *closeShutdown;
    QVBoxLayout *selectLayout;
    QPushButton *gpsStatus;
    QPushButton *selectOneFreq;
    QPushButton *selectTwoFreq;
    QPushButton *selectThreeFreq;

    void setupUi(MainWindow *MainWindow) {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1280, 800);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        MainWindow->setMinimumSize(QSize(1280, 800));
        MainWindow->setStyleSheet(
            "QPushButton {"
            "color: #111;"
            "border-radius: 20px;"
            "border-style: outset;"
            "border-color: black;"
            "background: #888;"
            "font: 20px 'Ubuntu';"
            "font-weight: bold;"
            "}"
            "QPushButton:hover {"
            "background: qradialgradient("
            "cx: 0.3, cy: -0.4, fx: 0.3, fy: 0.4,"
            "radius: 1.35, stop: 0 #fff, stop: 1 #bbb"
            ");"
            "}"
            "QPushButton:pressed {"
            "border-style: inset;"
            "background: qradialgradient("
            "cx: 0.4, cy: -0.1, fx: 0.4, fy: 0.1,"
            "radius: 1.35, stop: 0 #fff, stop: 1 #ddd"
            ");"
            "}"
            "QPushButton#selectOneFreq {"
            "border-top-right-radius: 0px;"
            "border-bottom-right-radius: 0px;"
            "border-right: 1px solid #000;"
            "}"
            "QPushButton#selectTwoFreq {"
            "border-top-left-radius: 0px;"
            "border-bottom-left-radius: 0px;"
            "border-left: 1px solid #000;"
            "border-top-right-radius: 0px;"
            "border-bottom-right-radius: 0px;"
            "border-right: 1px solid #000;"
            "}"
            "QPushButton#selectThreeFreq {"
            "border-top-left-radius: 0px;"
            "border-bottom-left-radius: 0px;"
            "border-left: 1px solid #000;"
            "}"
            "QPushButton#selectTimeAxis {"
            "border-top-right-radius: 0px;"
            "border-bottom-right-radius: 0px;"
            "border-right: 1px solid #000;"
            "}"
            "QPushButton#selectBeacon {"
            "border-top-left-radius: 0px;"
            "border-bottom-left-radius: 0px;"
            "border-left: 1px solid #000;"
            "}"
            "QPushButton#beaconFound {"
            "border-top-left-radius: 0px;"
            "border-bottom-left-radius: 0px;"
            "border-left: 1px solid #000;"
            "}"
            "QPushButton#selectDistanceAxis {"
            "border-top-left-radius: 0px;"
            "border-bottom-left-radius: 0px;"
            "border-left: 1px solid #000;"
            "}"
            "QPushButton#preblastLog {"
            "border-top-right-radius: 0px;"
            "border-bottom-right-radius: 0px;"
            "border-right: 1px solid #000;"
            "}"
            "QPushButton#postblastLog {"
            "border-top-right-radius: 0px;"
            "border-bottom-right-radius: 0px;"
            "border-right: 1px solid #000;"
            "}"
            "QPushButton#gpsStatus {"
            "border-bottom-left-radius: 0px;"
            "border-bottom-right-radius: 0px;"
            "border-bottom: 1px solid #000;"
            "}"
            "QPushButton#standbyLog {"
            "border-top-right-radius: 0px;"
            "border-bottom-right-radius: 0px;"
            "border-top-left-radius: 0px;"
            "border-bottom-left-radius: 0px;"
            "border-bottom: 1px solid #000;"
            "border-top: 1px solid #000;"
            "}"
            "QPushButton#tableLog {"
            "border-top-left-radius: 0px;"
            "border-top-right-radius: 0px;"
            "border-top: 1px solid #000;"
            "}"
            "QPushButton:focus {}");

        centralWidget = new QWidget(MainWindow);

        inputBeaconWidget = new BeaconInputDialog(MainWindow);
        foundBeaconWidget = new BeaconFoundDialog(MainWindow);
        warningWidget = new WarningDialog(MainWindow);
        gpsWidget = new GPSStatus(MainWindow);
        beaconTable = new BeaconTable(MainWindow);
        nameInputDialog = new NameInputDialog(MainWindow);
        adjustSpectrum = new AdjustSpectrum(MainWindow);

        keyboardInputWidget = new QQuickWidget(MainWindow);
        keyboardInputWidget->setObjectName("keyboardInputWidget");
        keyboardInputWidget->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        keyboardInputWidget->move(310, 425);
        keyboardInputWidget->setResizeMode(QQuickWidget::SizeRootObjectToView);
        keyboardInputWidget->setAttribute(Qt::WA_AlwaysStackOnTop);
        keyboardInputWidget->setClearColor(Qt::transparent);
        keyboardInputWidget->setMinimumSize(660, 375);
        keyboardInputWidget->setSource(QUrl("qrc:/main.qml"));
        keyboardInputWidget->setVisible(false);

        centralWidget->setObjectName("centralWidget");
        sizePolicy.setHeightForWidth(centralWidget->sizePolicy().hasHeightForWidth());
        centralWidget->setSizePolicy(sizePolicy);
        centralWidget->setMinimumSize(QSize(1280, 800));
        centralWidget->setMaximumSize(QSize(1280, 800));
        centralWidget->setStyleSheet("#centralWidget{background: #ddd;}");
        layoutWidget = new QWidget(centralWidget);
        layoutWidget->setObjectName("layoutWidget");
        layoutWidget->setGeometry(QRect(10, 10, 1260, 780));
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setSizeConstraint(QLayout::SetDefaultConstraint);
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        plotsLayout = new QHBoxLayout();
        plotsLayout->setSpacing(10);
        plotsLayout->setObjectName("plotsLayout");
        plotsLayout->setSizeConstraint(QLayout::SetDefaultConstraint);
        plotsLayout->setContentsMargins(10, 10, 10, 10);
        rightPlot = new QCustomPlot(layoutWidget);
        rightPlot->setObjectName("rightPlot");
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(rightPlot->sizePolicy().hasHeightForWidth());
        rightPlot->setSizePolicy(sizePolicy1);
        rightPlot->setMinimumSize(QSize(0, 0));
        rightPlot->setMaximumSize(QSize(16777215, 16777215));
        rightPlot->setAutoFillBackground(false);

        plotsLayout->addWidget(rightPlot);

        leftPlot = new QCustomPlot(layoutWidget);
        leftPlot->setObjectName("leftPlot");
        leftPlot->setEnabled(true);
        sizePolicy1.setHeightForWidth(leftPlot->sizePolicy().hasHeightForWidth());
        leftPlot->setSizePolicy(sizePolicy1);
        leftPlot->setMinimumSize(QSize(0, 0));
        leftPlot->setMaximumSize(QSize(16777215, 16777215));
        leftPlot->setAutoFillBackground(false);

        plotsLayout->addWidget(leftPlot);

        plotsLayout->setStretch(0, 2);
        plotsLayout->setStretch(1, 3);

        verticalLayout->addLayout(plotsLayout);

        panelLayout = new QHBoxLayout();
        panelLayout->setObjectName("panelLayout");
        panelLayout->setSizeConstraint(QLayout::SetDefaultConstraint);
        panelLayout->setContentsMargins(10, 10, 10, 10);
        panelLayout->setSpacing(0);
        dataLayout = new QVBoxLayout();
        dataLayout->setObjectName("dataLayout");
        miscLayout = new QHBoxLayout();
        miscLayout->setObjectName("miscLayout");
        peaksLayout = new QVBoxLayout();
        peaksLayout->setSpacing(0);
        peaksLayout->setObjectName("peaksLayout");
        peaksLayout->setSizeConstraint(QLayout::SetDefaultConstraint);
        peaksLayout->setContentsMargins(10, 10, 10, 10);
        peaksTitle = new QLabel(layoutWidget);
        peaksTitle->setObjectName("peaksTitle");
        peaksTitle->setAlignment(Qt::AlignCenter);
        peaksTitle->setStyleSheet(
            "border: 1px solid #000;"
            "font: 24px 'Ubuntu';"
            "font-weight: bold;");

        peaksLayout->addWidget(peaksTitle);

        peaksViewLayout = new QHBoxLayout();
        peaksViewLayout->setObjectName("peaksViewLayout");

        barsPlot = new QCustomPlot(layoutWidget);
        barsPlot->setObjectName("barsPlot");
        sizePolicy1.setHeightForWidth(barsPlot->sizePolicy().hasHeightForWidth());
        barsPlot->setSizePolicy(sizePolicy1);
        barsPlot->setMinimumSize(QSize(0, 0));
        barsPlot->setMaximumSize(QSize(16777215, 16777215));
        barsPlot->setAutoFillBackground(false);
        barsPlot->setVisible(false);

        peaksViewLayout->addWidget(barsPlot);

        peaksData = new QGridLayout();
        peaksData->setSpacing(0);
        peaksData->setObjectName("peaksData");
        peaksData->setSizeConstraint(QLayout::SetDefaultConstraint);
        peaksData->setContentsMargins(0, 0, 0, 0);
        peakOneFreq = new QHBoxLayout();
        peakOneFreq->setSpacing(0);
        peakOneFreq->setObjectName("peakOneFreq");
        peakOneFreq->setContentsMargins(0, 0, 0, 0);
        peakOneFreqValue = new QLabel(layoutWidget);
        peakOneFreqValue->setObjectName("peakOneFreqValue");
        peakOneFreqValue->setAutoFillBackground(true);
        peakOneFreqValue->setScaledContents(false);
        peakOneFreqValue->setAlignment(Qt::AlignCenter);
        peakOneFreqValue->setStyleSheet(
            "border: 1px solid #000;"
            "font: 24px 'Ubuntu';"
            "font-weight: bold;"
            "background-color: white;");

        peakOneFreq->addWidget(peakOneFreqValue);

        peakOneFreqUnit = new QLabel(layoutWidget);
        peakOneFreqUnit->setObjectName("peakOneFreqUnit");
        peakOneFreqUnit->setScaledContents(false);
        peakOneFreqUnit->setAlignment(Qt::AlignCenter);
        peakOneFreqUnit->setStyleSheet(
            "border: 1px solid #000;"
            "font: 24px 'Ubuntu';"
            "font-weight: bold;");

        peakOneFreq->addWidget(peakOneFreqUnit);

        peakOneFreq->setStretch(0, 2);
        peakOneFreq->setStretch(1, 1);

        peaksData->addLayout(peakOneFreq, 0, 0, 1, 1);

        peakTwoFreq = new QHBoxLayout();
        peakTwoFreq->setSpacing(0);
        peakTwoFreq->setObjectName("peakTwoFreq");
        peakTwoFreq->setContentsMargins(0, 0, 0, 0);
        peakTwoFreqValue = new QLabel(layoutWidget);
        peakTwoFreqValue->setObjectName("peakTwoFreqValue");
        peakTwoFreqValue->setAutoFillBackground(true);
        peakTwoFreqValue->setScaledContents(false);
        peakTwoFreqValue->setAlignment(Qt::AlignCenter);
        peakTwoFreqValue->setStyleSheet(
            "border: 1px solid #000;"
            "font: 24px 'Ubuntu';"
            "font-weight: bold;"
            "background-color: white;");

        peakTwoFreq->addWidget(peakTwoFreqValue);

        peakTwoFreqUnit = new QLabel(layoutWidget);
        peakTwoFreqUnit->setObjectName("peakTwoFreqUnit");
        peakTwoFreqUnit->setScaledContents(false);
        peakTwoFreqUnit->setAlignment(Qt::AlignCenter);
        peakTwoFreqUnit->setStyleSheet(
            "border: 1px solid #000;"
            "font: 24px 'Ubuntu';"
            "font-weight: bold;");

        peakTwoFreq->addWidget(peakTwoFreqUnit);

        peakTwoFreq->setStretch(0, 2);
        peakTwoFreq->setStretch(1, 1);

        peaksData->addLayout(peakTwoFreq, 1, 0, 1, 1);

        peakThreeFreq = new QHBoxLayout();
        peakThreeFreq->setSpacing(0);
        peakThreeFreq->setObjectName("peakThreeFreq");
        peakThreeFreq->setContentsMargins(0, 0, 0, 0);
        peakThreeFreqValue = new QLabel(layoutWidget);
        peakThreeFreqValue->setObjectName("peakThreeFreqValue");
        peakThreeFreqValue->setAutoFillBackground(true);
        peakThreeFreqValue->setScaledContents(false);
        peakThreeFreqValue->setAlignment(Qt::AlignCenter);
        peakThreeFreqValue->setStyleSheet(
            "border: 1px solid #000;"
            "font: 24px 'Ubuntu';"
            "font-weight: bold;"
            "background-color: white;");

        peakThreeFreq->addWidget(peakThreeFreqValue);

        peakThreeFreqUnit = new QLabel(layoutWidget);
        peakThreeFreqUnit->setObjectName("peakThreeFreqUnit");
        peakThreeFreqUnit->setScaledContents(false);
        peakThreeFreqUnit->setAlignment(Qt::AlignCenter);
        peakThreeFreqUnit->setStyleSheet(
            "border: 1px solid #000;"
            "font: 24px 'Ubuntu';"
            "font-weight: bold;");

        peakThreeFreq->addWidget(peakThreeFreqUnit);

        peakThreeFreq->setStretch(0, 2);
        peakThreeFreq->setStretch(1, 1);

        peaksData->addLayout(peakThreeFreq, 2, 0, 1, 1);

        peakOnePower = new QHBoxLayout();
        peakOnePower->setSpacing(0);
        peakOnePower->setObjectName("peakOnePower");
        peakOnePower->setContentsMargins(0, 0, 0, 0);
        peakOnePowerValue = new QLabel(layoutWidget);
        peakOnePowerValue->setObjectName("peakOnePowerValue");
        peakOnePowerValue->setAutoFillBackground(true);
        peakOnePowerValue->setScaledContents(false);
        peakOnePowerValue->setAlignment(Qt::AlignCenter);
        peakOnePowerValue->setStyleSheet(
            "border: 1px solid #000;"
            "font: 24px 'Ubuntu';"
            "font-weight: bold;"
            "background-color: white");

        peakOnePower->addWidget(peakOnePowerValue);

        peakOnePowerUnit = new QLabel(layoutWidget);
        peakOnePowerUnit->setObjectName("peakOnePowerUnit");
        peakOnePowerUnit->setScaledContents(false);
        peakOnePowerUnit->setAlignment(Qt::AlignCenter);
        peakOnePowerUnit->setStyleSheet(
            "border: 1px solid #000;"
            "font: 24px 'Ubuntu';"
            "font-weight: bold;");

        peakOnePower->addWidget(peakOnePowerUnit);

        peakOnePower->setStretch(0, 2);
        peakOnePower->setStretch(1, 1);

        peaksData->addLayout(peakOnePower, 0, 1, 1, 1);

        peakTwoPower = new QHBoxLayout();
        peakTwoPower->setSpacing(0);
        peakTwoPower->setObjectName("peakTwoPower");
        peakTwoPower->setContentsMargins(0, 0, 0, 0);
        peakTwoPowerValue = new QLabel(layoutWidget);
        peakTwoPowerValue->setObjectName("peakTwoPowerValue");
        peakTwoPowerValue->setAutoFillBackground(true);
        peakTwoPowerValue->setScaledContents(false);
        peakTwoPowerValue->setAlignment(Qt::AlignCenter);
        peakTwoPowerValue->setStyleSheet(
            "border: 1px solid #000;"
            "font: 24px 'Ubuntu';"
            "font-weight: bold;"
            "background-color: white;");

        peakTwoPower->addWidget(peakTwoPowerValue);

        peakTwoPowerUnit = new QLabel(layoutWidget);
        peakTwoPowerUnit->setObjectName("peakTwoPowerUnit");
        peakTwoPowerUnit->setScaledContents(false);
        peakTwoPowerUnit->setAlignment(Qt::AlignCenter);
        peakTwoPowerUnit->setStyleSheet(
            "border: 1px solid #000;"
            "font: 24px 'Ubuntu';"
            "font-weight: bold;");

        peakTwoPower->addWidget(peakTwoPowerUnit);

        peakTwoPower->setStretch(0, 2);
        peakTwoPower->setStretch(1, 1);

        peaksData->addLayout(peakTwoPower, 1, 1, 1, 1);

        peakThreePower = new QHBoxLayout();
        peakThreePower->setSpacing(0);
        peakThreePower->setObjectName("peakThreePower");
        peakThreePower->setContentsMargins(0, 0, 0, 0);
        peakThreePowerValue = new QLabel(layoutWidget);
        peakThreePowerValue->setObjectName("peakThreePowerValue");
        peakThreePowerValue->setAutoFillBackground(true);
        peakThreePowerValue->setScaledContents(false);
        peakThreePowerValue->setAlignment(Qt::AlignCenter);
        peakThreePowerValue->setStyleSheet(
            "border: 1px solid #000;"
            "font: 24px 'Ubuntu';"
            "font-weight: bold;"
            "background-color: white;");

        peakThreePower->addWidget(peakThreePowerValue);

        peakThreePowerUnit = new QLabel(layoutWidget);
        peakThreePowerUnit->setObjectName("peakThreePowerUnit");
        peakThreePowerUnit->setScaledContents(false);
        peakThreePowerUnit->setAlignment(Qt::AlignCenter);
        peakThreePowerUnit->setStyleSheet(
            "border: 1px solid #000;"
            "font: 24px 'Ubuntu';"
            "font-weight: bold;");

        peakThreePower->addWidget(peakThreePowerUnit);

        peakThreePower->setStretch(0, 2);
        peakThreePower->setStretch(1, 1);

        peaksData->addLayout(peakThreePower, 2, 1, 1, 1);

        peaksData->setRowStretch(0, 1);
        peaksData->setRowStretch(1, 1);
        peaksData->setRowStretch(2, 1);
        peaksData->setColumnStretch(0, 1);
        peaksData->setColumnStretch(1, 1);

        peaksViewLayout->addLayout(peaksData);

        peaksViewLayout->setStretch(0, 1);
        peaksViewLayout->setStretch(1, 1);

        peaksLayout->addLayout(peaksViewLayout);

        peaksLayout->setStretch(0, 1);
        peaksLayout->setStretch(1, 4);

        miscLayout->addLayout(peaksLayout);

        beaconLayout = new QVBoxLayout();
        beaconLayout->setObjectName("beaconLayout");
        beaconLayout->setSpacing(10);

        freqSelectLayout = new QHBoxLayout();
        freqSelectLayout->setObjectName("freqSelectLayout");
        freqSelectLayout->setContentsMargins(0, 0, 0, 0);
        freqSelectLayout->setSpacing(0);

        selectOneFreq = new QPushButton(layoutWidget);
        selectOneFreq->setObjectName("selectOneFreq");
        sizePolicy1.setHeightForWidth(selectOneFreq->sizePolicy().hasHeightForWidth());
        selectOneFreq->setFocusPolicy(Qt::NoFocus);
        selectOneFreq->setSizePolicy(sizePolicy1);

        freqSelectLayout->addWidget(selectOneFreq);

        selectTwoFreq = new QPushButton(layoutWidget);
        selectTwoFreq->setObjectName("selectTwoFreq");
        sizePolicy1.setHeightForWidth(selectTwoFreq->sizePolicy().hasHeightForWidth());
        selectTwoFreq->setFocusPolicy(Qt::NoFocus);
        selectTwoFreq->setSizePolicy(sizePolicy1);

        freqSelectLayout->addWidget(selectTwoFreq);

        selectThreeFreq = new QPushButton(layoutWidget);
        selectThreeFreq->setObjectName("selectThreeFreq");
        sizePolicy1.setHeightForWidth(selectThreeFreq->sizePolicy().hasHeightForWidth());
        selectThreeFreq->setFocusPolicy(Qt::NoFocus);
        selectThreeFreq->setSizePolicy(sizePolicy1);

        freqSelectLayout->addWidget(selectThreeFreq);

        freqSelectLayout->setStretch(0, 1);
        freqSelectLayout->setStretch(1, 1);
        freqSelectLayout->setStretch(2, 1);

        beaconLayout->addLayout(freqSelectLayout);

        axisSelectLayout = new QHBoxLayout();
        axisSelectLayout->setObjectName("axisSelectLayout");
        axisSelectLayout->setContentsMargins(0, 0, 0, 0);
        axisSelectLayout->setSpacing(0);

        selectTimeAxis = new QPushButton(layoutWidget);
        selectTimeAxis->setObjectName("selectTimeAxis");
        selectTimeAxis->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        selectTimeAxis->setFocusPolicy(Qt::NoFocus);
        selectTimeAxis->setStyleSheet(GREEN_BUTTON);

        axisSelectLayout->addWidget(selectTimeAxis);

        selectDistanceAxis = new QPushButton(layoutWidget);
        selectDistanceAxis->setObjectName("selectDistanceAxis");
        selectDistanceAxis->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        selectDistanceAxis->setFocusPolicy(Qt::NoFocus);
        selectDistanceAxis->setStyleSheet(RED_BUTTON);

        axisSelectLayout->addWidget(selectDistanceAxis);

        axisSelectLayout->setStretch(0, 1);
        axisSelectLayout->setStretch(1, 1);

        beaconLayout->addLayout(axisSelectLayout);

        preblastLayout = new QHBoxLayout();
        preblastLayout->setObjectName("preblastLayout");
        preblastLayout->setContentsMargins(0, 0, 0, 0);
        preblastLayout->setSpacing(0);

        preblastLog = new QPushButton(layoutWidget);
        preblastLog->setObjectName("preblastLog");
        preblastLog->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        preblastLog->setFocusPolicy(Qt::NoFocus);
        preblastLog->setStyleSheet(RED_BUTTON);

        preblastLayout->addWidget(preblastLog);

        selectBeacon = new QPushButton(layoutWidget);
        selectBeacon->setObjectName("selectBeacon");
        selectBeacon->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        selectBeacon->setFocusPolicy(Qt::NoFocus);
        selectBeacon->setStyleSheet(DISABLED_BUTTON);
        selectBeacon->setDisabled(true);

        preblastLayout->addWidget(selectBeacon);

        preblastLayout->setStretch(0, 1);
        preblastLayout->setStretch(1, 1);

        beaconLayout->addLayout(preblastLayout);

        postblastLayout = new QHBoxLayout();
        postblastLayout->setObjectName("postblastLayout");
        postblastLayout->setSizeConstraint(QLayout::SetDefaultConstraint);
        postblastLayout->setContentsMargins(0, 0, 0, 0);
        postblastLayout->setSpacing(0);

        postblastLog = new QPushButton(layoutWidget);
        postblastLog->setObjectName("postblastLog");
        postblastLog->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        postblastLog->setFocusPolicy(Qt::NoFocus);
        postblastLog->setStyleSheet(RED_BUTTON);

        postblastLayout->addWidget(postblastLog);

        beaconFound = new QPushButton(layoutWidget);
        beaconFound->setObjectName("beaconFound");
        beaconFound->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        beaconFound->setFocusPolicy(Qt::NoFocus);
        beaconFound->setStyleSheet(DISABLED_BUTTON);
        beaconFound->setDisabled(true);

        postblastLayout->addWidget(beaconFound);

        postblastLayout->setStretch(0, 1);
        postblastLayout->setStretch(1, 1);

        beaconLayout->addLayout(postblastLayout);

        beaconLayout->setStretch(0, 1);
        beaconLayout->setStretch(1, 1);
        beaconLayout->setStretch(2, 1);
        beaconLayout->setStretch(3, 1);

        miscLayout->addLayout(beaconLayout);

        miscLayout->setStretch(0, 2);
        miscLayout->setStretch(1, 2);

        dataLayout->addLayout(miscLayout);

        saveLayout = new QHBoxLayout();
        saveLayout->setObjectName("saveLayout");
        saveLayout->setContentsMargins(10, 10, 10, 10);
        saveLayout->setSpacing(10);

        switchLanguage = new QPushButton(layoutWidget);
        switchLanguage->setObjectName("switchLanguage");
        sizePolicy1.setHeightForWidth(switchLanguage->sizePolicy().hasHeightForWidth());
        switchLanguage->setFocusPolicy(Qt::NoFocus);
        switchLanguage->setSizePolicy(sizePolicy1);

        saveLayout->addWidget(switchLanguage);

        adjustButton = new QPushButton(layoutWidget);
        adjustButton->setObjectName("adjustButton");
        sizePolicy1.setHeightForWidth(adjustButton->sizePolicy().hasHeightForWidth());
        adjustButton->setFocusPolicy(Qt::NoFocus);
        adjustButton->setSizePolicy(sizePolicy1);

        saveLayout->addWidget(adjustButton);

        saveLog = new QPushButton(layoutWidget);
        saveLog->setObjectName("simpleView");
        sizePolicy1.setHeightForWidth(saveLog->sizePolicy().hasHeightForWidth());
        saveLog->setFocusPolicy(Qt::NoFocus);
        saveLog->setSizePolicy(sizePolicy1);

        saveLayout->addWidget(saveLog);

        startLog = new QPushButton(layoutWidget);
        startLog->setObjectName("startLog");
        sizePolicy1.setHeightForWidth(startLog->sizePolicy().hasHeightForWidth());
        startLog->setFocusPolicy(Qt::NoFocus);
        startLog->setSizePolicy(sizePolicy1);

        startLog->setCheckable(false);

        saveLayout->addWidget(startLog);

        closeShutdown = new QPushButton(layoutWidget);
        closeShutdown->setObjectName("closeShutdown");
        sizePolicy1.setHeightForWidth(closeShutdown->sizePolicy().hasHeightForWidth());
        closeShutdown->setFocusPolicy(Qt::NoFocus);
        closeShutdown->setSizePolicy(sizePolicy1);

        saveLayout->addWidget(closeShutdown);

        saveLayout->setStretch(0, 2);
        saveLayout->setStretch(1, 2);
        saveLayout->setStretch(2, 2);
        saveLayout->setStretch(3, 3);
        saveLayout->setStretch(4, 3);

        dataLayout->addLayout(saveLayout);

        dataLayout->setStretch(0, 3);
        dataLayout->setStretch(1, 1);

        panelLayout->addLayout(dataLayout);

        selectLayout = new QVBoxLayout();
        selectLayout->setSpacing(10);
        selectLayout->setObjectName("selectLayout");
        selectLayout->setSizeConstraint(QLayout::SetDefaultConstraint);
        selectLayout->setContentsMargins(10, 10, 10, 10);
        selectLayout->setSpacing(0);

        gpsStatus = new QPushButton(layoutWidget);
        gpsStatus->setObjectName("gpsStatus");
        sizePolicy1.setHeightForWidth(gpsStatus->sizePolicy().hasHeightForWidth());
        gpsStatus->setFocusPolicy(Qt::NoFocus);
        gpsStatus->setSizePolicy(sizePolicy1);
        gpsStatus->setStyleSheet(GREEN_BUTTON);

        selectLayout->addWidget(gpsStatus);

        standbyLog = new QPushButton(layoutWidget);
        standbyLog->setObjectName("standbyLog");
        standbyLog->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        standbyLog->setFocusPolicy(Qt::NoFocus);
        standbyLog->setStyleSheet(GREEN_BUTTON);

        selectLayout->addWidget(standbyLog);

        tableLog = new QPushButton(layoutWidget);
        tableLog->setObjectName("tableLog");
        tableLog->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        tableLog->setFocusPolicy(Qt::NoFocus);
        tableLog->setStyleSheet(GREEN_BUTTON);

        selectLayout->addWidget(tableLog);

        selectLayout->setStretch(0, 1);
        selectLayout->setStretch(1, 1);
        selectLayout->setStretch(2, 1);

        panelLayout->addLayout(selectLayout);

        panelLayout->setStretch(0, 6);
        panelLayout->setStretch(1, 1);

        verticalLayout->addLayout(panelLayout);

        statusLine = new QFrame(layoutWidget);
        statusLine->setObjectName("statusLine");
        statusLine->setFrameShape(QFrame::HLine);
        statusLine->setFrameShadow(QFrame::Sunken);
        statusLine->setLineWidth(1280);
        statusLabel = new QLabel(layoutWidget);
        statusLabel->setObjectName("statusLabel");
        statusLabel->setGeometry(QRect(10, 710, 1260, 80));

        verticalLayout->addWidget(statusLine);
        verticalLayout->addWidget(statusLabel);

        verticalLayout->setStretch(0, 1);
        verticalLayout->setStretch(1, 1);

        MainWindow->setCentralWidget(centralWidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    }

    void retranslateUi(MainWindow *MainWindow) {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow"));
        statusLabel->setText(QCoreApplication::translate("MainWindow", "Status: Inicializando"));
        peaksTitle->setText(QCoreApplication::translate("MainWindow", "Peaks Detectados"));
        peakOneFreqValue->setText(QCoreApplication::translate("MainWindow", ""));
        peakOneFreqUnit->setText("kHz");
        peakTwoFreqValue->setText(QCoreApplication::translate("MainWindow", ""));
        peakTwoFreqUnit->setText("kHz");
        peakThreeFreqValue->setText(QCoreApplication::translate("MainWindow", ""));
        peakThreeFreqUnit->setText("kHz");
        peakOnePowerValue->setText(QCoreApplication::translate("MainWindow", ""));
        peakOnePowerUnit->setText("dBFS");
        peakTwoPowerValue->setText(QCoreApplication::translate("MainWindow", ""));
        peakTwoPowerUnit->setText("dBFS");
        peakThreePowerValue->setText(QCoreApplication::translate("MainWindow", ""));
        peakThreePowerUnit->setText("dBFS");
        selectTimeAxis->setText(QCoreApplication::translate("MainWindow", "Versus\nTiempo"));
        selectDistanceAxis->setText(QCoreApplication::translate("MainWindow", "Versus\nDistancia"));
        selectBeacon->setText(QCoreApplication::translate("MainWindow", "Seleccionar\nBaliza"));
        beaconFound->setText(QCoreApplication::translate("MainWindow", "Baliza\nEncontrada"));
        preblastLog->setText(QCoreApplication::translate("MainWindow", "Registro\nPre-Tronadura"));
        postblastLog->setText(QCoreApplication::translate("MainWindow", "Registro\nPost-Tronadura"));
        standbyLog->setText(QCoreApplication::translate("MainWindow", "Registro inactivo"));
        tableLog->setText(QCoreApplication::translate("MainWindow", "Mostrar tabla"));
        switchLanguage->setText(QCoreApplication::translate("MainWindow", "Español"));
        adjustButton->setText(QCoreApplication::translate("MainWindow", "Ajustar\nEspectro"));
        saveLog->setText(QCoreApplication::translate("MainWindow", "Vista avanzada"));
        startLog->setText(QCoreApplication::translate("MainWindow", "Empezar Nuevo\nRegistro"));
        closeShutdown->setText(QCoreApplication::translate("MainWindow", "Cerrar y Apagar"));
        gpsStatus->setText(QCoreApplication::translate("MainWindow", "Estado GPS"));

        if (!simpleView) {
            selectOneFreq->setText(QString::number(MainWindow->beaconA, 'f', 2) + " kHz");
            selectTwoFreq->setText(QString::number(MainWindow->beaconB, 'f', 2) + " kHz");
            selectThreeFreq->setText(QString::number(MainWindow->beaconC, 'f', 2) + " kHz");
        } else {
            selectOneFreq->setText(QCoreApplication::translate("MainWindow", "Baliza A"));
            selectTwoFreq->setText(QCoreApplication::translate("MainWindow", "Baliza B"));
            selectThreeFreq->setText(QCoreApplication::translate("MainWindow", "Baliza C"));
        }

        inputBeaconWidget->beaconTopInputLabel->setText(QCoreApplication::translate("MainWindow", "Ingreso Nueva Baliza"));
        inputBeaconWidget->beaconOneInputLabel->setText(QCoreApplication::translate("MainWindow", "Distancia Baliza [metros]"));
        if (!simpleView) {
            inputBeaconWidget->beaconTypeA->setText(QString::number(MainWindow->beaconA, 'f', 2) + " kHz");
            inputBeaconWidget->beaconTypeB->setText(QString::number(MainWindow->beaconB, 'f', 2) + " kHz");
            inputBeaconWidget->beaconTypeC->setText(QString::number(MainWindow->beaconC, 'f', 2) + " kHz");
        } else {
            inputBeaconWidget->beaconTypeA->setText(QCoreApplication::translate("MainWindow", "Baliza A"));
            inputBeaconWidget->beaconTypeB->setText(QCoreApplication::translate("MainWindow", "Baliza B"));
            inputBeaconWidget->beaconTypeC->setText(QCoreApplication::translate("MainWindow", "Baliza C"));
        }
        inputBeaconWidget->beaconInputAccept->setText(QCoreApplication::translate("MainWindow", "Aceptar"));
        inputBeaconWidget->beaconInputCancel->setText(QCoreApplication::translate("MainWindow", "Cancelar"));

        foundBeaconWidget->beaconFoundLabel->setText(QCoreApplication::translate("MainWindow", "Una nueva baliza será registrada\n¿Está seguro de la ubicación de esta?"));
        foundBeaconWidget->beaconOneFoundLabel->setText(QCoreApplication::translate("MainWindow", "Identificador Baliza [ID]"));
        foundBeaconWidget->beaconFoundAccept->setText(QCoreApplication::translate("MainWindow", "Aceptar"));
        foundBeaconWidget->beaconFoundNotFound->setText(QCoreApplication::translate("MainWindow", "No encontrada"));
        foundBeaconWidget->beaconFoundCancel->setText(QCoreApplication::translate("MainWindow", "Cancelar"));

        warningWidget->warningLabel->setText(QCoreApplication::translate("MainWindow", "Comenzará un nuevo registro\nLuego de esto no podrá modificar el registro actual"));
        warningWidget->warningAccept->setText(QCoreApplication::translate("MainWindow", "Aceptar"));
        warningWidget->warningCancel->setText(QCoreApplication::translate("MainWindow", "Cancelar"));

        gpsWidget->statusTitle->setText(QCoreApplication::translate("MainWindow", "Estado GPS"));
        gpsWidget->gpsNameLabel->setText(QCoreApplication::translate("MainWindow", "Nombre"));
        gpsWidget->gpsModeLabel->setText(QCoreApplication::translate("MainWindow", "Modo"));
        gpsWidget->gpsStatusLabel->setText(QCoreApplication::translate("MainWindow", "Estado"));
        gpsWidget->gpsCoordXLabel->setText(QCoreApplication::translate("MainWindow", "Latitud"));
        gpsWidget->gpsCoordYLabel->setText(QCoreApplication::translate("MainWindow", "Longitud"));
        gpsWidget->gpsCoordZLabel->setText(QCoreApplication::translate("MainWindow", "Altura [msnm]"));
        gpsWidget->gpsAccHorLabel->setText(QCoreApplication::translate("MainWindow", "Precisión H [mm]"));
        gpsWidget->gpsAccVerLabel->setText(QCoreApplication::translate("MainWindow", "Precisión V [mm]"));
        gpsWidget->statusClose->setText(QCoreApplication::translate("MainWindow", "Cerrar"));

        beaconTable->updateButton->setText(QCoreApplication::translate("MainWindow", "Actualizar balizas"));
        beaconTable->generateButton->setText(QCoreApplication::translate("MainWindow", "Generar archivo"));
        beaconTable->cancelButton->setText(QCoreApplication::translate("MainWindow", "Cancelar"));
        beaconTable->beaconLabelsLayout->id->setText(QCoreApplication::translate("MainWindow", "Id Baliza"));
        beaconTable->beaconLabelsLayout->beaconType->setText(QCoreApplication::translate("MainWindow", "Tipo Baliza"));
        beaconTable->beaconLabelsLayout->preDistance->setText(QCoreApplication::translate("MainWindow", "Profund Pre"));
        beaconTable->beaconLabelsLayout->prePower->setText(QCoreApplication::translate("MainWindow", "Potencia Pre"));
        beaconTable->beaconLabelsLayout->postId->setText(QCoreApplication::translate("MainWindow", "Post Id"));
        beaconTable->beaconLabelsLayout->assignedId->setText(QCoreApplication::translate("MainWindow", "Asignado"));
        beaconTable->beaconLabelsLayout->postPower->setText(QCoreApplication::translate("MainWindow", "Potencia Post"));
        beaconTable->beaconLabelsLayout->diffNorthDistance->setText(QCoreApplication::translate("MainWindow", "Desplazamiento horizontal"));
        beaconTable->beaconLabelsLayout->diffEastDistance->setText(QCoreApplication::translate("MainWindow", "Rumbo"));
        beaconTable->beaconLabelsLayout->diffHeight->setText(QCoreApplication::translate("MainWindow", "Desplazamiento vertical"));
        beaconTable->beaconLabelsLayout->preLongitude->setText(QCoreApplication::translate("MainWindow", "Pre Longitud"));
        beaconTable->beaconLabelsLayout->preLatitude->setText(QCoreApplication::translate("MainWindow", "Pre Latitud"));
        beaconTable->beaconLabelsLayout->postLongitude->setText(QCoreApplication::translate("MainWindow", "Post Longitud"));
        beaconTable->beaconLabelsLayout->postLatitude->setText(QCoreApplication::translate("MainWindow", "Post Latitud"));

        nameInputDialog->nameTopInputLabel->setText(QCoreApplication::translate("MainWindow", "Nombre Configuración"));
        nameInputDialog->nameOneInputLabel->setText(QCoreApplication::translate("MainWindow", "Ingrese Nombre"));
        nameInputDialog->nameInputAccept->setText(QCoreApplication::translate("MainWindow", "Aceptar"));

        adjustSpectrum->adjustOneInputLabel->setText(QCoreApplication::translate("MainWindow", "Máximo"));
        adjustSpectrum->adjustTwoInputLabel->setText(QCoreApplication::translate("MainWindow", "Mínimo"));
        adjustSpectrum->adjustWindowOptionInputLabel->setText(QCoreApplication::translate("MainWindow", "Ventana"));
        adjustSpectrum->adjustFrequencyInputLabel->setText(QCoreApplication::translate("MainWindow", "Frecuencia"));
        adjustSpectrum->adjustSampleSizeInputLabel->setText(QCoreApplication::translate("MainWindow", "Muestras"));
        adjustSpectrum->adjustAverageInputLabel->setText(QCoreApplication::translate("MainWindow", "Promedios"));
        adjustSpectrum->adjustOneInputText->setText(QCoreApplication::translate("MainWindow", "4.0"));
        adjustSpectrum->adjustTwoInputText->setText(QCoreApplication::translate("MainWindow", "-140.0"));
        adjustSpectrum->adjustBeaconAInputLabel->setText(QCoreApplication::translate("MainWindow", "Baliza A"));
        adjustSpectrum->adjustBeaconBInputLabel->setText(QCoreApplication::translate("MainWindow", "Baliza B"));
        adjustSpectrum->adjustBeaconCInputLabel->setText(QCoreApplication::translate("MainWindow", "Baliza C"));
        adjustSpectrum->adjustInputAccept->setText(QCoreApplication::translate("MainWindow", "Aceptar"));
        adjustSpectrum->adjustInputCancel->setText(QCoreApplication::translate("MainWindow", "Cancelar"));

        for (int i = 0; i < 7; i++) {
            adjustSpectrum->adjustWindowOptionInputText->setItemText(i, DataWindow::windowName(i));
        }
    }
};

namespace Ui {
class MainWindow : public Ui_MainWindow {
};
}  // namespace Ui

QT_END_NAMESPACE
