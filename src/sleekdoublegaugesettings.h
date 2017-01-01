#ifndef SLEEKDOUBLEGAUGESETTINGS_H
#define SLEEKDOUBLEGAUGESETTINGS_H

#include <QWidget>

namespace Ui {
class SleekDoubleGaugeSettings;
}

class SleekDoubleGaugeSettings : public QWidget
{
    Q_OBJECT

public:
    explicit SleekDoubleGaugeSettings(QWidget *parent = 0);
    ~SleekDoubleGaugeSettings();

private:
    Ui::SleekDoubleGaugeSettings *ui;


public slots:
    void on_OkButton_clicked();
    void on_CancelButton_clicked() {emit cancel();}

signals:
    void ok(const QString&, const QString&, const QString&, const QString&, const QString&, double, double);
    void cancel();
};

#endif // SLEEKDOUBLEGAUGESETTINGS_H
