// Copyright (C) by Josh Blum. See LICENSE.txt for licensing information.

////////////////////////////////////////////////////////////////////////
// http://www.swig.org/Doc2.0/Library.html#Library_stl_exceptions
////////////////////////////////////////////////////////////////////////
%include <exception.i>

%exception
{
    try{$action}
    catch (const std::exception& e)
    {SWIG_exception(SWIG_RuntimeError, e.what());}
}

%{
#include <sstream>
%}

%include <PMC/PMC.i>

%include <PMC/Registry.i> //imports exception handling

////////////////////////////////////////////////////////////////////////
// add pythonic extensions
////////////////////////////////////////////////////////////////////////
%extend PMCC
{
    std::string __str__(void)
    {
        std::ostringstream oss;
        oss << *($self);
        return oss.str();
    }

    bool __nonzero__(void)
    {
        return bool(*($self));
    }

    bool _equal(const PMCC &rhs)
    {
        return ($self)->eq(rhs);
    }

    %insert("python")
    %{
        def __eq__(self, rhs):
            if not isinstance(rhs, PMCC): return False
            return self._equal(rhs)

        def __call__(self):
            import PMC
            return PMC.PMC2Py(self)
    %}
};
