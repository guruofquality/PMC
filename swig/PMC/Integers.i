/***********************************************************************
 * Support for various integers types
 **********************************************************************/

%include <PMC.i>

/***********************************************************************
 * Treatment for python long and int native types
 **********************************************************************/

DECL_PMC_SWIG_TYPE(long, long)
DECL_PMC_SWIG_TYPE(int, int)

%pythoncode %{

PMCRegisterType(
    is_py = lambda x: isinstance(x, int),
    py2pmc = int_to_pmc,
    is_pmc = pmc_is_int,
    pmc2py = lambda x: int(pmc_to_int(x)),
)

PMCRegisterType(
    is_py = lambda x: isinstance(x, long),
    py2pmc = long_to_pmc,
    is_pmc = pmc_is_long,
    pmc2py = lambda x: long(pmc_to_long(x)),
)

%}

/***********************************************************************
 * Best effort for other fixed-width types
 **********************************************************************/

%include <stdint.i>

%define DECL_PMC_SWIG_INTEGER_TYPE(name)

DECL_PMC_SWIG_TYPE(name ## _t, name)

%pythoncode %{

try:
    import numpy

    PMCRegisterType(
        is_py = lambda x: isinstance(x, numpy. ## name),
        py2pmc = lambda x: name ## _to_pmc(long(x)),
        is_pmc = pmc_is_ ## name,
        pmc2py = lambda x: numpy. ## name(pmc_to_ ## name(x)),
    )
except ImportError: pass

import ctypes

PMCRegisterType(
    is_py = lambda x: isinstance(x, ctypes.c_ ## name),
    py2pmc = lambda x: name ## _to_pmc(x.value),
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
