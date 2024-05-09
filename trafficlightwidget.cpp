#include "trafficlightwidget.h"

TrafficLightWidget::TrafficLightWidget(QWidget *parent) : QWidget(parent)
{
    auto vbox = new QVBoxLayout(this);
    m_red = new LightWidget(Qt::red);
    vbox->addWidget(m_red);
    m_yellow = new LightWidget(Qt::yellow);
    vbox->addWidget(m_yellow);
    m_green = new LightWidget(Qt::green);
    vbox->addWidget(m_green);
    auto pal = palette();
    pal.setColor(QPalette::Window, Qt::black);
    setPalette(pal);
    setAutoFillBackground(true);
}
