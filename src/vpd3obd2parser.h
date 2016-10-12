#ifndef VPD3OBD2PARSER_H
#define VPD3OBD2PARSER_H

#include "lineparser.h"


class ErrorCode{
  public:
    quint32 mask_;
    uint mid_;
    uint pid_;
    uint sid_;
    uint fmi_;
    QString msg_;

  public:
    ErrorCode(uint mask, uint mid, uint pid, uint sid, uint fmi, const QString& msg) :
              mask_(mask), mid_(mid), pid_(pid), sid_(sid), fmi_(fmi),msg_(msg){}
};


class VPD3OBD2Parser : public LineParser
{
private:
    QVector<ErrorCode*> errorCodes_;
public:
    VPD3OBD2Parser();
    virtual QVector<Measurement> parseLine(const QString&);
    virtual QVector<Measurement> parseDTC(const QString&);quint8 charHexToUInt(QString);
    virtual QString getDTCDescription(const QString & code);
    virtual bool checkForReconnect(const QString&);

};

#endif // VPD3PARSER_H
