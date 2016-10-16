#include "persistable.h"
#include <QDebug>
#include <QSettings>
#include <QMetaObject>


const QString Persistable::filename_ = "helm.ini";

Persistable::Persistable()
{

}



void Persistable::saveSettings(){
    qDebug() << "Persistable::saveSettings()";
    QSettings settings(Persistable::filename_, QSettings::IniFormat);
    settings.beginGroup(name_);
    settings.setValue("type", type_);
}
