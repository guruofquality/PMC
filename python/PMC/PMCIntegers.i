// Copyright (C) by Josh Blum. See LICENSE.txt for licensing information.

/***********************************************************************
 * Support for various integers types
 **********************************************************************/

%include <PMC/Registry.i>

%{
typedef signed long long_t;
typedef unsigned long ulong_t;
typedef signed long long longlong_t;
typedef unsigned long long ulonglong_t;
%}

/***********************************************************************
 * Treatment for python long and int native types
 **********************************************************************/

%define DECL_PMC_SWIG_BUILTIN_INTEGER_TYPE(name)

DECL_PMC_SWIG_TYPE(name, name ## _builtin)

%pythoncode %{

RegisterPy2PMC(
    is_py = lambda x: type(x) is name,
    py2pmc = name ## _builtin ## _to_pmc,
)

RegisterPMC2Py(
    is_pmc = pmc_is_ ## name ## _builtin,
    pmc2py = lambda x: name(pmc_to_ ## name ## _builtin(x)),
)

%}

%enddef

DECL_PMC_SWIG_BUILTIN_INTEGER_TYPE(int)
DECL_PMC_SWIG_BUILTIN_INTEGER_TYPE(long)

/***********************************************************************
 * Best effort for other fixed-width types
 **********************************************************************/

%include <stdint.i>

%define DECL_PMC_SWIG_INTEGER_TYPE(name)

DECL_PMC_SWIG_TYPE(name ## _t, name)

%pythoncode %{

try:
    import numpy

    RegisterPy2PMC(
        is_py = lambda x: type(x) is numpy. ## name,
        py2pmc = lambda x: name ## _to_pmc(long(x)),
    )

    RegisterPMC2Py(
        is_pmc = pmc_is_ ## name,
        pmc2py = lambda x: numpy. ## name(pmc_to_ ## name(x)),
    )
except ImportError: pass

import ctypes

RegisterPy2PMC(
    is_py = lambda x: type(x) is ctypes.c_ ## name,
    py2pmc = lambda x: name ## _to_pmc(x.value),)

RegisterPMC2Py(
    is_pmc = pmc_is_ ## name,
    pmc2py = lambda x: ctypes.c_ ## name(pmc_to_ ## name(x)),
)

%}

%enddef

DECL_PMC_SWIG_INTEGER_TYPE(int8)
DECL_PMC_SWIG_INTEGER_TYPE(int16)
DECL_PMC_SWIG_INTEGER_TYPE(int32)
DECL_PMC_SWIG_INTEGER_TYPE(int64)

DECL_PMC_SWIG_INTEGER_TYPE(uint8)
DECL_PMC_SWIG_INTEGER_TYPE(uint16)
DECL_PMC_SWIG_INTEGER_TYPE(uint32)
DECL_PMC_SWIG_INTEGER_TYPE(uint64)

//handle the long types not caught by the stdint types
DECL_PMC_SWIG_INTEGER_TYPE(long)
DECL_PMC_SWIG_INTEGER_TYPE(ulong)
DECL_PMC_SWIG_INTEGER_TYPE(longlong)
DECL_PMC_SWIG_INTEGER_TYPE(ulonglong)
