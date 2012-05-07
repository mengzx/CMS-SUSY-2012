#include <boost/python.hpp>
#include "TauFakeB.hh"
using namespace boost::python;

BOOST_PYTHON_MODULE(libzmeng) {

  class_<Operation::TauFakeB, bases<Operation::_Base> >( "TauFakeB",
                    init<const Utils::ParameterSet&>());

}
