#ifndef SERIALROWREADER_H
#define SERIALROWREADER_H
#include "rowreader.h"
#include "lineparser.h"
#include <QtSerialPort/QtSerialPort>
#include <QTextStream>
#include <QFile>

class SerialRowReader : public RowReader
{
protected:
    LineParser* parser_;
    QSerialPort* serialPort_;
    QString portName_;
    QFile logFile_;
    QTextStream logStream_;
    bool  useLogging_;
    virtual void open();
    virtual void close();
    virtual void postInit();
    virtual void transmit(const QString&);
    QStringList receive(unsigned int);
    //virtual void waitForChar(char);

    virtual bool waitForChar(char, unsigned int timeOut = 0);
    virtual void waitForString(const QString&);


public:
    SerialRowReader();
    virtual void setBaud(int);
    virtual void setComPort(QString);
    virtual void run();
    virtual void setParser(LineParser*);
    virtual void enableLogging(QString);
    virtual void reconnect();
};

#endif // SERIALROWREADER_H
