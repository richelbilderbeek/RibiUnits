#include "concentration.h"

#include <cassert>
#include <istream>
#include <boost/units/io.hpp>

std::istream& boost::units::si::operator>>(std::istream& is, Concentration& sd)
{
  double value = 0.0;
  is >> value;
  std::string unit;
  is >> unit;
  assert(unit == "m^-3");
  is >> unit;
  assert(unit == "mol");
  sd = Concentration(value * boost::units::si::mole / boost::units::si::cubic_meter);
  return is;
}

