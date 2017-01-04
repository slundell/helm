#include "sleekdoublegauge.h"
#include "ui_sleekdoublegaugesettings.h"
#include "sleekdoublegaugesettings.h"
#include <QElapsedTimer>
#include <QtMath>

SleekDoubleGauge::SleekDoubleGauge(HelmWidget *parent)
    : SleekRoundGauge(parent), background_(200,200)

{
    maxAngle_=180;
    type_ = "SleekDoubleGauge";
    avgFPS_=160;
    backgroundValid_ = false;

    update();
}

void SleekDoubleGauge::newMeasurement(Measurement m){
    if ( ( (subjectFilter_ == "") || (m.getSubject() == subjectFilter_))
        && ((parameterFilter_ == "") || (m.getParameter() == parameterFilter_))){

        if ((measurement_.getParameter() != m.getParameter()) || (measurement_.getUnit() != m.getUnit()))
            backgroundValid_ = false;

        measurement_ = m;
        leftValueAge_=0;
        rightValueAge_++;
        update();
    }
    if ( ( (subjectFilterRight_ == "") || (m.getSubject() == subjectFilterRight_))
        && ((parameterFilterRight_ == "") || (m.getParameter() == parameterFilterRight_))){

        if ((measurementRight_.getParameter() != m.getParameter()) || (measurementRight_.getUnit() != m.getUnit()))
            backgroundValid_ = false;

        measurementRight_ = m;
        rightValueAge_=0;
        leftValueAge_++;
        update();
    }
}

void SleekDoubleGauge::save(const QString& name, const QString& leftSubject, const QString& rightSubject, const QString& leftParameter, const QString& rightParameter, double min, double max){
    setName(name);
    subjectFilter_ = leftSubject;
    subjectFilterRight_ = rightSubject;
    parameterFilter_ = leftParameter;
    parameterFilterRight_ = rightParameter;

    minValue_ = min;
    maxValue_ = max;

    isInEditMode_ = true;
    saveSettings();
    show();
}

void SleekDoubleGauge::saveSettings(){

    SleekRoundGauge::saveSettings();
    qDebug() << "SleekDoubleGauge::saveSettings()";
    QSettings settings(Persistable::filename_, QSettings::IniFormat);
    settings.beginGroup(name_);

    settings.setValue("parameter_filter_left", parameterFilter_);
    settings.setValue("parameter_filter_right", parameterFilterRight_);
    settings.setValue("subject_filter_left", subjectFilter_);
    settings.setValue("subject_filter_right", subjectFilterRight_);
    settings.remove("parameter_filter");
    settings.remove("subject_filter");
    settings.sync();
}


void SleekDoubleGauge::readSettings(){
    SleekRoundGauge::readSettings();

    QSettings settings(Persistable::filename_, QSettings::IniFormat);

    settings.beginGroup(name_);

    setParameterFilterLeft(settings.value("parameter_filter_left", "").toString());
    setParameterFilterRight(settings.value("parameter_filter_right", "").toString());
    setSubjectFilterLeft(settings.value("subject_filter_left", "").toString());
    setSubjectFilterRight(settings.value("subject_filter_right", "").toString());

}

void SleekDoubleGauge::showSettingsForm()
{

    SleekDoubleGaugeSettings* s = new SleekDoubleGaugeSettings();
    connect(s, &SleekDoubleGaugeSettings::ok, this, &SleekDoubleGauge::save);
    s->show();


}

double SleekDoubleGauge::angleAt(double value){
  return ((((double)value/((double)maxValue_ - (double)minValue_)) * ((double)maxAngle_- (double)minAngle_) + (double)minAngle_));
}

double SleekDoubleGauge::xcoordLeft(double value, double length)
{
    return length * qCos(qDegreesToRadians(angleAt(value) + 90.0f));
}

double SleekDoubleGauge::ycoordLeft(double value, double length)
{
    return length * qSin(qDegreesToRadians(angleAt(value) + 90.0f));
}

double SleekDoubleGauge::xcoordRight(double value, double length)
{
    return length * qCos(qDegreesToRadians(90.0f - angleAt(value)));
}

double SleekDoubleGauge::ycoordRight(double value, double length)
{
    return length * qSin(qDegreesToRadians(90.0f - angleAt(value)));
}


void SleekDoubleGauge::createBackground(QPainter& /*painter*/){
    //Testa att uppdatera hela widgeten när ett nytt measurement kommer.
    qDebug() << "SleekDoubleGauge::createBackground()";

    background_ = background_.scaled(QSize(width(), height()));

    background_.fill(backgroundColor_);

    QPalette pal = palette();
    pal.setColor(backgroundRole(), backgroundColor_);
    setPalette(pal);

    QPainter painter(&background_);
    painter.setRenderHint(QPainter::Antialiasing);

    painter.translate(background_.width() / 2, background_.height() / 2);
    painter.scale(background_.width() / 200.0, background_.height() / 200.0);

    QFont font = painter.font();
    font.setPixelSize(16);
    font.fromString(fontString_);
    font.setItalic(false);
    painter.setFont(font);

    QPen pen;
    pen.setColor(scaleColor_);
    pen.setWidth(1);
    pen.setCapStyle(Qt::FlatCap);
    painter.setPen(pen);

    painter.drawEllipse(QPointF(0,0), 81, 81);

    for (double i = minValue_; i <= maxValue_; i+=ticsInterval_) {
        painter.drawLine(QPointF(xcoordRight(i, 69),
                         ycoordRight(i, 69)),
                         QPointF(xcoordRight(i, 73),
                         ycoordRight(i, 73)));
        painter.drawLine(QPointF(xcoordLeft(i, 69),
                         ycoordLeft(i, 69)),
                         QPointF(xcoordLeft(i, 73),
                         ycoordLeft(i, 73)));

    }


    QString t = measurement_.getUnit();
    painter.drawText(-80,0,160,60, (Qt::AlignVCenter | Qt::AlignHCenter), t);

    t = measurement_.getParameter();
    painter.drawText(-80,15,160,60, (Qt::AlignVCenter | Qt::AlignHCenter), t);
    backgroundValid_ = true;

}

void SleekDoubleGauge::paintEvent(QPaintEvent *){

    //qDebug() << "void SleekDoubleGauge::paintEvent(QPaintEvent *)";
    QElapsedTimer timer;
    timer.start();

    QPainter painter(this);
    painter.translate(width() / 2, height() / 2);
    int side = qMin(width(), height());
    painter.scale(side / 200.0, side / 200.0);
    painter.setRenderHint(QPainter::Antialiasing);

    if (resized_){
        backgroundValid_ = false;
        resized_ = false;
    }


    if (!backgroundValid_)
        createBackground(painter);



    QRectF source(0, 0, background_.width(), background_.height());
    QRectF target(-100, -100, 200, 200);
    painter.drawPixmap(target, background_, source);

    QVariant var = measurement_.getValue();

    double valLeft = 0;

    bool disableRight=false;
    bool disableLeft=false;

    if (var.canConvert<double>()){
        valLeft = var.toDouble();
    } else {
        qDebug() << "Not a double value" << valLeft;
        disableLeft = true;
    }

    var = measurementRight_.getValue();

    double valRight = 0;

    if (var.canConvert<double>()){
        valRight = var.toDouble();
    } else {
        qDebug() << "Not a double value" << valRight;
        disableRight = true;
    }

    if (leftValueAge_ > 100) disableLeft = true;
    if (rightValueAge_ > 100) disableRight = true;

    if (disableLeft) valLeft = 0;
    if (disableRight) valRight = 0;

     nominalTicsInterval_ = (maxValue_ - minValue_)/12;


     double handAngleLeft = angleAt(valLeft);
     double handAngleRight = angleAt(valRight);


     QPen pen;

     pen.setCapStyle(Qt::FlatCap);
     pen.setWidth(14);

     pen.setColor(scaleDarkColor_);
     painter.setPen(pen);
     painter.drawArc( -90, -90, 180, 180, -(90 + (int)handAngleLeft)*16, -((int)maxAngle_-(int)handAngleLeft)*16);
     painter.drawArc( -90, -90, 180, 180, -(90 - (int)handAngleRight)*16, ((int)maxAngle_-(int)handAngleRight)*16);

     pen.setColor(nominalColor_);
     painter.setPen(pen);
     painter.drawArc( -90, -90, 180, 180, -(90 + (int)handAngleLeft)*16, -((int)minAngle_-(int)handAngleLeft)*16);
     painter.drawArc( -90, -90, 180, 180, +(270 + (int)handAngleRight) * 16, ((int)minAngle_-(int)handAngleRight) * 16);



     pen.setColor(Qt::white); // nominalTickColor_);
     pen.setWidth(1);
     painter.setPen(pen);

     for (double i = minValue_; i <= maxValue_; i+=nominalTicsInterval_) {
         //A lot of unnessicary trigonometry being made here, but it does not seem to have that big impact on perf.
         if (i < valLeft)
            pen.setColor(nominalTickColor_);
         else
            pen.setColor(scaleDarkerColor_);

         painter.setPen(pen);

         painter.drawLine(QPointF(xcoordLeft(i, 84),
                          ycoordLeft(i, 84)),
                          QPointF(xcoordLeft(i,97),
                          ycoordLeft(i,97)));


         if (i < valRight)
            pen.setColor(nominalTickColor_);
         else
            pen.setColor(scaleDarkerColor_);

         painter.setPen(pen);

         painter.drawLine(QPointF(xcoordRight(i, 84),
                          ycoordRight(i, 84)),
                          QPointF(xcoordRight(i,97),
                          ycoordRight(i,97)));


     }


     pen.setWidth(1);
     pen.setColor(textColor_);
     painter.setPen(pen);


     double val=0;
     if ((!disableLeft) && (!disableRight)){
         if (!(((valLeft / valRight) > 1.15) || (valRight / valLeft) > 1.15)){
             val = (valLeft + valRight ) / 2;


             double diffPct;
             if (val == 0){
                diffPct = 0;
             } else {
                diffPct = 100 * (valLeft - valRight ) / val;
             }

             double maxIndicatorPct = 5;
             double diffAngle = -90 * diffPct/maxIndicatorPct;

             if (diffAngle > +160) diffAngle =  160;
             if (diffAngle < -160) diffAngle = -160;

             pen.setCapStyle(Qt::FlatCap);
             pen.setWidth(5);
             pen.setColor(nominalColor_);
             painter.setPen(pen);
             int size = 77;
             painter.drawArc( -size, -size, 2*size, 2*size, 90 * 16, ((int)diffAngle)*16);


        }

    } else {
        if (disableLeft) {
             val = valRight;
        }
        if (disableRight) {
             val = valLeft;
        }
    }

    if (((valLeft / valRight) > 1.25) || (valRight / valLeft) > 1.25){
        QFont font = painter.font();
        font.setPixelSize(32);
        font.fromString(fontString_);
        font.setItalic(true);
        painter.setFont(font);

        pen.setColor(scaleColor_);
        painter.setPen(pen);

        QString t;
        QString formatString = QString("%.") + QString::number(decimalPlaces_) + "f";
        QByteArray ba = formatString.toLatin1();
        const char *formatCharArr = ba.data();
        t = t.asprintf(formatCharArr, valLeft);
        painter.drawText(-60,-45,120,70, (Qt::AlignLeft | Qt::AlignTop), t);

        formatString = QString("%.") + QString::number(decimalPlaces_) + "f";
        ba = formatString.toLatin1();
        formatCharArr = ba.data();
        t = t.asprintf(formatCharArr, valRight);
        painter.drawText(-60,-45,120,70, (Qt::AlignRight | Qt::AlignBottom), t);

    } else {
       QFont font = painter.font();
       font.setPixelSize(56);
       font.fromString(fontString_);
       font.setItalic(true);
       painter.setFont(font);

       pen.setColor(scaleColor_);
       painter.setPen(pen);

       QString t;
       QString formatString = QString("%.") + QString::number(decimalPlaces_) + "f";
       QByteArray ba = formatString.toLatin1();
       const char *formatCharArr = ba.data();
       t = t.asprintf(formatCharArr, val);
       painter.drawText(-80,-64,160,120, (Qt::AlignVCenter | Qt::AlignHCenter), t);
    }

    /**********************************************/
    double FPS = 1000000000 / timer.nsecsElapsed();
    avgFPS_ = (avgFPS_ + 0.01*(FPS-avgFPS_));
    qDebug() << "SleekDoubleGauge::paintEvent fps:" << avgFPS_;
    return;
    /**********************************************/


}

void SleekDoubleGauge::oldPaintEvent(QPaintEvent *)
 {
    //qDebug() << "void SleekDoubleGauge::paintEvent(QPaintEvent *)";
    QElapsedTimer timer;
    timer.start();

    QVariant var = measurement_.getValue();

    double valLeft = 0;

    bool disableRight=false;
    bool disableLeft=false;

    if (var.canConvert<double>()){
        valLeft = var.toDouble();
    } else {
        qDebug() << "Not a double value" << valLeft;
        disableLeft = true;
    }

    var = measurementRight_.getValue();

    double valRight = 0;

    if (var.canConvert<double>()){
        valRight = var.toDouble();
    } else {
        qDebug() << "Not a double value" << valRight;
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



     double val=0;
     if ((!disableLeft) && (!disableRight)){
         if (!(((valLeft / valRight) > 1.25) || (valRight / valLeft) > 1.25)){
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
        }
         //qDebug() << diffPct;
    } else {
        if (disableLeft) {
             val = valRight;
        }
        if (disableRight) {
             val = valLeft;
        }
    }

    if (((valLeft / valRight) > 1.25) || (valRight / valLeft) > 1.25){
        QFont font = painter.font();
        font.setPixelSize(32);
        font.fromString(fontString_);
        font.setItalic(true);
        painter.setFont(font);

        QString t;
        QString formatString = QString("%.") + QString::number(decimalPlaces_) + "f";
        QByteArray ba = formatString.toLatin1();
        const char *formatCharArr = ba.data();
        t = t.asprintf(formatCharArr, valLeft);
        painter.drawText(-60,-35,120,70, (Qt::AlignLeft | Qt::AlignTop), t);

        formatString = QString("%.") + QString::number(decimalPlaces_) + "f";
        ba = formatString.toLatin1();
        formatCharArr = ba.data();
        t = t.asprintf(formatCharArr, valRight);
        painter.drawText(-60,-35,120,70, (Qt::AlignRight | Qt::AlignBottom), t);

    } else {
       QFont font = painter.font();
       font.setPixelSize(56);
       font.fromString(fontString_);
       font.setItalic(true);
       painter.setFont(font);
       QString t;
       QString formatString = QString("%.") + QString::number(decimalPlaces_) + "f";
       QByteArray ba = formatString.toLatin1();
       const char *formatCharArr = ba.data();
       t = t.asprintf(formatCharArr, val);
       painter.drawText(-80,-60,160,120, (Qt::AlignVCenter | Qt::AlignHCenter), t);
    }
    QFont font = painter.font();
     font.setPixelSize(16);
     font.fromString(fontString_);
     font.setItalic(false);
     painter.setFont(font);

     QString t = measurement_.getUnit();
     painter.drawText(-80,0,160,60, (Qt::AlignVCenter | Qt::AlignHCenter), t);

     t = measurement_.getParameter();
     painter.drawText(-80,15,160,60, (Qt::AlignVCenter | Qt::AlignHCenter), t);

     qDebug() << "SleekDoubleGauge::paintEvent execution time:" << timer.elapsed() << "ms";

 }
