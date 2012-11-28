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
%ignore operator <<(std::ostream &os, const PMCC &obj); //ignore warnings about %rename

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
        return PMCCompare(*($self), rhs);
    }

    bool __nonzero__(void)
    {
        return bool(*($self));
    }
};

#endif /*INCLUDED_PMC_PMC_I*/
