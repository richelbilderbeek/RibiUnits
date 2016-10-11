#include "concentration.h"

#include <fstream>
#include <boost/units/io.hpp>

// Boost.Test does not play well with -Weffc++
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include <boost/test/unit_test.hpp>


BOOST_AUTO_TEST_CASE(ribi_units_concentration)
{
  using Concentration = boost::units::quantity<boost::units::si::concentration>;
  //Concentration is in species per square meter
  {
    const Concentration d{
      1.0 * boost::units::si::mole / boost::units::si::cubic_meter
    };
    std::stringstream s;
    s << d;
    const std::string t{s.str()};
    //std::cerr << t << std::endl;
    BOOST_CHECK(t.substr(t.size() - 8, 8) == "m^-3 mol");
  }
  //Concentration uses a dot as a seperator
  {
    const Concentration d{12.34 * boost::units::si::mole / boost::units::si::cubic_meter};
    std::stringstream s;
    s << d;
    const std::string t{s.str()};
    BOOST_CHECK(t == "12.34 m^-3 mol");
  }
  //Concentration file I/O, one Concentration
  {
    const Concentration d{12.34 * boost::units::si::mole / boost::units::si::cubic_meter};
    const std::string filename{"ribi_units_concentration_1.txt"};
    {
      std::ofstream f{filename};
      f << d;
    }
    std::ifstream f{filename};
    Concentration d_too;
    f >> d_too;
    BOOST_CHECK(d == d_too);
    std::remove(filename.c_str());
  }
  //Concentration file I/O, two Concentration
  {
    const Concentration a{12.34 * boost::units::si::mole / boost::units::si::cubic_meter};
    const Concentration b{23.45 * boost::units::si::mole / boost::units::si::cubic_meter};
    const std::string filename{"ribi_units_concentration_2.txt"};
    {
      std::ofstream f{filename};
      f << a << " " << b;
    }
    std::ifstream f{filename};
    Concentration a_too;
    Concentration b_too;
    f >> a_too >> b_too;
    BOOST_CHECK(a == a_too);
    BOOST_CHECK(b == b_too);
    std::remove(filename.c_str());
  }
}

#pragma GCC diagnostic pop
