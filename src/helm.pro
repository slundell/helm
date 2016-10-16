# -------------------------------------------------
# Project created by QtCreator 2009-06-09T17:28:23
# -------------------------------------------------
TARGET = helm
TEMPLATE = app
CONFIG += console
SOURCES += main.cpp \
    mainwindow.cpp \
    rowreader.cpp \
    lineparser.cpp \
    nmeaparser.cpp \
    dispatcher.cpp \
    measurement.cpp \
    elm327rowreader.cpp \
    roundgauge.cpp \
    propslipcalculator.cpp \
    measurementlogger.cpp \
    obd2reader.cpp \
    serialrowreader.cpp \
    dtcdisplay.cpp \
    vpd3obd2parser.cpp \
    vpd3canframeparser.cpp \
    canframeparser.cpp \
    measurementgenerator.cpp \
    sleekroundgauge.cpp \
    sleekdoublegauge.cpp \
    volvomessage.cpp \
    canreader.cpp \
    helmwidget.cpp \
    canplayer.cpp \
    persistable.cpp \
    manager.cpp \
    settingswindow.cpp \
    sleekdoublegaugesettings.cpp \
    sleekroundgaugesettings.cpp \
    selectcomponenttype.cpp
HEADERS += mainwindow.h \
    rowreader.h \
    lineparser.h \
    nmeaparser.h \
    dispatcher.h \
    measurement.h \
    elm327rowreader.h \
    roundgauge.h \
    propslipcalculator.h \
    measurementlogger.h \
    dtccodes.h \
    obd2reader.h \
    serialrowreader.h \
    dtcdisplay.h \
    vpd3obd2parser.h \
    vpd3canframeparser.h \
    canframeparser.h \
    measurementgenerator.h \
    sleekroundgauge.h \
    sleekdoublegauge.h \
    volvomessage.h \
    canreader.h \
    helmwidget.h \
    canplayer.h \
    persistable.h \
    manager.h \
    settingswindow.h \
    sleekdoublegaugesettings.h \
    sleekroundgaugesettings.h \
    selectcomponenttype.h
FORMS += \
    settings.ui \
    sleekdoublegaugesettings.ui \
    sleekroundgaugesettings.ui \
    selectcomponenttype.ui

QT += widgets
QT += serialport
QT += serialbus

DISTFILES += \
    .travis.yml

