// Copyright (C) by Josh Blum. See LICENSE.txt for licensing information.

#include <PMC/PMC.hpp>
#include <stdexcept>
#include <complex>

template <typename InType, typename OutType>
void complex_to_x(const std::complex<InType> &in, std::complex<OutType> &out)
{
    out = std::complex<OutType>(in.real(), in.imag());
}

template <typename InType, typename OutType>
void complex_to_x(const std::complex<InType> &in, OutType &out)
{
    out = OutType(in.real());
}

template <typename OutType>
OutType pmc_to_x(const PMCC &p)
{
    if (p.is<char>()) return p.as<char>();
    if (p.is<signed char>()) return p.as<signed char>();
    if (p.is<unsigned char>()) return p.as<unsigned char>();
    if (p.is<signed short>()) return p.as<signed short>();
    if (p.is<unsigned short>()) return p.as<unsigned short>();
    if (p.is<signed int>()) return p.as<signed int>();
    if (p.is<unsigned long>()) return p.as<unsigned long>();
    if (p.is<signed long>()) return p.as<signed long>();
    if (p.is<signed long long>()) return p.as<signed long long>();
    if (p.is<unsigned long long>()) return p.as<unsigned long long>();
    if (p.is<float>()) return p.as<float>();
    if (p.is<double>()) return p.as<double>();
    if (p.is<std::complex<float> >())
    {
        OutType out; complex_to_x(p.as<std::complex<float> >(), out); return out;
    }
    if (p.is<std::complex<double> >())
    {
        OutType out; complex_to_x(p.as<std::complex<double> >(), out); return out;
    }
    throw std::domain_error("this pmc is not a number");
}

PMCC PMC_impl_safe_convert(const PMCC *p, const std::type_info &type)
{
    if (p->type() == type) return *p;

    //try to convert to an integer type
    try
    {
        #define try_pmt_to_x(t) if (type == typeid(t)) return PMC_M(pmc_to_x<t >(*p));

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
    }
    catch(const std::domain_error &){}

    //TODO try to deal with std::vector for numeric arrays at some point

    return *p;
}
