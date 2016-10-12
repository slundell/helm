#ifndef PERSISTABLE_H
#define PERSISTABLE_H

#include <QString>

class Persistable
{

protected:
    QString name_;
    QString type_;
public:
    explicit Persistable();
    virtual void saveSettings();
    virtual void readSettings(){};
    virtual void setName(const QString& name) {name_ = name;} //only to be called from persistance manager.
    virtual void init(){}

};

#endif // PERSISTABLE_H
