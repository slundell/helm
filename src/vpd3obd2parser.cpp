#include "vpd3obd2parser.h"
#include <QStringList>
#include <QRegExp>
#include <QDebug>
#include <QMessageBox>

VPD3OBD2Parser::VPD3OBD2Parser()
{
    errorCodes_.push_back(new ErrorCode(0x00000000, 128, 21,  0, 3,  "ECU-temperatur: Spänningen överskrider normalvärde eller är kortsluten mot högre spänning."));
    errorCodes_.push_back(new ErrorCode(0x00000000, 128, 21,  0, 4,  "ECU-temperatur: Spänningen underskrider normalvärde eller är kortsluten mot batteriminus."));
    
    errorCodes_.push_back(new ErrorCode(0x00000000, 128, 43,  0, 11, "Start switch status: Fel har uppkommit under initieringen av motorstyrenheten."));
    
    errorCodes_.push_back(new ErrorCode(0x00000000, 128, 91,  0, 3,  "Trottelreglageposition: Spänningen överskrider normalvärde eller är kortsluten mot högre spänning."));
    errorCodes_.push_back(new ErrorCode(0x00000000, 128, 91,  0, 4,  "Trottelreglageposition: Spänningen underskrider normalvärde eller är kortsluten mot batteriminus."));
    errorCodes_.push_back(new ErrorCode(0x00000000, 128, 91,  0, 11, "Trottelreglageposition: Icke identifierbart fel."));
    
    errorCodes_.push_back(new ErrorCode(0x00000000, 128, 97,  0, 0,  "Vatten i bränslet."));
    
    errorCodes_.push_back(new ErrorCode(0x00000000, 128, 100, 0, 1,  "Oljetryck (motor): Oljetrycket för lågt."));
    
    errorCodes_.push_back(new ErrorCode(0x00000000, 128, 102, 0, 3,  "Laddlufttryck: Spänningen överskrider normalvärde eller är kortsluten mot högre spänning."));
    errorCodes_.push_back(new ErrorCode(0x00000000, 128, 102, 0, 4,  "Laddlufttryck: Spänningen underskrider normalvärde eller är kortsluten mot batteriminus."));
    errorCodes_.push_back(new ErrorCode(0x00000000, 128, 102, 0, 11, "Laddlufttryck: Icke identifierbart fel."));
    
    errorCodes_.push_back(new ErrorCode(0x00000000, 128, 105, 0, 3,  "Laddlufttemperatur: Spänningen överskrider normalvärde eller är kortsluten mot högre spänning."));
    errorCodes_.push_back(new ErrorCode(0x00000000, 128, 105, 0, 4,  "Laddlufttemperatur: Spänningen underskrider normalvärde eller är kortsluten mot batteriminus."));
    errorCodes_.push_back(new ErrorCode(0x00000000, 128, 105, 0, 11, "Laddlufttemperatur: Icke identifierbart fel."));
    
    errorCodes_.push_back(new ErrorCode(0x00000000, 128, 108, 0, 3,  "Atmosfärstryck: Spänningen överskrider normalvärde eller är kortsluten mot högre spänning."));
    errorCodes_.push_back(new ErrorCode(0x00000000, 128, 108, 0, 4,  "Atmosfärstryck: Spänningen underskrider normalvärde eller är kortsluten mot batteriminus."));
    
    errorCodes_.push_back(new ErrorCode(0x00000000, 128, 110, 0, 0,  "Kylvätsketemperatur: Givarvärdet är giltigt men överskrider normalt arbetsområde."));
    errorCodes_.push_back(new ErrorCode(0x00000000, 128, 110, 0, 3,  "Kylvätsketemperatur: Spänningen överskrider normalvärde eller är kortsluten mot högre spänning."));
    errorCodes_.push_back(new ErrorCode(0x00000000, 128, 110, 0, 4,  "Kylvätsketemperatur: Spänningen underskrider normalvärde eller är kortsluten mot batteriminus."));
    
    errorCodes_.push_back(new ErrorCode(0x00000000, 128, 158, 0, 1,  "Batterispänning: Givarvärdet är giltigt men underskrider normalt arbetsområde."));
    
    errorCodes_.push_back(new ErrorCode(0x00000000, 128, 164, 0, 2,  "Bränsletryck: Intermittenta eller felaktiga data."));
    errorCodes_.push_back(new ErrorCode(0x00000000, 128, 164, 0, 3,  "Bränsletryck: Spänningen överskrider normalvärde eller är kortsluten mot högre spänning."));
    errorCodes_.push_back(new ErrorCode(0x00000000, 128, 164, 0, 4,  "Bränsletryck: Spänningen underskrider normalvärde eller är kortsluten mot batteriminus."));
    errorCodes_.push_back(new ErrorCode(0x00000000, 128, 164, 0, 11, "Bränsletryck: Icke identifierbart fel."));
    
    errorCodes_.push_back(new ErrorCode(0x00000000, 128, 190, 0, 3,  "Motorvarvtal: Spänningen överskrider normalvärde eller är kortsluten mot högre spänning."));
    errorCodes_.push_back(new ErrorCode(0x00000000, 128, 190, 0, 11, "Motorvarvtal: Icke identifierbart fel."));
    
    errorCodes_.push_back(new ErrorCode(0x00000000, 128, 0, 1, 11, "Enhetsinjektor nr 1: Icke identifierbart fel."));
    errorCodes_.push_back(new ErrorCode(0x00000000, 128, 0, 2, 11, "Enhetsinjektor nr 2: Icke identifierbart fel."));
    errorCodes_.push_back(new ErrorCode(0x00000000, 128, 0, 3, 11, "Enhetsinjektor nr 3: Icke identifierbart fel."));
    errorCodes_.push_back(new ErrorCode(0x00000000, 128, 0, 4, 11, "Enhetsinjektor nr 4: Icke identifierbart fel."));
    errorCodes_.push_back(new ErrorCode(0x00000000, 128, 0, 5, 11, "Enhetsinjektor nr 5: Icke identifierbart fel."));
    
    errorCodes_.push_back(new ErrorCode(0x00000000, 128, 0, 21, 11, "Varvtalsgivare, kamaxel: Icke identifierbart fel."));
    errorCodes_.push_back(new ErrorCode(0x00000000, 128, 0, 22, 11, "Varvtalsgivare, svänghjul: Icke identifierbart fel."));
    
    errorCodes_.push_back(new ErrorCode(0x00000000, 128, 0, 27, 0,  "VNT-ventil: Givarvärdet är giltigt men överskrider normalt arbetsområde."));
    errorCodes_.push_back(new ErrorCode(0x00000000, 128, 0, 27, 11, "VNT-ventil: Icke identifierbart fel."));
    
    errorCodes_.push_back(new ErrorCode(0x00000000, 128, 0, 211, 3, "Spänningsmatning, givare 2: Spänningen överskrider normalvärde eller är kortsluten mot högre spänning"));
    errorCodes_.push_back(new ErrorCode(0x00000000, 128, 0, 211, 4, "Spänningsmatning, givare 2: Spänningen underskrider normalvärde eller är kortsluten mot batteriminus."));
    
    errorCodes_.push_back(new ErrorCode(0x00000000, 128, 0, 212, 3, "Spänningsmatning, givare 1: Spänningen överskrider normalvärde eller är kortsluten mot högre spänning"));
    errorCodes_.push_back(new ErrorCode(0x00000000, 128, 0, 212, 4, "Spänningsmatning, givare 1: Spänningen underskrider normalvärde eller är kortsluten mot batteriminus."));
    
    errorCodes_.push_back(new ErrorCode(0x00000000, 128, 0, 218, 11, "ECM huvudrelä: Icke identifierbart fel."));
    
    errorCodes_.push_back(new ErrorCode(0x00000000, 128, 0, 213, 11, "Kommunikationsfel J1939: Icke identifierbart fel."));
    
    errorCodes_.push_back(new ErrorCode(0x00000000, 128, 0, 232, 11, "5 Volt DC Matarspänning: Icke identifierbart fel."));
    
    errorCodes_.push_back(new ErrorCode(0x00000000, 128, 0, 253, 12, "Datasats minne EEPROM: Felaktig komponent."));
    
    errorCodes_.push_back(new ErrorCode(0x00000000, 128, 0, 254, 11, "Motorstyrenhet: Icke identifierbart fel."));
    
    errorCodes_.push_back(new ErrorCode(0x00000000, 128, 0, 50, 11,  "Bränsletrycksövervakning MPROP: Icke identifierbart fel."));

    errorCodes_.push_back(new ErrorCode(0x00000000, 128, 0, 54, 3,  "Booster-spänning (High bank 1): Spänningen överskrider normalvärde eller är kortsluten mot högre spänning."));
    errorCodes_.push_back(new ErrorCode(0x00000000, 128, 0, 54, 4,  "Booster-spänning (High bank 1): Spänningen underskrider normalvärde eller är kortsluten mot batteriminus."));
    errorCodes_.push_back(new ErrorCode(0x00000000, 128, 0, 54, 11, "Booster-spänning (High bank 1): Icke identifierbart fel."));
    
    errorCodes_.push_back(new ErrorCode(0x00000000, 128, 0, 55, 3,  "Booster-spänning (High bank 2): Spänningen överskrider normalvärde eller är kortsluten mot högre spänning."));
    errorCodes_.push_back(new ErrorCode(0x00000000, 128, 0, 55, 4,  "Booster-spänning (High bank 2): Spänningen underskrider normalvärde eller är kortsluten mot batteriminus."));
    errorCodes_.push_back(new ErrorCode(0x00000000, 128, 0, 55, 11, "Booster-spänning (High bank 2): Icke identifierbart fel."));
    
    errorCodes_.push_back(new ErrorCode(0x00000000, 128, 0, 56, 11, "System startup test for shutoff path: Icke identifierbart fel."));
    
    errorCodes_.push_back(new ErrorCode(0x00000000, 128, 0, 70, 3,  "Bränsletrycksövervakning 1: Bränsletrycket för högt. Flödesövervakning, negativ avvikelse."));
    errorCodes_.push_back(new ErrorCode(0x00000000, 128, 0, 70, 4,  "Bränsletrycksövervakning 1: Bränsletrycket för lågt. Flödesövervakning, positiv avvikelse."));
    errorCodes_.push_back(new ErrorCode(0x00000000, 128, 0, 70, 11, "Bränsletrycksövervakning 1: Bränsletrycksfel."));

    errorCodes_.push_back(new ErrorCode(0x00000000, 128, 0, 71, 4,  "Bränsletrycksövervakning 2: Upptäckt av läckage."));
    errorCodes_.push_back(new ErrorCode(0x00000000, 128, 0, 71, 11, "Bränsletrycksövervakning 2: Upptäckt av små läckage / Flödesövervakning i tomgång."));

    errorCodes_.push_back(new ErrorCode(0x00000000, 140, 0, 96, 1, "Bränslenivå: Datavärde normalt men under normalt arbetsområde.."));
    errorCodes_.push_back(new ErrorCode(0x00000000, 140, 0, 96, 3, "Bränslenivå: Onormalt hög spänning eller kortslutning mot högre spänning."));
    errorCodes_.push_back(new ErrorCode(0x00000000, 140, 0, 96, 4, "Bränslenivå: Onormalt låg spänning eller kortslutning mot lägre spänning."));

    errorCodes_.push_back(new ErrorCode(0x00000000, 140, 0, 289, 3, "Powertrim-strömbrytare: Onormalt hög spänning eller kortslutning mot högre spänning."));
    errorCodes_.push_back(new ErrorCode(0x00000000, 140, 0, 289, 4, "Powertrim-strömbrytare: Onormalt låg spänning eller kortslutning mot lägre spänning."));

    errorCodes_.push_back(new ErrorCode(0x00000000, 140, 0, 290, 3, "Powertrim-signal eller -matning: Onormalt hög spänning eller kortslutning mot högre spänning."));
    errorCodes_.push_back(new ErrorCode(0x00000000, 140, 0, 290, 4, "Powertrim-signal eller -matning: Onormalt låg spänning eller kortslutning mot lägre spänning."));

    errorCodes_.push_back(new ErrorCode(0x00000000, 140, 0, 395, 4, "Instrumentmatning: Onormalt låg spänning eller kortslutning mot lägre spänning."));
    errorCodes_.push_back(new ErrorCode(0x00000000, 140, 0, 395, 6, "Instrumentmatning: Onormalt hög ström eller kortslutning till batteriets minusledare."));

    errorCodes_.push_back(new ErrorCode(0x00000000, 140, 0, 396, 5, "Tillbehörsströmförsörjning (synk): Onormalt låg ström eller avbrott."));
    errorCodes_.push_back(new ErrorCode(0x00000000, 140, 0, 396, 6, "Tillbehörsströmförsörjning (synk): Onormalt hög ström eller kortslutning till batteriets minusledare."));

    errorCodes_.push_back(new ErrorCode(0x00000000, 140, 0, 410, 1, "Djuplarm: Datavärde normalt men under normalt arbetsområde."));

    errorCodes_.push_back(new ErrorCode(0x00000000, 140, 0, 231, 2,  "J1939 Kommunikationsvarning / -fel: Intermitenta eller felaktiga data."));
    errorCodes_.push_back(new ErrorCode(0x00000000, 140, 0, 231, 9,  "J1939 Kommunikationsvarning / -fel: Onormal uppdateringshastighet."));
    errorCodes_.push_back(new ErrorCode(0x00000000, 140, 0, 231, 11, "J1939 Kommunikationsvarning / -fel: Oidentifierbart fel."));

    errorCodes_.push_back(new ErrorCode(0x00000000, 140, 0, 253, 12, "Fel på kalibreringsminne: Felaktig enhet eller komponent."));

    errorCodes_.push_back(new ErrorCode(0x00000000, 140, 0, 254, 12, "Internt CPU-fel: Felaktig enhet eller komponent."));

    errorCodes_.push_back(new ErrorCode(0x00000000, 140, 0, 11, 3,   "Crank switch (nyckelstart): Onormalt hög spänning eller kortslutning mot högre spänning."));

    errorCodes_.push_back(new ErrorCode(0x00000000, 140, 0, 30, 3,   "Powertrimmotor uppåt: Onormalt hög spänning eller kortslutning mot högre spänning."));
    errorCodes_.push_back(new ErrorCode(0x00000000, 140, 0, 30, 4,   "Powertrimmotor uppåt: Onormalt låg spänning eller kortslutning mot lägre spänning."));

    errorCodes_.push_back(new ErrorCode(0x00000000, 140, 0, 31, 3,   "Powertrimmotor nedåt: Onormalt hög spänning eller kortslutning mot högre spänning."));
    errorCodes_.push_back(new ErrorCode(0x00000000, 140, 0, 31, 4,   "Powertrimmotor nedåt: Onormalt låg spänning eller kortslutning mot lägre spänning."));
}

quint8 VPD3OBD2Parser::charHexToUInt(QString charHex){
  bool ok;
  quint8 bin = charHex.toInt(&ok, 16);
  if (!ok) qDebug() << "Parse error: " << charHex;
  return bin;
}

QVector<Measurement> VPD3OBD2Parser::parseLine(const QString& line)
{
    QStringList words = line.split(" ",QString::SkipEmptyParts);

    QVector<Measurement> measurements;

    qDebug() << "got line: " << line;
    if (words.size()<2) return measurements;
    if (line.contains("at")) return measurements;
    if (line.contains("AT")) return measurements;
    if (line.contains("ERROR")) return measurements;

    QString mode = words[0];
    QString PID  = words[1];

    //7F means unsupported PID
    if (mode == "7F") return measurements;

    if ((mode == "43") || (mode == "47")) return parseDTC(line);
    if (mode == "44"){
        Measurement m;
        m.setValue("DTC");
        m.setSubject("Engine");
        m.setParameter("DTC");
        m.setUnit("");
        m.setMessage("All DTCs have been cleared");
        qDebug() << m.getMessage();
        measurements.push_back(m);
    }
    else if (mode == "41"){
        if (PID == "04") {
           Measurement m;
           quint32 b = charHexToUInt(words[2]);
           m.setValue((double)b*100.0/255.0);
           m.setSubject("Engine");
           m.setParameter("Calculated Load");
           m.setUnit("%");
           measurements.push_back(m);
        }
        else if (PID == "05") {
            Measurement m;
            quint32 b = charHexToUInt(words[2]);
            m.setValue((int)b - 40);
            m.setSubject("Engine");
            m.setParameter("Coolant Temperature");
            m.setUnit("C");
            measurements.push_back(m);
         }
         else if (PID == "0C") {
            Measurement m;
            quint32 msb = charHexToUInt(words[2]);
            quint32 lsb = charHexToUInt(words[3]);
            m.setValue(((msb * 256) + lsb)/4);
            m.setSubject("Engine");
            m.setParameter("RPM");
            m.setUnit("RPM");
            measurements.push_back(m);
        }
        else if (PID == "0B") {
            Measurement m;
            quint32 b = charHexToUInt(words[2]);
            m.setValue(b);
            m.setSubject("Engine");
            m.setParameter("Intake Manifold Absolute Pressure");
            m.setUnit("kPa");
            measurements.push_back(m);
        }
        else if (PID == "0F") {
            Measurement m;
            quint32 b = charHexToUInt(words[2]);
            m.setValue((int)b - 40);
            m.setSubject("Engine");
            m.setParameter("Intake Air Temperature");
            m.setUnit("C");
            measurements.push_back(m);
        }
        else if (PID == "10") {
            Measurement m;
            quint32 msb = charHexToUInt(words[2]);
            quint32 lsb = charHexToUInt(words[3]);
            m.setValue(((msb * 256) + lsb)/100);
            m.setSubject("Engine");
            m.setParameter("Manifold Air Flow");
            m.setUnit("g/sec");
            measurements.push_back(m);
        }
        else if (PID == "23") {
           Measurement m;
           quint32 msb = charHexToUInt(words[2]);
           quint32 lsb = charHexToUInt(words[3]);
           m.setValue(((msb * 256) + lsb) * 10);
           m.setSubject("Engine");
           m.setParameter("Fuel Rail Pressure");
           m.setUnit("kPa");
           measurements.push_back(m);
       }
    }
    if (measurements.size() == 0){
       qDebug() << "Unparsed line: " << line;
    }

    return measurements;
}


#include "dtccodes.h"

QString VPD3OBD2Parser::getDTCDescription(const QString & code)
{
    int i;
    for (i=0; dtc_list[i].dtc != "END"; i++){
        if (code == dtc_list[i].dtc) return dtc_list[i].desc;
    }
    return "Unknown";
}

QVector<Measurement> VPD3OBD2Parser::parseDTC(const QString & response)
{

    QVector<Measurement> measurements;

    QStringList words = response.split(" ",QString::SkipEmptyParts);

    if ((words[0] != "43") && (words[0] != "47"))
        return measurements;

    for (quint8 i=1; i+1 < words.size(); i+=2){
        unsigned int p = charHexToUInt(words[i]);

        quint8 c1 = (p & 0xC0);

        QString code;

        if (c1==0)
            code+="P";
        else if (c1==1)
            code+="C";
        else if (c1==2)
            code+="B";
        else if (c1==3)
            code+="U";

        quint8 c2 = (p & 0x30);

        code += QString::number(c2);

        quint8 c3 = (p & 0xF);

        code += QString::number(c3);

        code += words[i+1];

        if (code != "P0000"){
            Measurement m;
            m.setValue(code);
            m.setSubject("Engine");
            m.setParameter("DTC");
            m.setUnit("");
            m.setMessage(getDTCDescription(code));
            qDebug() << m.getMessage();
            measurements.push_back(m);
        }
    }

    qDebug() << "Num DTC sent: " << measurements.size();
    return measurements;
}

bool VPD3OBD2Parser::checkForReconnect(const QString& sentences){

  if (sentences.contains("BUFFER") || sentences.contains("NO DATA") || sentences.contains("STOPPED") || sentences.contains("RESET")|| sentences.contains("ELM327"))
  {
     return true;
  }
  return false;
}
//Old CAN - code
  //bool ok;
 // QString w;
  //for (int i=1;i<words.size();++i)
   //   w+=words[i];

  //quint32 bin = w.toInt(&ok, 16);




/*
  if (words[0] == "14000")
  {
      Measurement m;

      m.setValue(words[7].toInt(&ok, 16));
      m.setSubject("Engine");
      m.setParameter("Speed");
      m.setUnit("RPM");
      if (ok)
          measurements.push_back(m);

  }

  else if (words[1] == "04240")
  {

      {
          Measurement m;
          bool ok;
          m.setValue((words[9]+words[10]).toInt(&ok, 16));
          m.setSubject("Engine");
          m.setParameter("Speed");
          m.setUnit("RPM");
          if (ok)
              measurements.push_back(m);
      }
      {
          Measurement m;
          bool ok;
          m.setValue(words[8].toInt(&ok, 16));
          m.setSubject("Engine");
          m.setParameter("MAP");
          m.setUnit("bar");
          if (ok)
              measurements.push_back(m);
      }
  }
  else if (words[1] == "08000")
  {

      Measurement m;
      bool ok;
      m.setValue(words[7].toInt(&ok, 16));
      m.setSubject("Engine");
      m.setParameter("MAT");
      m.setUnit("C");
      if (ok)
          measurements.push_back(m);

             ErrorCode* err;

      foreach (err, errorCodes_)
      {
          if (err->mask_ && bin)
          {
              Measurement m;
              m.setValue("felkod");
              m.setSubject("Engine");
              m.setParameter("Speed");
              m.setUnit("RPM");
              m.setMessage(err->msg_);
              measurements.push_back(m);
          }

      }


  }

  static const int numRex=3;
  QRegExp rex[numRex];

  rex[0].setPattern("14000\\w");
  rex[1].setPattern("14000\\w");
  rex[2].setPattern("14000\\w");

  bool matched = false;
  for (int i=0;i<numRex;++i)
  {
      if (rex[i].indexIn(line) != -1)
      {
          matched = true;
      }
  }

  if (!matched){
      Measurement m;
      m.setValue(line);
      m.setSubject("Engine");
      m.setParameter("Unknown message");
      m.setUnit("");
      measurements.push_back(m);
  }*/
