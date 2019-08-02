# C++17
CONFIG += c++17
QMAKE_CXXFLAGS += -std=c++17

QMAKE_CXXFLAGS += -Wall -Wextra -Weffc++ -Werror

# Go ahead and use Qt.Core: it is about as platform-independent as
# the STL and Boost
QT += core

# Go ahead and use Qt.Gui: it is about as platform-independent as
# the STL and Boost. It is needed for QImage
QT += gui

# Don't define widgets: it would defy the purpose of this console
# application to work non-GUI
#greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG   += console
CONFIG   -= app_bundle
TEMPLATE = app

CONFIG(release, debug|release) {
  DEFINES += NDEBUG
}



include(RibiUnits.pri)
include(RibiUnitsTest.pri)

SOURCES += main_test_console.cpp

# Boost.Test
LIBS += -lboost_unit_test_framework

# gcov
QMAKE_CXXFLAGS += -fprofile-arcs -ftest-coverage
LIBS += -lgcov
