#include "sleekdoublegauge.h"

SleekDoubleGauge::SleekDoubleGauge(QWidget *parent) : SleekRoundGauge(parent)
{
    maxAngle_=180;
    update();
}

void SleekDoubleGauge::newMeasurement(Measurement m){
    if ( ( (subjectFilter_ == "") || (m.getSubject() == subjectFilter_))
        && ((typeFilter_ == "") || (m.getType() == typeFilter_))){
        measurement_ = m;
        leftValueAge_=0;
        rightValueAge_++;
        update();
    }
    if ( ( (subjectFilterRight_ == "") || (m.getSubject() == subjectFilterRight_))
        && ((typeFilterRight_ == "") || (m.getType() == typeFilterRight_))){
        measurementRight_ = m;
        rightValueAge_=0;
        leftValueAge_++;
        update();
    }
}


void SleekDoubleGauge::paintEvent(QPaintEvent *)
 {
    //qDebug() << "void SleekDoubleGauge::paintEvent(QPaintEvent *)";

    QVariant var = measurement_.getValue();

    double valLeft = 0;

    bool disableRight=false;
    bool disableLeft=false;

    if (var.canConvert<double>()){
        valLeft = var.toDouble();
    } else {
        qDebug() << "Not a double value";
        disableLeft = true;
    }

    var = measurementRight_.getValue();

    double valRight = 0;

    if (var.canConvert<double>()){
        valRight = var.toDouble();
    } else {
        qDebug() << "Not a double value";
        disableRight = true;
    }

    if (leftValueAge_ > 100) disableLeft = true;
    if (rightValueAge_ > 100) disableRight = true;

    if (disableLeft) valLeft = 0;
    if (disableRight) valRight = 0;


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



     double handAngleLeft = ((double)valLeft/((double)maxValue_ - (double)minValue_)) * ((double)maxAngle_- (double)minAngle_) + (double)minAngle_;

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
     painter.drawArc( -90, -90, 180, 180, -(90 + (int)handAngleLeft)*16, -((int)maxAngle_-(int)handAngleLeft)*16);

     pen.setColor(nominalColor_);
     pen.setWidth(14);

     //pen.setColor(nominalColor);
     pen.setCapStyle(Qt::FlatCap);
     painter.setPen(pen);
     painter.drawArc( -90, -90, 180, 180, -(90 + (int)handAngleLeft)*16, -((int)minAngle_-(int)handAngleLeft)*16);

     painter.save();
     pen.setColor(nominalTickColor_);
     pen.setWidth(1);
     pen.setCapStyle(Qt::FlatCap);
     painter.setPen(pen);

     painter.rotate(minAngle_ + 90);
     for (double i = minValue_; i <= maxValue_; i+=nominalTicsInterval_) {


         if (i <= valLeft)
            pen.setColor(nominalTickColor_);
         else
            pen.setColor(scaleDarkerColor_);
         painter.setPen(pen);

         painter.drawLine(83, 0, 97, 0);
         painter.rotate(nominalTicsAngle);

     }

     painter.restore();



     painter.save();
     pen.setColor(scaleColor_);
     painter.setPen(pen);
     painter.rotate(minAngle_ + 90);


     for (double i = minValue_; i <= maxValue_; i+=ticsInterval_) {
         painter.drawLine(69, 0, 73, 0);
         painter.rotate(ticsAngle);
     }

     painter.restore();


     // right scale


     double handAngleRight = ((double)valRight/((double)maxValue_ - (double)minValue_)) * ((double)maxAngle_- (double)minAngle_) + (double)minAngle_;

     pen.setWidth(1);
     pen.setCapStyle(Qt::FlatCap);
     pen.setColor(scaleColor_);
     painter.setPen(pen);

     painter.drawEllipse(QPointF(0,0), 81, 81);


     pen.setColor(scaleDarkColor_);
     pen.setWidth(14);

     pen.setCapStyle(Qt::FlatCap);
     painter.setPen(pen);
     painter.drawArc( -90, -90, 180, 180, -(90 - (int)handAngleRight)*16, ((int)maxAngle_-(int)handAngleRight)*16);

     pen.setColor(nominalColor_);
     pen.setWidth(14);

     pen.setCapStyle(Qt::FlatCap);
     painter.setPen(pen);
     painter.drawArc( -90, -90, 180, 180, +(270 + (int)handAngleRight) * 16, ((int)minAngle_-(int)handAngleRight) * 16);

     painter.save();
     pen.setColor(nominalTickColor_);
     pen.setWidth(1);
     pen.setCapStyle(Qt::FlatCap);
     painter.setPen(pen);

     painter.rotate(90 - minAngle_);
     for (double i = minValue_; i <= maxValue_; i+=nominalTicsInterval_) {

         if (i <= valRight)
            pen.setColor(nominalTickColor_);
         else
            pen.setColor(scaleDarkerColor_);
         painter.setPen(pen);

         painter.drawLine(83, 0, 97, 0);
         painter.rotate(-nominalTicsAngle);

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
     painter.rotate(90 - minAngle_);


     for (double i = minValue_; i <= maxValue_; i+=ticsInterval_) {
         painter.drawLine(69, 0, 73, 0);
         painter.rotate(-ticsAngle);
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

     double val;
     if ((!disableLeft) && (!disableRight)){
         val = (valLeft + valRight ) / 2;


         double diffPct;
         if (val == 0){
            diffPct = 0;
         } else {
            diffPct = 100 * (valLeft - valRight ) / val;
         }

         double maxIndicatorPct = 25;
         double diffAngle = 90 * diffPct/maxIndicatorPct;

         if (diffAngle > 90)  diffAngle =  90;
         if (diffAngle < -90) diffAngle = -90;
         painter.save();

         QTransform transform;
         transform.translate(width() / 2, height() / 2);
         transform.scale(side / 200.0, side / 200.0);
         transform.translate(0, -40);
         transform.rotate(diffAngle);
         painter.setTransform(transform);
         painter.drawLine(-20, 0, 20, 0);
         painter.setBrush(scaleColor_);
         painter.drawEllipse(QPoint(-20, 0), 2, 2);
         painter.drawEllipse(QPoint(+20, 0), 2, 2);
         painter.restore();

         //qDebug() << diffPct;
    } else {
        if (disableLeft) {
             val = valRight;
        }
        if (disableRight) {
             val = valLeft;
        }
    }

     QString t;
     QString formatString = QString("%.") + QString::number(decimalPlaces_) + "f";
     QByteArray ba = formatString.toLatin1();
     const char *formatCharArr = ba.data();
     t = t.asprintf(formatCharArr, val);
     //qDebug() << t;
     painter.drawText(-80,-60,160,120, (Qt::AlignVCenter | Qt::AlignHCenter), t);


     font.setPixelSize(16);
     font.fromString(fontString_);
     font.setItalic(false);
     painter.setFont(font);

     t = measurement_.getUnit();
     painter.drawText(-80,10,160,60, (Qt::AlignVCenter | Qt::AlignHCenter), t);


 }
