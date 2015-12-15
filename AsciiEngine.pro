TEMPLATE = app
CONFIG += console c++11 debug
CONFIG -= app_bundle
CONFIG -= qt

QMAKE_CXXFLAGS += -std=c++11

INCLUDEPATH += ./AsciiGL

LIBS += -lncurses -lpthread -L./AsciiGL -lascii-gl

SOURCES += main.cpp \
    GameObject.cpp \
    Debug.cpp \
    Transform.cpp \
    FileReader.cpp \
    Texture.cpp \
    Mesh.cpp \
    Scene.cpp \
    Game.cpp \
    stb_image.cpp

HEADERS += \
    GameObject.h \
    Component.h \
    Debug.h \
    Transform.h \
    FileReader.h \
    Texture.h \
    Mesh.h \
    Scene.h \
    Game.h \
    stb_image.h

