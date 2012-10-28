/***********************************************************************
 * PMC Python SWIG support file: include me to add custom types
 **********************************************************************/

#ifndef INCLUDED_PMC_I
#define INCLUDED_PMC_I

%module PMC

%{

#include <PMC/PMC.hpp>

%}

struct PMCC
{
    %extend
    {
        const char *__str__(void)
        {
            return $self->type().name();
        }

        bool __eq__(const PMCC &rhs)
        {
            return *($self) == rhs;
        }

    }
};

struct PMC : PMCC
{

};


%define DECL_PMC_SWIG_TYPE(type, name)
%inline %{

bool pmc_is_ ## name(const PMCC &p)
{
    return p.is<type >();
}

const type &pmc_to_ ## name(const PMCC &p)
{
    return p.as<type >();
}

PMC name ## _to_pmc(const type &p)
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
