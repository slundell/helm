#include "roundgauge.h"
#include <cmath>

RoundGauge::RoundGauge(HelmWidget *parent)
     : HelmWidget(parent), measurement_(), minValue_(0), maxValue_(4500), nominalValue_(1800), criticalValue_(3000), minAngle_(60), maxAngle_(300), ticsInterval_(250)
{
    setWindowTitle(tr("Gauge"));
    decimalPlaces_ = 0;

}

void RoundGauge::saveSettings(){

    HelmWidget::saveSettings();

    QSettings settings("helm.ini", QSettings::IniFormat);
    settings.beginGroup(name_);

    settings.setValue("max", maxValue_);
    settings.setValue("min", minValue_);
    settings.setValue("critical", criticalValue_);
    settings.setValue("nominal", nominalValue_);
    settings.setValue("tics_interval", ticsInterval_);
    settings.setValue("decimal_places", decimalPlaces_);
}


void RoundGauge::readSettings(){
    HelmWidget::readSettings();

    QSettings settings("helm.ini", QSettings::IniFormat);

    settings.beginGroup(name_);
    setMax(settings.value("max").toDouble());
    setMin(settings.value("min").toDouble());
    setCritical(settings.value("critical").toDouble());
    setNominal(settings.value("nominal").toDouble());
    setTicsInterval(settings.value("tics_interval").toDouble());
    setDecimalPlaces(settings.value("decimal_places").toDouble());
}

void RoundGauge::registerPublisher(QObject* o)
{
    qDebug() << "Registering Publisher";
    QObject::connect((QObject*)o, SIGNAL(notify(Measurement)),
                     (QObject*)this, SLOT(newMeasurement(Measurement)));
}

void RoundGauge::newMeasurement(Measurement m){
    if ( ( (subjectFilter_ == "") || (m.getSubject() == subjectFilter_))
        && ((typeFilter_ == "") || (m.getType() == typeFilter_))){
        measurement_ = m;
        update();
    }
}

void RoundGauge::paintEvent(QPaintEvent *)
 {

    QVariant var = measurement_.getValue();

    double val = 0;

    if (var.canConvert<double>())
        val = var.toDouble();

    static const QPointF hand[3] = {
         QPointF( 4, 15),

         QPointF(-4, 15),
         QPointF( 0, -80)
     };


     double ticsAngle = (maxAngle_ - minAngle_) / ((maxValue_ - minValue_)/ticsInterval_);
     double labelsAngle = (maxAngle_ - minAngle_) / ((maxValue_ - minValue_)/labelsInterval_);
     double criticalAngle =  (criticalValue_/(maxValue_-minValue_)*(maxAngle_-minAngle_))+minAngle_;
     double nominalAngle =  (nominalValue_/(maxValue_-minValue_)*(maxAngle_-minAngle_))+minAngle_;

     QColor handColor(255, 50, 50);
     QColor scaleColor(255, 255, 255);
     QColor textColor(255, 255, 255);
     QColor criticalColor(255, 0, 0);
     QColor nominalColor(0, 255, 0);
     QColor backgroundColor(0,0,0);

     int side = qMin(width(), height());


     QPainter painter(this);

     QPalette pal = palette();
     pal.setColor(backgroundRole(), backgroundColor);
     setPalette(pal);


     painter.setRenderHint(QPainter::Antialiasing);
     painter.translate(width() / 2, height() / 2);
     painter.scale(side / 200.0, side / 200.0);

     painter.setPen(Qt::NoPen);
     painter.setBrush(handColor);

     painter.save();
//     measurement_.set_value(minValue_);
//     measurement_.set_value(maxValue_);
//     measurement_.set_value(minValue_+ticsInterval_);
     double handAngle = ((double)val/((double)maxValue_ - (double)minValue_)) * ((double)maxAngle_- (double)minAngle_) + (double)minAngle_;
//     handAngle = 180;

     //qDebug() << "Hand rotation: " << handAngle;


     painter.rotate(handAngle + 180.0);
     painter.drawConvexPolygon(hand, 3);
     painter.restore();

     QPen pen;
     pen.setWidth(1);
     pen.setColor(scaleColor);
     painter.setPen(pen);

     painter.drawArc( -96, -96, 192, 192, -((int)minAngle_ + 90)*16, -((int)maxAngle_-(int)minAngle_)*16);


     pen.setWidth(4);

     pen.setColor(nominalColor);
     painter.setPen(pen);
     painter.drawArc( -96, -96, 192, 192, -(90 + (int)nominalAngle)*16, -((int)maxAngle_-(int)nominalAngle)*16);

     pen.setColor(criticalColor);
     painter.setPen(pen);
     painter.drawArc( -96, -96, 192, 192, -(90 + (int)criticalAngle)*16, -((int)maxAngle_-(int)criticalAngle)*16);


     painter.save();
     painter.setPen(scaleColor);

     painter.rotate(minAngle_ + 90);


     for (double i = minValue_; i <= maxValue_; i+=ticsInterval_) {
         painter.drawLine(88, 0, 96, 0);
         painter.rotate(ticsAngle);

     }
     painter.restore();

     painter.save();
     painter.setPen(scaleColor);
     //painter.rotate(90);
     double offset = 75;
     double a = minAngle_+90;
     for (double i = minValue_; i <= maxValue_; i+=labelsInterval_) {

         QString s = QString::number(i);
         double x = offset * cos(a/360.0*2*3.14);
         double y = offset * sin(a/360.0*2*3.14);
         painter.drawText(x-25, y-10, 50, 20, (Qt::AlignVCenter | Qt::AlignHCenter),  s);
         a += labelsAngle;
     }
     painter.restore();

     pen.setWidth(1);
     pen.setColor(textColor);
     painter.setPen(pen);
     QString t = measurement_.getValue().toString()+" "+measurement_.getUnit();
     painter.drawText(-100,0,200,100, (Qt::AlignVCenter | Qt::AlignHCenter) , t);

 }


void RoundGauge :: showSettingsForm(){
    /*
    QDialog *widget = new QDialog;
    Ui::DialInstrumentSetup ui;
    ui.setupUi(widget);
    widget->show();
    */
}
