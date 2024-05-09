#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setupLight();
    connect(&_port, &SerialPort::dataReceived, this, &MainWindow::dataHandle);


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setupLight()
{
    road1_1 = new TrafficWidget(ui->road1Widget);
    road1_2 = new TrafficWidget(ui->road1Widget_2);
    road2_1 = new TrafficWidget(ui->road2Widget);
    road2_2 = new TrafficWidget(ui->road2Widget_2);
}

void MainWindow::dataHandle(QByteArray data)
{
    // Convert QByteArray to QString
    QString dataString = QString::fromUtf8(data);

    // Split the string by spaces
    QStringList parts = dataString.split(" ");

    // Loop through each part to extract numbers
    for (const QString &part : parts) {
        if (part.startsWith("R")) {
            // Extract the number after "R"
            t_red = part.mid(1).toInt();
        } else if (part.startsWith("G")) {
            // Extract the number after "G"
            t_green = part.mid(1).toInt();
        } else if (part.startsWith("Y")) {
            // Extract the number after "Y"
            t_yellow = part.mid(1).toInt();
        }
    }

    road1_1->setTrafficTime1(t_red, t_green, t_yellow);
    road1_2->setTrafficTime1(t_red, t_green, t_yellow);

    road2_1->setTrafficTime2(t_red, t_green, t_yellow);
    road2_2->setTrafficTime2(t_red, t_green, t_yellow);

    ui->stopButton->setEnabled(true);

}

void MainWindow::on_connectButton_clicked()
{
    _port.connect("COM2");

    road1_1->setTrafficTime1(t_red, t_green, t_yellow);
    road1_2->setTrafficTime1(t_red, t_green, t_yellow);

    road2_1->setTrafficTime2(t_red, t_green, t_yellow);
    road2_2->setTrafficTime2(t_red, t_green, t_yellow);

    ui->connectButton->setEnabled(false);

}


void MainWindow::on_sendButton_clicked()
{
    t_red = ui->redEdit->text().toInt();
    t_green = ui->greenEdit->text().toInt();
    t_yellow = ui->yellowEdit->text().toInt();

    road1_1->setTrafficTime1(t_red, t_green, t_yellow);
    road1_2->setTrafficTime1(t_red, t_green, t_yellow);
    road2_1->setTrafficTime2(t_red, t_green, t_yellow);
    road2_2->setTrafficTime2(t_red, t_green, t_yellow);

    QString timeString = QString("G%1 R%2 Y%3\n").arg(ui->greenEdit->text())
                             .arg(ui->redEdit->text()).arg(ui->yellowEdit->text());

    _port.write(timeString.toUtf8());
    ui->stopButton->setEnabled(true);

}

void offAll(TrafficWidget *road){
    road->_light->redLight()->turnOff();
    road->_light->greenLight()->turnOff();
    road->_light->yellowLight()->turnOff();
}

void MainWindow::on_stopButton_clicked()
{
    offAll(road1_1);
    offAll(road1_2);
    offAll(road2_1);
    offAll(road2_2);

    road1_1->machine->stop();
    road1_2->machine->stop();
    road2_1->machine->stop();
    road2_2->machine->stop();

    ui->stopButton->setEnabled(false);
}

