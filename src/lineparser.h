#ifndef LINEPARSER_H
#define LINEPARSER_H

#include <QObject>
#include <QVector>
#include "measurement.h"

class LineParser : public QObject
{
public:
    LineParser();
    virtual QVector<Measurement> parseLine(const QString&) = 0 ;//pure virtual
    virtual bool checkForReconnect(const QString&);
};

#endif // LINEPARSER_H
