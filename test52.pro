#-------------------------------------------------
#
# Project created by QtCreator 2017-08-10T07:56:45
#
#-------------------------------------------------

QT       += core
QT       += network

QT       -= gui

TARGET = test52
CONFIG   += console
CONFIG   += c++11
CONFIG   -= app_bundle
TEMPLATE = app


SOURCES += main.cpp \
    readlog.cpp \
    sendlog.cpp

HEADERS += \
    GlobalVariable.h \
    readlog.h \
    sendlog.h
