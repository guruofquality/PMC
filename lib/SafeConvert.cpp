// Copyright (C) by Josh Blum. See LICENSE.txt for licensing information.

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning (disable:4244)  // conversion possible loss of data
#endif //_MSC_VER

#include <PMC/PMC.hpp>
#include <PMC/Containers.hpp>
#include <boost/foreach.hpp>
#include <complex>

//! Some silly name for an object we will throw as an exception
struct CantTouchThis{};

/***********************************************************************
 * templated converver for various numeric formats
 **********************************************************************/
template <typename InType, typename OutType>
void convnum(const std::complex<InType> &in, std::complex<OutType> &out)
{
    out = std::complex<OutType>(OutType(in.real()), OutType(in.imag()));
}

template <typename InType, typename OutType>
void convnum(const std::complex<InType> &in, OutType &out)
{
    out = OutType(in.real());
}

template <typename InType, typename OutType>
void convnum(const InType &in, OutType &out)
{
    out = OutType(in);
}

/***********************************************************************
 * Special derived class to make a PMCC w/ explicit constructor
 * (used in the conversion of PMCList to OutType)
 **********************************************************************/
struct PMCD : PMCC
{
    PMCD(void){}

    template <typename ValueType>
    explicit PMCD(const ValueType &v)
    {
        this->reset(PMC_M(v).get());
    }
};

/***********************************************************************
 * convert a PMC w/ a numeric type to the given output type
 **********************************************************************/
template <typename OutType>
OutType pmc_to_x(const PMCC &p)
{
    #define pmc_to_x_helper_(t) if (p.is<t >()) \
    {OutType out; convnum(p.as<t >(), out); return out;}
    #define pmc_to_x_helper(t) pmc_to_x_helper_(t) pmc_to_x_helper_(std::complex<t >)
    pmc_to_x_helper(char)
    pmc_to_x_helper(signed char)
    pmc_to_x_helper(unsigned char)
    pmc_to_x_helper(signed short)
    pmc_to_x_helper(unsigned short)
    pmc_to_x_helper(signed int)
    pmc_to_x_helper(unsigned int)
    pmc_to_x_helper(signed long)
    pmc_to_x_helper(unsigned long)
    pmc_to_x_helper(signed long long)
    pmc_to_x_helper(unsigned long long)
    pmc_to_x_helper(float)
    pmc_to_x_helper(double)
    throw CantTouchThis();
}

/***********************************************************************
 * convert a PMC w/ a numeric vector to the given output type
 **********************************************************************/
template <typename OutType>
std::vector<OutType> pmc_to_v(const PMCC &p)
{
    #define pmc_to_v_helper_(t) if (p.is<std::vector<t > >()) \
    { \
        const std::vector<t > &in = p.as<std::vector<t > >(); \
        std::vector<OutType> out(in.size()); \
        for (size_t i = 0; i < in.size(); i++) convnum(in[i], out[i]); \
        return out; \
    }
    #define pmc_to_v_helper(t) pmc_to_v_helper_(t) pmc_to_v_helper_(std::complex<t >)
    pmc_to_v_helper(char)
    pmc_to_v_helper(signed char)
    pmc_to_v_helper(unsigned char)
    pmc_to_v_helper(signed short)
    pmc_to_v_helper(unsigned short)
    pmc_to_v_helper(signed int)
    pmc_to_v_helper(unsigned int)
    pmc_to_v_helper(signed long)
    pmc_to_v_helper(unsigned long)
    pmc_to_v_helper(signed long long)
    pmc_to_v_helper(unsigned long long)
    pmc_to_v_helper(float)
    pmc_to_v_helper(double)

    #define pmc_container_v_helper(t) if (p.is<t >()) \
    { \
        const t &in = p.as<t >(); \
        std::vector<OutType> out(in.size()); \
        for (size_t i = 0; i < in.size(); i++) convnum(pmc_to_x<OutType>(in[i]), out[i]); \
        return out; \
    }
    pmc_container_v_helper(PMCList)
    pmc_container_v_helper(PMCTuple<0>)
    pmc_container_v_helper(PMCTuple<1>)
    pmc_container_v_helper(PMCTuple<2>)
    pmc_container_v_helper(PMCTuple<3>)
    pmc_container_v_helper(PMCTuple<4>)
    pmc_container_v_helper(PMCTuple<5>)
    pmc_container_v_helper(PMCTuple<6>)
    pmc_container_v_helper(PMCTuple<7>)
    pmc_container_v_helper(PMCTuple<8>)
    pmc_container_v_helper(PMCTuple<9>)
    pmc_container_v_helper(PMCTuple<10>)
    pmc_container_v_helper(PMCTuple<11>)

    throw CantTouchThis();
}

/***********************************************************************
 * actual converter implementation
 **********************************************************************/
PMCC PMC_impl_safe_convert(const PMCC *p, const std::type_info &type)
{
    if (p->type() == type) return *p;

    #define try_pmc_to_x_(t) \
    {\
        if (type == typeid(t)) return PMC_M(pmc_to_x<t >(*p)); \
        if (type == typeid(std::vector<t >)) return PMC_M(pmc_to_v<t >(*p)); \
    }
    #define try_pmc_to_x(t) try_pmc_to_x_(t) try_pmc_to_x_(std::complex<t >)

    //check if each output type matches and convert
    try
    {
        try_pmc_to_x(char);
        try_pmc_to_x(signed char);
        try_pmc_to_x(unsigned char);

        try_pmc_to_x(signed short);
        try_pmc_to_x(unsigned short);

        try_pmc_to_x(signed int);
        try_pmc_to_x(unsigned int);

        try_pmc_to_x(signed long);
        try_pmc_to_x(unsigned long);

        try_pmc_to_x(signed long long);
        try_pmc_to_x(unsigned long long);

        try_pmc_to_x(float);
        try_pmc_to_x(double);

        #define try_pmc_to_container(t) if (type == typeid(t)) \
        { \
            const std::vector<PMCD> vec = pmc_to_v<PMCD>(*p); \
            t out; \
            for (size_t i = 0; i < std::min(out.size(), vec.size()); i++) out[i] = vec[i]; \
            return PMC_M(out); \
        }
        if (type == typeid(PMCList)) return PMC_M(pmc_to_v<PMCD>(*p));
        try_pmc_to_container(PMCTuple<0>)
        try_pmc_to_container(PMCTuple<1>)
        try_pmc_to_container(PMCTuple<2>)
        try_pmc_to_container(PMCTuple<3>)
        try_pmc_to_container(PMCTuple<4>)
        try_pmc_to_container(PMCTuple<5>)
        try_pmc_to_container(PMCTuple<6>)
        try_pmc_to_container(PMCTuple<7>)
        try_pmc_to_container(PMCTuple<8>)
        try_pmc_to_container(PMCTuple<9>)
        try_pmc_to_container(PMCTuple<10>)
        try_pmc_to_container(PMCTuple<11>)
    }

    catch(const CantTouchThis &){}

    //vector of strings in
    if (p->is<std::vector<std::string> >() and type == typeid(PMCList))
    {
        PMCList l;
        BOOST_FOREACH(const std::string &e, p->as<std::vector<std::string> >())
        {
            l.push_back(PMC_M(e));
        }
        return PMC_M(l);
    }

    //vector of strings out
    if (p->is<PMCList>() and type == typeid(std::vector<std::string>))
    {
        std::vector<std::string> l;
        BOOST_FOREACH(const PMCC &e, p->as<PMCList>())
        {
            l.push_back(e.as<std::string>());
        }
        return PMC_M(l);
    }

    return *p;
}

#ifdef _MSC_VER
#pragma warning(pop)
#endif //_MSC_VER
