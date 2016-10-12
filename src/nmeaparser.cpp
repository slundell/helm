#include "nmeaparser.h"
#include <QDebug>
NMEAParser::NMEAParser()
{
}


QVector<Measurement> NMEAParser::parseLine(const QString& line)
{
    QStringList words = line.split(",",QString::KeepEmptyParts);
    QVector<Measurement> measurements;
/*
    QString dump;
    qDebug()<<line;
    for (int i=0;i<words.count();++i)
            dump += " |" + words[i] + "| ";
    qDebug() << dump;
*/

    if (words[0].contains("$GPRMC"))
    {

        Measurement m;
        m.setValue(words[7].toDouble());
        m.setSubject("B�t");
        m.setType("Fart �ver grund");
        m.setUnit("Knop");
        measurements.push_back(m);
    }
    return measurements;
}
