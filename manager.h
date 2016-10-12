#ifndef PERSISTABLEFACTORY_H
#define PERSISTABLEFACTORY_H

#include <QObject>
#include <QVector>
#include "persistable.h"
#include "dispatcher.h"

class Manager : public QObject
{
    Q_OBJECT

private:
    static QVector<Persistable*> persistables_;
    static Dispatcher dispatcher_;
    static void load(const QString&);


public:
    explicit Manager(QObject *parent = 0);

    static void saveAll();
    static void loadAll();
    static void initAll();
    static void closeAll(){}

};

#endif // PERSISTABLEFACTORY_H
