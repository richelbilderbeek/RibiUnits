#include "concentrationchange.h"

#include <set>
#include <fstream>
#include <boost/units/io.hpp>
#include "concentration.h"
#include "rate.h"

using namespace ribi::units;

// Boost.Test does not play well with -Weffc++
#pragma GCC diagnostic push

#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE(ribi_units_concentrationchange)
{
  using ConcentrationChange = boost::units::quantity<boost::units::si::concentration_change>;
  //Concentration density is in species per square meter
  {
    const ConcentrationChange d{
      1.0 * boost::units::si::mole_per_cubic_meter_per_second};
    std::stringstream s;
    s << d;
    const std::string t{s.str()};
    const std::string measured{t.substr(t.size() - 13,13)};
    const std::set<std::string> expected = { "m^-3 mol s^-1", "m^-3 s^-1 mol"};
    BOOST_CHECK(expected.count(measured) == 1);
  }
  //Concentration density uses a dot as a seperator
  {
    const ConcentrationChange d{12.34 * boost::units::si::mole_per_cubic_meter_per_second};
    std::stringstream s;
    s << d;
    const std::string t{s.str()};
    const std::set<std::string> expected = { "12.34 m^-3 mol s^-1", "12.34 m^-3 s^-1 mol"};
    BOOST_CHECK(expected.count(t) == 1);
  }
  //Concentration density file I/O, one ConcentrationChange
  {
    const ConcentrationChange d{12.34 * boost::units::si::mole_per_cubic_meter_per_second};
    const std::string filename{"ribi_units_concentrationchange_1.txt"};
    {
      std::ofstream f{filename};
      f << d;
    }
    std::ifstream f{filename};
    ConcentrationChange d_too;
    f >> d_too;
    BOOST_CHECK(d == d_too);
    std::remove(filename.c_str());
  }
  //Concentration density file I/O, two ConcentrationChange
  {
    const ConcentrationChange a{12.34 * boost::units::si::mole_per_cubic_meter_per_second};
    const ConcentrationChange b{23.45 * boost::units::si::mole_per_cubic_meter_per_second};
    const std::string filename{"ribi_units_concentrationchange_2.txt"};
    {
      std::ofstream f{filename};
      f << a << " " << b;
    }
    std::ifstream f{filename};
    ConcentrationChange a_too;
    ConcentrationChange b_too;
    f >> a_too >> b_too;
    BOOST_CHECK(a == a_too);
    BOOST_CHECK(b == b_too);
    std::remove(filename.c_str());
  }
  //Combining ConcentrationDensity, ConcentrationChange and Rate
  //Exponential growth
  {
    const double n_unitless{0.7};
    const double r_unitless{1.3};
    const Concentration n{n_unitless * boost::units::si::mole_per_cubic_meter};
    const Rate r{r_unitless * boost::units::si::per_second};
    const ConcentrationChange dndt{n * r};
    BOOST_CHECK_EQUAL(dndt.value(), n_unitless * r_unitless);
  }
  //Logistic growth
  {
    const double n_unitless{0.7};
    const double k_unitless{2.0};
    const double r_unitless{1.3};
    const Concentration n{n_unitless * boost::units::si::mole_per_cubic_meter};
    const Concentration k{k_unitless * boost::units::si::mole_per_cubic_meter};
    const Rate r{r_unitless * boost::units::si::per_second};
    const ConcentrationChange dndt{ n * r * (1.0 - (n / k))};
    const auto measured = dndt.value();
    const auto expected = n_unitless * r_unitless * (1.0 - (n_unitless / k_unitless));
    BOOST_CHECK(std::abs(measured - expected) < 0.00001);
  }
}

#pragma GCC diagnostic pop
