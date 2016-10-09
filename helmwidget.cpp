#include "helmwidget.h"

quint8 HelmWidget::nameNum_ = 1;

HelmWidget::HelmWidget(QWidget *parent) :
    QWidget(parent, Qt::FramelessWindowHint)
{
    name_ = QString("helmwidget_") + QString::number(nameNum_);
    nameNum_++;

    readSettings();
}

HelmWidget::~HelmWidget(){
    saveSettings();
}

void HelmWidget::saveSettings(){
    QSettings settings("helm.ini", QSettings::IniFormat);
    settings.beginGroup(name_);
    settings.setValue("position", pos());
    settings.setValue("size", size());
}

void HelmWidget::readSettings(){
    QSettings settings("helm.ini", QSettings::IniFormat);

    settings.beginGroup(name_);
    //qDebug() << name_;

    QPoint pos = settings.value("position").toPoint();
    //qDebug() << pos.x() << ", " << pos.y();
    move(pos);

    QSize size = settings.value("size").toSize();
    resize(size);


}

void HelmWidget::mouseReleaseEvent(QMouseEvent*){
    qDebug() << "HelmWidget:mouseReleaseEvent";
    saveSettings();
}

void HelmWidget::resizeEvent(QResizeEvent*){
    qDebug() << "HelmWidget:resizeEvent";
    saveSettings();
    repaint();

}


void HelmWidget::mousePressEvent(QMouseEvent* event){
    oldPos = event->globalPos();
    qDebug() << "HelmWidget::mousePressedEvent: (" << event->globalX() <<", " << event->globalY() << ")";
}

void HelmWidget::mouseMoveEvent(QMouseEvent* event){

    const QPoint delta = event->globalPos() - oldPos;
    move(x()+delta.x(), y()+delta.y());
    oldPos = event->globalPos();
    //move(event->globalPos());
}
