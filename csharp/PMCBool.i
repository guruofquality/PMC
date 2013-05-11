// Copyright (C) by Josh Blum. See LICENSE.txt for licensing information.

/***********************************************************************
 * Support for the boolean type
 **********************************************************************/

%include <PMC/Registry.i>

DECL_PMC_SWIG_TYPE(bool, bool)

%pragma(csharp) moduleimports=%{

class PMCBoolRegister : CS2PMCConverter
{

    static PMCC my_bool_to_pmc(System.Object obj)
    {
        return PMCBool.bool_to_pmc((bool)obj);
    }

    static PMCBoolRegister()
    {
        System.Console.WriteLine("PMCBoolRegister!!!!!");
        PMCRegistry.Register(typeof(bool), my_bool_to_pmc);
    }
}

%}

