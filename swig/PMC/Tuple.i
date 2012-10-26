/***********************************************************************
 * Support for the Python tuple type
 **********************************************************************/

%include <PMC.i>

%{
#include <PMC/Containers.hpp>
%}

/*

%inline %{

typedef PMCTuple<PMCC,PMCC,PMCC> PMCTuple3;

bool pmc_is_tuple3(const PMCC &p)
{
    return p.is_type<PMCTuple3 >();
}

boost::array<PMCC, 3> pmc_tuple3_get(const PMCC &p)
{
    //PMCTier(x[0], x[1], x[2]) = p.cast<PMCTuple3 >();
}

boost::array<PMCC, 3> pmc_tuple3_test(void){}

PMC pmc_make_tuple(const PMCC &x0, const PMCC &x1, const PMCC &x2)
{
    return PMC::make(PMCTuple3(x0, x1, x2));
}

%}

%pythoncode %{

print pmc_tuple3_test()
print dir(pmc_tuple3_test())

%}

*/
/*
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

*/
