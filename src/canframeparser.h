#ifndef CANFRAMEPARSER_H
#define CANFRAMEPARSER_H

#include <QObject>
#include "volvomessage.h"

class CANFrameParser : public QObject
{
    Q_OBJECT

public:
    explicit CANFrameParser(QObject *parent = 0);
    virtual QVector<Measurement> parse(const QCanBusFrame&) = 0; //pure virtual

};

#endif // CANFRAMEPARSER_H
