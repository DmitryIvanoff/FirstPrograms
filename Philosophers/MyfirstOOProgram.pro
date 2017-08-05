#-------------------------------------------------
#
# Project created by QtCreator 2014-12-18T13:40:29
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = MyfirstOOProgram
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    shared.cpp \
    philosopher.cpp \
    master.cpp

HEADERS += \
    shared.h \
    philosopher.h \
    master.h \
    config.h
