// Copyright (C) by Josh Blum. See LICENSE.txt for licensing information.

#ifndef INCLUDED_PMC_SERIALIZE_TYPES_HPP
#define INCLUDED_PMC_SERIALIZE_TYPES_HPP

#include <PMC/Serialize.hpp>
#include <PMC/Containers.hpp>

/***********************************************************************
 * bool
 **********************************************************************/
PMC_SERIALIZE_EXPORT(bool, "PMC<bool>")

/***********************************************************************
 * integer types
 **********************************************************************/
#include <boost/cstdint.hpp>

PMC_SERIALIZE_EXPORT(char, "PMC<char>") //char != signed char != unsigned char

#if (ULONG_MAX == 0xffffffff) || defined(__APPLE__)

//this long is only serializable on 32 bit machines
//use fixed-width typedefs if this sucks
PMC_SERIALIZE_EXPORT(signed long, "PMC<l32>")
PMC_SERIALIZE_EXPORT(unsigned long, "PMC<ul32>")

#else

//this long long is only serializable on 64 bit machines
//use fixed-width typedefs if this sucks
PMC_SERIALIZE_EXPORT(signed long long, "PMC<ll64>")
PMC_SERIALIZE_EXPORT(unsigned long long, "PMC<ull64>")

#endif

PMC_SERIALIZE_EXPORT(boost::int8_t, "PMC<int8>")
PMC_SERIALIZE_EXPORT(boost::int16_t, "PMC<int16>")
PMC_SERIALIZE_EXPORT(boost::int32_t, "PMC<int32>")
PMC_SERIALIZE_EXPORT(boost::int64_t, "PMC<int64>")
PMC_SERIALIZE_EXPORT(boost::uint8_t, "PMC<uint8>")
PMC_SERIALIZE_EXPORT(boost::uint16_t, "PMC<uint16>")
PMC_SERIALIZE_EXPORT(boost::uint32_t, "PMC<uint32>")
PMC_SERIALIZE_EXPORT(boost::uint64_t, "PMC<uint64>")

/***********************************************************************
 * float types
 **********************************************************************/
PMC_SERIALIZE_EXPORT(float, "PMC<float32>")
PMC_SERIALIZE_EXPORT(double, "PMC<float64>")

/***********************************************************************
 * complex float types
 **********************************************************************/
#include <boost/serialization/complex.hpp>

PMC_SERIALIZE_EXPORT(std::complex<float>, "PMC<complex64>")
PMC_SERIALIZE_EXPORT(std::complex<double>, "PMC<complex128>")

/***********************************************************************
 * string
 **********************************************************************/
#include <boost/serialization/string.hpp>

PMC_SERIALIZE_EXPORT(std::string, "PMC<string>")

/***********************************************************************
 * pair
 **********************************************************************/
#include <boost/serialization/utility.hpp>

PMC_SERIALIZE_EXPORT(PMCPair, "PMC<Pair>")

/***********************************************************************
 * dict
 **********************************************************************/
#include <boost/serialization/map.hpp>

PMC_SERIALIZE_EXPORT(PMCDict, "PMC<Dict>")

/***********************************************************************
 * list
 **********************************************************************/
#include <boost/serialization/vector.hpp>

PMC_SERIALIZE_EXPORT(PMCList, "PMC<List>")

/***********************************************************************
 * set
 **********************************************************************/
#include <boost/serialization/set.hpp>

PMC_SERIALIZE_EXPORT(PMCSet, "PMC<Set>")

/***********************************************************************
 * tuple
 **********************************************************************/
#include <boost/serialization/array.hpp>

template <class Archive, size_t size>
void serialize(Archive &ar, PMCTuple<size> &t, const unsigned int)
{
    boost::array<PMCC, size> &p = t;
    ar & p;
}

template <class Archive>
void serialize(Archive &ar, PMCTuple<0> &t, const unsigned int)
{
    //NOP - size 0 tuple
}

PMC_SERIALIZE_EXPORT(PMCTuple<0>, "PMC<Tuple0>")
PMC_SERIALIZE_EXPORT(PMCTuple<1>, "PMC<Tuple1>")
PMC_SERIALIZE_EXPORT(PMCTuple<2>, "PMC<Tuple2>")
PMC_SERIALIZE_EXPORT(PMCTuple<3>, "PMC<Tuple3>")
PMC_SERIALIZE_EXPORT(PMCTuple<4>, "PMC<Tuple4>")
PMC_SERIALIZE_EXPORT(PMCTuple<5>, "PMC<Tuple5>")
PMC_SERIALIZE_EXPORT(PMCTuple<6>, "PMC<Tuple6>")
PMC_SERIALIZE_EXPORT(PMCTuple<7>, "PMC<Tuple7>")
PMC_SERIALIZE_EXPORT(PMCTuple<8>, "PMC<Tuple8>")
PMC_SERIALIZE_EXPORT(PMCTuple<9>, "PMC<Tuple9>")
PMC_SERIALIZE_EXPORT(PMCTuple<10>, "PMC<Tuple10>")
PMC_SERIALIZE_EXPORT(PMCTuple<11>, "PMC<Tuple11>")

#endif /*INCLUDED_PMC_SERIALIZE_TYPES_HPP*/
