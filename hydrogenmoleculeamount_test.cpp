#include "hydrogenmoleculeamount.h"

#include <fstream>
#include <boost/units/io.hpp>

// Boost.Test does not play well with -Weffc++
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE(ribi_units_hydrogenmoleculeamount)
{
  using HydrogenMoleculeAmount = boost::units::quantity<boost::units::si::hydrogen_molecule_amount>;
  //Hydrogen molecule amounts can be displayed
  {
    const HydrogenMoleculeAmount sa{1.0 * boost::units::si::hydrogen_molecules_mol};
    std::stringstream s;
    s << sa;
    const std::string t{s.str()};
    BOOST_CHECK(!t.empty());
  }
  //#define FIX_ISSUE_999
  #ifdef FIX_ISSUE_999
  //Hydrogen molecule amounts are in mole
  {
    const HydrogenMoleculeAmount sa{1.0 * boost::units::si::hydrogen_molecules_mol};
    std::stringstream s;
    s << sa;
    const std::string t{s.str()};
    BOOST_CHECK(!t.empty());
    std::cout << t << std::endl;
    BOOST_CHECK(t.substr(t.size()-3,3) == "mol");
  }
  #endif
  //Can add hydrogen molecule amounts
  {
    const double a{1.0};
    const double b{2.0};
    const double c{a + b};
    const HydrogenMoleculeAmount sa{a * boost::units::si::hydrogen_molecules_mol};
    const HydrogenMoleculeAmount sb{b * boost::units::si::hydrogen_molecules_mol};
    const HydrogenMoleculeAmount sc{sa + sb};
    BOOST_CHECK(sc == HydrogenMoleculeAmount{c * boost::units::si::hydrogen_molecules_mol});
  }
}

#pragma GCC diagnostic pop
