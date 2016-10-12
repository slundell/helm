#include "canreader.h"
#include <QDebug>

CANReader::CANReader()
{
}

void CANReader::open(QString iface){
    bool supportsSocketCan = false;
    foreach (const QByteArray &backend, QCanBus::instance()->plugins()) {
        if (backend == "socketcan") {
            supportsSocketCan = true;
            break;
        }
    }
    if (!supportsSocketCan){
        qDebug() << "No SocketCan support!";
        exit(1);
    }
   device_ = QCanBus::instance()->createDevice("socketcan", iface);

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
