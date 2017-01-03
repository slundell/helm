#include "measurementgenerator.h"
#include <QDebug>
#include <QSettings>
#include <QVariant>



MeasurementGenerator::MeasurementGenerator()
    : min_(0), max_(100), subject_(""), parameter_(""), unit_("")
{
    currValue_ = min_;
    up_ = true;
    type_ = "MeasurementGenerator";
}

MeasurementGenerator::MeasurementGenerator(double min, double max, QString subject, QString type, QString unit)
    : min_(min), max_(max), subject_(subject), parameter_(type), unit_(unit)
{
    currValue_ = min_;
    up_ = true;
    type_ = "MeasurementGenerator";
}



void MeasurementGenerator::saveSettings(){
    Persistable::saveSettings();
    qDebug() << "MeasurementGenerator::saveSettings()";
    QSettings settings(Persistable::filename_, QSettings::IniFormat);
    settings.beginGroup(name_);

    settings.setValue("min", min_);
    settings.setValue("max", max_);
    settings.setValue("subject", subject_);
    settings.setValue("parameter", parameter_);
    settings.setValue("unit", unit_);
}

void MeasurementGenerator::readSettings(){
    Persistable::readSettings();

    QSettings settings(Persistable::filename_, QSettings::IniFormat);

    settings.beginGroup(name_);

    max_ = settings.value("max", 100).toDouble();
    min_ = settings.value("min", 0).toDouble();
    subject_ = settings.value("subject", "").toString();
    parameter_ = settings.value("parameter", "").toString();
    unit_ = settings.value("unit", "").toString();



}


void MeasurementGenerator::init(){
    start();
}


void MeasurementGenerator :: run(){


    qDebug() << "MeasurementGenerator::run()";
    while (true){

        if (up_){
            double add = ((max_ - min_) / 100.0) * 2 *(((double)max_ - (double)currValue_)/(double)max_);
            if ( add/currValue_ <= 0.001)
               up_ = false;
            currValue_ += add;
            if (currValue_ >= max_){
                up_ = false;
                currValue_ = max_;
            }
        } else {
            currValue_ -= ((max_ - min_) / 19.0);
            if (currValue_ <= min_){
                up_ = true;
                currValue_ = min_;
            }
        }

        Measurement m;
        m.setValue(currValue_);
        m.setSubject(subject_);
        m.setParameter(parameter_);
        m.setUnit(unit_);

        emit notify(m);
        msleep(50);
    }
}
