// Copyright (C) by Josh Blum. See LICENSE.txt for licensing information.

#ifndef INCLUDED_PMC_SERIALIZE_HPP
#define INCLUDED_PMC_SERIALIZE_HPP

#include <PMC/PMC.hpp>

//! Required headers for class export macro
#include <boost/serialization/export.hpp>
#include <boost/serialization/extended_type_info.hpp>

/*!
 * Export a type into the serialization environment.
 * This is a registration for boost archive polymorphic.
 * Its recommended to make this call once in a cpp file.
 * Example: PMC_SERIALIZE_EXPORT(FooBar, "PMC<FooBar>")
 */
#define PMC_SERIALIZE_EXPORT(type, key) \
    BOOST_CLASS_EXPORT_GUID(PMCImplContainer< type >, key)

//! Serialization for PMCImpl
template<class Archive>
void serialize(Archive &, PMCImpl &, const unsigned int);

//! Serialization for PMCImpl derived classes
template <class Archive, typename ValueType>
void serialize(Archive &ar, PMCImplContainer<ValueType> &t, const unsigned int);

//! Serialization for PMCC base class
namespace boost { namespace serialization {
template<class Archive>
void save(Archive & ar, const PMCC &t, unsigned int version);
template<class Archive>
void load(Archive & ar, PMCC &t, unsigned int version);
}}

//! Include the PMCC templated serialize implementation
#include <PMC/Detail/Serialize.hpp>

//! Required headers to register with polymorphic archive
#include <boost/archive/polymorphic_iarchive.hpp>
#include <boost/archive/polymorphic_oarchive.hpp>

#endif /*INCLUDED_PMC_SERIALIZE_HPP*/
