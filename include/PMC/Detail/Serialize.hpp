// Copyright (C) by Josh Blum. See LICENSE.txt for licensing information.

#ifndef INCLUDED_PMC_DETAIL_SERIALIZE_HPP
#define INCLUDED_PMC_DETAIL_SERIALIZE_HPP

#include <PMC/Config.hpp>
#include <PMC/PMC.hpp>

/***********************************************************************
 * Need empty serialize for impl super-class
 **********************************************************************/
template<class Archive>
void serialize(Archive &, PMCImpl &, const unsigned int){}

/***********************************************************************
 * Implement serialize for all container instantiations
 **********************************************************************/
#include <boost/serialization/base_object.hpp>

template <typename ValueType> template <class Archive>
void PMCImplContainer<ValueType>::serialize(Archive &ar, const unsigned int)
{
    boost::serialization::base_object<PMCImpl>(*this);
    ar & value;
}

/***********************************************************************
 * PMCC split serialization load and save
 **********************************************************************/
#include <boost/serialization/split_free.hpp>

namespace boost { namespace serialization {
template<class Archive>
void save(Archive & ar, const PMCC &t, unsigned int version)
{
    const bool is_null = not t;
    ar & is_null;
    if (is_null) return;

    const PMCImpl *base = t.get();
    ar & base;

    //TODO save is intern
}
template<class Archive>
void load(Archive & ar, PMCC &t, unsigned int version)
{
    bool is_null = true;
    ar & is_null;
    if (is_null) return;

    PMCImpl *base = t.get();
    ar & base;
    t.reset(base);

    //TODO restore is intern and intern()
}
}}

BOOST_SERIALIZATION_SPLIT_FREE(PMCC)

/***********************************************************************
 * register the "primitive" types
 **********************************************************************/
PMC_SERIALIZE_EXPORT(bool)

//TODO cstdint types

PMC_SERIALIZE_EXPORT(char)
PMC_SERIALIZE_EXPORT(short)
PMC_SERIALIZE_EXPORT(int)
PMC_SERIALIZE_EXPORT(long)
PMC_SERIALIZE_EXPORT(long long)

PMC_SERIALIZE_EXPORT(unsigned char)
PMC_SERIALIZE_EXPORT(unsigned short)
PMC_SERIALIZE_EXPORT(unsigned int)
PMC_SERIALIZE_EXPORT(unsigned long)
PMC_SERIALIZE_EXPORT(unsigned long long)

PMC_SERIALIZE_EXPORT(float)
PMC_SERIALIZE_EXPORT(double)

#include <complex>
#include <boost/serialization/complex.hpp>

PMC_SERIALIZE_EXPORT(std::complex<float>)
PMC_SERIALIZE_EXPORT(std::complex<double>)

#include <string>

PMC_SERIALIZE_EXPORT(std::string)

#include <PMC/Containers.hpp>
#include <boost/serialization/map.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/serialization/set.hpp>
#include <boost/serialization/array.hpp>

PMC_SERIALIZE_EXPORT(PMCDict)
PMC_SERIALIZE_EXPORT(PMCList)
PMC_SERIALIZE_EXPORT(PMCSet)

template <size_t size> template <class Archive>
void PMCTuple<size>::serialize(Archive &ar, const unsigned int)
{
    boost::array<PMCC, size> &p = *this;
    ar & p;
}

template <> template <class Archive>
void PMCTuple<0>::serialize(Archive &ar, const unsigned int)
{
    //NOP - size 0 tuple
}

PMC_SERIALIZE_EXPORT(PMCTuple<0>)
PMC_SERIALIZE_EXPORT(PMCTuple<1>)
PMC_SERIALIZE_EXPORT(PMCTuple<2>)
PMC_SERIALIZE_EXPORT(PMCTuple<3>)
PMC_SERIALIZE_EXPORT(PMCTuple<4>)
PMC_SERIALIZE_EXPORT(PMCTuple<5>)
PMC_SERIALIZE_EXPORT(PMCTuple<6>)
PMC_SERIALIZE_EXPORT(PMCTuple<7>)
PMC_SERIALIZE_EXPORT(PMCTuple<8>)
PMC_SERIALIZE_EXPORT(PMCTuple<9>)
PMC_SERIALIZE_EXPORT(PMCTuple<10>)
PMC_SERIALIZE_EXPORT(PMCTuple<11>)

#endif /*INCLUDED_PMC_DETAIL_SERIALIZE_HPP*/
