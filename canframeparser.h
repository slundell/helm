#ifndef CANFRAMEPARSER_H
#define CANFRAMEPARSER_H

#include <QObject>

class CANFrameParser : public QObject
{
    Q_OBJECT
public:
    explicit CANFrameParser(QObject *parent = 0);

signals:

public slots:
};

#endif // CANFRAMEPARSER_H