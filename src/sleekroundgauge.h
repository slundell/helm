#ifndef SLEEKROUNDGAUGE_H
#define SLEEKROUNDGAUGE_H
#include "roundgauge.h"

class SleekRoundGauge : public RoundGauge
{

protected:
    double nominalTicsInterval_;
    QColor scaleColor_;
    QColor scaleDarkColor_;
    QColor scaleDarkerColor_;
    QColor textColor_;
    QColor nominalColor_;
    QColor nominalTickColor_;
    QColor backgroundColor_;
    QString fontString_;


    virtual void paintEvent(QPaintEvent *event);

public:
    SleekRoundGauge(HelmWidget * parent=0);

    virtual void setNominalTicsInterval(double nti) { nominalTicsInterval_ = nti; }
    virtual void showSettingsForm();
    void save(const QString&, const QString&, const QString&, double, double);

};

#endif // SLEEKROUNDGAUGE_H
