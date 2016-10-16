#ifndef MEASUREMENTGENERATOR_H
#define MEASUREMENTGENERATOR_H

#include <QThread>
#include "measurement.h"
#include "persistable.h"

class MeasurementGenerator : public QThread, public Persistable

{
    Q_OBJECT
protected:
    double min_;
    double max_;
    double currValue_;
    bool up_;
    QString subject_;
    QString parameter_;
    QString unit_;

public:
    MeasurementGenerator();
    MeasurementGenerator(double, double, QString, QString, QString);
    virtual void readSettings();
    virtual void saveSettings();
    virtual void init();
    virtual void run();
signals:
    void notify(Measurement);
};

#endif // MEASUREMENTGENERATOR_H
