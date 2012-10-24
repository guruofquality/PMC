/***********************************************************************
 * Support for various floating point types
 **********************************************************************/

%include <PMC.i>

DECL_PMC_SWIG_TYPE(double, double)

DECL_PMC_SWIG_TYPE(float, float)

%pythoncode %{

#python float is a float64
PMCRegisterType(
    is_py = lambda x: isinstance(x, float),
    py2pmc = double_to_pmc,
    is_pmc = lambda x: False,#pmc_is_double,
    pmc2py = lambda x: float(pmc_to_double(x)),
)

#use other fixed types for float32

try:
    import numpy

    PMCRegisterType(
        is_py = lambda x: isinstance(x, numpy.float32),
        py2pmc = lambda x: float_to_pmc(float(x)),
        is_pmc = pmc_is_float,
        pmc2py = lambda x: numpy.float32(pmc_to_float(x)),
    )
    PMCRegisterType(
        is_py = lambda x: isinstance(x, numpy.float64),
        py2pmc = lambda x: double_to_pmc(float(x)),
        is_pmc = pmc_is_double,
        pmc2py = lambda x: numpy.float64(pmc_to_double(x)),
    )

except ImportError: pass

import ctypes

PMCRegisterType(
    is_py = lambda x: isinstance(x, ctypes.c_float),
    py2pmc = lambda x: float_to_pmc(x.value),
    is_pmc = pmc_is_float,
    pmc2py = lambda x: ctypes.c_float(pmc_to_float(x)),
)
PMCRegisterType(
    is_py = lambda x: isinstance(x, ctypes.c_double),
    py2pmc = lambda x: double_to_pmc(x.value),
    is_pmc = pmc_is_double,
    pmc2py = lambda x: ctypes.c_double(pmc_to_double(x)),
)

%}

