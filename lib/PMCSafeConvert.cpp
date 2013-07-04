// Copyright (C) by Josh Blum. See LICENSE.txt for licensing information.

#include <PMC/PMC.hpp>
#include <PMC/Containers.hpp>
#include <complex>

//! Some silly name for an object we will throw as an exception
struct CantTouchThis{};

/***********************************************************************
 * templated converver for various numeric formats
 **********************************************************************/
template <typename InType, typename OutType>
void convnum(const std::complex<InType> &in, std::complex<OutType> &out)
{
    out = std::complex<OutType>(in.real(), in.imag());
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
    #define pmc_to_x_helper(t) if (p.is<t >()) \
    {OutType out; convnum(p.as<t >(), out); return out;}
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
    pmc_to_x_helper(std::complex<float>)
    pmc_to_x_helper(std::complex<double>)
    throw CantTouchThis();
}

/***********************************************************************
 * convert a PMC w/ a numeric vector to the given output type
 **********************************************************************/
template <typename OutType>
std::vector<OutType> pmc_to_v(const PMCC &p)
{
    #define pmc_to_v_helper(t) if (p.is<std::vector<t > >()) \
    { \
        const std::vector<t > &in = p.as<std::vector<t > >(); \
        std::vector<OutType> out(in.size()); \
        for (size_t i = 0; i < in.size(); i++) convnum(in[i], out[i]); \
        return out; \
    }
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
    pmc_to_v_helper(std::complex<float>)
    pmc_to_v_helper(std::complex<double>)

    //special case PMCList
    if (p.is<PMCList>())
    {
        const PMCList &in = p.as<PMCList>();
        std::vector<OutType> out(in.size());
        for (size_t i = 0; i < in.size(); i++)
        {
            convnum(pmc_to_x<OutType>(in[i]), out[i]);
        }
        return out;
    }

    throw CantTouchThis();
}

/***********************************************************************
 * actual converter implementation
 **********************************************************************/
PMCC PMC_impl_safe_convert(const PMCC *p, const std::type_info &type)
{
    if (p->type() == type) return *p;

    #define try_pmt_to_x(t) \
    {\
        if (type == typeid(t)) return PMC_M(pmc_to_x<t >(*p)); \
        if (type == typeid(std::vector<t >)) return PMC_M(pmc_to_v<t >(*p)); \
    }

    //check if each output type matches and convert
    try
    {
        try_pmt_to_x(char);
        try_pmt_to_x(signed char);
        try_pmt_to_x(unsigned char);

        try_pmt_to_x(signed short);
        try_pmt_to_x(unsigned short);

        try_pmt_to_x(signed int);
        try_pmt_to_x(unsigned int);

        try_pmt_to_x(signed long);
        try_pmt_to_x(unsigned long);

        try_pmt_to_x(signed long long);
        try_pmt_to_x(unsigned long long);

        try_pmt_to_x(float);
        try_pmt_to_x(double);

        try_pmt_to_x(std::complex<float>);
        try_pmt_to_x(std::complex<double>);

        //special case PMCList
        if (type == typeid(PMCList)) return PMC_M(pmc_to_v<PMCD>(*p));
    }
    catch(const CantTouchThis &){}

    return *p;
}
