QT += core gui virtualkeyboard quickwidgets qml quick sql multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

CONFIG += c++14 console

INCLUDEPATH += \
    inc \
    fftw \
    src/common \
    src/hostapi/alsa \
    src/hostapi/asihpi \
    src/hostapi/asio/ASIOSDK \
    src/hostapi/asio/ASIOSDK/common \
    src/hostapi/asio/ASIOSDK/host \
    src/hostapi/asio/ASIOSDK/host/pc \
    src/hostapi/coreaudio \
    src/hostapi/dsound \
    src/hostapi/jack \
    src/hostapi/oss \
    src/hostapi/skeleton \
    src/hostapi/wasapi \
    src/hostapi/wdmks \
    src/hostapi/wmme \
    src/os/win \
    src/os/unix


# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS
win32{
DEFINES += _WIN64
#DEFINES += _DEBUG
DEFINES += _USRDLL
DEFINES += PA_ENABLE_DEBUG_OUTPUT
DEFINES += _CRT_SECURE_NO_DEPRECATE
DEFINES += PAWIN_USE_WDMKS_DEVICE_INFO
DEFINES += _AFXDLL
DEFINES -= UNICODE
DEFINES += _USE_MATH_DEFINES
DEFINES += PA_USE_ASIO=1
DEFINES += PA_USE_DS=0
DEFINES += PA_USE_WMME=1
DEFINES += PA_USE_WASAPI=0
DEFINES += PA_USE_WDMKS=1

}
unix{
DEFINES += PA_USE_ALSA=1
DEFINES += PA_USE_ASIHPI=0
DEFINES += PA_USE_JACK=0
DEFINES += PA_USE_OSS=0
}

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    src/utils.cpp \
    src/mainwindow.cpp \
    src/dataprocessor.cpp \
    src/usbadc.cpp \
    src/datalogger.cpp \
    src/fakegps.cpp \
    src/emlidgps.cpp \
    src/statemachine.cpp \
    src/qcustomplot.cpp

HEADERS += \
    inc/dialogs/beacontable.h \
    inc/abstract/datareader.h \
    inc/abstract/gpsreader.h \
    inc/stylesheetdefines.h \
    inc/mainwindow.h \
    inc/dataprocessor.h \
    inc/datawindow.h \
    inc/ui_mainwindow.h \
    inc/utils.h \
    inc/usbadc.h \
    inc/fakegps.h \
    inc/emlidgps.h \
    inc/qcustomplot.h \
    inc/datalogger.h \
    inc/statemachine.h \
    inc/dialogs.h

LIBS+= -lfftw3 -lpthread -lportaudio -lwiringPi

RESOURCES += resources/richikb/richikb.qrc \
    resources.qrc \
    languages/languages.qrc

OTHER_FILES += \
    resources/richikb/style.qml \
    languages/richigui_en.qm \
    languages/richigui_es.qm

DISTFILES += \
    stylesheet.qss

TRANSLATIONS += \
    languages/richigui_en.ts \
    languages/richigui_es.ts