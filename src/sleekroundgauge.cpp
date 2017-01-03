#include "sleekroundgauge.h"
#include "sleekroundgaugesettings.h"

SleekRoundGauge::SleekRoundGauge(HelmWidget *parent) : RoundGauge(parent)
{
    nominalTicsInterval_ = 10; //if not a positive value, the for-loop below will be infinite
    scaleColor_ = QColor(255, 255, 255);
    scaleDarkColor_ = QColor(2, 5, 6);
    scaleDarkerColor_ = QColor(0, 0, 2);
    textColor_ = QColor(250, 250, 250);
    nominalColor_ = QColor(0, 45, 97);
    nominalTickColor_ = QColor(5, 50, 102);
    backgroundColor_ = QColor(0,0,2);

    fontString_ = "Lato Thin";

    type_ = "SleekRoundGauge";
}


void SleekRoundGauge::save(const QString& name, const QString& subject, const QString& parameter, double min, double max){
    setName(name);
    subjectFilter_ = subject;
    parameterFilter_ = parameter;

    minValue_ = min;
    maxValue_ = max;

    isInEditMode_ = true;
    saveSettings();
    show();
}

void SleekRoundGauge::showSettingsForm(){

    SleekRoundGaugeSettings* s = new SleekRoundGaugeSettings();
    connect(s, &SleekRoundGaugeSettings::ok, this, &SleekRoundGauge::save);
    s->show();
}

void SleekRoundGauge::paintEvent(QPaintEvent *)
 {

    QVariant var = measurement_.getValue();

    double val = 0;

    if (var.canConvert<double>()){
        val = var.toDouble();
    } else {
        return;
    }




     double ticsAngle = (maxAngle_ - minAngle_) / ((maxValue_ - minValue_)/ticsInterval_);
     double nominalTicsAngle = (maxAngle_ - minAngle_) / ((maxValue_ - minValue_)/nominalTicsInterval_);
     /*double criticalAngle =  (criticalValue_/(maxValue_-minValue_)*(maxAngle_-minAngle_))+minAngle_;
     double nominalAngle =  (nominalValue_/(maxValue_-minValue_)*(maxAngle_-minAngle_))+minAngle_;*/

     int side = qMin(width(), height());


     QPainter painter(this);

     QPalette pal = palette();
     pal.setColor(backgroundRole(), backgroundColor_);
     setPalette(pal);


     painter.setRenderHint(QPainter::Antialiasing);
     painter.translate(width() / 2, height() / 2);
     painter.scale(side / 200.0, side / 200.0);


     //for pos = min to pos < value; pos += tickInterval


//     measurement_.set_value(minValue_);
//     measurement_.set_value(maxValue_);
//     measurement_.set_value(minValue_+ticsInterval_);
     double handAngle = ((double)val/((double)maxValue_ - (double)minValue_)) * ((double)maxAngle_- (double)minAngle_) + (double)minAngle_;
//     handAngle = 180;

     //qDebug() << "Hand rotation: " << handAngle;

/*
     painter.rotate(handAngle + 180.0);
     painter.drawConvexPolygon(hand, 3);
     painter.restore();
*/
     QPen pen;
     pen.setWidth(1);
     pen.setCapStyle(Qt::FlatCap);
     pen.setColor(scaleColor_);
     painter.setPen(pen);

     painter.drawEllipse(QPointF(0,0), 81, 81);


     pen.setColor(scaleDarkColor_);
     pen.setWidth(14);

     //pen.setColor(nominalColor);
     pen.setCapStyle(Qt::FlatCap);
     painter.setPen(pen);
     painter.drawArc( -90, -90, 180, 180, -(90 + (int)handAngle)*16, -((int)maxAngle_-(int)handAngle)*16);

     pen.setColor(nominalColor_);
     pen.setWidth(14);

     //pen.setColor(nominalColor);
     pen.setCapStyle(Qt::FlatCap);
     painter.setPen(pen);
     painter.drawArc( -90, -90, 180, 180, -(90 + (int)handAngle)*16, -((int)minAngle_-(int)handAngle)*16);

     painter.save();
     pen.setColor(nominalTickColor_);
     pen.setWidth(1);
     pen.setCapStyle(Qt::FlatCap);
     painter.setPen(pen);

     painter.rotate(minAngle_ + 90);
     for (double i = minValue_; i <= maxValue_; i+=nominalTicsInterval_) {


         if (i <= val)
            pen.setColor(nominalTickColor_);
         else
            pen.setColor(scaleDarkerColor_);
         painter.setPen(pen);

         painter.drawLine(83, 0, 97, 0);
         painter.rotate(nominalTicsAngle);

     }

     painter.restore();
/*
     pen.setColor(criticalColor);
     painter.setPen(pen);
     painter.drawArc( -96, -96, 192, 192, -(90 + (int)criticalAngle)*16, -((int)maxAngle_-(int)criticalAngle)*16);
*/

     painter.save();
     pen.setColor(scaleColor_);
     painter.setPen(pen);
     painter.rotate(minAngle_ + 90);


     for (double i = minValue_; i <= maxValue_; i+=ticsInterval_) {
         painter.drawLine(69, 0, 73, 0);
         painter.rotate(ticsAngle);
     }

     painter.restore();

     pen.setWidth(1);
     pen.setColor(textColor_);
     painter.setPen(pen);

     QFont font = painter.font();
     font.setPixelSize(56);
     font.fromString(fontString_);
     font.setItalic(true);
     painter.setFont(font);

     QString t;
     QString formatString = QString("%.") + QString::number(decimalPlaces_) + "f";
     QByteArray ba = formatString.toLatin1();
     const char *formatCharArr = ba.data();
     t = t.asprintf(formatCharArr, measurement_.getValue().toDouble());
     qDebug() << t;
     painter.drawText(-80,-60,160,120, (Qt::AlignVCenter | Qt::AlignHCenter), t);


     font.setPixelSize(16);
     font.fromString(fontString_);
     font.setItalic(false);
     painter.setFont(font);

     t = measurement_.getUnit();
     painter.drawText(-80,10,160,60, (Qt::AlignVCenter | Qt::AlignHCenter), t);


 }
