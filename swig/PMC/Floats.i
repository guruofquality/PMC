/***********************************************************************
 * Support for various floating point types
 **********************************************************************/

%include <PMC/PMC.i>

DECL_PMC_SWIG_TYPE(double, float64)

DECL_PMC_SWIG_TYPE(float, float32)

%pythoncode %{

########################################################################
## python float is a float64
########################################################################
RegisterPy2PMC(
    is_py = lambda x: isinstance(x, float),
    py2pmc = float64_to_pmc,
)

RegisterPMC2Py(
    is_pmc = pmc_is_float64,
    pmc2py = lambda x: float(pmc_to_float64(x)),
)

########################################################################
## use other fixed types for float32
########################################################################

try:
    import numpy

    RegisterPy2PMC(
        is_py = lambda x: isinstance(x, numpy.float32),
        py2pmc = lambda x: float32_to_pmc(float(x)),
    )

    RegisterPMC2Py(
        is_pmc = pmc_is_float32,
        pmc2py = lambda x: numpy.float32(pmc_to_float32(x)),
    )

    RegisterPy2PMC(
        is_py = lambda x: isinstance(x, numpy.float64),
        py2pmc = lambda x: float64_to_pmc(float(x)),
    )

    RegisterPMC2Py(
        is_pmc = pmc_is_float64,
        pmc2py = lambda x: numpy.float64(pmc_to_float64(x)),
    )

except ImportError: pass

import ctypes

RegisterPy2PMC(
    is_py = lambda x: isinstance(x, ctypes.c_float),
    py2pmc = lambda x: float32_to_pmc(x.value),
)

RegisterPMC2Py(
    is_pmc = pmc_is_float32,
    pmc2py = lambda x: ctypes.c_float(pmc_to_float32(x)),
)

RegisterPy2PMC(
    is_py = lambda x: isinstance(x, ctypes.c_double),
    py2pmc = lambda x: float64_to_pmc(x.value),
)

RegisterPMC2Py(
    is_pmc = pmc_is_float64,
    pmc2py = lambda x: ctypes.c_double(pmc_to_float64(x)),
)

%}

