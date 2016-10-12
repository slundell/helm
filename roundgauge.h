#ifndef ROUNDGAUGE_H
#define ROUNDGAUGE_H

#include <QWidget>
#include <QLabel>
#include <QDebug>
#include <QPainter>

#include "helmwidget.h"

class RoundGauge : public HelmWidget
{
    Q_OBJECT
protected:


    double minValue_;
    double maxValue_;
    double nominalValue_;
    double criticalValue_;
    double minAngle_;
    double maxAngle_;
    double ticsInterval_;
    double labelsInterval_;
    unsigned int decimalPlaces_;


public:
    RoundGauge(HelmWidget * parent=0);

    virtual void setMin(double min) {minValue_=min;}
    virtual void setMax(double max) {maxValue_=max;}
    virtual void setDecimalPlaces(double dp) {decimalPlaces_ = dp;}
    virtual void setCritical(double c) {criticalValue_=c;}
    virtual void setNominal(double n) {nominalValue_=n;}
    virtual void setMaxAngle(double max) {maxAngle_=max;}
    virtual void setMinAngle(double min) {minAngle_=min;}
    virtual void setTicsInterval(double i) {ticsInterval_=i;}
    virtual void setLabelsInterval(double i) {labelsInterval_=i;}


    virtual void saveSettings();
    virtual void readSettings();


protected:
    virtual void paintEvent(QPaintEvent *event);


};
#endif // ROUNDGAUGE_H
