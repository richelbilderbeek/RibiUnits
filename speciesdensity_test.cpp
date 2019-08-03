#include "speciesdensity.h"

#include <fstream>
#include <sstream>

#include <boost/units/io.hpp>

// Boost.Test does not play well with -Weffc++


#include <boost/test/unit_test.hpp>

using namespace ribi::units;

BOOST_AUTO_TEST_CASE(ribi_units_speciesdensity)
{
  //using SpeciesDensity = boost::units::quantity<boost::units::si::species_density>;
  //Species density is in species per square meter
  {
    const SpeciesDensity d{1.0 * boost::units::si::species_per_square_meter};
    std::stringstream s;
    s << d;
    const std::string t{s.str()};
    BOOST_CHECK(t.substr(t.size() - 4, 4) == "m^-2");
  }
  //Species density uses a dot as a seperator
  {
    const SpeciesDensity d{12.34 * boost::units::si::species_per_square_meters};
    std::stringstream s;
    s << d;
    const std::string t{s.str()};
    BOOST_CHECK(t == "12.34 m^-2");
  }
  //Species density can be multiplied by an area to obtain the number of species
  {
    using Area = boost::units::quantity<boost::units::si::area>;
    const SpeciesDensity d{0.1 * boost::units::si::species_per_square_meter};
    const Area a(123.4 * boost::units::si::square_meter);
    const auto n = d * a;
    std::stringstream s;
    s << n;
    const std::string t{s.str()};
    BOOST_CHECK(t.substr(t.size() - 13, 13) == "dimensionless");
  }
  //Species density file I/O, one SpeciesDensity
  {
    const SpeciesDensity d{12.34 * boost::units::si::species_per_square_meter};
    const std::string filename{"ribi_units_speciesdensity_1.txt"};
    {
      std::ofstream f{filename};
      f << d;
    }
    std::ifstream f{filename};
    SpeciesDensity d_too;
    f >> d_too;
    BOOST_CHECK(d == d_too);
    std::remove(filename.c_str());
  }
  //Species density file I/O, two SpeciesDensity
  {
    const SpeciesDensity a{12.34 * boost::units::si::species_per_square_meter};
    const SpeciesDensity b{23.45 * boost::units::si::species_per_square_meter};
    const std::string filename{"ribi_units_speciesdensity_2.txt"};
    {
      std::ofstream f{filename};
      f << a << " " << b;
    }
    std::ifstream f{filename};
    SpeciesDensity a_too;
    SpeciesDensity b_too;
    f >> a_too >> b_too;
    BOOST_CHECK(a == a_too);
    BOOST_CHECK(b == b_too);
    std::remove(filename.c_str());
  }
}



