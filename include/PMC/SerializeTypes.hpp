// Copyright (C) by Josh Blum. See LICENSE.txt for licensing information.

#ifndef INCLUDED_PMC_SERIALIZE_TYPES_HPP
#define INCLUDED_PMC_SERIALIZE_TYPES_HPP

#include <PMC/Serialize.hpp>
#include <PMC/Containers.hpp>

/***********************************************************************
 * bool
 **********************************************************************/
PMC_SERIALIZE_EXPORT(bool)

/***********************************************************************
 * integer types
 **********************************************************************/
#include <boost/cstdint.hpp>

PMC_SERIALIZE_EXPORT(boost::int8_t)
PMC_SERIALIZE_EXPORT(boost::int16_t)
PMC_SERIALIZE_EXPORT(boost::int32_t)
PMC_SERIALIZE_EXPORT(boost::int64_t)
PMC_SERIALIZE_EXPORT(boost::uint8_t)
PMC_SERIALIZE_EXPORT(boost::uint16_t)
PMC_SERIALIZE_EXPORT(boost::uint32_t)
PMC_SERIALIZE_EXPORT(boost::uint64_t)

/***********************************************************************
 * float types
 **********************************************************************/
PMC_SERIALIZE_EXPORT(float)
PMC_SERIALIZE_EXPORT(double)

/***********************************************************************
 * complex float types
 **********************************************************************/
#include <boost/serialization/complex.hpp>

PMC_SERIALIZE_EXPORT(std::complex<float>)
PMC_SERIALIZE_EXPORT(std::complex<double>)

/***********************************************************************
 * string
 **********************************************************************/
#include <boost/serialization/string.hpp>

PMC_SERIALIZE_EXPORT(std::string)

/***********************************************************************
 * pair
 **********************************************************************/
#include <boost/serialization/utility.hpp>

PMC_SERIALIZE_EXPORT(PMCPair)

/***********************************************************************
 * dict
 **********************************************************************/
#include <boost/serialization/map.hpp>

PMC_SERIALIZE_EXPORT(PMCDict)

/***********************************************************************
 * list
 **********************************************************************/
#include <boost/serialization/vector.hpp>

PMC_SERIALIZE_EXPORT(PMCList)

/***********************************************************************
 * set
 **********************************************************************/
#include <boost/serialization/set.hpp>

PMC_SERIALIZE_EXPORT(PMCSet)

/***********************************************************************
 * tuple
 **********************************************************************/
#include <boost/serialization/array.hpp>

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

#endif /*INCLUDED_PMC_SERIALIZE_TYPES_HPP*/
