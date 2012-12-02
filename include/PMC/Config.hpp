// Copyright (C) by Josh Blum. See LICENSE.txt for licensing information.

#ifndef INCLUDED_PMC_CONFIG_HPP
#define INCLUDED_PMC_CONFIG_HPP

// http://gcc.gnu.org/wiki/Visibility
// Generic helper definitions for shared library support
#if defined _WIN32 || defined __CYGWIN__
  #define PMC_HELPER_DLL_IMPORT __declspec(dllimport)
  #define PMC_HELPER_DLL_EXPORT __declspec(dllexport)
  #define PMC_HELPER_DLL_LOCAL
#else
  #if __GNUC__ >= 4
    #define PMC_HELPER_DLL_IMPORT __attribute__ ((visibility ("default")))
    #define PMC_HELPER_DLL_EXPORT __attribute__ ((visibility ("default")))
    #define PMC_HELPER_DLL_LOCAL  __attribute__ ((visibility ("hidden")))
  #else
    #define PMC_HELPER_DLL_IMPORT
    #define PMC_HELPER_DLL_EXPORT
    #define PMC_HELPER_DLL_LOCAL
  #endif
#endif

// Now we use the generic helper definitions above to define PMC_API and PMC_LOCAL.
// PMC_API is used for the public API symbols. It either DLL imports or DLL exports (or does nothing for static build)
// PMC_LOCAL is used for non-api symbols.

#define PMC_DLL //always building a DLL

#ifdef PMC_DLL // defined if PMC is compiled as a DLL
  #ifdef PMC_DLL_EXPORTS // defined if we are building the PMC DLL (instead of using it)
    #define PMC_API PMC_HELPER_DLL_EXPORT
  #else
    #define PMC_API PMC_HELPER_DLL_IMPORT
  #endif // PMC_DLL_EXPORTS
  #define PMC_LOCAL PMC_HELPER_DLL_LOCAL
#else // PMC_DLL is not defined: this means PMC is a static lib.
  #define PMC_API
  #define PMC_LOCAL
#endif // PMC_DLL

#define PMC_INLINE inline

#include <boost/intrusive_ptr.hpp>
struct PMCImpl;
typedef boost::intrusive_ptr<PMCImpl> PMCBase;

#include <ciso646>

#endif /*INCLUDED_PMC_CONFIG_HPP*/
