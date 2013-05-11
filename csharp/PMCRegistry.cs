// Copyright (C) by Josh Blum. See LICENSE.txt for licensing information.

using System;
using System.Collections.Generic;
using System.Reflection;

public class PMCConverter
{
}

public class PMCRegistry
{

    public delegate PMCC CS2PMCDelagate(Object obj);
    private static Dictionary<Type, CS2PMCDelagate> CS2PMC_map = new Dictionary<Type, CS2PMCDelagate>();

    static PMCRegistry()
    {
        foreach (Type type in Assembly.GetExecutingAssembly().GetTypes())
        {
            if (type.IsClass && type.IsSubclassOf(typeof(PMCConverter)))
            {
                System.Runtime.CompilerServices.RuntimeHelpers.RunClassConstructor(type.TypeHandle);
            }
        }
    }

    public static PMCC CS2PMC(Object obj)
    {
        if (!CS2PMC_map.ContainsKey(obj.GetType()))
        {
            throw new System.ArgumentException(
                "Cannot convert obj to PMC, nothing is known about type: " + obj.GetType().ToString());
        }
        return CS2PMC_map[obj.GetType()](obj);
    }

    public static void Register(Type t, CS2PMCDelagate d)
    {
        CS2PMC_map[t] = d;
    }

}
