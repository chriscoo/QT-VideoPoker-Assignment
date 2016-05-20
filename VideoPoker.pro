#-------------------------------------------------
#
# Project created by QtCreator 2016-05-19T17:33:02
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = VideoPoker
TEMPLATE = app


SOURCES += main.cpp\
        Controller/mainview.cpp \
    Model/videopokergame.cpp

HEADERS  += Controller/mainview.h \
    Model/videopokergame.h

FORMS    += View/mainview.ui


INCLUDEPATH += "C:/Program Files (x86)/Windows Kits/10/Include/10.0.10150.0/ucrt"


LIBS += -L"C:/Program Files (x86)/Windows Kits/10/Lib/10.0.10150.0/ucrt/x64"
