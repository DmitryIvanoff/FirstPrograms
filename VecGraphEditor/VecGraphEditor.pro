#-------------------------------------------------
#
# Project created by QtCreator 2015-05-24T18:34:24
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = VecGraphEditor
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    myrect.cpp \
    myellipse.cpp \
    myline.cpp

HEADERS  += mainwindow.h \
    myrect.h \
    myellipse.h \
    myline.h

FORMS    += mainwindow.ui

RESOURCES += \
    myres.qrc
