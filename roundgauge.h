#ifndef ROUNDGAUGE_H
#define ROUNDGAUGE_H

#include <QWidget>
#include <QLabel>
#include <QDebug>
#include <QPainter>

#include "measurement.h"

class RoundGauge : public QWidget
{
    Q_OBJECT
protected:
    Measurement measurement_;

    double minValue_;
    double maxValue_;
    double nominalValue_;
    double criticalValue_;
    double minAngle_;
    double maxAngle_;
    double ticsInterval_;
    double labelsInterval_;
    unsigned int decimalPlaces_;
    QString subjectFilter_;
    QString typeFilter_;
    int x_;
    int y_;
public:
    RoundGauge(QWidget * parent=0);

    virtual void setMin(double min) {minValue_=min;}
    virtual void setMax(double max) {maxValue_=max;}
    virtual void setDecimalPlaces(double dp) {decimalPlaces_ = dp;}
    virtual void setCritical(double c) {criticalValue_=c;}
    virtual void setNominal(double n) {nominalValue_=n;}
    virtual void setMaxAngle(double max) {maxAngle_=max;}
    virtual void setMinAngle(double min) {minAngle_=min;}
    virtual void setTicsInterval(double i) {ticsInterval_=i;}
    virtual void setLabelsInterval(double i) {labelsInterval_=i;}
    virtual void setTypeFilter(QString s) {typeFilter_=s;}
    virtual void setSubjectFilter(QString s) {subjectFilter_=s;}
    virtual void showSettingsForm();
    virtual void registerPublisher(QObject*);

    virtual void setX(int x){ x_=x; move(x_,y_);}
    virtual void setY(int y){ y_=y; move(x_,y_);}
    virtual void setXY(int x, int y){ x_=x; y_=y; move(x_,y_);}


protected:
    virtual void paintEvent(QPaintEvent *event);


public slots:
    virtual void newMeasurement(Measurement);

};
#endif // ROUNDGAUGE_H
