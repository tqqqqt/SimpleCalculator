QT += testlib
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

SOURCES +=  tst_programmistobject.cpp \
    ../Calculator/source/numbermath.cpp \
    ../Calculator/source/programmistobject.cpp

HEADERS += \
    ../Calculator/source/numbermath.h \
    ../Calculator/source/programmistobject.h \
    ../Calculator/source/programobject.h
