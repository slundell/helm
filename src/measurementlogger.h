#ifndef MEASUREMENTLOGGER_H
#define MEASUREMENTLOGGER_H
#include <QObject>
#include <QTextStream>
#include <QString>
#include <QVariant>
#include <QFile>
#include "measurement.h"


class MeasurementLogger : public QObject
{
    Q_OBJECT
private:
    QTextStream stream_;

public:
    MeasurementLogger(const QString &);
    virtual void registerPublisher(QObject*);
public slots:
    virtual void newMeasurement(Measurement);

};

#endif // MEASUREMENTLOGGER_H
