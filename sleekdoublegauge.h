#ifndef SLEEKDOUBLEGAUGE_H
#define SLEEKDOUBLEGAUGE_H

#include "sleekroundgauge.h"

class SleekDoubleGauge : public SleekRoundGauge
{

protected:
    QString subjectFilterRight_;
    QString typeFilterRight_;
    Measurement measurementRight_;
    unsigned int rightValueAge_;
    unsigned int leftValueAge_;

    virtual void paintEvent(QPaintEvent *event);

public:
    SleekDoubleGauge(HelmWidget * parent=0);
    virtual void setTypeFilterLeft(QString s) {setTypeFilter(s);}
    virtual void setSubjectFilterLeft(QString s) {setSubjectFilter(s);}

    virtual void setTypeFilterRight(QString s) {typeFilterRight_=s;}
    virtual void setSubjectFilterRight(QString s) {subjectFilterRight_=s;}


public slots:
    virtual void newMeasurement(Measurement);
};

#endif // SLEEKDOUBLEGAUGE_H
