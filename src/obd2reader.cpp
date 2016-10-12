#include "obd2reader.h"
#include <QDebug>
#include "measurement.h"

OBD2Reader::OBD2Reader()
{
    serialPort_ = new QSerialPort();
    useLogging_ = false;
    resetAllDTCs_ = false;
}


void OBD2Reader::resetAllDTCs(){
    resetAllDTCs_=true;
}

/*
QStringList OBD2Reader::receive(unsigned int timeOut)
{
    //qDebug() << "started waiting for char: " << w;
    char c;
    QString response;
    unsigned int t = 0;
    while (true){
        if (serialPort_->getChar(&c))
        {
            //qDebug() << "got: " << c;
            if (c=='>')
            {
                //response.remove(QRegExp("[\\n\\t\\r]"));
                response = response.trimmed();
                //qDebug() << "Received response:" << response;
                QStringList lines = response.split("\r",QString::SkipEmptyParts);
                return lines;
            }
            else
            {
                response += c;
            }
        }
        else
        {
            t++;
        }
        if ((timeOut != 0) && (t > timeOut))
        {
            qDebug() << "Timeout waiting for response:" << response;
            QStringList lines;
            return lines;
        }
        msleep(1);

        //qDebug() << response;
    }
}
*/
void OBD2Reader::run()
{
    open();
    postInit();
    bool quit = false;
    qDebug()<<"Running SerialRowReader::run()";
    quint8 i = 0;
    while (!quit)
    {

        i++;

       /* QString hex;
        hex.setNum(pid,16);
        if (hex.length() == 1)
            hex = "0" + hex;
        pid++;
        QString msg = "01 " + hex + " 1\r";
        transmit(msg);
        */
        QStringList lines;

        if ( resetAllDTCs_ ){
            transmit("04\r"); //Reset DTCs
            lines += receive(100);
        }

        if ( true ){
            transmit("01 0C 1\r"); //RPM
            lines += receive(100);
        }

        if ( i % 2 == 0 ){
            transmit("01 05 1\r"); //Coolant temp
            lines += receive(100);
        }


        if ( i % 3 == 0 ){
            transmit("01 0B 1\r"); //MAP
            lines += receive(100);
        }

        if ( i % 4 == 0 ){
            transmit("01 0F 1\r"); //intake air temp
            lines += receive(100);
        }

        if ( i % 5 == 0 ){
            transmit("01 10 1\r"); //MAF
            lines += receive(100);
        }

        if ( i % 7 == 0 ){
            transmit("01 04 1\r"); //Engine load
            lines += receive(100);
        }

        if ( i % 9 == 0 ){
            transmit("01 23 1\r"); //Fuel Rail Pressure
            lines += receive(100);
        }

        if ( i % 25 == 0 ){
            transmit("03\r"); //DTC
            lines += receive(100);

            transmit("07\r"); //DTC
            lines += receive(100);
        }
        if (lines.size() == 0)
           reconnect();

        foreach(QString line, lines){
            if ((parser_->checkForReconnect(line)))
                reconnect();
            QVector<Measurement> ms  = parser_->parseLine(line);
            for (int j=ms.size()-1; j>=0; --j){
                emit notify(ms[j]);
            }
        }
        /*
         * transmit("01 01 1\r");
         * line = recieve();
         * parser->parse();
         * notify()
         * */


/*
        //qDebug() << "-----"<<sentences<<"-----";
        //if (serialPort_->canReadLine()){
            int len;

            while ( (len = serialPort_->readLine(buffer, buffsize))>0){;
                watchdog = 0;
                buffer[len] = '\0';
                QString msg(buffer);
                qDebug() << msg;
                answer.append(msg);
                if  (useLogging_){
                    //qDebug() << "logging: " << msg;
                    logFile_.write(buffer);
                    logFile_.flush();
                }
                //qDebug() << sentences.length();
                if (answer.length() > 2048)
                {
                    qDebug() << "**************cleared*****************";
                    answer.clear();
                }
                if ((parser_->checkForReconnect(answer)))
                    reconnect();
                if (answer.contains(newline)){
                    answer = answer.left(answer.indexOf(newline));

                    QVector<Measurement> ms;  = parser_->parseLine(answer);
                    for (int j=ms.size()-1; j>=0; --j){
                        emit notify(ms[j]);
                    }

                }

               // qDebug() << sentences.length();


            }
        //}
       msleep(1);
       if (watchdog++ > watchdogTimeout)
       {
           reconnect();
           watchdog = 0;
       }*/
    }
    close();
}



