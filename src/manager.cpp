#include "manager.h"
#include <QSettings>
#include <QDebug>
#include "sleekdoublegauge.h"
#include "roundgauge.h"
#include "sleekroundgauge.h"


QVector<Persistable*> Manager::persistables_;
Dispatcher Manager::dispatcher_;

Manager::Manager(QObject *parent) : QObject(parent)
{

}



void Manager::load(const QString &name){
    qDebug() << "PersistanceManager::load(" << name << ")";
    QSettings settings("helm.ini", QSettings::IniFormat);
    settings.beginGroup(name);
    QString type = settings.value("type").toString();

    if (type == "SleekDoubleGauge"){
        SleekDoubleGauge* s = new SleekDoubleGauge();
        s->setName(name);
        s->readSettings();
        dispatcher_.registerSubscriber(s);
        persistables_.push_back(s);
    } else if (type == "SleekRoundGauge"){
        SleekRoundGauge* s = new SleekRoundGauge();
        s->setName(name);
        s->readSettings();
        dispatcher_.registerSubscriber(s);
        persistables_.push_back(s);

    } else if (type == "RoundGauge"){
        RoundGauge* r = new RoundGauge();
        r->setName(name);
        r->readSettings();
        dispatcher_.registerSubscriber(r);
        persistables_.push_back(r);

    } else {
        qDebug() << "Could not load" << name << "since type" << type << "is unknown";
        return;
    }

}

void Manager::loadAll(){
    qDebug() << "PersistableFactory::createAll()";
    QSettings settings("helm.ini", QSettings::IniFormat);
    QStringList groups = settings.childGroups();
    qDebug() << groups;

    for (quint16 i=0; i < groups.size(); ++i){
        Manager::load(groups[i]);

    }

}

void Manager::initAll(){
    for(quint16 i=0; i<persistables_.size(); ++i){
        persistables_[i]->init();
    }
}
