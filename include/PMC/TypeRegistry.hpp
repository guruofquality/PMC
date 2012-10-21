/* This program is free software. It comes without any warranty, to
* the extent permitted by applicable law. You can redistribute it
* and/or modify it under the terms of the Do What The Fuck You Want
* To Public License, Version 2, as published by Sam Hocevar. See
* http://sam.zoy.org/wtfpl/COPYING for more details. */

#ifndef INCLUDED_PMC_TYPE_REGISTRY_HPP
#define INCLUDED_PMC_TYPE_REGISTRY_HPP

#include <PMC/PMC.hpp>
#include <boost/function.hpp>



template<typename Value>
PMC MakePMC(void)
{
    return PMC(Value());
}

typedef boost::function<PMC(void)> PMCFactory;

PMC_API void PMCRegisterType(const std::type_info &type, const PMCFactory &factory);

template<typename Value>
PMC_INLINE void PMCRegisterType(void)
{
    PMCFactory factory(&MakePMC<Value>);
    PMCRegisterType(typeid(Value), factory);
}

#endif /*INCLUDED_PMC_TYPE_REGISTRY_HPP*/
