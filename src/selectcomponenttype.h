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
    void onTypeSelected(const QString&);
    void onCancel();
    //connect these
public slots:
    void on_OkButton_clicked();
    void on_CancelButton_clicked();
};

#endif // SELECTCOMPONENTTYPE_H
