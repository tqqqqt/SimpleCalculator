QT += testlib
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

SOURCES +=  tst_calculatorobject.cpp \
    ../Calculator/source/calculatorobject.cpp

HEADERS += \
    ../Calculator/source/calculatorobject.h
