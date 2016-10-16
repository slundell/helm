#include "sleekroundgaugesettings.h"
#include "ui_sleekroundgaugesettings.h"


SleekRoundGaugeSettings::SleekRoundGaugeSettings(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SleekRoundGaugeSettings)
{
    ui->setupUi(this);
    ui->MinText->setValidator(new QDoubleValidator()); //TODO: Leaky?
    ui->MaxText->setValidator(new QDoubleValidator()); //TODO: Leaky?
    ui->ParameterText->setValidator(new QRegExpValidator(QRegExp("[a-zA-Z0-9_\\s]*"))); //TODO: Leaky?
    ui->SubjectText->setValidator(new QRegExpValidator(QRegExp("[a-zA-Z0-9_\\s]*"))); //TODO: Leaky?
}

SleekRoundGaugeSettings::~SleekRoundGaugeSettings()
{
    delete ui;
}

void SleekRoundGaugeSettings::on_OkButton_clicked()
{
    emit ok(ui->NameText->text(),
            ui->SubjectText->text(),
            ui->ParameterText->text(),
            ui->MinText->text().toDouble(),
            ui->MaxText->text().toDouble()
            );
    hide();
}


