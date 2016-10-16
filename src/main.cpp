#include <QGuiApplication>
#include "mainwindow.h"
#include "measurement.h"
#include "dispatcher.h"
#include "elm327rowreader.h"
#include "vpd3obd2parser.h"
#include "obd2reader.h"
#include "nmeaparser.h"
#include "roundgauge.h"
#include "canreader.h"
#include "canframeparser.h"
#include "vpd3canframeparser.h"
#include "sleekroundgauge.h"
#include "sleekdoublegauge.h"
#include "propslipcalculator.h"
#include "measurementlogger.h"
#include "dtcdisplay.h"
#include "measurementgenerator.h"
#include "persistable.h"
#include "manager.h"
#include <QDateTime>

//#include <qapplication.h>
#include <stdio.h>
#include <stdlib.h>

 /*void myMessageOutput(QtMsgType type, const char *msg)
 {
     switch (type) {
     case QtDebugMsg:
         fprintf(stderr, "Debug: %s\n", msg);
         break;
     case QtWarningMsg:
         fprintf(stderr, "Warning: %s\n", msg);
         break;
     case QtCriticalMsg:
         fprintf(stderr, "Critical: %s\n", msg);
         break;
     case QtFatalMsg:
         fprintf(stderr, "Fatal: %s\n", msg);
         abort();
     }
 }
*/
int main(int argc, char *argv[])
{
    qRegisterMetaType<Measurement>("Measurement");
//  qInstallMsgHandler(myMessageOutput);
    QApplication a(argc, argv);


    QString date = QDateTime::currentDateTime().toString("yyyy-MM-dd_hh.mm.ss");

/*
    CANReader canReaderBB;
    VPD3CANFrameParser canBBParser;
    canBBParser.setSubject("Engine Port");
    canReaderBB.setParser(&canBBParser);
    canReaderBB.open("vcan0");

    CANReader canReaderSB;
    VPD3CANFrameParser canSBParser;
    canSBParser.setSubject("Engine Starboard");
    canReaderSB.setParser(&canSBParser);
    canReaderSB.open("vcan1");
*/

    Manager::instance()->init();
    Manager::instance()->loadAll();

    //MeasurementGenerator mgBB(1, 4100, "Engine Port", "Engine Speed", "RPM");
    //MeasurementGenerator mgSB(1, 4000, "Engine Starboard", "Engine Speed", "RPM");


    Manager::instance()->initAll();




  quint8 r = a.exec();
  Manager::instance()->closeAll();
  return r;

}
