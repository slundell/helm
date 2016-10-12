#include "measurementgenerator.h"


MeasurementGenerator::MeasurementGenerator(double min, double max, QString subject, QString type, QString unit)
    : min_(min), max_(max), subject_(subject), type_(type), unit_(unit)
{
    currValue_ = min;
    up_ = true;
}


void MeasurementGenerator :: run(){

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
        m.setType(type_);
        m.setUnit(unit_);

        emit notify(m);
        msleep(50);
    }
}
