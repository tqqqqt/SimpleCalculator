QT += testlib
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

HEADERS += \
        ../Calculator/source/calculatormath.h \
        ../Calculator/source/numbermath.h

SOURCES += \
        tst_project_tests.cpp \
        ../Calculator/source/calculatormath.cpp \
        ../Calculator/source/numbermath.cpp
