/* This program is free software. It comes without any warranty, to
* the extent permitted by applicable law. You can redistribute it
* and/or modify it under the terms of the Do What The Fuck You Want
* To Public License, Version 2, as published by Sam Hocevar. See
* http://sam.zoy.org/wtfpl/COPYING for more details. */

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
 * The PMC tuple is just a typedef for boost tuple!
 * This could be swapped out for C++11 tuple in the future.
 * Unlike the other containers, the template arguments
 * need to be specified based on the tuple length.
 * Example: PMCTuple<PMCC> or PMCTuple<PMCC, PMCC>
 **********************************************************************/
#include <boost/tuple/tuple.hpp>
#include <boost/tuple/tuple_comparison.hpp>
#define PMCTuple boost::tuple
#define PMCTier boost::tie

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

#endif /*INCLUDED_PMC_CONTAINERS_HPP*/
