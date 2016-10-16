#ifndef SLEEKDOUBLEGAUGE_H
#define SLEEKDOUBLEGAUGE_H

#include "sleekroundgauge.h"

class SleekDoubleGauge : public SleekRoundGauge
{

protected:
    QString subjectFilterRight_;
    QString parameterFilterRight_;
    Measurement measurementRight_;
    unsigned int rightValueAge_;
    unsigned int leftValueAge_;

    virtual void paintEvent(QPaintEvent *event);

public:
    SleekDoubleGauge(HelmWidget * parent=0);
    virtual void setParameterFilterLeft(QString s) {setParameterFilter(s);}
    virtual void setSubjectFilterLeft(QString s) {setSubjectFilter(s);}

    virtual void setParameterFilterRight(QString s) {parameterFilterRight_=s;}
    virtual void setSubjectFilterRight(QString s) {subjectFilterRight_=s;}

    virtual void saveSettings();
    virtual void readSettings();
    virtual void showSettingsForm();

public slots:
    virtual void newMeasurement(Measurement);
    virtual void save(const QString&, const QString&, const QString&, const QString&, const QString&, double, double);

};

#endif // SLEEKDOUBLEGAUGE_H
