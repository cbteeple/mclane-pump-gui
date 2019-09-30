#include "mytimer.h"
#include <QDebug>

MyTimer::MyTimer()
{
    // create a timer
    timer = new QTimer(this);

    // msec
    timer->start(1000);
}

void MyTimer::MyTimerSlot()
{
    qDebug() << "Timer...";
}
