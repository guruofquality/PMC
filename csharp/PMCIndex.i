// Copyright (C) by Josh Blum. See LICENSE.txt for licensing information.

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
