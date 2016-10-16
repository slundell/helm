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

void SelectComponentType::on_OkButton_clicked()
{
    qDebug() << "SelectComponentType::on_OkButton_clicked";
}

void SelectComponentType::on_CancelButton_clicked()
{
    qDebug() << "SelectComponentType::on_CancelButton_clicked";
}
