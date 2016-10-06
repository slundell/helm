#ifndef PROPSLIPCALCULATOR_H
#define PROPSLIPCALCULATOR_H

#include <QObject>
#include "dispatcher.h"

class PropSlipCalculator : public Dispatcher
{
    Q_OBJECT

private:
    double gearRatio_;
    double propPitch_;

    Measurement rpm_;
    Measurement speed_;
public:
    PropSlipCalculator();


    virtual void setGearRatio(double v){ gearRatio_ = v; }
    virtual void setPropPitch(double v){ propPitch_ = v; }


public slots:
    virtual void newMeasurement(Measurement);

signals:
    void notify(Measurement);
};

#endif // PROPSLIPCALCULATOR_H
