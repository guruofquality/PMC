// Copyright (C) by Josh Blum. See LICENSE.txt for licensing information.

#ifndef INCLUDED_PMC_SERIALIZE_HPP
#define INCLUDED_PMC_SERIALIZE_HPP

#include <PMC/Config.hpp>
#include <PMC/PMC.hpp>
#include <string>
#include <iostream>

#include <boost/serialization/split_free.hpp>


#include <iostream>

#include <boost/serialization/export.hpp>
#include <boost/serialization/base_object.hpp>

template <typename ValueType> template <class Archive>
void PMCImplContainer<ValueType>::serialize(Archive &ar, const unsigned int)
{
    boost::serialization::base_object<PMCImpl>(*this);
    ar & value;
}

template<class Archive>
void serialize(Archive &, PMCImpl &, const unsigned int){}

namespace boost { namespace serialization {
template<class Archive>
void save(Archive & ar, const PMCC &t, unsigned int version)
{
    const PMCImpl *base = t.get();
    ar & base;
}
template<class Archive>
void load(Archive & ar, PMCC &t, unsigned int version)
{
    PMCImpl *base = t.get();
    ar & base;
    t.reset(base);
}
}}

BOOST_SERIALIZATION_SPLIT_FREE(PMCC)


#endif /*INCLUDED_PMC_SERIALIZE_HPP*/
