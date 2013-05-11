// Copyright (C) by Josh Blum. See LICENSE.txt for licensing information.

using System;
using System.Collections.Generic;
using System.Reflection;

public class CS2PMCConverter
{
}

public sealed class PMCRegistrySingleton
{
    private static volatile PMCRegistrySingleton instance;
    private static object syncRoot = new Object();

    private PMCRegistrySingleton()
    {
        System.Console.WriteLine("PMCRegistrySingleton!!!!!");
        //System.Runtime.CompilerServices.RuntimeHelpers.RunClassConstructor(type.TypeHandle);
        Assembly currAssembly = Assembly.GetExecutingAssembly();

        Type baseType = typeof(CS2PMCConverter);

        foreach (Type type in currAssembly.GetTypes())
        {
            if (type.IsClass && type.IsSubclassOf(baseType))
            {
                System.Runtime.CompilerServices.RuntimeHelpers.RunClassConstructor(type.TypeHandle);
            }
        }
    }

   public static PMCRegistrySingleton Instance
   {
      get 
      {
         if (instance == null) 
         {
            lock (syncRoot) 
            {
               if (instance == null) 
                  instance = new PMCRegistrySingleton();
            }
         }

         return instance;
      }
   }
}

public class PMCRegistry
{

    public delegate PMCC CS2PMCDelagate(Object obj);
    private static Dictionary<Type, CS2PMCDelagate> CS2PMC_map = new Dictionary<Type, CS2PMCDelagate>();

    //public static PMCC PMC_M(Object obj)
    //{
    //    return PMCRegistry.CS2PMC(obj);
    //}

    public static PMCC CS2PMC(Object obj)
    {
        PMCRegistrySingleton s = PMCRegistrySingleton.Instance;
        if (s == null || !CS2PMC_map.ContainsKey(obj.GetType()))
        {
            throw new System.ArgumentException(
                "Cannot convert obj to PMC, nothing is known about type: " + obj.GetType().ToString());
        }
        return CS2PMC_map[obj.GetType()](obj);
    }

    //do implicit shit -- can use as operator
    public static Object PMC2CS(PMCC p)
    {
        return 0;
    }

    public static void Register(Type t, CS2PMCDelagate d)
    {
        CS2PMC_map[t] = d;
    }

}
