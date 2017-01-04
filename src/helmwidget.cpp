#include "helmwidget.h"
#include <QApplication> //for qApp
#include <QDialog>



quint8 HelmWidget::nameNum_ = 1;

HelmWidget::HelmWidget(QWidget *parent) :
    QWidget(parent) //Qt::FramelessWindowHint)
{
    name_ = QString("helmwidget_") + QString::number(nameNum_);
    nameNum_++;
    isInEditMode_ = false;
    type_ = "HelmWidget";
    resized_ = true;
}

void HelmWidget::init(){
    setWindowFlags(Qt::Window);
    show();
}

void HelmWidget::saveSettings(){
    Persistable::saveSettings();
    qDebug() << "HelmWidget::saveSettings()";
    QSettings settings(Persistable::filename_, QSettings::IniFormat);
    settings.beginGroup(name_);
    settings.setValue("position", pos());
    settings.setValue("size", size());
    settings.setValue("type_filter", parameterFilter_);
    settings.setValue("subject_filter", subjectFilter_);
    settings.sync();
}

void HelmWidget::readSettings(){
    QSettings settings(Persistable::filename_, QSettings::IniFormat);

    settings.beginGroup(name_);
    //qDebug() << name_;

    QPoint pos = settings.value("position", (QPoint(200,200))).toPoint();
    //qDebug() << pos.x() << ", " << pos.y();
    move(pos);

    QSize size = settings.value("size", QSize(200,200)).toSize();
    resize(size);


}
void HelmWidget::registerPublisher(QObject* o)
{
    qDebug() << "Registering Publisher";
    QObject::connect((QObject*)o, SIGNAL(notify(Measurement)),
                     (QObject*)this, SLOT(newMeasurement(Measurement)));
}

void HelmWidget::newMeasurement(Measurement m){
    if ( ( (subjectFilter_ == "") || (m.getSubject() == subjectFilter_))
        && ((parameterFilter_ == "") || (m.getParameter() == parameterFilter_))){
        measurement_ = m;
        update();
    }
}

/*
void HelmWidget :: showSettingsForm(){
  qDebug() << "HelmWidget:showSettingsForm";
   ComponentSettings* cs = new ComponentSettings();
   cs->show();

}
*/
void HelmWidget::mouseReleaseEvent(QMouseEvent*){
    qDebug() << "HelmWidget:mouseReleaseEvent";
    //saveSettings();
    resized_ = true;
}

void HelmWidget::resizeEvent(QResizeEvent *){
    qDebug() << "HelmWidget:resizeEvent";
    //saveSettings();
    if (isInEditMode_){
        resized_ = true;
        repaint();
    } else {

    }

}

void HelmWidget::mouseDoubleClickEvent(QMouseEvent * e){
    qDebug() << "HelmWidget::mouseDoubleClickEvent";

    isInEditMode_ = !isInEditMode_;

    if (isInEditMode_){
        setWindowFlags(Qt::Window | Qt::Tool); //TODO: Keep the no-frame window and just add a pixel frame inside the widget.
        qDebug() << "In edit mode";
    } else {
        saveSettings();
        setWindowFlags(Qt::Window | Qt::Tool); //FramelessWindowHint);
        qDebug() << "Not in edit mode";
    }

    resized_ = true;
    show();
    e->accept();
}

void HelmWidget::mousePressEvent(QMouseEvent* event){
    if (isInEditMode_){
        oldPos_ = event->globalPos();
    }
    qDebug() << "HelmWidget::mousePressedEvent: (" << event->globalX() <<", " << event->globalY() << ")";
}

void HelmWidget::mouseMoveEvent(QMouseEvent* event){
    if (isInEditMode_) {
        resized_ = true;
        const QPoint delta = event->globalPos() - oldPos_;
        move(x()+delta.x(), y()+delta.y());
        oldPos_ = event->globalPos();
    }
}


/*
 * Qt::WindowFlags type = (flags & Qt::WindowType_Mask);
    if (type == Qt::Window) {
        text = "Qt::Window";
    } else if (type == Qt::Dialog) {
        text = "Qt::Dialog";
    } else if (type == Qt::Sheet) {
        text = "Qt::Sheet";
    } else if (type == Qt::Drawer) {
        text = "Qt::Drawer";
    } else if (type == Qt::Popup) {
        text = "Qt::Popup";
    } else if (type == Qt::Tool) {
        text = "Qt::Tool";
    } else if (type == Qt::ToolTip) {
        text = "Qt::ToolTip";
    } else if (type == Qt::SplashScreen) {
        text = "Qt::SplashScreen";
    }

    if (flags & Qt::MSWindowsFixedSizeDialogHint)
        text += "\n| Qt::MSWindowsFixedSizeDialogHint";
    if (flags & Qt::X11BypassWindowManagerHint)
        text += "\n| Qt::X11BypassWindowManagerHint";
    if (flags & Qt::FramelessWindowHint)
        text += "\n| Qt::FramelessWindowHint";
    if (flags & Qt::NoDropShadowWindowHint)
        text += "\n| Qt::NoDropShadowWindowHint";
    if (flags & Qt::WindowTitleHint)
        text += "\n| Qt::WindowTitleHint";
    if (flags & Qt::WindowSystemMenuHint)
        text += "\n| Qt::WindowSystemMenuHint";
    if (flags & Qt::WindowMinimizeButtonHint)
        text += "\n| Qt::WindowMinimizeButtonHint";
    if (flags & Qt::WindowMaximizeButtonHint)
        text += "\n| Qt::WindowMaximizeButtonHint";
    if (flags & Qt::WindowCloseButtonHint)
        text += "\n| Qt::WindowCloseButtonHint";
    if (flags & Qt::WindowContextHelpButtonHint)
        text += "\n| Qt::WindowContextHelpButtonHint";
    if (flags & Qt::WindowShadeButtonHint)
        text += "\n| Qt::WindowShadeButtonHint";
    if (flags & Qt::WindowStaysOnTopHint)
        text += "\n| Qt::WindowStaysOnTopHint";
    if (flags & Qt::CustomizeWindowHint)
        text += "\n| Qt::CustomizeWindowHint";
*/
