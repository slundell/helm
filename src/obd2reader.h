#ifndef OBD2READER_H
#define OBD2READER_H
#include "serialrowreader.h"
#include "lineparser.h"
#include <QtSerialPort/QtSerialPort>
#include <QTextStream>
#include <QFile>

class OBD2Reader : public SerialRowReader
{
private:
    bool resetAllDTCs_;

public:
    OBD2Reader();
    virtual void run();

public slots:
    virtual void resetAllDTCs();

};

#endif // OBD2READER_H
