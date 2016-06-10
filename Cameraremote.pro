#-------------------------------------------------
#
# Project created by QtCreator 2015-08-03T15:25:05
#
#-------------------------------------------------

QT       += core gui
QT       += network
CONFIG += c++11
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Cameraremote
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    streamdecoder.cpp

HEADERS  += mainwindow.h \
    streamdecoder.h

FORMS    += mainwindow.ui
QMAKE_LFLAGS += -static -static-libgcc
