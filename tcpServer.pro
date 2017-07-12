#-------------------------------------------------
#
# Project created by QtCreator 2017-07-11T23:06:41
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = tcpServer
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    decodemachine.cpp \
    huffmantree.cpp

HEADERS  += mainwindow.h \
    decodemachine.h \
    huffmantree.h

FORMS    += mainwindow.ui

QT+=network
