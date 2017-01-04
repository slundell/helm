#ifndef CANFRAMEPARSER_H
#define CANFRAMEPARSER_H

#include <QObject>
#include "volvomessage.h"

class CANFrameParser : public QObject
{
    Q_OBJECT

protected:
        QString subject_;

public:
    explicit CANFrameParser(QObject *parent = 0);
    virtual QVector<Measurement> parse(const QCanBusFrame&) = 0; //pure virtual


    virtual QString getName() { return "VPD3CANFrameParser"; }
    virtual QString getSubject() { return subject_; }
    virtual void setSubject(const QString &s) { subject_ = s ;}

};

#endif // CANFRAMEPARSER_H
