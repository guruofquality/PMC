/***********************************************************************
 * Support for the complex floating point types
 **********************************************************************/

%include <PMC.i>

%include <std_complex.i>

DECL_PMC_SWIG_TYPE(std::complex<float>, complex64)
DECL_PMC_SWIG_TYPE(std::complex<double>, complex128)

%pythoncode %{

########################################################################
## python complex is a complex128
########################################################################
RegisterPy2PMC(
    is_py = lambda x: isinstance(x, complex),
    py2pmc = complex128_to_pmc,
)

RegisterPMC2Py(
    is_pmc = pmc_is_complex128,
    pmc2py = pmc_to_complex128,
)

########################################################################
## use other fixed types for complex64
########################################################################
try:
    import numpy

    RegisterPy2PMC(
        is_py = lambda x: isinstance(x, numpy.complex64),
        py2pmc = lambda x: complex64_to_pmc(complex(x)),
    )

    RegisterPMC2Py(
        is_pmc = pmc_is_complex64,
        pmc2py = lambda x: numpy.complex64(pmc_to_complex64(x)),
    )

    RegisterPy2PMC(
        is_py = lambda x: isinstance(x, numpy.complex128),
        py2pmc = lambda x: complex128_to_pmc(complex(x)),
    )

    RegisterPMC2Py(
        is_pmc = pmc_is_complex128,
        pmc2py = lambda x: numpy.complex128(pmc_to_complex128(x)),
    )

except ImportError: pass

%}
