#-------------------------------------------------
#
# Project created by QtCreator 2016-05-19T17:33:02
#
#-------------------------------------------------
#
#  Created by Chris Arsenault on 2016-05-13.
#  Copyright © 2016 Chris Arsenault. All rights reserved.
#
QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = VideoPoker
TEMPLATE = app


SOURCES += main.cpp\
        Controller/mainview.cpp \
    Model/videopokergame.cpp \
    Model/Card.cpp \
    Model/Deck.cpp \
    Model/Hand.cpp

HEADERS  += Controller/mainview.h \
    Model/videopokergame.h \
    Model/Card.h \
    Model/Deck.h \
    Model/Hand.h

FORMS    += View/mainview.ui


INCLUDEPATH += "C:/Program Files (x86)/Windows Kits/10/Include/10.0.10150.0/ucrt"


LIBS += -L"C:/Program Files (x86)/Windows Kits/10/Lib/10.0.10150.0/ucrt/x64"

RESOURCES += \
    media.qrc
