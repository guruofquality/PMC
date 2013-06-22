// Copyright (C) by Josh Blum. See LICENSE.txt for licensing information.

/***********************************************************************
 * Support for the Python list type
 **********************************************************************/

%include <PMC/Registry.i>

%{
#include <PMC/Containers.hpp>
%}

%include <std_vector.i>

%template (PMCList) std::vector<PMCC>;

DECL_PMC_SWIG_TYPE(std::vector<PMCC>, swig_list)

%pythoncode %{

def py_list_to_swig_list(py_list):
    t = PMCList()
    for item in py_list:
        t.push_back(Py2PMC(item))
    return t

RegisterPy2PMC(
    is_py = lambda x: type(x) is list,
    py2pmc = lambda x: swig_list_to_pmc(py_list_to_swig_list(x)),
)

RegisterPMC2Py(
    is_pmc = pmc_is_swig_list,
    pmc2py = lambda x: list(map(PMC2Py, pmc_to_swig_list(x))),
)

%}
