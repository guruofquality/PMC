/***********************************************************************
 * Support for the Python tuple type
 **********************************************************************/

%include <PMC.i>

%{
#include <PMC/Containers.hpp>
%}

%include <std_vector.i>

%template (PMCTuple) std::vector<PMCC>;

DECL_PMC_SWIG_TYPE(std::vector<PMCC>, swig_tuple)

%pythoncode %{

def py_set_to_swig_tuple(py_tuple):
    t = PMCTuple()
    for item in py_tuple:
        t.push_back(Py2PMC(item))
    return t

RegisterPy2PMC(
    is_py = lambda x: isinstance(x, tuple),
    py2pmc = lambda x: swig_tuple_to_pmc(py_set_to_swig_tuple(x)),
)

RegisterPMC2Py(
    is_pmc = pmc_is_swig_tuple,
    pmc2py = lambda x: tuple(map(PMC2Py, pmc_to_swig_tuple(x))),
)

%}
