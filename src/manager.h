#ifndef PERSISTABLEFACTORY_H
#define PERSISTABLEFACTORY_H

#include <QObject>
#include <QVector>
#include "persistable.h"
#include "dispatcher.h"
#include "ui_settings.h"
#include "settingswindow.h"
#include "selectcomponenttype.h"

class Manager : public QObject
{
    Q_OBJECT

private:

    static QVector<Persistable*> persistables_;
    static Dispatcher dispatcher_;
    static SettingsWindow* settingsWindow_;
    static SelectComponentType* selectComponentTypeWindow_;

    static Manager* instance_;
    void load(const QString&);
    void initUI();

    explicit Manager(QObject *parent = 0);

public:

    static Manager* instance();
    ~Manager();

    void saveAll();
    void loadAll();
    void initAll();
    void closeAll(){}
    void init();
    void showUI();
    void deleteComponent(const QString&);

signals:
    void createdNew(const QString&);
    void deleted(const QString&);

public slots:
    void onCreateNew(const QString&);
    void onDelete(const QString&);
    void onEdit(const QString&){}
    void onSave();
    void onSelectComponentType();

};
#endif // PERSISTABLEFACTORY_H
