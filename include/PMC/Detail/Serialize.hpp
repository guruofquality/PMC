// Copyright (C) by Josh Blum. See LICENSE.txt for licensing information.

#ifndef INCLUDED_PMC_DETAIL_SERIALIZE_HPP
#define INCLUDED_PMC_DETAIL_SERIALIZE_HPP

/***********************************************************************
 * Need empty serialize for impl super-class
 **********************************************************************/
template<class Archive>
void serialize(Archive &, PMCImpl &, const unsigned int){}

/***********************************************************************
 * Implement serialize for all container instantiations
 **********************************************************************/
#include <boost/serialization/base_object.hpp>

template <class Archive, typename ValueType>
void serialize(Archive &ar, PMCImplContainer<ValueType> &t, const unsigned int)
{
    boost::serialization::base_object<PMCImpl>(t);
    ar & t.value;
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

    ar & t->intern;
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

    bool intern = true;
    ar & intern;
    if (intern) t = t.intern();
}
}}

BOOST_SERIALIZATION_SPLIT_FREE(PMCC)

#endif /*INCLUDED_PMC_DETAIL_SERIALIZE_HPP*/
