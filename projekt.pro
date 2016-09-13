#-------------------------------------------------
#
# Project created by QtCreator 2016-09-12T16:55:25
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = projekt
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    ball.cpp \
    vector.cpp \
    point.cpp

HEADERS  += mainwindow.h \
    ball.h \
    vector.h \
    point.h \
    sleeper.h

FORMS    += mainwindow.ui

RESOURCES += \
    resource.qrc
