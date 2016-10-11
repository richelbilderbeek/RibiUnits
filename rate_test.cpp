#include "rate.h"

#include <fstream>
#include <boost/units/io.hpp>
#include "speciesdensity.h"

using namespace ribi::units;

// Boost.Test does not play well with -Weffc++
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE(ribi_units_rate)
{
  //Species density is in species per square meter
  {
    const Rate d{
      1.0 * boost::units::si::per_second};
    std::stringstream s;
    s << d;
    const std::string t{s.str()};
    //std::cerr << t << std::endl;
    BOOST_CHECK(t.substr(t.size() - 4, 4) == "s^-1");
  }
  //Species density uses a dot as a seperator
  {
    const Rate d{12.34 * boost::units::si::per_second};
    std::stringstream s;
    s << d;
    const std::string t{s.str()};
    BOOST_CHECK(t == "12.34 s^-1");
  }
  //Species growth can be multiplied by an area to obtain the growth rate
  {
    using Area = boost::units::quantity<boost::units::si::area>;
    const Rate d{0.1 * boost::units::si::per_second};
    const Area a(123.4 * boost::units::si::square_meter);
    const auto n = d * a;
    std::stringstream s;
    s << n;
    const std::string t{s.str()};
    BOOST_CHECK(t.substr(t.size() - 4, 4) == "s^-1");
  }
  //Species density file I/O, one Rate
  {
    const Rate d{12.34 * boost::units::si::per_second};
    const std::string filename{"ribi_units_rate_1.txt"};
    {
      std::ofstream f{filename};
      f << d;
    }
    std::ifstream f{filename};
    Rate d_too;
    f >> d_too;
    BOOST_CHECK(d == d_too);
    std::remove(filename.c_str());
  }
  //Species density file I/O, two Rate
  {
    const Rate a{12.34 * boost::units::si::per_second};
    const Rate b{23.45 * boost::units::si::per_second};
    const std::string filename{"ribi_units_rate_2.txt"};
    {
      std::ofstream f{filename};
      f << a << " " << b;
    }
    std::ifstream f{filename};
    Rate a_too;
    Rate b_too;
    f >> a_too >> b_too;
    BOOST_CHECK(a == a_too);
    BOOST_CHECK(b == b_too);
    std::remove(filename.c_str());
  }
}

#pragma GCC diagnostic pop
