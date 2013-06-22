// Copyright (C) by Josh Blum. See LICENSE.txt for licensing information.

/***********************************************************************
 * Support for the boolean type
 **********************************************************************/

%include <PMC/Registry.i>

DECL_PMC_SWIG_TYPE(bool, bool)

%pythoncode %{

RegisterPy2PMC(
    is_py = lambda x: type(x) is bool,
    py2pmc = bool_to_pmc,
)

RegisterPMC2Py(
    is_pmc = pmc_is_bool,
    pmc2py = pmc_to_bool,
)

import ctypes
RegisterPy2PMC(
    is_py = lambda x: type(x) is ctypes.c_bool,
    py2pmc = lambda x: bool_to_pmc(x.value),
)

%}
