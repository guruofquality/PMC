// Copyright (C) by Josh Blum. See LICENSE.txt for licensing information.

/***********************************************************************
 * PMC Python SWIG support file: include me to add custom types
 **********************************************************************/

#ifndef INCLUDED_PMC_PMC_I
#define INCLUDED_PMC_PMC_I

%{
#include <PMC/PMC.hpp>
#include <sstream>
%}

////////////////////////////////////////////////////////////////////////
// comprehend base class
////////////////////////////////////////////////////////////////////////
#define SWIG_INTRUSIVE_PTR_NAMESPACE boost
%include <intrusive_ptr.i>
%template (boost_intrusive_ptr_pmc_impl) boost::intrusive_ptr<PMCImpl>;

////////////////////////////////////////////////////////////////////////
// comprehend PMC types
////////////////////////////////////////////////////////////////////////
%include <std_string.i>
%include <PMC/Config.hpp>
%include <PMC/PMC.hpp>

////////////////////////////////////////////////////////////////////////
// add pythonic extensions
////////////////////////////////////////////////////////////////////////
%extend PMCC
{
    std::string __str__(void)
    {
        std::ostringstream oss;
        oss << *($self);
        return oss.str();
    }

    bool __eq__(const PMCC &rhs)
    {
        return *($self) == rhs;
    }

    bool __nonzero__(void)
    {
        return bool(*($self));
    }
};


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
    return PMC::make(p);
}

%}

%enddef

#endif /*INCLUDED_PMC_PMC_I*/
