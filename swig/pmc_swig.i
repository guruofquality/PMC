%module PMC

%{

//#include <boost/intrusive_ptr.hpp>
#include <PMC/PMC.hpp>

%}

struct PMC// : boost::intrusive_ptr<void>
{

};

struct PMCC : PMC
{

};

%pythoncode %{

_registry = list()

def RegisterType(is_py, is_pmc, pmc2py, py2pmc):
    _registry.append((is_py, is_pmc, pmc2py, py2pmc))

def PMC2Py(p):
    for is_py, is_pmc, pmc2py, py2pmc in _registry:
        if is_pmc(p): return pmc2py(p)
    raise TypeError, 'cannot convert %s to Python type'%str(p)

def Py2PMC(p):
    for is_py, is_pmc, pmc2py, py2pmc in _registry:
        if is_py(p): return py2pmc(p)
    raise TypeError, 'cannot convert %s to PMC type'%str(p)

%}

#ifdef PMC_SWIG_BUILDING
%include "pmc_default_types.i"
#endif
