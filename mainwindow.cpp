//most of your edits will go in here!

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "settingsdialog.h"

#include <QMessageBox>
#include <QtSerialPort/QSerialPort>
#include <iostream>
#include <cmath>
#include <QtPlugin>
#include <QTimer>
#include <string>

//#include <windows.h>
//Q_IMPORT_PLUGIN(QWindowsIntegrationPlugin)

//note documentation for qcustomplot

//  ----- Begin Constructor -----
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    serial = new QSerialPort(this); //initializes the serial port
    settings = new SettingsDialog;  //creates a new settings dialog

    ui->actionConnect->setEnabled(true);    //sets initial state of serial control buttons
    ui->actionDisconnect->setEnabled(false);//...
    ui->actionQuit->setEnabled(true);       //...
    ui->actionConfigure->setEnabled(true);  //...
    initActionsConnections();

    //Make connections between GUI buttons and your functions here
    connect(ui->Update,SIGNAL(clicked(bool)),this,SLOT(setUpdate())); //clicked goes low when UPDATE is pressed
    connect(ui->pushButton_grab,SIGNAL(clicked(bool)),this,SLOT(sendGrabCommand())); //clicked goes low when Grab is pressed
    connect(ui->pushButton_stop,SIGNAL(clicked(bool)),this,SLOT(sendStopCommand()));
    connect(ui->pushButton_release,SIGNAL(clicked(bool)),this,SLOT(sendReleaseCommand()));
    connect(ui->openButton,SIGNAL(clicked(bool)),this,SLOT(sendOpenCommand())); //clicked goes low when Grab is pressed

    //Error messages:
    connect(serial, SIGNAL(error(QSerialPort::SerialPortError)), this,
            SLOT(handleError(QSerialPort::SerialPortError)));

    //Packet for sending data:
    packet.resize(17); //nothing special about 17-- specificies the # of bytes to be sent over serial

    //Timer:
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(stopTimer())); //this connects the timer to the function stop timer

}
//  ----- End Constructor -----

//  ----- Begin Deconstructor -----
MainWindow::~MainWindow()
{
    delete settings;
    delete ui;
}
//  ----- End Deconstructor -----


//-----Functions in the class MainWindow-----


// -------------------------------------
// --- Put your functions here! ---
// -------------------------------------

void MainWindow::startTimer()
{
    MainWindow::timer->start(1000);          //starts timer (I believe units are milliseconds).
}

void MainWindow::stopTimer()
{
    timer->stop();
    //do something
}

void MainWindow::setUpdate()
{

//    std::string grabString = ("Some text for grabbing");
//    //define packet to send over the serial port here...
    packet[0] = 0x00;   //byte of data (could be ascii character)
//    // query spin box int temp=ui->spinBox_1->value;
//    //packet[1] =...
//    //...
//    packet[16] = 0x00;
//    writeData(packet); //sends serial packet

    QString grabString1("update");
    qDebug() << grabString1 << grabString1.toUtf8().toHex();
    writeData(grabString1.toUtf8().toHex());
}

void MainWindow::sendGrabCommand()
{

    QString grabString("forward 1000 250 75 5");
    qDebug() << grabString << grabString.toUtf8().toHex();
//    writeData(grabString.toUtf8().toHex());
    writeData(grabString.toUtf8());
    QByteArray sendByte;
    sendByte.resize(1);
    sendByte[0] = 0x0D;
    qDebug() << sendByte;
    writeData(sendByte);
}

void MainWindow::sendOpenCommand()
{

    QString openString("reverse 250 250 75 5");
    qDebug() << openString << openString.toUtf8().toHex();
//    writeData(grabString.toUtf8().toHex());
    writeData(openString.toUtf8());
    QByteArray sendByte;
    sendByte.resize(1);
    sendByte[0] = 0x0D;
    qDebug() << sendByte;
    writeData(sendByte);
}

void MainWindow::sendStopCommand()
{

    QString grabString("Stop!");
    qDebug() << grabString << grabString.toUtf8().toHex();
//    writeData(grabString.toUtf8().toHex());
    QByteArray stopByte;
    stopByte.resize(1);
    stopByte[0] = 0x03;
    qDebug() << stopByte;
    writeData(stopByte);
}

void MainWindow::sendReleaseCommand()
{

    QString releaseString("reverse 250 250 75 5");
    qDebug() << releaseString << releaseString.toUtf8().toHex();
    writeData(releaseString.toUtf8().toHex());
    //    writeData(releaseString.toUtf8().toHex());
    writeData(releaseString.toUtf8());
    QByteArray sendByte;
    sendByte.resize(1);
    sendByte[0] = 0x0D;
    qDebug() << sendByte;
    writeData(sendByte);

}


// -------------------------------------
// ---  shouldn't need to edit these ---
// -------------------------------------

void MainWindow::openSerialPort()
{
    SettingsDialog::Settings p = settings->settings();
    serial->setPortName(p.name);
    serial->setBaudRate(p.baudRate);
    serial->setDataBits(p.dataBits);
    serial->setParity(p.parity);
    serial->setStopBits(p.stopBits);
    serial->setFlowControl(p.flowControl);
    if (serial->open(QIODevice::ReadWrite)) {
            ui->actionConnect->setEnabled(false);
            ui->actionDisconnect->setEnabled(true);
            ui->actionConfigure->setEnabled(false);
            ui->statusBar->showMessage(tr("Connected to %1 : %2, %3, %4, %5, %6")
                                       .arg(p.name).arg(p.stringBaudRate).arg(p.stringDataBits)
                                       .arg(p.stringParity).arg(p.stringStopBits).arg(p.stringFlowControl));
    } else {
        QMessageBox::critical(this, tr("Error"), serial->errorString());

        ui->statusBar->showMessage(tr("Open error"));
    }
}

void MainWindow::closeSerialPort()
{
    if (serial->isOpen())
        serial->close();
    ui->actionConnect->setEnabled(true);
    ui->actionDisconnect->setEnabled(false);
    ui->actionConfigure->setEnabled(true);
    ui->statusBar->showMessage(tr("Disconnected"));
}

void MainWindow::writeData(const QByteArray &data)
{
    serial->write(data);
    std::cout<<(int)data[0];
}

void MainWindow::handleError(QSerialPort::SerialPortError error)
{
    if (error == QSerialPort::ResourceError) {
        QMessageBox::critical(this, tr("Critical Error"), serial->errorString());
        closeSerialPort();
    }
}

void MainWindow::initActionsConnections()
{
    connect(ui->actionConnect, SIGNAL(triggered()), this, SLOT(openSerialPort()));
    connect(ui->actionDisconnect, SIGNAL(triggered()), this, SLOT(closeSerialPort()));
    connect(ui->actionQuit, SIGNAL(triggered()), this, SLOT(close()));
    connect(ui->actionConfigure, SIGNAL(triggered()), settings, SLOT(show()));
}


