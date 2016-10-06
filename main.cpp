#include <QGuiApplication>
#include "mainwindow.h"
#include "measurement.h"
#include "dispatcher.h"
#include "elm327rowreader.h"
#include "vpd3obd2parser.h"
#include "obd2reader.h"
#include "nmeaparser.h"
#include "roundgauge.h"
#include "sleekroundgauge.h"
#include "sleekdoublegauge.h"
#include "propslipcalculator.h"
#include "measurementlogger.h"
#include "dtcdisplay.h"
#include "measurementgenerator.h"

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
    Dispatcher dispatch;

    ///////////////////////////////////// PORT ENGINE SETUP /////////////////////////////////////
 /*   ELM327RowReader elmBB;
    //elmBB.setComPort("/dev/ttyD3BB");
    elmBB.setComPort("COM6");
    elmBB.setBaud(115200);
    elmBB.enableLogging(QString("/home/simon/boatlogs/engine_BB_")+date+".txt");

    VPD3OBD2Parser d3BB;
    elmBB.setParser(&d3BB);
    dispatch.registerPublisher(&elmBB);


    elmBB.start();

    DTCDisplay dtcBB;
    dtcBB.registerPublisher(&elmBB);
    dtcBB.setWinTitle("DTC Babord");
    dtcBB.registerDTCResetter(&elmBB);*/

    MeasurementGenerator mgBB(0, 4100, "Engine Port", "RPM", "RPM");
    MeasurementGenerator mgSB(0, 4000, "Engine Starboard", "RPM", "RPM");
    //dispatch.registerPublisher(&mgBB);

    SleekDoubleGauge rpmBB;
    rpmBB.registerPublisher(&mgBB);
    rpmBB.registerPublisher(&mgSB);
    rpmBB.setCritical(3500);
    rpmBB.setNominal(3000);
    rpmBB.setMax(4000);
    rpmBB.setMin(0);
    rpmBB.setTicsInterval(250);
    rpmBB.setNominalTicsInterval(250);
    rpmBB.setDecimalPlaces(0);
    rpmBB.setTypeFilterLeft("RPM");
    rpmBB.setTypeFilterRight("RPM");

    rpmBB.setSubjectFilterLeft("Engine Port");
    rpmBB.setSubjectFilterRight("Engine Starboard");


    rpmBB.setXY(860,640);
    rpmBB.resize(QSize(350, 350));

    rpmBB.show();

    //SLEEP
    QMutex dummy;
    dummy.lock();
    QWaitCondition waitCondition;
    waitCondition.wait(&dummy, 5000);

    mgBB.start();
    waitCondition.wait(&dummy, 2000);


    mgSB.start();


    /*
    RoundGauge mapBB;
    mapBB.registerPublisher(&elmBB);
    mapBB.setCritical(200);
    mapBB.setNominal(100);
    mapBB.setMax(255);
    mapBB.setMin(0);
    mapBB.setTicsInterval(25);
    mapBB.setLabelsInterval(50);
    mapBB.setTypeFilter("Intake Manifold Absolute Pressure");

    RoundGauge tempBB;
    tempBB.registerPublisher(&elmBB);
    tempBB.setCritical(90);
    tempBB.setNominal(60);
    tempBB.setMax(130);
    tempBB.setMin(0);
    tempBB.setTicsInterval(5);
    tempBB.setLabelsInterval(20);
    tempBB.setTypeFilter("Coolant Temperature");

    RoundGauge loadBB;
    loadBB.registerPublisher(&elmBB);
    loadBB.setCritical(90);
    loadBB.setNominal(80);
    loadBB.setMax(100);
    loadBB.setMin(0);
    loadBB.setTicsInterval(10);
    loadBB.setLabelsInterval(20);
    loadBB.setTypeFilter("Calculated Load");

    RoundGauge matBB;
    matBB.registerPublisher(&elmBB);
    matBB.setCritical(80);
    matBB.setNominal(70);
    matBB.setMax(150);
    matBB.setMin(0);
    matBB.setTicsInterval(10);
    matBB.setLabelsInterval(25);
    matBB.setTypeFilter("Intake Air Temperature");

    RoundGauge mafBB;
    mafBB.registerPublisher(&elmBB);
    mafBB.setCritical(80);
    mafBB.setNominal(70);
    mafBB.setMax(150);
    mafBB.setMin(0);
    mafBB.setTicsInterval(10);
    mafBB.setLabelsInterval(25);
    mafBB.setTypeFilter("Manifold Air Flow");


    RoundGauge frpBB;
    frpBB.registerPublisher(&elmBB);
    frpBB.setCritical(80);
    frpBB.setNominal(70);
    frpBB.setMax(150);
    frpBB.setMin(0);
    frpBB.setTicsInterval(10);
    frpBB.setLabelsInterval(25);
    frpBB.setTypeFilter("Fuel Rail Pressure");
*/

/*
    mapBB.resize(QSize(84,84));
    mapBB.setXY(0,940);

    tempBB.resize(QSize(84,84));
    tempBB.setXY(0,856);

    loadBB.resize(QSize(84,84));
    loadBB.setXY(200,740);

    matBB.resize(QSize(84,84));
    matBB.setXY(116,740);

    mafBB.resize(QSize(84,84));
    mafBB.setXY(32,740);

    frpBB.resize(QSize(84,84));
    frpBB.setXY(284,740);

    rpmBB.show();
    mapBB.show();
    tempBB.show();
    loadBB.show();
    matBB.show();
    mafBB.show();
    frpBB.show();

    ///////////////////////////////////// STARBOARD ENGINE SETUP /////////////////////////////////////
    ELM327RowReader elmSB;
    //elmSB.setComPort("/dev/ttyD3SB");
    elmSB.setComPort("COM6");
    elmSB.setBaud(115200);
    elmSB.enableLogging(QString("/home/simon/boatlogs/engine_SB_")+date+".txt");

    VPD3OBD2Parser d3SB;
    elmSB.setParser(&d3SB);
    dispatch.registerPublisher(&elmSB);

    elmSB.start();

    DTCDisplay dtcSB;
    dtcSB.registerPublisher(&elmSB);
    dtcSB.setWinTitle("DTC Styrbord");
    dtcBB.registerDTCResetter(&elmSB);

    RoundGauge rpmSB;
    rpmSB.registerPublisher(&elmSB);
    rpmSB.setCritical(3800);
    rpmSB.setNominal(2800);
    rpmSB.setMax(4000);
    rpmSB.setMin(0);
    rpmSB.setTicsInterval(100);
    rpmSB.setLabelsInterval(500);
    rpmSB.setTypeFilter("RPM");

    RoundGauge mapSB;
    mapSB.registerPublisher(&elmSB);
    mapSB.setCritical(200);
    mapSB.setNominal(100);
    mapSB.setMax(255);
    mapSB.setMin(0);
    mapSB.setTicsInterval(25);
    mapSB.setLabelsInterval(50);
    mapSB.setTypeFilter("Intake Manifold Absolute Pressure");

    RoundGauge tempSB;
    tempSB.registerPublisher(&elmSB);
    tempSB.setCritical(90);
    tempSB.setNominal(60);
    tempSB.setMax(130);
    tempSB.setMin(0);
    tempSB.setTicsInterval(5);
    tempSB.setLabelsInterval(20);
    tempSB.setTypeFilter("Coolant Temperature");

    RoundGauge loadSB;
    loadSB.registerPublisher(&elmSB);
    loadSB.setCritical(90);
    loadSB.setNominal(80);
    loadSB.setMax(100);
    loadSB.setMin(0);
    loadSB.setTicsInterval(10);
    loadSB.setLabelsInterval(20);
    loadSB.setTypeFilter("Calculated Load");

    RoundGauge matSB;
    matSB.registerPublisher(&elmSB);
    matSB.setCritical(80);
    matSB.setNominal(70);
    matSB.setMax(150);
    matSB.setMin(0);
    matSB.setTicsInterval(10);
    matSB.setLabelsInterval(25);
    matSB.setTypeFilter("Intake Air Temperature");

    RoundGauge mafSB;
    mafSB.registerPublisher(&elmSB);
    mafSB.setCritical(80);
    mafSB.setNominal(70);
    mafSB.setMax(150);
    mafSB.setMin(0);
    mafSB.setTicsInterval(10);
    mafSB.setLabelsInterval(25);
    mafSB.setTypeFilter("Manifold Air Flow");


    RoundGauge frpSB;
    frpSB.registerPublisher(&elmSB);
    frpSB.setCritical(80);
    frpSB.setNominal(70);
    frpSB.setMax(150);
    frpSB.setMin(0);
    frpSB.setTicsInterval(10);
    frpSB.setLabelsInterval(25);
    frpSB.setTypeFilter("Fuel Rail Pressure");

    rpmSB.setXY(484,824);
    rpmSB.resize(QSize(200,200));

    mapSB.resize(QSize(84,84));
    mapSB.setXY(684,940);

    tempSB.resize(QSize(84,84));
    tempSB.setXY(684,856);

    loadSB.resize(QSize(84,84));
    loadSB.setXY(484,740);

    matSB.resize(QSize(84,84));
    matSB.setXY(568,740);

    mafSB.resize(QSize(84,84));
    mafSB.setXY(652,740);

    frpSB.resize(QSize(84,84));
    frpSB.setXY(400,740);

    rpmSB.show();
    mapSB.show();
    tempSB.show();
    loadSB.show();
    matSB.show();
    mafSB.show();
    frpSB.show();

    ///////////////////////////////////// GPS Setup /////////////////////////////////////
    SerialRowReader gps;
    gps.setBaud(4800);
    gps.setComPort("/dev/ttyPS2");
    gps.enableLogging(QString("/home/simon/boatlogs/gps_")+date+".txt");
    NMEAParser nmea;
    gps.setParser(&nmea);
    dispatch.registerPublisher(&gps);

    RoundGauge speed;
    speed.registerPublisher(&gps);
    speed.setCritical(25);
    speed.setNominal(18);
    speed.setMax(30);
    speed.setMin(0);
    speed.setLabelsInterval(5);
    speed.setTicsInterval(1);
    speed.setXY(500,500);
    speed.show();





    PropSlipCalculator propslip;
    propslip.registerPublisher(&gps);
    propslip.registerPublisher(&elmSB);
    propslip.setGearRatio(1.0/1.63);
    propslip.setPropPitch(17);

    RoundGauge slip;
    slip.registerPublisher(&propslip);
    slip.setCritical(30);
    slip.setNominal(10);
    slip.setMax(30);
    slip.setMin(0);
    slip.setLabelsInterval(5);
    slip.setTicsInterval(5);

    slip.resize(QSize(84,84));
    slip.setXY(684,856);
    slip.show();

*/







/*
    MeasurementLogger loggerSB("/home/simon/boatlogs/d3SBlog.txt");
    loggerSB.registerPublisher(&elmSB);

    MeasurementLogger loggerBB("/home/simon/boatlogs/d3BBlog.txt");
    loggerBB.registerPublisher(&elmBB);

    gps.start();
    elmSB.start();
*/
    return a.exec();
}




/*
QMessageBox msgBox;
msgBox.setText("Felkod mottagen");
msgBox.setInformativeText(code+": "+m.getMessage());
msgBox.setStandardButtons(QMessageBox::Discard);
msgBox.setDefaultButton(QMessageBox::Discard);
int ret = msgBox.exec();
*/


