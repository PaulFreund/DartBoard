#-------------------------------------------------
#
# Project created by QtCreator 2014-01-22T18:44:00
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = DartBoard
TEMPLATE = app


SOURCES += main.cpp \
    DartBoard.cpp

win32 {
    SOURCES +=
}
unix {
    SOURCES +=
}

HEADERS  += \
    DartBoard.h

FORMS    += dartboard.ui
