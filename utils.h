#ifndef UTILS_H
#define UTILS_H

#include <QKeySequence>
#include <QAbstractButton>
#include <QShortcut>
#include <windows.h> // for Sleep

void bindShortcut(QAbstractButton *button, const QKeySequence &shortcut)
{
    QObject::connect(new QShortcut(shortcut, button), &QShortcut::activated, [button](){ button->animateClick(); });
}


void qSleep(int ms)
    {

    #ifdef Q_OS_WIN
        Sleep(uint(ms));
    #else
        struct timespec ts = { ms / 1000, (ms % 1000) * 1000 * 1000 };
        nanosleep(&ts, NULL);
    #endif
    }


#endif // UTILS_H
