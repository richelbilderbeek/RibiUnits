#include "rate.h"

#include <cassert>
#include <istream>

#include <boost/units/io.hpp>

std::istream& boost::units::si::operator>>(std::istream& is, Rate& sd)
{
  double value = 0.0;
  is >> value;
  std::string unit;
  is >> unit;
  assert(unit == "s^-1");
  sd = Rate(
    value
    * boost::units::si::per_second);
  return is;
}
