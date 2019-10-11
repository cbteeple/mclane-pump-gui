#-------------------------------------------------
#
# Project created by QtCreator 2015-08-31T11:45:18
#
#-------------------------------------------------
# Shouldn't need to change anything in here

QT       += core gui
QT       += serialport
QT       += widgets printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Pump_GUI
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
        settingsdialog.cpp \
        qcustomplot.cpp

HEADERS  += mainwindow.h \
            settingsdialog.h \
            qcustomplot.h \
            utils.h

FORMS    += mainwindow.ui \
            settingsdialog.ui

RESOURCES += \
    Pump_GUI.qrc

isEmpty(TARGET_EXT) {
    win32 {
        TARGET_CUSTOM_EXT = .exe
    }
    macx {
        TARGET_CUSTOM_EXT = .app
    }
} else {
    TARGET_CUSTOM_EXT = $${TARGET_EXT}
}

win32 {
    DEPLOY_COMMAND = windeployqt
}
macx {
    DEPLOY_COMMAND = macdeployqt
}

CONFIG( debug, debug|release ) {
    # debug
    DEPLOY_TARGET = $$shell_quote($$shell_path($${OUT_PWD}/debug/$${TARGET}$${TARGET_CUSTOM_EXT}))
} else {
    # release
    DEPLOY_TARGET = $$shell_quote($$shell_path($${OUT_PWD}/release/$${TARGET}$${TARGET_CUSTOM_EXT}))
}

#  # Uncomment the following line to help debug the deploy command when running qmake
#  warning($${DEPLOY_COMMAND} $${DEPLOY_TARGET})

QMAKE_POST_LINK = $${DEPLOY_COMMAND} $${DEPLOY_TARGET}
