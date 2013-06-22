// Copyright (C) by Josh Blum. See LICENSE.txt for licensing information.

/***********************************************************************
 * Support for the Python dict type
 **********************************************************************/

%include <PMC/Registry.i>

%{
#include <PMC/Containers.hpp>
%}

%include <std_map.i>

%template (PMCDict) std::map<PMCC, PMCC>;

#define STD_MAP(type) std::map<type, type>
DECL_PMC_SWIG_TYPE(STD_MAP(PMCC), swig_dict)

%pythoncode %{

def swig_dict_to_py_dict(swig_dict):
    d = dict()
    for key in swig_dict.keys():
        value = swig_dict[key]
        d[PMC2Py(key)] = PMC2Py(value)
    return d

def py_dict_to_swig_dict(py_dict):
    d = PMCDict()
    for key, value in py_dict.iteritems():
        d[Py2PMC(key)] = Py2PMC(value)
    return d

RegisterPy2PMC(
    is_py = lambda x: type(x) is dict,
    py2pmc = lambda x: swig_dict_to_pmc(py_dict_to_swig_dict(x)),
)

RegisterPMC2Py(
    is_pmc = pmc_is_swig_dict,
    pmc2py = lambda x: swig_dict_to_py_dict(pmc_to_swig_dict(x)),
)

%}
