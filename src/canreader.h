#ifndef SOCKETCANREADER_H
#define SOCKETCANREADER_H

#include <QTextStream>
#include <QFile>
#include <QCanBus>
#include <QThread>
#include "canframeparser.h"
#include "measurement.h"
#include "volvomessage.h"
#include "persistable.h"

class CANReader : public QObject, public Persistable
{
    Q_OBJECT


protected:
    QCanBusDevice* device_;
    CANFrameParser* parser_;
    QString canBusDeviceName_;


//    QFile logFile_;
//    QTextStream logStream_;
//    bool  useLogging_;

public:
    CANReader();
    virtual void open(QString);
    void init();
    virtual void close();

    virtual void saveSettings();
    virtual void readSettings();

//    virtual void setBaud(int);

    virtual void setParser(CANFrameParser*);
//    virtual void enableLogging(QString);


signals:
    void notify(Measurement); //TODO: const&

public slots:
    void receiveFrames();


};

#endif // SOCKETCANREADER_H
