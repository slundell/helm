#ifndef VPD3CANPARSER_H
#define VPD3CANPARSER_H

#include <canframeparser.h>

class VPD3CANFrameParser : public CANFrameParser
{
    Q_OBJECT
public:
    explicit VPD3CANFrameParser();

signals:

public slots:
};

#endif // VPD3CANPARSER_H
