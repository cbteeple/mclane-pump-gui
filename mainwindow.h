#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtCore/QtGlobal>

#include <QMainWindow>

#include <QtSerialPort/QSerialPort>


QT_BEGIN_NAMESPACE

namespace Ui {
class MainWindow;
}

QT_END_NAMESPACE

//class Console;
class SettingsDialog;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public: //these are the constructor and destructor
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    QTimer *timer;

private slots:
    //declare user functions here
    void openSerialPort();
    void closeSerialPort();
    void writeData(const QByteArray &data);
    void setUpdate();
    void startTimer();
    void stopTimer();
    void handleError(QSerialPort::SerialPortError error);
    void sendGrabCommand();
    void sendStopCommand();
    void sendReleaseCommand();
    void sendOpenCommand();

private:
    void initActionsConnections();

private:
    //declare user variables here
    Ui::MainWindow *ui;     //this might be some pointer nonsense
    SettingsDialog *settings;
    QSerialPort *serial;
    QByteArray packet;
};

#endif // MAINWINDOW_H
