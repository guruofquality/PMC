// Copyright (C) by Josh Blum. See LICENSE.txt for licensing information.

%{
#include <PMC/Pool.hpp>
%}

%include <std_vector.i>
%template (std_vector_PMC) std::vector<PMC>;

%include <PMC/PMC.i>
%include <PMC/Pool.hpp>
