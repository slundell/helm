#include "serialrowreader.h"
#include <QDebug>
#include "measurement.h"

SerialRowReader::SerialRowReader()
{
    serialPort_ = new QSerialPort();
    useLogging_ = false;
}


void SerialRowReader::setBaud(int b)
{
    serialPort_->setBaudRate(b);
}

void SerialRowReader::open()
{

    qDebug() << "Opening port...";

    serialPort_->setPortName(portName_);
    serialPort_->setFlowControl(QSerialPort::NoFlowControl);
    serialPort_->setParity(QSerialPort::NoParity);
    serialPort_->setDataBits(QSerialPort::Data8);
    serialPort_->setStopBits(QSerialPort::OneStop);
    //serialPort_->setQueryMode(QextSerialPort::Polling);
    serialPort_->open(QIODevice::ReadWrite);

  for (uint i=0; (i < 100) && !(serialPort_->isOpen()); ++i)
    {
       serialPort_->open(QIODevice::ReadWrite);
       msleep(250);
    }
    qDebug() << "is open: " << serialPort_->isOpen();


}

void SerialRowReader::close()
{
    serialPort_->close();
}

void SerialRowReader::postInit()
{
}

void SerialRowReader::transmit(const QString& s)
{
    QByteArray ba = s.toLatin1();
    /*int i = */serialPort_->write(ba);
    qDebug() << "sent: " << s;
    serialPort_->waitForBytesWritten(100);
   // qDebug() << "sent wait done: " << s;
}
bool SerialRowReader::waitForChar(char w, unsigned int timeOut)
{
    //qDebug() << "started waiting for char: " << w;
    char c;
    unsigned int t = 0;
    while (true){
        if (serialPort_->getChar(&c))
        {
            //qDebug() << "got: " << c;
            if (c==w)
            {
                return true;
            }
        }
        else
        {
            t++;
        }
        if ((timeOut != 0) && (t > timeOut))
        {
            return false;
        }
        msleep(5);

        //qDebug() << t;
    }
    //qDebug() << "done waiting for char: " << w;

}

void SerialRowReader::waitForString(const QString& wait_for)
{
    char c;
    QString recieved;
    while (true){
        if (serialPort_->getChar(&c))
        {
            recieved.append(c);
            //qDebug() << "String so far: >" << recieved << "<";
            if (recieved.contains(wait_for))
            {
                //qDebug() << "Done waiting";
                break;
            }
        }

        msleep(1);
    }
}

void SerialRowReader::enableLogging(const QString fileName)
{
    logFile_.setFileName(fileName);
    if (logFile_.open(QFile::WriteOnly | QFile::Truncate)) {
      logStream_.setDevice(&logFile_);
      useLogging_ = true;
    }
}

void SerialRowReader::reconnect()
{
    close();
    open();
    postInit();
}

void SerialRowReader::run()
{
    qint64 buffsize = 1024;
    char buffer[buffsize+1];
    QString newline="\r";
    unsigned int watchdog = 0;
    unsigned int watchdogTimeout = 50;
    open();
    postInit();
    bool quit = false;
    QString sentences;
    qDebug()<<"Running SerialRowReader::run()";
    while (!quit)
    {
        //qDebug() << "-----"<<sentences<<"-----";
        QByteArray ba;
        //if (serialPort_->canReadLine()){
            int len;

            if ( (len = serialPort_->readLine(buffer, buffsize))>0){;
                watchdog = 0;
                buffer[len] = '\0';
                QString msg(buffer);
                //qDebug() << msg;
                sentences.append(msg);
                if  (useLogging_){
                    //qDebug() << "logging: " << msg;
                    logFile_.write(buffer);
                    logFile_.flush();
                }
                //qDebug() << sentences.length();
                if (sentences.length() > 2048)
                {
                    qDebug() << "**************cleared*****************";
                    sentences.clear();
                }
                if ((parser_->checkForReconnect(sentences))/* || (len==0)*/)
                    reconnect();
                while (sentences.contains(newline)){
                     QString sentence = sentences.left(sentences.indexOf(newline));
                     sentences = sentences.mid(sentences.indexOf(newline)+1);
                    // TODO: Let subclass decide weather a reconnect-condition exists.
                  /*  int lastNL = sentences.lastIndexOf(newline);
                    int secondToLastNL = sentences.lastIndexOf(newline, lastNL);
                     QString sentence = sentences.mid(secondToLastNL, lastNL - secondToLastNL);
                     sentences.remove(1, lastNL-1);

                     logStream_ << "." << lastNL  << "." << secondToLastNL << "." << sentences << ".";
*/
                    QVector<Measurement> ms = parser_->parseLine(sentence);
                    QString uni="";
                    for (int j=ms.size()-1; j>=0; --j){
                       // qDebug()<<"uni"<<uni;
                        if (!uni.contains(ms[j].getType())){
                            emit notify(ms[j]);

                            uni+=ms[j].getType();
                        }
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
       }
    }
    close();
}
QStringList SerialRowReader::receive(unsigned int timeOut)
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

void SerialRowReader::setParser(LineParser* lp){
    parser_=lp;
}


void SerialRowReader::setComPort(QString p)
{
   /* if (true)
        p = "\\\\.\\"+p;
*/
    portName_ = p;
}
