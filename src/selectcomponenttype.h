#ifndef SELECTCOMPONENTTYPE_H
#define SELECTCOMPONENTTYPE_H

#include <QWidget>

namespace Ui {
class SelectComponentType;
}

class SelectComponentType : public QWidget
{
    Q_OBJECT

public:
    explicit SelectComponentType(QWidget *parent = 0);
    ~SelectComponentType();

private:
    Ui::SelectComponentType *ui;


signals:
    void onComponentTypeSelected(const QString&);
    void onCancel();


public slots:
    void on_CancelButton_clicked();
    void on_RoundGaugeButton_clicked();
    void on_SleekRoundGaugeButton_clicked();
    void on_SleekDoubleGaugeButton_clicked();
    void on_MeasurementGenerator_clicked();
    void on_CANReaderButton_clicked();
    void on_ELM327ReaderButton_clicked();

};

#endif // SELECTCOMPONENTTYPE_H
