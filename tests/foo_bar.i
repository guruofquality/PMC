// Copyright (C) by Josh Blum. See LICENSE.txt for licensing information.

%module foo_bar

%{

struct FooBar
{
    int _foo;
    float _bar;

    int foo(void) const
    {
        return _foo;
    }

    float bar(void) const
    {
        return _bar;
    }
};

bool operator==(const FooBar &lhs, const FooBar &rhs)
{
    return (lhs.foo() == rhs.foo()) && (lhs.bar() == rhs.bar());
}

%}

struct FooBar
{
    int _foo;
    float _bar;

    int foo(void);

    float bar(void);
};

////////////////////////////////////////////////////////////////////////
// This is what a typical registry looks like
////////////////////////////////////////////////////////////////////////
%include <PMC/Registry.i> //include the registration macros

//
// Export swig defintions for converting this object:
// - FooBar is the C++ type as defined in your header files
// - swig_foo_bar is the name of the swig functions DECL_ creates
//
DECL_PMC_SWIG_TYPE(FooBar, swig_foo_bar)

//
// import the python module
// This import statement is needed before the registration step
// The import statement is how it would look in your client code
//
%pythoncode %{
from foo_bar import *
%}

//
// Register the swigged type into PMC:
// - swig_foo_bar is the name of the swig functions made by DECL_
// - FooBar is the name of the python class for your object
//
REG_PMC_SWIG_TYPE(swig_foo_bar, FooBar)
