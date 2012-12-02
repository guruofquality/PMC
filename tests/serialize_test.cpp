// Copyright (C) by Josh Blum. See LICENSE.txt for licensing information.

#include <boost/test/unit_test.hpp>
#include <iostream>

#include <PMC/PMC.hpp>
#include <PMC/Serialize.hpp>

// include headers that implement a archive in simple text format
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <sstream>


//BOOST_CLASS_EXPORT_GUID(PMCImplContainer<int>, "PMCImplContainer<int>")

BOOST_CLASS_EXPORT_KEY2(PMCImplContainer<int>, "PMCImplContainer<int>")
BOOST_CLASS_EXPORT_IMPLEMENT(PMCImplContainer<int>)

BOOST_AUTO_TEST_CASE(test_foo)
{
    std::stringstream ss;
    boost::archive::text_oarchive oa(ss);

    PMCC p = PMC_M(int(1234));

    oa << p;

    std::cout << "ss " << ss.str() << std::endl;

    boost::archive::text_iarchive ia(ss);
    PMCC p1;
    ia >> p1;

    std::cout << "p1 " << p1 << std::endl;
    std::cout << "p1 " << p1.as<int>() << std::endl;
}
