#-------------------------------------------------
#
# Project created by QtCreator 2024-08-21T17:15:22
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Calculator
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        Functions/functionswindow.cpp \
        Graphics/GraphicsInfo/graphicsinfowindow.cpp \
        Graphics/GraphicsPainter/graphicspainterwindow.cpp \
        History/historywindow.cpp \
        Mode/modewindow.cpp \
        Programmist/programmistwindow.cpp \
        Settings/programmistsettingswindow.cpp \
        Settings/settingswindow.cpp \
        Value/valuewindow.cpp \
        main.cpp \
        mainwindow.cpp \
        source/calculatormath.cpp \
        source/calculatorobject.cpp \
        source/numbermath.cpp \
        source/programmistobject.cpp \
        source/valueinfo.cpp \
        source/valueobject.cpp

HEADERS += \
        Functions/functionswindow.h \
        Graphics/GraphicsInfo/graphicsinfowindow.h \
        Graphics/GraphicsPainter/graphicspainterwindow.h \
        History/historywindow.h \
        Mode/modewindow.h \
        Programmist/programmistwindow.h \
        Settings/programmistsettingswindow.h \
        Settings/settingswindow.h \
        Value/valuewindow.h \
        mainwindow.h \
        source/calculatormath.h \
        source/calculatorobject.h \
        source/numbermath.h \
        source/programmistobject.h \
        source/programobject.h \
        source/valueinfo.h \
        source/valueobject.h

FORMS += \
        Functions/functionswindow.ui \
        Graphics/GraphicsInfo/graphicsinfowindow.ui \
        Graphics/GraphicsPainter/graphicspainterwindow.ui \
        History/historywindow.ui \
        Mode/modewindow.ui \
        Programmist/programmistwindow.ui \
        Settings/programmistsettingswindow.ui \
        Settings/settingswindow.ui \
        Value/valuewindow.ui \
        mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES +=

RESOURCES += \
    resources.qrc
