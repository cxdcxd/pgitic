#-------------------------------------------------
#
# Project created by QtCreator 2015-04-18T06:13:45
#
#-------------------------------------------------

INCLUDEPATH += /usr/include/QtMobility
INCLUDEPATH += /usr/include/QtMultimediaKit

CONFIG += mobility
MOBILITY = multimedia

LIBS += -L/usr/lib -lQtMultimediaKit
LIBS += -L/usr/local/lib -lwiringPi

QT       += core
QT       += network
QT       += MOBILITY


QT       -= gui

TARGET = main
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    mytcpsocket.cpp \
    audioout.cpp \
    audioin.cpp \
    mygpio.cpp \
    recorder.cpp

HEADERS += \
    mytcpsocket.h \
    audioout.h \
    audioin.h \
    mygpio.h \
    recorder.h
