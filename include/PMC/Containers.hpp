// Copyright (C) by Josh Blum. See LICENSE.txt for licensing information.

#ifndef INCLUDED_PMC_CONTAINERS_HPP
#define INCLUDED_PMC_CONTAINERS_HPP

#include <PMC/PMC.hpp>

/*!
 * \file Containers.hpp
 *
 * This header contains definitions for commonly used typedefs for contains of PMCs.
 * The typedefs are named aptly so they can be used with standard python containers.
 *
 * All types below have conversions with the builtin python container types,
 * and are supported by the PMC to/from Python functions in the library.
 *
 * When using standard container types across the c++/python boundary,
 * the user should consider using the container types in this header
 */

/***********************************************************************
 * The PMC list is a fixed size array of PMCC
 **********************************************************************/
#include <vector>
typedef std::vector<PMCC> PMCList;

/***********************************************************************
 * The PMC tuple is just a typedef for boost::array/std::array.
 * This is an array and not tuple because array is homogeneous.
 * Example: PMCTuple<3> for a tuple of 3 elements.
 **********************************************************************/
#include <boost/array.hpp>
template <size_t size>
struct PMCTuple : boost::array<PMCC, size>
{
    //empty
};

/***********************************************************************
 * The PMC set is a set of PMCC
 **********************************************************************/
#include <set>
typedef std::set<PMCC> PMCSet;

/***********************************************************************
 * The PMC dictionary is a key value mapping of PMCC
 **********************************************************************/
#include <map>
typedef std::map<PMCC, PMCC> PMCDict;

/***********************************************************************
 * The PMC pair may be used when iterating through a PMCDIct
 * Example:
 * const PMCDict &m = p.as<PMCDict>();
 * BOOST_FOREACH(const PMCPair &pr, m)
 * {
 *     //do something with pr
 * }
 **********************************************************************/
#include <utility>
typedef std::pair<PMCC, PMCC> PMCPair;

#endif /*INCLUDED_PMC_CONTAINERS_HPP*/
