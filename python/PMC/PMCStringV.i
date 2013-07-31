// Copyright (C) by Josh Blum. See LICENSE.txt for licensing information.

/***********************************************************************
 * Support for the vector of strings type
 **********************************************************************/

%include <PMC/Registry.i>

%include <std_string.i>
%include <std_vector.i>

%template (StringVector) std::vector<std::string>;

DECL_PMC_SWIG_TYPE(std::vector<std::string>, string_vector)

%pythoncode %{

RegisterPMC2Py(
    is_pmc = pmc_is_string_vector,
    pmc2py = pmc_to_string_vector,
)

%}
