// Copyright (C) by Josh Blum. See LICENSE.txt for licensing information.

/***********************************************************************
 * Support for the string type
 **********************************************************************/

%include <PMC/Registry.i>

%include <std_string.i>

DECL_PMC_SWIG_TYPE(std::string, string)

%inline %{

PMCC string_to_pmc_intern(const char *s)
{
    return PMC_M(s);
}

%}

%pythoncode %{

RegisterPy2PMC(
    is_py = lambda x: type(x) is str,
    py2pmc = string_to_pmc_intern,
)

RegisterPMC2Py(
    is_pmc = pmc_is_string,
    pmc2py = pmc_to_string,
)

%}

/***********************************************************************
 * Support for a vector of strings
 **********************************************************************/
%include <std_vector.i>

%template (StringVector) std::vector<std::string>;

DECL_PMC_SWIG_TYPE(std::vector<std::string>, string_vector)
REG_PMC_SWIG_TYPE(string_vector, StringVector)
