#ifndef SETTINGSWINDOW_H
#define SETTINGSWINDOW_H

#include <QWidget>
#include "ui_settings.h"

class SettingsWindow : public QWidget, private Ui::SettingsForm
{
    Q_OBJECT
public:
    explicit SettingsWindow(QWidget *parent = 0);

signals:
    void createNew();
    void edit(const QString&);
    void deleteIt(const QString&);
    void close();

public slots:
    void on_NewButton_clicked();
    void on_EditButton_clicked();
    void on_DeleteButton_clicked();
    void on_CloseButton_clicked();

    void onComponentAdded(const QString&);
    void onComponentDeleted(const QString&);
};

#endif // SETTINGSWINDOW_H
