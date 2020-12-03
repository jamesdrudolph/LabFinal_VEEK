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


SOURCES += src/main.cpp\
        src/mainwindow.cpp \
    src/D8MCapture.cpp

HEADERS  += src/mainwindow.h \
    src/D8MCapture.h

FORMS    += src/mainwindow.ui

unix {
        CONFIG += link_pkgconfig
        PKGCONFIG += opencv
}
