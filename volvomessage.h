#ifndef VOLVOMESSAGE_H
#define VOLVOMESSAGE_H

#include <QByteArray>
#include <QCanBus>
#include <QDebug>
#include "measurement.h"

class VolvoMessage
{

protected:
    qint32 canId_;
    quint8 moduleId_;
    quint8 commandId_;
    quint8 functionId_;
    quint8 functionParam_;
    quint8 errorResponse_;
    quint8 lastFrameSeq_;
    bool isComplete_;
    QByteArray data_;


public:
    explicit VolvoMessage();
    bool parseCANFrame(const QCanBusFrame&); //true if parsed OK
    bool isComplete(){ return isComplete_;}
    bool hasErrorResponse() {return errorResponse_;}
    quint32 length() {return data_.size();}
    QByteArray getData() const {return data_;}
    quint32 getCANId() const { return canId_;}
    quint8 getModuleId() const {return moduleId_;}
    quint8 getCommandId() const { return commandId_;}
    quint8 getFunctionId() const { return functionId_;}
    quint8 getFunctionParam() const { return functionParam_;}
    void clear();
    virtual QString toString() const;


};

#endif // VOLVOMESSAGE_H
