
include(../RibiLibraries/ConsoleApplicationNoWeffcpp.pri)
#include(../RibiLibraries/BoostAll.pri)

include(CppUnits.pri)
include(CppUnitsTest.pri)

SOURCES += main_test_console.cpp

# Boost.Test
LIBS += -lboost_unit_test_framework

# gcov
QMAKE_CXXFLAGS += -fprofile-arcs -ftest-coverage
LIBS += -lgcov

# Boost.Graph
LIBS += \
  -lboost_date_time \
  -lboost_graph \
  -lboost_regex

# QResources give this error
QMAKE_CXXFLAGS += -Wno-unused-variable
