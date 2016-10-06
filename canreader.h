#ifndef SOCKETCANREADER_H
#define SOCKETCANREADER_H

#include <QTextStream>
#include <QFile>
#include <QCanBus>
#include <QThread>
#include "canframeparser.h"
#include "measurement.h"
#include "volvomessage.h"

class CANReader : public QThread
{
    Q_OBJECT


protected:
    VolvoMessage vm_;

//    CANFrameParser* parser_;
//    QFile logFile_;
//    QTextStream logStream_;
//    bool  useLogging_;
    virtual void open();
    virtual void close();
    virtual void run();

    /*
    QStringList receive(unsigned int);
*/

public:
    CANReader();
/*
    virtual void setBaud(int);
    virtual void run();
    virtual void setParser(CANFrameParser*);
    virtual void enableLogging(QString);
    */

signals:

};

#endif // SOCKETCANREADER_H
