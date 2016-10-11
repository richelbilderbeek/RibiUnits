#include "speciesgrowth.h"

#include <cassert>
#include <istream>

#include <boost/units/io.hpp>

//#include "speciesdensity.h"
//#include "rate.h"

std::istream& boost::units::si::operator>>(std::istream& is, SpeciesGrowth& sd)
{
  double value = 0.0;
  is >> value;
  std::string unit;
  is >> unit;
  assert(unit == "m^-2");
  is >> unit;
  assert(unit == "s^-1");
  sd = SpeciesGrowth(
    value
    * boost::units::si::species_per_square_meter_per_second);
  return is;
}

