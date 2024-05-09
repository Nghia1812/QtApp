#include "trafficwidget.h"


TrafficWidget::TrafficWidget(TrafficLightWidget* light, QWidget *parent)
    : QWidget(parent)
{
    _light = light;
    machine = new QStateMachine(this);
}

QState* createLightState(LightWidget *light, int duration,  QState *parent=nullptr)
{
    auto lightState = new QState(parent);
    auto timer = new QTimer(lightState);
    timer->setInterval(duration);
    timer->setSingleShot(true);
    auto timing = new QState(lightState);
    QObject::connect(timing, &QAbstractState::entered, light, &LightWidget::turnOn);
    QObject::connect(timing, &QAbstractState::entered, timer, QOverload<>::of(&QTimer::start));
    QObject::connect(timing, &QAbstractState::exited, light, &LightWidget::turnOff);
    auto done = new QFinalState(lightState);
    timing->addTransition(timer, &QTimer::timeout, done);
    lightState->setInitialState(timing);
    return lightState;
}

void TrafficWidget::setTrafficTime1(int red, int green, int yellow)
{
    //Light states
    auto redGoingGreen = createLightState(_light->redLight(), red*1000); //=red
    redGoingGreen->setObjectName("redGoingGreen");
    _light->redLight()->m_counterValue = red;

    auto greenGoingYellow = createLightState(_light->greenLight(), green*1000); //=green
    greenGoingYellow->setObjectName("greenGoingYellow");
    _light->greenLight()->m_counterValue = green;

    auto yellowGoingRed = createLightState(_light->yellowLight(), yellow*500); //=yellow/2
    yellowGoingRed->setObjectName("yellowGoingRed");
    auto yellowGoingGreen = createLightState(_light->yellowLight(), yellow*500); //=yellow/2
    yellowGoingGreen->setObjectName("yellowGoingGreen");
    _light->yellowLight()->m_counterValue = yellow;

    redGoingGreen->addTransition(redGoingGreen, &QState::finished, greenGoingYellow);
    greenGoingYellow->addTransition(greenGoingYellow, &QState::finished, yellowGoingRed);
    yellowGoingRed->addTransition(yellowGoingRed, &QState::finished, yellowGoingGreen);
    yellowGoingGreen->addTransition(yellowGoingGreen, &QState::finished, redGoingGreen);

    machine->addState(redGoingGreen);
    machine->addState(greenGoingYellow);
    machine->addState(yellowGoingRed);
    machine->addState(yellowGoingGreen);

    machine->setInitialState(redGoingGreen);

    machine->start();
}




void TrafficWidget::setTrafficTime2(int red, int green, int yellow)
{
    //light state
    auto greenGoingYellow = createLightState(_light->greenLight(), green*1000); //=green
    greenGoingYellow->setObjectName("greenGoingYellow");
    _light->greenLight()->m_counterValue = green;

    auto yellowGoingRed = createLightState(_light->yellowLight(), yellow*500); //=yellow/2
    yellowGoingRed->setObjectName("yellowGoingRed");
    auto yellowGoingGreen = createLightState(_light->yellowLight(), yellow*500); //=yellow/2
    yellowGoingGreen->setObjectName("yellowGoingGreen");
    _light->yellowLight()->m_counterValue = yellow;

    auto redGoingGreen = createLightState(_light->redLight(), red*1000); //=red
    redGoingGreen->setObjectName("redGoingGreen");
    _light->redLight()->m_counterValue = red;

    redGoingGreen->addTransition(redGoingGreen, &QState::finished, greenGoingYellow);
    greenGoingYellow->addTransition(greenGoingYellow, &QState::finished, yellowGoingRed);
    yellowGoingRed->addTransition(yellowGoingRed, &QState::finished, yellowGoingGreen);
    yellowGoingGreen->addTransition(yellowGoingGreen, &QState::finished, redGoingGreen);

    machine->addState(redGoingGreen);
    machine->addState(greenGoingYellow);
    machine->addState(yellowGoingRed);
    machine->addState(yellowGoingGreen);

    machine->setInitialState(greenGoingYellow);
    machine->start();
}



