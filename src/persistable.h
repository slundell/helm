#ifndef PERSISTABLE_H
#define PERSISTABLE_H

#include <QString>

class Persistable
{

protected:
    QString name_;
    QString type_;

public:
    static const QString filename_;


    explicit Persistable();
    virtual ~Persistable() {}
    virtual void saveSettings();
    virtual void readSettings(){}
    virtual void setName(const QString& name) {name_ = name;} //only to be called from persistance manager.
    virtual void init(){}

    virtual QString getName() const { return name_; }
};

#endif // PERSISTABLE_H
