// Copyright (C) by Josh Blum. See LICENSE.txt for licensing information.

/***********************************************************************
 * Support for arrays of fixed-width numbers
 **********************************************************************/

%include <PMC/Registry.i>

%{
#include <complex>
typedef float float32_t;
typedef double float64_t;
typedef signed long long_t;
typedef unsigned long ulong_t;
typedef signed long long longlong_t;
typedef unsigned long long ulonglong_t;
typedef std::complex<float> complex64_t;
typedef std::complex<double> complex128_t;
%}

%include <stdint.i>
%include <std_complex.i>
%include <std_vector.i>
%include <std_pair.i>

%template (pair_ptr_size) std::pair<ptrdiff_t, size_t>;

%define DECL_PMC_SWIG_NUMERIC_ARRAY_2(type, ntype)

%inline %{

bool pmc_is_array_of_ ## type(const PMCC &p)
{
    return p.is<std::vector<type> >();
}

std::pair<ptrdiff_t, size_t> info_of_array_of_ ## type(const PMCC &p)
{
    const std::vector<type> &v = p.as<std::vector<type> >();
    return std::pair<ptrdiff_t, size_t>(ptrdiff_t(&v[0]), v.size());
}

PMC pmc_make_array_of_ ## type(const ptrdiff_t addr, const size_t size)
{
    std::vector<type> v(size);
    type *item_ptr = (type *) addr;
    v.assign(item_ptr, item_ptr+size);
    return PMC_M(v);
}

%}

%pythoncode %{

try:
    import numpy

    def pmc_to_numpy_array_ ## type(p):
        addr, size = info_of_array_of_ ## type(p)
        dtype = numpy.dtype(numpy.ntype)
        readonly = not isinstance(p, PMC)
        return pointer_to_ndarray(addr, dtype, size, readonly, p)

    def numpy_array_ ## type ## _to_pmc(a):
        return pmc_make_array_of_ ## type(a.ctypes.data, len(a))

    RegisterPy2PMC(
        is_py = lambda x: isinstance(x, numpy.ndarray) and (x.dtype == numpy.ntype),
        py2pmc = numpy_array_ ## type ## _to_pmc,
    )

    RegisterPMC2Py(
        is_pmc = pmc_is_array_of_ ## type,
        pmc2py = pmc_to_numpy_array_ ## type,
    )
except ImportError: pass
%}

%enddef

%define DECL_PMC_SWIG_NUMERIC_ARRAY(type)

DECL_PMC_SWIG_NUMERIC_ARRAY_2(type ## _t, type)

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
DECL_PMC_SWIG_NUMERIC_ARRAY(int64)

DECL_PMC_SWIG_NUMERIC_ARRAY(uint8)
DECL_PMC_SWIG_NUMERIC_ARRAY(uint16)
DECL_PMC_SWIG_NUMERIC_ARRAY(uint32)
DECL_PMC_SWIG_NUMERIC_ARRAY(uint64)

//make sure to covert long for the x32 case
DECL_PMC_SWIG_NUMERIC_ARRAY_2(long_t, long)
DECL_PMC_SWIG_NUMERIC_ARRAY_2(ulong_t, long) //numpy has no ulong

//make sure to covert long long for the x64 case
DECL_PMC_SWIG_NUMERIC_ARRAY_2(longlong_t, longlong)
DECL_PMC_SWIG_NUMERIC_ARRAY_2(ulonglong_t, ulonglong)

DECL_PMC_SWIG_NUMERIC_ARRAY(float32)
DECL_PMC_SWIG_NUMERIC_ARRAY(float64)

DECL_PMC_SWIG_NUMERIC_ARRAY(complex64)
DECL_PMC_SWIG_NUMERIC_ARRAY(complex128)
