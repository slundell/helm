#include "selectcomponenttype.h"
#include "ui_selectcomponenttype.h"
#include <QDebug>

SelectComponentType::SelectComponentType(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SelectComponentType)
{
    ui->setupUi(this);
}

SelectComponentType::~SelectComponentType()
{
    delete ui;
}


void SelectComponentType::on_CancelButton_clicked()
{
    qDebug() << "SelectComponentType::on_CancelButton_clicked";
    hide();
}

void SelectComponentType::on_RoundGaugeButton_clicked()
{
    qDebug() << "SelectComponentType::on_RoundGaugeButton_clicked";
    emit onComponentTypeSelected("RoundGauge");
}

void SelectComponentType::on_SleekRoundGaugeButton_clicked()
{
    qDebug() << "SelectComponentType::on_SleekRoundGaugeButton_clicked";
    emit onComponentTypeSelected("SleekRoundGauge");
}

void SelectComponentType::on_SleekDoubleGaugeButton_clicked()
{
    qDebug() << "SelectComponentType::on_SleekDoubleGaugeButton_clicked";
    emit onComponentTypeSelected("SleekDoubleGauge");
}

void SelectComponentType::on_MeasurementGenerator_clicked()
{
    qDebug() << "SelectComponentType::on_MeasurementGenerator_clicked";
    emit onComponentTypeSelected("MeasurementGenerator");
}

void SelectComponentType::on_CANReaderButton_clicked()
{
    qDebug() << "SelectComponentType::on_CANReaderButton_clicked";
    emit onComponentTypeSelected("CANReader");
}

void SelectComponentType::on_ELM327ReaderButton_clicked()
{
    qDebug() << "SelectComponentType::on_ELM327ReaderButton_clicked";
    emit onComponentTypeSelected("ELM327Reader");
}
