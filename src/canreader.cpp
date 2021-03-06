#include "canreader.h"
#include <QDebug>
#include <QSettings>
#include "vpd3canframeparser.h"

CANReader::CANReader()
{
    type_="CANReader";
}

void CANReader::init()
{
    qDebug() << "CANReader::init()";
   open(canBusDeviceName_);
}

void CANReader::open(QString iface)
{
    qDebug() << "CANReader::open()"<< iface;
    canBusDeviceName_ = iface;
    bool supportsSocketCan = false;
    foreach (const QByteArray &backend, QCanBus::instance()->plugins()) {
        if (backend == "socketcan") {
            qDebug() << "SocketCan support found!";
            supportsSocketCan = true;
            break;
        }
    }
    if (!supportsSocketCan){
        qDebug() << "No SocketCan support!";
        exit(1);
    }
   device_ = QCanBus::instance()->createDevice("socketcan", canBusDeviceName_);

   if (device_ == nullptr){
       qDebug() << "Unable to create device!";
       qDebug() << device_->errorString();
       exit(1);
   }
   if (!device_->connectDevice()){
       qDebug() << "Unable to connect!";
       qDebug() << device_->errorString();
       exit(1);
   } else {
       connect(device_, &QCanBusDevice::framesReceived, this, &CANReader::receiveFrames);
       qDebug() << "Connected";
   }
}

void CANReader::close(){
    //TODO: Close and disconnect
}

void CANReader::setParser(CANFrameParser* p){
    parser_=p;
}


void CANReader::saveSettings(){
    Persistable::saveSettings();
    qDebug() << "CANReader::saveSettings()";
    QSettings settings(Persistable::filename_, QSettings::IniFormat);
    settings.beginGroup(name_);
    settings.setValue("device", canBusDeviceName_);
    settings.setValue("parser", parser_->getName());
    settings.setValue("subject", parser_->getSubject());
    settings.sync();
}

void CANReader::readSettings(){
    qDebug() << "CANReader::readSettings()";
    QSettings settings(Persistable::filename_, QSettings::IniFormat);

    settings.beginGroup(name_);

    QString parserType = settings.value("parser", "").toString();
    QString deviceName = settings.value("device", "").toString();
    QString subject    = settings.value("subject", "").toString();
    //A bit more error checking needed.

    if (parserType == "VPD3CANFrameParser") {
        qDebug() << "Using VPD3CANFrameParser to parse";
        parser_ = new VPD3CANFrameParser();
        parser_->setSubject(subject);
        open(deviceName);
    } else {
        qDebug() << "Unknown parser:" << parserType;

    }
}

void CANReader::receiveFrames(){
    //qDebug() << "CANReader::receiveFrames()";

    QCanBusFrame frame;
    if (sender()){ //check that we have a valid ptr
        QCanBusDevice* device = (QCanBusDevice*)sender();
        while (device->framesAvailable()){
            frame = device->readFrame();
            QVector<Measurement> m = parser_->parse(frame);
            for (quint16 i=0; i< m.size(); ++i){
                emit notify(m[i]);
            }

        }
    }
}
