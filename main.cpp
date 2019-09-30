//should not need to change this unless you change functionality significantly
#include "mainwindow.h"
#include <QApplication>
#include <QtSerialPort/QtSerialPort>

#include <QTextStream>
#include <QFile>
#include <QStringList>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    w.show();
    return a.exec();
}


