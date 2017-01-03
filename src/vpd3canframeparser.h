#ifndef VPD3CANPARSER_H
#define VPD3CANPARSER_H

#include <canframeparser.h>

class VPD3CANFrameParser : public CANFrameParser
{
    Q_OBJECT

protected:
    VolvoMessage vm_;
    QString subject_;

    QVector<Measurement> parseVolvoMessage(const VolvoMessage&);
public:
    explicit VPD3CANFrameParser();
    QVector<Measurement> parse(const QCanBusFrame&);
    virtual void setSubject(const QString&);
    virtual QString getName() { return "VPD3CANFrameParser"; }
    virtual QString getSubject() {return subject_; }

signals:
};

#endif // VPD3CANPARSER_H
