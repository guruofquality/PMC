// Copyright (C) by Josh Blum. See LICENSE.txt for licensing information.

%include <PMC/Registry.i>

/***********************************************************************
 * Support for the boolean type
 **********************************************************************/
DECL_PMC_SWIG_TYPE(bool, bool)
REG_PMC_SWIG_TYPE(bool, System.Boolean, PMCBasicTypes)

/***********************************************************************
 * Support for the fixed int types
 **********************************************************************/
%include <stdint.i>

DECL_PMC_SWIG_TYPE(uint8_t, uint8)
//REG_PMC_SWIG_TYPE(uint8, System.Byte, PMCBasicTypes)

DECL_PMC_SWIG_TYPE(int8_t, int8)
//REG_PMC_SWIG_TYPE(int8, System.SByte, PMCBasicTypes)

%typemap(javabody) SWIGTYPE %{

cockbats

%}
