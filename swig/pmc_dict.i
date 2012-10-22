%include <pmc_utils.i>

%include "std_map.i"

%inline %{
typedef std::map<PMCC, PMCC> PMCDict;
%}

%template (PMCDict) std::map<PMCC, PMCC>;

DECL_PMC_SWIG_TYPE(PMCDict, swig_dict)

%pythoncode %{

def swig_dict_to_py_dict(swig_dict):
    return dict([(PMC2Py(key), PMC2Py(value)) for key, value in swig_dict.iteritems()])

def py_dict_to_swig_dict(py_dict):
    d = PMCDict()
    for key, value in py_dict.iteritems():
        d[Py2PMC(key)] = Py2PMC(value)
    return d

%}

%pythoncode %{

RegisterType(
    is_py = lambda x: isinstance(x, dict),
    is_pmc = pmc_is_swig_dict,
    pmc2py = lambda x: swig_dict_to_py_dict(pmc_to_swig_dict(x)),
    py2pmc = lambda x: swig_dict_to_pmc(py_dict_to_swig_dict(x)),
)

%}
