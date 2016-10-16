#ifndef SLEEKROUNDGAUGESETTINGS_H
#define SLEEKROUNDGAUGESETTINGS_H

#include <QWidget>

namespace Ui {
class SleekRoundGaugeSettings;
}

class SleekRoundGaugeSettings : public QWidget
{
    Q_OBJECT

public:
    explicit SleekRoundGaugeSettings(QWidget *parent = 0);
    ~SleekRoundGaugeSettings();

private:
    Ui::SleekRoundGaugeSettings *ui;


public slots:
    void on_OkButton_clicked();
    void on_CloseButton_clicked() {emit cancel();}

signals:
    void ok(const QString&, const QString&, const QString&, double, double);
    void cancel();
};

#endif // SLEEKDOUBLEGAUGESETTINGS_H
