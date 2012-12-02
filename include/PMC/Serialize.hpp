// Copyright (C) by Josh Blum. See LICENSE.txt for licensing information.

#ifndef INCLUDED_PMC_SERIALIZE_HPP
#define INCLUDED_PMC_SERIALIZE_HPP

#include <boost/serialization/export.hpp>
#include <PMC/Detail/Serialize.hpp>

#define PMC_SERIALIZE_EXPORT(type, key) \
    BOOST_CLASS_EXPORT_KEY2(PMCImplContainer< type >, key) \
    BOOST_CLASS_EXPORT_IMPLEMENT(PMCImplContainer< type >)

#endif /*INCLUDED_PMC_SERIALIZE_HPP*/
