#ifndef ELM327ROWREADER_H
#define ELM327ROWREADER_H
#include "obd2reader.h"

class ELM327RowReader : public OBD2Reader
{
    Q_OBJECT
public:
    ELM327RowReader();
    virtual void postInit();
};

#endif // ELM327ROWREADER_H
