#include "moleculeamount.h"

#include <fstream>
#include <boost/units/io.hpp>

// Boost.Test does not play well with -Weffc++
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE(ribi_units_moleculeamount)
{
  using MoleculeAmount = boost::units::quantity<boost::units::si::molecule_amount>;
  //Can add molecule amounts
  {
    const MoleculeAmount a{1.0 * boost::units::si::molecules_mol};
    const MoleculeAmount b{1.0 * boost::units::si::molecules_mol};
    a + b;
  }
  //Molecule amounts are in mole
  {
    using MoleculeAmount = boost::units::quantity<boost::units::si::molecule_amount>;
    const MoleculeAmount a{1.0 * boost::units::si::molecules_mol};
    std::stringstream s;
    s << a;
    const std::string t{s.str()};
    BOOST_CHECK(!t.empty());
    BOOST_CHECK(t.substr(t.size()-3,3) == "mol");
  }
}

#pragma GCC diagnostic pop
