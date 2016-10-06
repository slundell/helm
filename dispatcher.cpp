#include "dispatcher.h"
#include <QMetaType>
#include <QDebug>

Dispatcher::Dispatcher()
{
    qDebug() << "Constructing MeasurementDispatcher";
    newMeasurementMutex_ = new QMutex();

}

void Dispatcher::registerSubscriber(QObject* o)
{
    qDebug() << "Registering Subscriber";
    QObject::connect((QObject*)this, SIGNAL(notify(Measurement)),
                     (QObject*)o, SLOT(newMeasurement(Measurement)));
}

void Dispatcher::registerPublisher(QObject* o)
{
    qDebug() << "Registering Publisher";
    QObject::connect((QObject*)o, SIGNAL(notify(Measurement)),
                     (QObject*)this, SLOT(newMeasurement(Measurement)));
}

void Dispatcher::newMeasurement(Measurement m)
{
    QMutexLocker ml(newMeasurementMutex_);
    //qDebug() << "Dispatcher recieve: " << m.getValue();
    emit notify(m);
}
