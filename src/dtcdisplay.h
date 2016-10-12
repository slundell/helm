#ifndef DTCDISPLAY_H
#define DTCDISPLAY_H

#include <QWidget>
#include <QLabel>
#include <QDebug>
#include <QPainter>
#include <QMessageBox>

#include "measurement.h"

class DTCDisplay : public QObject
{
    Q_OBJECT
private:
    Measurement measurement_;

    QString subjectFilter_;
    QString typeFilter_;
    QStringList activeMsgBoxDTCs_;
    QStringList ignoreDTCs_;

    QString winTitle_;
    QMessageBox msgBox_;

public:
    DTCDisplay();

    virtual void setWinTitle(QString s) {winTitle_=s;}
    virtual void setTypeFilter(QString s) {typeFilter_=s;}
    virtual void setSubjectFilter(QString s) {subjectFilter_=s;}
    virtual void showSettingsForm();
    virtual void registerPublisher(QObject*);

    virtual void registerDTCResetter(QObject*);


public slots:
    virtual void newMeasurement(Measurement);

signals:
    void resetAllDTCs();

};


#endif // DTCDISPLAY_H
