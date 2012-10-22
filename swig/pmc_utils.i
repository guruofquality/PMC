#ifndef INCLUDED_PMC_UTILS_I
#define INCLUDED_PMC_UTILS_I

%define DECL_PMC_SWIG_TYPE(type, name)
%inline %{

bool pmc_is_ ## name(const PMCC &p)
{
    return p.is_type<type>();
}

type pmc_to_ ## name(const PMCC &p)
{
    return p.cast<type>();
}

PMCC name ## _to_pmc(const type &p)
{
    return PMC::make(p);
}

%}

%enddef

#endif /*INCLUDED_PMC_UTILS_I*/
