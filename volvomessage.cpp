#include "volvomessage.h"

VolvoMessage::VolvoMessage()
{
    clear();
}

QString VolvoMessage::toString() const{
    QString s;
    s = s.asprintf("%08X  ",canId_);
    for (quint16 i=0; i<data_.size(); ++i){
      s += s.asprintf(" %02X", data_[i]);
    }
    return s;
}

void VolvoMessage::clear(){
    canId_=0;
    errorResponse_=false;
    moduleId_=0;
    commandId_=0;
    functionId_=0;
    functionParam_=0;
    lastFrameSeq_=0;
    isComplete_=false;
    data_.clear();

}

bool VolvoMessage::parseCANFrame(const QCanBusFrame& frame){

    QByteArray payload = frame.payload();
    canId_ = frame.frameId();
      if (frame.frameId() == 0x01000021){
        if ( (payload[0]  & 0xF0) == 0xC0 ) {
            //One-frame msg
            //vm.reported_length = payload[0] & 0x07; //lowest three bits are the length in bytes.
            moduleId_ = payload[1];

            errorResponse_ = ((payload[2] == (char)0x7F) || (payload[2] == (char)0x7E));

            data_[0] = payload[5];
            data_[1] = payload[6];
            data_[2] = payload[7];

            if (errorResponse_){
                commandId_ = payload[3];
                functionId_ = payload[4];

            } else {
                commandId_ = payload[2] - 0x40;
                functionId_ = payload[3];
                functionParam_ = payload[4];
            }

            lastFrameSeq_ = 0;
            isComplete_ = true;
        } else {

            if ((char)payload[0] == 0x8F){
                //Multi frame start
                lastFrameSeq_ = 0;

                //vm.reported_length = payload[0] & 0x07; //lowest three bits are the length in bytes.
                //vm.actual_length = 4;
                moduleId_ = payload[1];

                errorResponse_ = (((char)payload[2] == 0x7F) || ((char)payload[2] == 0x7E));

                if (errorResponse_){
                    commandId_ = payload[3];
                    functionId_ = payload[4];
                } else {
                    commandId_ = payload[2] - 0x40;
                    functionId_ = payload[3];
                    functionParam_ = payload[4];
                }


                data_[0] = payload[5];
                data_[1] = payload[6];
                data_[2] = payload[7];

                isComplete_=false;


            } else if ((payload[0] & 0xF0) == 0x40){
                //Last frame in multi-frame message
                for (quint8 i=1;i<8;i++){
                    data_.push_back(payload[i]);
                }
                lastFrameSeq_ = 0;
                isComplete_ = true;
            }
            else if ((char)payload[0] > lastFrameSeq_){
                //Mid-frame in multi-frame message
                for (quint8 i=1;i<8;i++){
                    data_.push_back(payload[i]);
                }
                lastFrameSeq_ = payload[0];
                isComplete_ = false;
            }


        }
      } else {
          for (quint8 i=0;i<8;++i){
            data_.push_back(payload[i]);
          }
          isComplete_=true;
      }
      return true;
}
