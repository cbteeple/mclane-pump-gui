//should not need to change this unless you change functionality significantly
#include "mainwindow.h"
#include <QApplication>
#include <QtSerialPort/QtSerialPort>

#include <QTextStream>
#include <QFile>
#include <QStringList>
#include <QScreen>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    w.show();
    return a.exec();
}


