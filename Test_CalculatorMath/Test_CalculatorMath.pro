QT += testlib
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

SOURCES +=  tst_calculatormath.cpp \
    ../Calculator/source/calculatormath.cpp \
    ../Calculator/source/calculatorobject.cpp \
    ../Calculator/source/numbermath.cpp

HEADERS += \
    ../Calculator/source/calculatormath.h \
    ../Calculator/source/calculatorobject.h \
    ../Calculator/source/numbermath.h
