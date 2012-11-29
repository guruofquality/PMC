// Copyright (C) by Josh Blum. See LICENSE.txt for licensing information.

#include <boost/test/unit_test.hpp>
#include <iostream>

#include <PMC/PMC.hpp>

PMC_INLINE bool operator==(const PMCC &lhs, const PMCC &rhs)
{
    return PMCCompare(lhs, rhs);
}

BOOST_AUTO_TEST_CASE(test_null)
{
    PMC null_pmc;
    BOOST_CHECK(not null_pmc);
    null_pmc = PMC_M(1);
    BOOST_CHECK(null_pmc);
    null_pmc.reset();
    BOOST_CHECK(not null_pmc);
}

BOOST_AUTO_TEST_CASE(test_as)
{
    PMC x0 = PMC_M(int(42));
    BOOST_CHECK_EQUAL(x0.as<int>(), 42);

    PMC x1 = PMC_M(double(4.2));
    BOOST_CHECK_EQUAL(x1.as<double>(), 4.2);
}

BOOST_AUTO_TEST_CASE(test_as_errors)
{
    PMC x0 = PMC_M(int(42));
    PMC x1 = PMC_M(double(4.2));
    PMC x2;

    BOOST_CHECK_THROW(x0.as<long long>(), std::logic_error);
    BOOST_CHECK_THROW(x1.as<float>(), std::logic_error);
    BOOST_CHECK_THROW(x2.as<float>(), std::logic_error);
}

BOOST_AUTO_TEST_CASE(test_equals)
{
    PMC x0 = PMC_M(int(42));
    PMC x1 = PMC_M(int(42));
    BOOST_CHECK_EQUAL(x0, x1);

    PMC v0 = PMC_M(std::vector<int>());
    v0.as<std::vector<int> >().push_back(4);
    v0.as<std::vector<int> >().push_back(2);

    PMC v1 = PMC_M(std::vector<int>());
    v1.as<std::vector<int> >().push_back(4);
    v1.as<std::vector<int> >().push_back(2);
    BOOST_CHECK_EQUAL(v0, v1);
}

BOOST_AUTO_TEST_CASE(test_constness_builds)
{
    //not really a unit test, but should compile
    PMC x0 = PMC_M(int(42));
    const PMC &x1 = x0;
    PMCC x2 = PMC_M(int(42));

    const int &x0_const_ref = x0.as<int>();
    const int &x1_const_ref = x1.as<int>();
    const int &x2_const_ref = x2.as<int>();

    int &x0_rw_ref = x0.as<int>();
    int &x1_rw_ref = x1.as<int>();
    //int &x2_rw_ref = x2.as<int>(); //should not compile

    PMCC x3 = x0;
    PMCC x4 = x2;
    //PMC x5 = x2; //should not compile
}

BOOST_AUTO_TEST_CASE(test_constness)
{
    PMC x0 = PMC_M(int(42));
    PMCC x1 = PMC_M(int(42));
    BOOST_CHECK_EQUAL(x0.as<int>(), 42);
    BOOST_CHECK_EQUAL(x1.as<int>(), 42);
    BOOST_CHECK_EQUAL(x0, x1);
}

BOOST_AUTO_TEST_CASE(test_floats)
{
    PMC f32 = PMC_M(float(4.2));
    BOOST_CHECK(f32.is<float>());
    BOOST_CHECK(not f32.is<double>());

    PMC f64 = PMC_M(double(4.2));
    BOOST_CHECK(not f64.is<float>());
    BOOST_CHECK(f64.is<double>());
}
