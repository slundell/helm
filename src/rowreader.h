#ifndef ROWREADER_H
#define ROWREADER_H

#include <QThread>
#include "measurement.h"
class RowReader : public QThread
{
    Q_OBJECT
public:
    RowReader();
    virtual void run() = 0; // pure virtual
    virtual void reconnect();
signals:
    void notify(Measurement);

};

#endif // ROWREADER_H
