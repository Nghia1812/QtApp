#ifndef TRAFFICLIGHTWIDGET_H
#define TRAFFICLIGHTWIDGET_H

#include <QVBoxLayout>
#include <QLCDNumber>
#include "lightwidget.h"

//! [1]
class TrafficLightWidget : public QWidget
{
    Q_OBJECT
public:
    explicit TrafficLightWidget(QWidget *parent = nullptr);

    LightWidget *redLight() const { return m_red; }
    LightWidget *yellowLight() const { return m_yellow; }
    LightWidget *greenLight() const { return m_green; }

    virtual ~TrafficLightWidget() {};
private:
    LightWidget *m_red;
    LightWidget *m_yellow;
    LightWidget *m_green;


public slots:
    void turnOffAll(){
        greenLight()->turnOff();
        redLight()->turnOff();
        yellowLight()->turnOff();
    };
};
//! [1]

#endif // TRAFFICLIGHTWIDGET_H
