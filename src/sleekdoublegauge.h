#ifndef SLEEKDOUBLEGAUGE_H
#define SLEEKDOUBLEGAUGE_H

#include "sleekroundgauge.h"
#include <QPixmap>

class SleekDoubleGauge : public SleekRoundGauge
{

protected:
    QString subjectFilterRight_;
    QString parameterFilterRight_;
    Measurement measurementRight_;
    unsigned int rightValueAge_;
    unsigned int leftValueAge_;
    double avgFPS_;

    virtual void paintEvent(QPaintEvent *event);
    virtual void oldPaintEvent(QPaintEvent *event);

    double angleAt(double value);
    virtual double xcoordLeft(double, double);
    virtual double ycoordLeft(double, double);
    virtual double xcoordRight(double, double);
    virtual double ycoordRight(double, double);
    QPixmap background_;
    bool backgroundValid_;

    virtual void createBackground(QPainter&);

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
