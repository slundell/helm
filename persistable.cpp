#include "persistable.h"
#include <QDebug>
#include <QSettings>
#include <QMetaObject>

Persistable::Persistable()
{

}



void Persistable::saveSettings(){
    qDebug() << "Persistable::saveSettings()";
    QSettings settings("helm.ini", QSettings::IniFormat);
    settings.beginGroup(name_);
    settings.setValue("type", type_);
}
