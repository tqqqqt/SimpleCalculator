QT += testlib
QT += core gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

SOURCES +=  tst_graphicsinnfoobject.cpp \
    ../Calculator/source/calculatorobject.cpp \
    ../Calculator/source/graphicsinfoobject.cpp

HEADERS += \
    ../Calculator/source/calculatorobject.h \
    ../Calculator/source/graphicsinfoobject.h
