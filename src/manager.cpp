#include "manager.h"
#include <QSettings>
#include <QDebug>
#include "sleekdoublegauge.h"
#include "roundgauge.h"
#include "sleekroundgauge.h"
#include "measurementgenerator.h"


//define static variables
QVector<Persistable*> Manager::persistables_;
Dispatcher Manager::dispatcher_;
SettingsWindow* Manager::settingsWindow_;
Manager* Manager::instance_;

Manager::Manager(QObject *parent) : QObject(parent)
{
    qDebug() << "Manager::Manager(QObject *parent)";

}

Manager *Manager::instance()
{
    if (!instance_)
              instance_ = new Manager();
    return instance_;
}

Manager::~Manager()
{
    for(quint16 i=0; i<persistables_.size(); ++i){
        delete persistables_[i];
    }
}


void Manager::init(){
    initUI();
}

void Manager::initUI(){
    settingsWindow_ = new SettingsWindow();
    if (!instance_)
        qDebug() << "Instance not inited";



    if (!settingsWindow_)
        qDebug() << "settingsWindow not inited";
    if (!connect(settingsWindow_, &SettingsWindow::createNew, instance_, &Manager::onCreateNew))
        qDebug() << "Error connecting";
    connect(settingsWindow_, &SettingsWindow::close, instance_, &Manager::onSave);
    connect(settingsWindow_, &SettingsWindow::edit, instance_, &Manager::onEdit);
    connect(settingsWindow_, &SettingsWindow::deleteIt, instance_, &Manager::onDelete);

    connect(this, &Manager::createdNew, settingsWindow_, &SettingsWindow::onComponentAdded);
    connect(this, &Manager::deleted, settingsWindow_, &SettingsWindow::onComponentDeleted);

}

void Manager::showUI(){
    if (settingsWindow_)
        settingsWindow_->show();
}

void Manager::deleteComponent(const QString & c)
{
    for (quint16 i=0; i<persistables_.size(); ++i){
        if (persistables_[i]->getName() == c){
            delete persistables_[i];
            persistables_.remove(i);

            emit deleted(c);
        }

    }
    saveAll();
    QSettings settings(Persistable::filename_, QSettings::IniFormat);
    settings.remove(c);
    settings.sync();
}

void Manager::onCreateNew()
{
    qDebug() << "Manager::createNewSlot";
    QString type = "SleekRoundGauge";
    if (type == "SleekDoubleGauge"){
        SleekDoubleGauge* s = new SleekDoubleGauge();
        dispatcher_.registerSubscriber(s);
        persistables_.push_back(s);
        s->showSettingsForm();
    } else if (type == "SleekRoundGauge"){
        SleekRoundGauge* s = new SleekRoundGauge();
        dispatcher_.registerSubscriber(s);
        persistables_.push_back(s);
        s->showSettingsForm();
    } else if (type == "RoundGauge"){
        RoundGauge* s = new RoundGauge();
        dispatcher_.registerSubscriber(s);
        persistables_.push_back(s);
        s->showSettingsForm();
    } else if (type == "MeasurementGenerator"){
        MeasurementGenerator* m = new MeasurementGenerator();
        dispatcher_.registerPublisher(m);
        persistables_.push_back(m);
        //m->showSettingsForm();
    }



}

void Manager::onDelete(const QString &c)
{
    qDebug() << "Manager::onDelete" << c;
    deleteComponent(c);
}

void Manager::onSave()
{
    saveAll();
}

void Manager::load(const QString &name){
    qDebug() << "Manager::load(" << name << ")";
    QSettings settings(Persistable::filename_, QSettings::IniFormat);
    settings.beginGroup(name);
    QString type = settings.value("type").toString();

    if (type == "SleekDoubleGauge"){
        SleekDoubleGauge* s = new SleekDoubleGauge();
        s->setName(name);
        s->readSettings();
        emit createdNew(name);
        dispatcher_.registerSubscriber(s);
        persistables_.push_back(s);
    } else if (type == "SleekRoundGauge"){
        SleekRoundGauge* s = new SleekRoundGauge();
        s->setName(name);
        s->readSettings();
        emit createdNew(name);
        dispatcher_.registerSubscriber(s);
        persistables_.push_back(s);
    } else if (type == "RoundGauge"){
        RoundGauge* r = new RoundGauge();
        r->setName(name);
        r->readSettings();
        emit createdNew(name);
        dispatcher_.registerSubscriber(r);
        persistables_.push_back(r);
    } else if (type == "MeasurementGenerator"){
        MeasurementGenerator* m = new MeasurementGenerator();
        m->setName(name);
        m->readSettings();
        emit createdNew(name);
        dispatcher_.registerPublisher(m);
        persistables_.push_back(m);
    }
    else {
        qDebug() << "Could not load" << name << "since type" << type << "is unknown";
        return;
    }


}

void Manager::loadAll(){
    qDebug() << "Manager::loadAll()";
    QSettings settings(Persistable::filename_, QSettings::IniFormat);
    QStringList groups = settings.childGroups();
    qDebug() << groups;

    for (quint16 i=0; i < groups.size(); ++i){
        Manager::load(groups[i]);

    }
}

void Manager::saveAll(){
    qDebug() << "Manager::saveAll()";
    for (quint16 i=0; i < persistables_.size(); ++i){
        persistables_[i]->saveSettings();

    }
}

void Manager::initAll(){
    for(quint16 i=0; i<persistables_.size(); ++i){
        persistables_[i]->init();
    }
    showUI();
}

