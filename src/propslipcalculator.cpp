#include "propslipcalculator.h"
#include <QDebug>
PropSlipCalculator::PropSlipCalculator()
{
}


void PropSlipCalculator::newMeasurement(Measurement m)
{
    QMutexLocker ml(newMeasurementMutex_);
    //qDebug() << "PropSlipCalculator recieve: " << m.getValue();

    if ((m.getSubject() == "Engine") && (m.getType() == "Speed") && (m.getUnit() == "RPM"))
    {
        rpm_ = m;
        //qDebug() << "PropSlipCalculator recieve: rpm" << m.getValue();
    }
    else if ((m.getSubject() == "Båt") && (m.getUnit() == "Knop"))
    {
        speed_ = m;
        //qDebug() << "PropSlipCalculator recieve:  speed" << m.getValue();
    }

    if ((speed_.getValue().canConvert<double>()) && (rpm_.getValue().canConvert<int>()))
    {

        double speed = speed_.getValue().toDouble();
        int rpm = rpm_.getValue().toInt();

        //speed = 25;
        //rpm = 3600;

        double slip = 0;
        if (speed > 1.0)
        {
            slip = 100 * speed / ((double)rpm * 60 * gearRatio_ * propPitch_ * 2.54 / 1852000);
        }
        else
        {
            slip = 0;
        }
        //qDebug() << "Slip: " << slip;
        Measurement slipm;
        slipm.setSubject(tr("Propeller"));
        slipm.setType(tr("Slip"));
        slipm.setUnit(tr("%"));
        slipm.setPrecision(2);
        slipm.setValue(slip);
        //qDebug() << "emit slip";
        emit notify(slipm); //maybe need to unlock mutex first?
    }
}
