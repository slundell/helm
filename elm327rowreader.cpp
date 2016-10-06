#include "elm327rowreader.h"
#include <QDebug>
ELM327RowReader::ELM327RowReader()
{
}

void ELM327RowReader::postInit()
{

    //Init sequence for an ELM327 USB
reconnect:
    transmit("AT WS\n\r");
    //waitForChar('>');

    while (!waitForChar('>', 5))
    {
        close();
        open();
        transmit("AT WS\n\r");
    }
    /*

    SET 115200 BAUD
    transmit("AT PP 0C SV 23\n\r");
    waitForString("OK"); //OK
    transmit("AT PP 0C ON\n\r");
    waitForString("OK"); //OK
    transmit("ATZ\n\r");
    waitForString("ELM327 v1.3\n");

    */

    /*
     * J1939 initiation sequence
     *
    transmit("AT D0\n\r");
    if (!waitForChar('>',5)) goto reconnect;
    transmit("AT SPA\n\r");
    if (!waitForChar('>',5)) goto reconnect;
    transmit("AT H1\n\r");
    if (!waitForChar('>',5)) goto reconnect;
    transmit("AT AL\n\r");
    if (!waitForChar('>',5)) goto reconnect;

    transmit("AT MA\n\r");
    */


    transmit("AT SP3\n\r");
    if (!waitForChar('>',5)) goto reconnect;
    transmit("AT E0\n\r");
    if (!waitForChar('>',5)) goto reconnect;
    transmit("01 01 1\n\r");
    if (!waitForChar('>',3000)) goto reconnect;
    qDebug() << "Port inited";
}
