#ifndef TRAFFICWIDGET_H
#define TRAFFICWIDGET_H

#include <QTimer>
#include <QWidget>

#include <QStateMachine>
#include <QFinalState>
#include <QVBoxLayout>

#include "lightwidget.h"
#include "trafficlightwidget.h"

class TrafficWidget : public QWidget
{
    Q_OBJECT
public:
    explicit TrafficWidget(TrafficLightWidget* light, QWidget *parent = nullptr);
    virtual ~TrafficWidget() {};

public:
    QStateMachine *machine;
    TrafficLightWidget* _light;

public:
    void setTrafficTime1(int red, int green, int yellow);
    void setTrafficTime2(int red, int green, int yellow);

};

#endif // TRAFFICWIDGET_H
