// Copyright (C) by Josh Blum. See LICENSE.txt for licensing information.

#ifndef INCLUDED_PMC_SERIALIZE_HPP
#define INCLUDED_PMC_SERIALIZE_HPP

#include <boost/serialization/export.hpp>

#define PMC_SERIALIZE_EXPORT_HELP(type) \
    BOOST_CLASS_EXPORT_KEY2(type, #type) \
    BOOST_CLASS_EXPORT_IMPLEMENT(type)

#define PMC_SERIALIZE_EXPORT(type) \
    PMC_SERIALIZE_EXPORT_HELP(PMCImplContainer< type >)

#include <PMC/Detail/Serialize.hpp>

#endif /*INCLUDED_PMC_SERIALIZE_HPP*/
