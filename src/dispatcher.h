#ifndef DISPATCHER_H
#define DISPATCHER_H

#include <QObject>
#include <QMutex>
#include "measurement.h"


class Dispatcher : public QObject
{
    Q_OBJECT

protected:
    QMutex* newMeasurementMutex_;

public:
    Dispatcher();
    void registerSubscriber(QObject*);
    void registerPublisher(QObject*);

public slots:
   void newMeasurement(Measurement);

signals:
    void notify(Measurement);
};

#endif // DISPATCHER_H
