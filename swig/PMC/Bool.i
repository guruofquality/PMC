/***********************************************************************
 * Support for the boolean type
 **********************************************************************/

%include <PMC.i>

DECL_PMC_SWIG_TYPE(bool, bool)

%pythoncode %{

PMCRegisterType(
    is_py = lambda x: isinstance(x, bool),
    is_pmc = pmc_is_bool,
    pmc2py = pmc_to_bool,
    py2pmc = bool_to_pmc,
)

%}
