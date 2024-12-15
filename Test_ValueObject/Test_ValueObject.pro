QT += testlib
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

SOURCES +=  tst_valueobject.cpp \
    ../Calculator/source/valueobject.cpp

HEADERS += \
    ../Calculator/source/valueobject.h
