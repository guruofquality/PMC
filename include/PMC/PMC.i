// Copyright (C) by Josh Blum. See LICENSE.txt for licensing information.

/***********************************************************************
 * PMC Python SWIG support file: include me to add custom types
 **********************************************************************/

#ifndef INCLUDED_PMC_PMC_I
#define INCLUDED_PMC_PMC_I

%{
#include <PMC/PMC.hpp>
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

#endif /*INCLUDED_PMC_PMC_I*/
