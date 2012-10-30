/* This program is free software. It comes without any warranty, to
* the extent permitted by applicable law. You can redistribute it
* and/or modify it under the terms of the Do What The Fuck You Want
* To Public License, Version 2, as published by Sam Hocevar. See
* http://sam.zoy.org/wtfpl/COPYING for more details. */

/***********************************************************************
 * PMC Python SWIG support file: include me to add custom types
 **********************************************************************/

#ifndef INCLUDED_PMC_PMC_I
#define INCLUDED_PMC_PMC_I

%{

#include <PMC/PMC.hpp>

%}

struct PMCC
{
    %extend
    {
        const char *__str__(void)
        {
            if (not ($self)) return "NULL PMC";
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

/***********************************************************************
 * pull PMC module routines into namespace for adding custom types
 **********************************************************************/
%pythoncode %{
from PMC import *
%}

#endif /*INCLUDED_PMC_PMC_I*/
