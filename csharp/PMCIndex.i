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

%typemap(csclassmodifiers) PMCC "public partial class"

%include <PMC/PMC.i>

%include <PMC/Registry.i> //imports exception handling

////////////////////////////////////////////////////////////////////////
// add csharp extensions
////////////////////////////////////////////////////////////////////////
%extend PMCC
{
    std::string __to_string(void)
    {
        std::ostringstream oss;
        oss << *($self);
        return oss.str();
    }

    bool __operator_bool(void)
    {
        return bool(*($self));
    }

    bool __equals(const PMCC &rhs)
    {
        return ($self)->eq(rhs);
    }
};


%pragma(csharp) moduleimports=%{

public partial class PMCC
{

    static public PMCC M(System.Object obj)
    {
        return PMCRegistry.CS2PMC(obj);
    }

    public T cast<T>()
    {
        return (T)PMCRegistry.PMC2CS(this);
    }

    public override string ToString()
    {
        return __to_string();
    }

    //public static explicit operator bool(PMCC x) 
    //{
    //    return x.__operator_bool();
    //}

    public override bool Equals(System.Object obj)
    {
        // If parameter is null return false.
        if (obj == null)
        {
            return false;
        }

        // If parameter cannot be cast to PMCC return false.
        PMCC p = obj as PMCC;
        if ((System.Object)p == null)
        {
            return false;
        }

        // Return true if the fields match:
        return __equals(p);
    }

    public override int GetHashCode()
    {
        return base.GetHashCode();
    }
}

%}
