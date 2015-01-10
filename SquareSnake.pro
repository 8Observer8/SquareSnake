#-------------------------------------------------
#
# Project created by QtCreator 2014-11-10T18:03:36
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SquareSnake
TEMPLATE = app


SOURCES += main.cpp\
        MainWindow.cpp \
    Field.cpp \
    Snake.cpp \
    Painter.cpp \
    Game.cpp \
    Fruit.cpp \
    Scene.cpp

HEADERS  += MainWindow.h \
    Field.h \
    Snake.h \
    Painter.h \
    Game.h \
    Fruit.h \
    Scene.h

FORMS    += MainWindow.ui

RESOURCES += \
    Shaders.qrc
