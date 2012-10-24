
%pythoncode %{

_py_to_pmc_registry = list()
_pmc_to_py_registry = list()

def RegisterPy2PMC(is_py, py2pmc):
    _py_to_pmc_registry.append((is_py, py2pmc))

def RegisterPMC2Py(is_pmc, pmc2py):
    _pmc_to_py_registry.append((is_pmc, pmc2py))

def PMC2Py(p):
    for is_pmc, pmc2py in _pmc_to_py_registry:
        if is_pmc(p): return pmc2py(p)
    raise TypeError, 'cannot convert %s to Python type'%str(p)

def Py2PMC(p):
    for is_py, py2pmc in _py_to_pmc_registry:
        if is_py(p): return py2pmc(p)
    raise TypeError, 'cannot convert %s to PMC type'%str(p)

%}

%include <PMC/None.i>
%include <PMC/Bool.i>
%include <PMC/Integers.i>
%include <PMC/Floats.i>
%include <PMC/Dict.i>
