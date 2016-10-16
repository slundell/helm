#include "dtcdisplay.h"


DTCDisplay::DTCDisplay(): measurement_()
{
    parameterFilter_ = "DTC";
    winTitle_ = "DTC";
}


void DTCDisplay::registerPublisher(QObject* o)
{
    qDebug() << "Registering Publisher";
    QObject::connect((QObject*)o, SIGNAL(notify(Measurement)),
                     (QObject*)this, SLOT(newMeasurement(Measurement)));
}

void DTCDisplay::registerDTCResetter(QObject* o)
{
    QObject::connect((QObject*)this, SIGNAL(resetAllDTCs()),
                     (QObject*)o, SLOT(resetAllDTCs()));
}


void DTCDisplay::newMeasurement(Measurement m){

    if ( ( (subjectFilter_ == "") || (m.getSubject() == subjectFilter_))
        && ((parameterFilter_ == "") || (m.getParameter() == parameterFilter_))){
        measurement_ = m;

        if (!activeMsgBoxDTCs_.contains((m.getValue().toString())) &&
            !ignoreDTCs_.contains((m.getValue()).toString())
           ){

            QString PID = m.getValue().toString();
            QString msg = m.getMessage();

            activeMsgBoxDTCs_.append(PID);


            msgBox_.setWindowTitle(winTitle_);
            msgBox_.setText(msgBox_.text() + "\n" + PID + ": " + msg);
            msgBox_.setStandardButtons(QMessageBox::Discard | QMessageBox::Ignore | QMessageBox::Reset);

            msgBox_.setDefaultButton(QMessageBox::Discard);
            if(msgBox_.exec() == QMessageBox::Discard){
                activeMsgBoxDTCs_.removeAll(PID);
                ignoreDTCs_.append(PID);
            } else if(msgBox_.exec() == QMessageBox::Ignore) {
                activeMsgBoxDTCs_.removeAll(PID);
            } else if(msgBox_.exec() == QMessageBox::Reset) {
                resetAllDTCs();
            }
        }
    }
}

void DTCDisplay :: showSettingsForm(){
    /*
    QDialog *widget = new QDialog;
    Ui::DialInstrumentSetup ui;
    ui.setupUi(widget);
    widget->show();
    */
}
