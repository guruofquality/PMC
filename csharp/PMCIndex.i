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
// add csharp extensions
////////////////////////////////////////////////////////////////////////
%extend PMCC
{
    std::string ToString(void)
    {
        std::ostringstream oss;
        oss << *($self);
        return oss.str();
    }
};
