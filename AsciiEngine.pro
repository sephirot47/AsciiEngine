TEMPLATE = app
CONFIG += console c++11 debug
CONFIG -= app_bundle
CONFIG -= qt

INCLUDEPATH += ./AsciiGL

LIBS += -lncurses -lpthread -L./AsciiGL -lascii-gl

SOURCES += main.cpp \
    GameObject.cpp

HEADERS += \
    GameObject.h \
    Component.h

