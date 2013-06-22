// Copyright (C) by Josh Blum. See LICENSE.txt for licensing information.

/***********************************************************************
 * Support for the Python tuple type
 **********************************************************************/

%include <PMC/Registry.i>

%{
#include <PMC/Containers.hpp>
%}

%define DECL_PMC_TUPLE_TYPE(n)

%inline %{

bool pmc_is_tuple ## n(const PMCC &p)
{
    return p.is<PMCTuple<n> >();
}

const PMCC &pmc_tuple ## n ## _get(const PMCC &p, const size_t i)
{
    return p.as<PMCTuple<n> >()[i];
}

void pmc_tuple ## n ## _set(const PMC &p, const size_t i, const PMCC &x)
{
    p.as<PMCTuple<n> >()[i] = x;
}

PMC pmc_make_tuple ## n(void)
{
    return PMC_M(PMCTuple<n>());
}

%}

%pythoncode %{

def pmc_make_swig_tuple ## n(elems):
    t = pmc_make_tuple ## n()
    for i, elem in enumerate(elems):
        pmc_tuple ## n ## _set(t, i, Py2PMC(elem))
    return t

RegisterPy2PMC(
    is_py = lambda x: type(x) is tuple and len(x) == n,
    py2pmc = pmc_make_swig_tuple ## n,
)

def pmc_make_py_tuple ## n(p):
    l = []
    for i in range(n):
        elem = pmc_tuple ## n ## _get(p, i)
        l.append(PMC2Py(elem))
    return tuple(l)

RegisterPMC2Py(
    is_pmc = pmc_is_tuple ## n,
    pmc2py = pmc_make_py_tuple ## n,
)

%}

%enddef

DECL_PMC_TUPLE_TYPE(0)
DECL_PMC_TUPLE_TYPE(1)
DECL_PMC_TUPLE_TYPE(2)
DECL_PMC_TUPLE_TYPE(3)
DECL_PMC_TUPLE_TYPE(4)
DECL_PMC_TUPLE_TYPE(5)
DECL_PMC_TUPLE_TYPE(6)
DECL_PMC_TUPLE_TYPE(7)
DECL_PMC_TUPLE_TYPE(8)
DECL_PMC_TUPLE_TYPE(9)
DECL_PMC_TUPLE_TYPE(10)
