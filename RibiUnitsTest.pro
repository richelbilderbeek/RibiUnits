unix:!macx{
  # Linux only
  message("Console application, built for Linux")

  message(Host name: $$QMAKE_HOST.name)
  contains(QMAKE_HOST.name,pc-157-103) {
    message("Host is student computer")
    QMAKE_CXX = g++-4.9
    QMAKE_LINK = g++-4.9
    QMAKE_CC = gcc-4.9
    QMAKE_CXXFLAGS += -Wall -Wextra -Weffc++ -Werror -std=c++1y
  }
  !contains(QMAKE_HOST.name,pc-157-103) {
    message("Host is not student computer")
    CONFIG += c++14
    QMAKE_CXX = g++-5
    QMAKE_LINK = g++-5
    QMAKE_CC = gcc-5
    QMAKE_CXXFLAGS += -Wall -Wextra -Weffc++ -Werror -std=c++14
  }
}

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
  DEFINES += NDEBUG NTRACE_BILDERBIKKEL
}



include(RibiUnits.pri)
include(RibiUnitsTest.pri)

SOURCES += main_test_console.cpp

# Boost.Test
LIBS += -lboost_unit_test_framework

# gcov
QMAKE_CXXFLAGS += -fprofile-arcs -ftest-coverage
LIBS += -lgcov
