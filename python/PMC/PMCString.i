// Copyright (C) by Josh Blum. See LICENSE.txt for licensing information.

/***********************************************************************
 * Support for the string type
 **********************************************************************/

%include <PMC/Registry.i>

%include <std_string.i>

DECL_PMC_SWIG_TYPE(std::string, string)

%pythoncode %{

RegisterPy2PMC(
    is_py = lambda x: isinstance(x, str),
    py2pmc = string_to_pmc,
)

RegisterPMC2Py(
    is_pmc = pmc_is_string,
    pmc2py = pmc_to_string,
)

%}
