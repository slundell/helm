#ifndef HELMWIDGET_H
#define HELMWIDGET_H

#include <QWidget>
#include <QMouseEvent>
#include <QDebug>
#include <QSettings>
#include "measurement.h"
#include "persistable.h"

class HelmWidget : public QWidget, public Persistable
{
    Q_OBJECT


protected:
    Measurement measurement_;

    static quint8 nameNum_;
    QString subjectFilter_;
    QString typeFilter_;

    bool isInEditMode_;

    int x_;
    int y_;
    QPoint oldPos_;


    virtual void setTypeFilter(QString s) {typeFilter_=s;}
    virtual void setSubjectFilter(QString s) {subjectFilter_=s;}

    virtual void setX(int x){ x_=x; move(x_,y_);}
    virtual void setY(int y){ y_=y; move(x_,y_);}
    virtual void setXY(int x, int y){ x_=x; y_=y; move(x_,y_);}



public:
    explicit HelmWidget(QWidget *parent = 0);
    virtual void saveSettings();
    virtual void readSettings();
    virtual void init();
    virtual void showSettingsForm();
    virtual void registerPublisher(QObject*);


    //events
    virtual void mouseDoubleClickEvent(QMouseEvent*);
    virtual void mousePressEvent(QMouseEvent*);
    virtual void mouseMoveEvent(QMouseEvent*);
    virtual void mouseReleaseEvent(QMouseEvent *);
    virtual void resizeEvent(QResizeEvent *);


public slots:
    virtual void newMeasurement(Measurement);

};

#endif // HELMWIDGET_H
