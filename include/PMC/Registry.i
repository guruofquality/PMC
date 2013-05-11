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

/***********************************************************************
 * REG_PMC_SWIG_TYPE helper macro:
 *  - registers the conversion in the simple no-brainer case
 **********************************************************************/
#ifdef SWIGPYTHON
%define REG_PMC_SWIG_TYPE(cname, pytype)
%pythoncode %{

RegisterPy2PMC(
    is_py = lambda x: isinstance(x, pytype),
    py2pmc = cname ## _to_pmc,
)

RegisterPMC2Py(
    is_pmc = pmc_is_ ## cname,
    pmc2py = pmc_to_ ## cname,
)

%}

%enddef
#endif //SWIGPYTHON

/***********************************************************************
 * REG_PMC_SWIG_TYPE helper macro:
 *  - registers the conversion in the simple no-brainer case
 **********************************************************************/
#ifdef SWIGCSHARP
%define REG_PMC_SWIG_TYPE(cname, cstype, parent)

%pragma(csharp) moduleimports=%{

class cname ## Register : PMCConverter
{

    static PMCC cname ## _to_pmc_helper(System.Object obj)
    {
        return parent.cname ## _to_pmc((cstype)obj);
    }

    static cname ## Register()
    {
        PMCRegistry.Register(typeof(cstype), cname ## _to_pmc_helper);
    }
}

public partial class PMCC
{
    public static implicit operator cstype(PMCC p)
    {
        return parent.pmc_to_ ## cname(p);
    }
}

%}

%enddef
#endif //SWIGCSHARP

////////////////////////////////////////////////////////////////////////
// Convenience import for python registry code
////////////////////////////////////////////////////////////////////////
#ifdef SWIGPYTHON
%pythoncode %{

from PMC import *

%}
#endif

#endif /*INCLUDED_PMC_REGISTRY_I*/
