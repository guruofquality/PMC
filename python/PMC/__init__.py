# Copyright (C) by Josh Blum. See LICENSE.txt for licensing information.

from PMCIndex import PMCC, PMC

_py_to_pmc_registry = list()
_pmc_to_py_registry = list()

def RegisterPy2PMC(is_py, py2pmc):
    _py_to_pmc_registry.append((is_py, py2pmc))

def RegisterPMC2Py(is_pmc, pmc2py):
    _pmc_to_py_registry.append((is_pmc, pmc2py))

def Py2PMC(p):
    if isinstance(p, PMCC): return p
    for is_py, py2pmc in _py_to_pmc_registry:
        if is_py(p): return py2pmc(p)
    raise TypeError, 'cannot convert %s to PMC type'%str(p)

def PMC2Py(p):
    for is_pmc, pmc2py in _pmc_to_py_registry:
        if is_pmc(p): return pmc2py(p)
    return p

import PMCNone
import PMCBool
import PMCIntegers
import PMCFloats
import PMCComplex
import PMCString
import PMCTuple
import PMCSet
import PMCList
import PMCDict
import PMCNumericArray


from PMCPool import PMCPool

__all__ = ["RegisterPy2PMC", "RegisterPMC2Py", "Py2PMC", "PMC2Py", "PMCC", "PMC", "PMCPool"]
