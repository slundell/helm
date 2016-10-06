#ifndef NMEAPARSER_H
#define NMEAPARSER_H
#include <QString>
#include <QStringList>
#include "lineparser.h"
class NMEAParser : public LineParser
{
public:
    NMEAParser();
    virtual QVector<Measurement> parseLine(const QString&);
};

#endif // NMEAPARSER_H
