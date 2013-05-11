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

    public delegate bool PMCisDelagate(PMCC p);
    public delegate Object PMC2CSDelagate(PMCC p);
    private static List<Tuple<PMCisDelagate, PMC2CSDelagate>> PMC2CS_map = new List<Tuple<PMCisDelagate, PMC2CSDelagate>>();

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

    public static Object PMC2CS(PMCC p)
    {
        foreach (Tuple<PMCisDelagate, PMC2CSDelagate> pair in PMC2CS_map)
        {
            if (pair.Item1(p)) return pair.Item2(p);
        }
        throw new System.ArgumentException(
            "Cannot convert PMC to obj, nothing is known about: " + p.ToString());
    }

    public static void Register(Type t, CS2PMCDelagate d)
    {
        CS2PMC_map[t] = d;
    }

}
