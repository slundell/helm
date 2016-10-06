#include "canreader.h"
#include <QDebug>

CANReader::CANReader()
{
}

void CANReader::open(){
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
}
void CANReader::close(){}


void CANReader::run(){
/*
    if (!open) open();
    bool tryLastFrameAgain = false;
    while (true){
        if (tryLastFrameAgain || readPacket){
           if (frame.frameType() != QCanBusFrame::ErrorFrame){
               if (vm_.parseCANFrame(ReadCanBusFrame)){
                       if (vm_.isComplete()){
                           if (!vm_.hasErrorResponse())
                                vpd3canparser_->parse(vm_);
                           vm_.clear();
                       }
               } else {

                   if (vm.size > 0)
                        tryLastFrameAgain = true;

                   vm_.clear();
               }
            }
        }



        usleep(1);
    }


*/
}
