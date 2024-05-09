#ifndef LIGHTWIDGET_H
#define LIGHTWIDGET_H

#include <QWidget>
#include <QPainter>
#include <QTimer>

class LightWidget : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(bool on READ isOn WRITE setOn)
public:
    explicit LightWidget(const QColor &color, QWidget *parent = nullptr);
    virtual ~LightWidget() {};

    int m_counterValue = 0; // Default counter value

    bool isOn() const { return m_on; }

    void setOn(bool on)
    {
        if (on == m_on)
            return;
        m_on = on;
        update();
    }

public slots:
    void turnOff() { setOn(false); }
    void turnOn() { setOn(true); }


protected:
    void paintEvent(QPaintEvent *) override
    {
        if (!m_on)
            return;
        QPainter painter(this);
        painter.setRenderHint(QPainter::Antialiasing);
        painter.setBrush(m_color);
        painter.drawEllipse(rect());

        // Draw the counter text
        QFont font = painter.font();
        font.setPointSize(14);
        painter.setFont(font);

        QString counterText = QString::number(m_counterValue);
        QRect textRect = rect();
        painter.drawText(textRect, Qt::AlignHCenter | Qt::AlignVCenter, counterText);
    }

signals:
    void countDone();

private:
    QColor m_color;
    bool m_on = false;
};

#endif // LIGHTWIDGET_H
