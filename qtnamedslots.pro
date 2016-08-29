greaterThan(QT_MAJOR_VERSION, 4) {
    CONFIG += c++11
} else {
    unix:QMAKE_CXXFLAGS += -std=c++11
    macx {
        QMAKE_CXXFLAGS += -stdlib=libc++
        QMAKE_MACOSX_DEPLOYMENT_TARGET = 10.7
    }
}
QT = core
TARGET = qtnamedslots
CONFIG += console
CONFIG -= app_bundle
TEMPLATE = app
SOURCES = main.cpp
OTHER_FILES = README.md
