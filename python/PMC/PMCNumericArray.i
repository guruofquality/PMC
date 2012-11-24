// Copyright (C) by Josh Blum. See LICENSE.txt for licensing information.

/***********************************************************************
 * Support for arrays of fixed-width numbers
 **********************************************************************/

%{
#include <PMC/PMC.hpp>
%}

%import <PMC/PMC.i>

%{
#include <complex>
typedef float float32_t;
typedef double float64_t;
typedef std::complex<float> complex64_t;
typedef std::complex<double> complex128_t;
%}

%include <stdint.i>
%include <std_complex.i>
%include <std_vector.i>
%include <std_pair.i>

%template (pair_ptr_size) std::pair<ptrdiff_t, size_t>;

%define DECL_PMC_SWIG_NUMERIC_ARRAY(type)

%inline %{

bool pmc_is_array_of_ ## type(const PMCC &p)
{
    return p.is<std::vector<type ## _t> >();
}

std::pair<ptrdiff_t, size_t> info_of_array_of_ ## type(const PMCC &p)
{
    const std::vector<type ## _t> &v = p.as<std::vector<type ## _t> >();
    return std::pair<ptrdiff_t, size_t>(ptrdiff_t(&v[0]), v.size());
}

PMC pmc_make_array_of_ ## type(const ptrdiff_t addr, const size_t size)
{
    std::vector<type ## _t> v(size);
    type ## _t *item_ptr = (type ## _t *) addr;
    v.assign(item_ptr, item_ptr+size);
    return PMC::make(v);
}

%}

%pythoncode %{

from PMC import *

try:
    import numpy

    def pmc_to_numpy_array_ ## type(p):
        addr, size = info_of_array_of_ ## type(p)
        dtype = numpy.dtype(numpy.type)
        readonly = not isinstance(p, PMC)
        return pointer_to_ndarray(addr, dtype, size, readonly, p)

    def numpy_array_ ## type ## _to_pmc(a):
        return pmc_make_array_of_ ## type(a.ctypes.data, len(a))

    RegisterPy2PMC(
        is_py = lambda x: isinstance(x, numpy.ndarray) and (x.dtype == numpy.type),
        py2pmc = numpy_array_ ## type ## _to_pmc,
    )

    RegisterPMC2Py(
        is_pmc = pmc_is_array_of_ ## type,
        pmc2py = pmc_to_numpy_array_ ## type,
    )
except ImportError: pass
%}

%enddef

%pythoncode %{
def pointer_to_ndarray(addr, dtype, nitems, readonly=False, container=None):
    class array_like:
        __array_interface__ = {
            'data' : (addr, readonly),
            'typestr' : dtype.base.str,
            'descr' : dtype.base.descr,
            'shape' : (nitems,) + dtype.shape,
            'strides' : None,
            'version' : 3,
            'container' : container,
        }
    return numpy.asarray(array_like()).view(dtype.base)
%}

DECL_PMC_SWIG_NUMERIC_ARRAY(int8)
DECL_PMC_SWIG_NUMERIC_ARRAY(int16)
DECL_PMC_SWIG_NUMERIC_ARRAY(int32)
//DECL_PMC_SWIG_NUMERIC_ARRAY(int64)

DECL_PMC_SWIG_NUMERIC_ARRAY(uint8)
DECL_PMC_SWIG_NUMERIC_ARRAY(uint16)
DECL_PMC_SWIG_NUMERIC_ARRAY(uint32)
//DECL_PMC_SWIG_NUMERIC_ARRAY(uint64)

DECL_PMC_SWIG_NUMERIC_ARRAY(float32)
DECL_PMC_SWIG_NUMERIC_ARRAY(float64)

DECL_PMC_SWIG_NUMERIC_ARRAY(complex64)
DECL_PMC_SWIG_NUMERIC_ARRAY(complex128)
