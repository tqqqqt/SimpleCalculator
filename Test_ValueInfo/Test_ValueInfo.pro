QT += testlib
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

SOURCES +=  tst_valueinfo.cpp \
    ../Calculator/source/numbermath.cpp \
    ../Calculator/source/valueinfo.cpp

HEADERS += \
    ../Calculator/source/numbermath.h \
    ../Calculator/source/valueinfo.h
