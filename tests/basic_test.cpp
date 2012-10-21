#include <boost/test/unit_test.hpp>
#include <iostream>

#include <PMC/PMC.hpp>

BOOST_AUTO_TEST_CASE(test_null)
{
    PMC null_pmc;
    BOOST_CHECK(not null_pmc);
    null_pmc = PMC::make(1);
    BOOST_CHECK(null_pmc);
    null_pmc.reset();
    BOOST_CHECK(not null_pmc);
}

BOOST_AUTO_TEST_CASE(test_cast)
{
    PMC x0 = PMC::make(int(42));
    BOOST_CHECK_EQUAL(x0.cast<int>(), 42);

    PMC x1 = PMC::make(double(4.2));
    BOOST_CHECK_EQUAL(x1.cast<double>(), 4.2);
}

BOOST_AUTO_TEST_CASE(test_cast_errors)
{
    PMC x0 = PMC::make(int(42));
    PMC x1 = PMC::make(double(4.2));
    PMC x2;

    BOOST_CHECK_THROW(x0.cast<long long>(), std::logic_error);
    BOOST_CHECK_THROW(x1.cast<float>(), std::logic_error);
    BOOST_CHECK_THROW(x2.cast<float>(), std::logic_error);
}

BOOST_AUTO_TEST_CASE(test_equals)
{
    PMC x0 = PMC::make(int(42));
    PMC x1 = PMC::make(int(42));
    BOOST_CHECK_EQUAL(x0, x1);

    PMC v0 = PMC::make(std::vector<int>());
    v0.cast<std::vector<int> >().push_back(4);
    v0.cast<std::vector<int> >().push_back(2);

    PMC v1 = PMC::make(std::vector<int>());
    v1.cast<std::vector<int> >().push_back(4);
    v1.cast<std::vector<int> >().push_back(2);
    BOOST_CHECK_EQUAL(v0, v1);
}

BOOST_AUTO_TEST_CASE(test_constness_builds)
{
    //not really a unit test, but should compile
    PMC x0 = PMC::make(int(42));
    const PMC &x1 = x0;
    PMCC x2 = PMC::make(int(42));

    const int &x0_const_ref = x0.cast<int>();
    const int &x1_const_ref = x1.cast<int>();
    const int &x2_const_ref = x2.cast<int>();

    int &x0_rw_ref = x0.cast<int>();
    //int &x1_rw_ref = x1.cast<int>(); //should not compile
    //int &x2_rw_ref = x2.cast<int>(); //should not compile
}

BOOST_AUTO_TEST_CASE(test_constness)
{
    PMC x0 = PMC::make(int(42));
    PMCC x1 = PMC::make(int(42));
    BOOST_CHECK_EQUAL(x0.cast<int>(), 42);
    BOOST_CHECK_EQUAL(x1.cast<int>(), 42);
    BOOST_CHECK_EQUAL(x0, x1);
}
