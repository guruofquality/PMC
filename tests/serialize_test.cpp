// Copyright (C) by Josh Blum. See LICENSE.txt for licensing information.

#include <boost/test/unit_test.hpp>
#include <algorithm>
#include <iostream>

#include <PMC/PMC.hpp>
#include <PMC/SerializeTypes.hpp>
#include <boost/cstdint.hpp>

// include headers that implement a archive in simple text format
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <sstream>

static void loopback_test(PMCC p0)
{
    std::cout << "\ndoing loopback test on " << p0 << std::endl;
    std::stringstream ss;
    boost::archive::text_oarchive oa(ss);

    oa << p0;
    std::cout << "stringstream holds " << ss.str() << std::endl;

    boost::archive::text_iarchive ia(ss);
    PMCC p1;
    ia >> p1;

    BOOST_CHECK(p0.eq(p1));
}

BOOST_AUTO_TEST_CASE(test_integer_types)
{
    loopback_test(PMC_M(char(0)));
    loopback_test(PMC_M(short(0)));
    loopback_test(PMC_M(int(0)));
    loopback_test(PMC_M(long(0)));
    loopback_test(PMC_M((long long)(0)));

    loopback_test(PMC_M((signed char)(0)));
    loopback_test(PMC_M((signed short)(0)));
    loopback_test(PMC_M((signed int)(0)));
    loopback_test(PMC_M((signed long)(0)));
    loopback_test(PMC_M((signed long long)(0)));

    loopback_test(PMC_M((unsigned char)(0)));
    loopback_test(PMC_M((unsigned short)(0)));
    loopback_test(PMC_M((unsigned int)(0)));
    loopback_test(PMC_M((unsigned long)(0)));
    loopback_test(PMC_M((unsigned long long)(0)));

    loopback_test(PMC_M(boost::int8_t(0)));
    loopback_test(PMC_M(boost::int16_t(0)));
    loopback_test(PMC_M(boost::int32_t(0)));
    loopback_test(PMC_M(boost::int64_t(0)));

    loopback_test(PMC_M(boost::uint8_t(0)));
    loopback_test(PMC_M(boost::uint16_t(0)));
    loopback_test(PMC_M(boost::uint32_t(0)));
    loopback_test(PMC_M(boost::uint64_t(0)));
}

BOOST_AUTO_TEST_CASE(test_simple_loopbacks)
{
    loopback_test(PMC()); //null
    loopback_test(PMC_M(true));
    loopback_test(PMC_M(false));
    loopback_test(PMC_M(int(1234)));
    loopback_test(PMC_M(long(6789)));
    loopback_test(PMC_M("hello"));
}

bool myeq(const PMCC &i, const PMCC &j)
{
    return i.eq(j);
}

template <typename T>
static void loopback_test_container(const T &t0)
{
    PMCC p0 = PMC_M(t0);

    std::cout << "doing loopback test on " << p0 << std::endl;
    std::stringstream ss;
    boost::archive::text_oarchive oa(ss);

    oa << p0;
    std::cout << "stringstream holds " << ss.str() << std::endl;

    boost::archive::text_iarchive ia(ss);
    PMCC p1;
    ia >> p1;

    BOOST_CHECK(std::equal(t0.begin(), t0.end(), p1.as<T>().begin(), myeq));
}

BOOST_AUTO_TEST_CASE(test_pmc_tuple_loopback)
{
    PMCTuple<0> t0;
    loopback_test_container(t0);

    PMCTuple<1> t1;
    t1[0] = PMC_M(42);
    loopback_test_container(t1);

    PMCTuple<4> t4;
    t4[0] = PMC_M(5);
    t4[1] = PMC_M(6);
    t4[2] = PMC_M(7);
    t4[3] = PMC_M(8);
    loopback_test_container(t4);
}

BOOST_AUTO_TEST_CASE(test_pmc_list_loopback)
{
    PMCList l0;
    loopback_test_container(l0);

    PMCList l1(1);
    l1[0] = PMC_M(42);
    loopback_test_container(l1);

    PMCList l4(4);
    l4[0] = PMC_M(5);
    l4[1] = PMC_M(6);
    l4[2] = PMC_M(7);
    l4[3] = PMC_M(8);
    loopback_test_container(l4);
}
