// Copyright (C) by Josh Blum. See LICENSE.txt for licensing information.

#ifndef INCLUDED_PMC_SERIALIZE_HPP
#define INCLUDED_PMC_SERIALIZE_HPP

#include <boost/serialization/export.hpp>
#include <boost/serialization/extended_type_info.hpp>
#include <PMC/Detail/Serialize.hpp>

#if defined(PMC_SERIALIZE_DECLARE)

    #define PMC_SERIALIZE_EXPORT(type, key) \
    BOOST_CLASS_EXPORT_KEY2(PMCImplContainer< type >, key)

#elif defined(PMC_SERIALIZE_IMPLEMENT)

    #define PMC_SERIALIZE_EXPORT(type, key) \
    BOOST_CLASS_EXPORT_IMPLEMENT(PMCImplContainer< type >)

#else

    #define PMC_SERIALIZE_EXPORT(type, key) \
    BOOST_CLASS_EXPORT_GUID(PMCImplContainer< type >, key)

#endif

#endif /*INCLUDED_PMC_SERIALIZE_HPP*/
