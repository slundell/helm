#ifndef HELMWIDGET_H
#define HELMWIDGET_H

#include <QWidget>
#include <QMouseEvent>
#include <QDebug>
#include <QSettings>

class HelmWidget : public QWidget
{
    Q_OBJECT


protected:
    QPoint oldPos;

    QString name_;
    static quint8 nameNum_;

    virtual void mousePressEvent(QMouseEvent*);
    virtual void mouseMoveEvent(QMouseEvent*);
    virtual void mouseReleaseEvent(QMouseEvent *);
    virtual void resizeEvent(QResizeEvent *);

public:
    explicit HelmWidget(QWidget *parent = 0);
    virtual ~HelmWidget();
    virtual void saveSettings();
    virtual void readSettings();

signals:

public slots:

};

#endif // HELMWIDGET_H
