#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "serialport.h"
#include "trafficwidget.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    int  t_red = 10, t_yellow = 3, t_green = 7;

private slots:
    void on_connectButton_clicked();

    void on_sendButton_clicked();

    void on_stopButton_clicked();

private:
    SerialPort _port;
    QString _portName;

    TrafficWidget* road1_1;
    TrafficWidget* road1_2;
    TrafficWidget* road2_1;
    TrafficWidget* road2_2;

signals:
    void dataRcv(QByteArray data);

private:
    void setupLight();
    void dataHandle(QByteArray data);
    //void offAll(TrafficWidget* road);

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
