#ifndef SOCKETCANREADER_H
#define SOCKETCANREADER_H

#include <QTextStream>
#include <QFile>
#include <QCanBus>
#include <QThread>
#include "canframeparser.h"
#include "measurement.h"
#include "volvomessage.h"

class CANReader : public QObject
{
    Q_OBJECT


protected:
    QCanBusDevice* device_;
    CANFrameParser* parser_;
//    QFile logFile_;
//    QTextStream logStream_;
//    bool  useLogging_;

public:
    CANReader();
    virtual void open(QString);
    virtual void close();

//    virtual void setBaud(int);

    virtual void setParser(CANFrameParser*);
//    virtual void enableLogging(QString);


signals:
    void notify(Measurement); //TODO: const&

public slots:
    void receiveFrames();


};

#endif // SOCKETCANREADER_H
