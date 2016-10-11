#include "speciesdensity.h"

#include <cassert>
#include <istream>

#include <boost/units/io.hpp>

std::istream& boost::units::si::operator>>(std::istream& is, SpeciesDensity& sd)
{
  double value = 0.0;
  is >> value;
  std::string unit;
  is >> unit;
  assert(unit == "m^-2");
  sd = SpeciesDensity(value * boost::units::si::species_per_square_meter);
  return is;
}

