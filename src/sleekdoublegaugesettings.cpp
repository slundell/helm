#include "sleekdoublegaugesettings.h"
#include "ui_sleekdoublegaugesettings.h"


SleekDoubleGaugeSettings::SleekDoubleGaugeSettings(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SleekDoubleGaugeSettings)
{
    ui->setupUi(this);
    ui->MinText->setValidator(new QDoubleValidator()); //TODO: Leaky?
    ui->MaxText->setValidator(new QDoubleValidator()); //TODO: Leaky?
    ui->LeftParameterText->setValidator(new QRegExpValidator(QRegExp("[a-zA-Z0-9_\\s]*"))); //TODO: Leaky?
    ui->RightParameterText->setValidator(new QRegExpValidator(QRegExp("[a-zA-Z0-9_\\s]*"))); //TODO: Leaky?
    ui->LeftSubjectText->setValidator(new QRegExpValidator(QRegExp("[a-zA-Z0-9_\\s]*"))); //TODO: Leaky?
    ui->RightSubjectText->setValidator(new QRegExpValidator(QRegExp("[a-zA-Z0-9_\\s]*"))); //TODO: Leaky?

}

SleekDoubleGaugeSettings::~SleekDoubleGaugeSettings()
{
    delete ui;
}

void SleekDoubleGaugeSettings::on_OkButton_clicked()
{
    emit ok(ui->NameText->text(),
            ui->LeftSubjectText->text(),
            ui->RightSubjectText->text(),
            ui->LeftParameterText->text(),
            ui->RightParameterText->text(),
            ui->MinText->text().toDouble(),
            ui->MaxText->text().toDouble()
            );
}


