#include "ribi_time_unit.h"

#include <cassert>
#include <istream>

#include <boost/units/io.hpp>

std::istream& boost::units::si::operator>>(std::istream& is, Time& sd)
{
  double value = 0.0;
  is >> value;
  std::string unit;
  is >> unit;
  assert(unit == "s");
  sd = Time(value * seconds);
  return is;
}

