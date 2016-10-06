#include "measurementlogger.h"
#include <QDebug>
MeasurementLogger::MeasurementLogger(const QString & filename)
{
    QFile file(filename);
    if (file.open(QFile::WriteOnly | QFile::Append)) {
        stream_.setDevice(&file);
        qDebug() << "Opened OK: "<<filename<<stream_.device();
    }
    else
    {
        qDebug() << "error opening file "<<filename;

    }
}

void MeasurementLogger::newMeasurement(Measurement m)
{
   //qDebug() << "Logging: " << m.getSubject() << " " << m.getType();

   stream_ << m.getSubject() << " ";
   stream_ << m.getType() << " ";

   QVariant v = m.getValue();
   if (v.canConvert(QVariant::Int))
       stream_ << v.toInt() << " ";
   else if (v.canConvert(QVariant::Double))
       stream_ << v.toDouble() << " ";
   else if (v.canConvert(QVariant::String))
       stream_ << v.toString() << " ";


   stream_ << m.getPrecision() << " ";
   stream_ << m.getUnit() << " ";
   stream_ << m.getMessage();
   stream_ << endl << flush;

}

void MeasurementLogger::registerPublisher(QObject* o)
{
    QObject::connect((QObject*)o, SIGNAL(notify(Measurement)),
                     (QObject*)this, SLOT(newMeasurement(Measurement)));
}
