/***********************************************************************
 * PMC Python SWIG support file: include me to add custom types
 **********************************************************************/

#ifndef INCLUDED_PMC_I
#define INCLUDED_PMC_I

%module PMC

%{

#include <PMC/PMC.hpp>

%}

struct PMC
{
    %extend
    {
        const char *__str__(void)
        {
            return $self->type().name();
        }
    }
};

struct PMCC : PMC
{

};


%define DECL_PMC_SWIG_TYPE(type, name)
%inline %{

bool pmc_is_ ## name(const PMCC &p)
{
    return p.is_type<type >();
}

type pmc_to_ ## name(const PMCC &p)
{
    return p.cast<type >();
}

PMCC name ## _to_pmc(const type &p)
{
    return PMC::make(p);
}

%}

%enddef

#ifdef PMC_SWIG_EXPORTS
%include <PMC/Index.i>
#else
%pythoncode %{
from PMC import *
%}
#endif

#endif /*INCLUDED_PMC_I*/
