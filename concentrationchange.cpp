#include "concentrationchange.h"

#include <boost/units/io.hpp>

#include <cassert>
#include <istream>

//#include "concentration.h"
//#include "rate.h"

std::istream& boost::units::si::operator>>(std::istream& is, ConcentrationChange& sd)
{
  double value = 0.0;
  is >> value;
  std::string unit;
  is >> unit;  
  assert(unit == "m^-3");
  is >> unit;
  assert(unit == "s^-1" || unit == "mol");
  is >> unit;
  assert(unit == "mol" || unit == "s^-1");
  sd = ConcentrationChange(
    value
    * boost::units::si::mole_per_cubic_meter_per_second);
  return is;
}

