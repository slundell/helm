#ifndef MEASUREMENT_H
#define MEASUREMENT_H

#include <QMetaType>
#include <QString>
#include <QVariant>


class ValueType;
class Measurement
{

private:
    QString subject_; // Air, water, engine 1, engine 2...
    QString type_;    // Temperature, pressure, COG...
    QVariant value_;    // The actual measurement
    double precision_;
    QString unit_;    // Celcius, per minute, hPa
    QString message_; // Error etc...

public:
    Measurement(){}
    Measurement(QString s, QString t, QVariant v, double p, QString u, QString m = "") :
            subject_(s), type_(t), value_(v), precision_(p), unit_(u), message_(m) { }

    void setSubject(QString s) { subject_ = s; }
    void setType(QString t) { type_ = t; }
    void setUnit(QString u) { unit_ = u; }
    void setMessage(QString m){ message_ = m; }
    void setValue(const QVariant& v){ value_ = v; }
    void setPrecision(double p){ precision_ = p; }

    QString getSubject() const { return subject_; }
    QString getUnit() const { return unit_; }
    QString getType() const { return type_; }
    QString getMessage() const { return message_; }
    QVariant getValue() const { return value_; }
    double getPrecision() const { return precision_; }

};

Q_DECLARE_METATYPE(Measurement)

enum NS {N, S};
enum EW {E, W};
class GeoPos{
    double long_;
    double lat_;
    NS long_dir_;
    EW lat_dir;
};



#endif // MEASUREMENT_H
