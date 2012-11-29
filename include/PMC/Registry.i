// Copyright (C) by Josh Blum. See LICENSE.txt for licensing information.

/***********************************************************************
 * PMC Python SWIG support file: include me to add custom types
 **********************************************************************/

#ifndef INCLUDED_PMC_REGISTRY_I
#define INCLUDED_PMC_REGISTRY_I

%{
#include <PMC/PMC.hpp>
%}

////////////////////////////////////////////////////////////////////////
// http://www.swig.org/Doc2.0/Library.html#Library_stl_exceptions
////////////////////////////////////////////////////////////////////////
%include <exception.i>

%exception
{
    try{$action}
    catch (const std::exception& e)
    {SWIG_exception(SWIG_RuntimeError, e.what());}
}

%import <PMC/PMC.i>

/***********************************************************************
 * DECL_PMC_SWIG_TYPE helper macro declares:
 *  - pmc_is_<typename> - tests if a PMC is typename
 *  - pmc_to_<typename> - converts PMC to swig object
 *  - <typename>_to_pmc - converts swig object to PMC
 **********************************************************************/
%define DECL_PMC_SWIG_TYPE(type, cname)
%inline %{

bool pmc_is_ ## cname(const PMCC &p)
{
    return p.is<type >();
}

const type &pmc_to_ ## cname(const PMCC &p)
{
    return p.as<type >();
}

PMC cname ## _to_pmc(const type &p)
{
    return PMC_M(p);
}

%}

%enddef

////////////////////////////////////////////////////////////////////////
// Convenience import for python registry code
////////////////////////////////////////////////////////////////////////
%pythoncode %{

from PMC import *

%}

#endif /*INCLUDED_PMC_REGISTRY_I*/
