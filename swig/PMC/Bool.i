/***********************************************************************
 * Support for the boolean type
 **********************************************************************/

%include <PMC.i>

DECL_PMC_SWIG_TYPE(bool, bool)

%pythoncode %{

RegisterPy2PMC(
    is_py = lambda x: isinstance(x, bool),
    py2pmc = bool_to_pmc,
)

RegisterPMC2Py(
    is_pmc = pmc_is_bool,
    pmc2py = pmc_to_bool,
)

import ctypes
RegisterPy2PMC(
    is_py = lambda x: isinstance(x, ctypes.c_bool),
    py2pmc = lambda x: bool_to_pmc(x.value),
)

%}
