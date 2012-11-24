// Copyright (C) by Josh Blum. See LICENSE.txt for licensing information.

/***********************************************************************
 * Support for the Python set type
 **********************************************************************/

%{
#include <PMC/PMC.hpp>
%}

%import <PMC/PMC.i>

%{
#include <PMC/Containers.hpp>
%}

%include <std_set.i>

%template (PMCSet) std::set<PMCC>;

DECL_PMC_SWIG_TYPE(std::set<PMCC>, swig_set)

%pythoncode %{

from PMC import *

def py_set_to_swig_set(py_set):
    s = PMCSet()
    for item in py_set:
        s.insert(Py2PMC(item))
    return s

RegisterPy2PMC(
    is_py = lambda x: isinstance(x, set),
    py2pmc = lambda x: swig_set_to_pmc(py_set_to_swig_set(x)),
)

RegisterPMC2Py(
    is_pmc = pmc_is_swig_set,
    pmc2py = lambda x: set(map(PMC2Py, pmc_to_swig_set(x))),
)

%}
