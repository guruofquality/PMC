#include <boost/test/unit_test.hpp>
#include <iostream>



#include <PMC/PMC.hpp>

namespace boost {
namespace serialization {

template<class Archive>
void serialize(Archive & ar, PMCC & p, const unsigned int version)
{
}

} // namespace serialization
} // namespace boost

BOOST_AUTO_TEST_CASE(test_nothing)
{
    
}
