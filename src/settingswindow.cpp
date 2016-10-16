#include "settingswindow.h"
#include <QDebug>

SettingsWindow::SettingsWindow(QWidget *parent) : QWidget(parent)
{
    setupUi(this);
}


//This signals could probably be directly setup, but...
void SettingsWindow::on_NewButton_clicked()
{
    qDebug() << "SettingsWindow::on_NewButton_clicked()";
    emit createNew();
}

void SettingsWindow::on_EditButton_clicked()
{
    qDebug() << "SettingsWindow::on_EditButton_clicked()";
    emit edit("helmwidget_1");
}

void SettingsWindow::on_DeleteButton_clicked()
{
    qDebug() << "SettingsWindow::on_DeleteButton_clicked()";

    emit deleteIt(PersistableList->currentItem()->text());
}

void SettingsWindow::on_CloseButton_clicked()
{
    qDebug() << "SettingsWindow::on_CloseButton_clicked()";
    emit close();
    hide();
}

void SettingsWindow::onComponentAdded(const QString& component)
{
    PersistableList->addItem(component);
}

void SettingsWindow::onComponentDeleted(const QString& component)
{
    qDebug() << "SettingsWindow::onComponentDeleted" << component;

    for (quint16 i=0; i < PersistableList->count(); ++i){
        if (PersistableList->item(i)->text() == component)
            PersistableList->takeItem(i);
    }
}
