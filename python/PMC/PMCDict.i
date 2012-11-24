// Copyright (C) by Josh Blum. See LICENSE.txt for licensing information.

/***********************************************************************
 * Support for the Python dict type
 **********************************************************************/

%{
#include <PMC/PMC.hpp>
%}

%import <PMC/PMC.i>

%{
#include <PMC/Containers.hpp>
%}

%include <std_map.i>

%template (PMCDict) std::map<PMCC, PMCC>;

#define STD_MAP(type) std::map<type, type>
DECL_PMC_SWIG_TYPE(STD_MAP(PMCC), swig_dict)

%pythoncode %{

from PMC import *

def swig_dict_to_py_dict(swig_dict):
    return dict([(PMC2Py(key), PMC2Py(value)) for key, value in swig_dict.iteritems()])

def py_dict_to_swig_dict(py_dict):
    d = PMCDict()
    for key, value in py_dict.iteritems():
        d[Py2PMC(key)] = Py2PMC(value)
    return d

RegisterPy2PMC(
    is_py = lambda x: isinstance(x, dict),
    py2pmc = lambda x: swig_dict_to_pmc(py_dict_to_swig_dict(x)),
)

RegisterPMC2Py(
    is_pmc = pmc_is_swig_dict,
    pmc2py = lambda x: swig_dict_to_py_dict(pmc_to_swig_dict(x)),
)

%}
