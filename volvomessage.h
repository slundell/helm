#ifndef VOLVOMESSAGE_H
#define VOLVOMESSAGE_H

#include <QVector>
class VolvoMessage
{

protected:
    qint32 can_id_;
    quint8 module_id_;
    quint8 command_id_;
    quint8 function_id_;
    quint8 function_param_;
    quint8 error_response_;
    bool isComplete_;
    QVector<quint8> data_;


public:
    explicit VolvoMessage();
    bool parseCANFrame(const &QCanBusFrame); //true if parsed OK
    bool isComplete(){ return isComplete_;}
    bool hasErrorResponse() {return error_response_;}
    quint32 length();
    QVector<quint8> getData(){return data_;}
    void clear();


};

#endif // VOLVOMESSAGE_H
