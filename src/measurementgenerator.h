#ifndef MEASUREMENTGENERATOR_H
#define MEASUREMENTGENERATOR_H

#include <QThread>
#include "measurement.h"
class MeasurementGenerator : public QThread

{
    Q_OBJECT
protected:
    double min_;
    double max_;
    double currValue_;
    bool up_;
    QString subject_;
    QString type_;
    QString unit_;

public:
    MeasurementGenerator(double, double, QString, QString, QString);
    virtual void run();
signals:
    void notify(Measurement);
};

#endif // MEASUREMENTGENERATOR_H
