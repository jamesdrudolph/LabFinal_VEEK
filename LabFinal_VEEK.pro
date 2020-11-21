#-------------------------------------------------
#
# Project created by QtCreator 2020-11-21T01:50:48
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

TARGET = LabFinal_VEEK
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    D8MCapture.cpp

HEADERS  += mainwindow.h \
    D8MCapture.h

FORMS    += mainwindow.ui

unix {
        CONFIG += link_pkgconfig
        PKGCONFIG += opencv
}