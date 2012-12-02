// Copyright (C) by Josh Blum. See LICENSE.txt for licensing information.

#ifndef INCLUDED_PMC_SERIALIZE_HPP
#define INCLUDED_PMC_SERIALIZE_HPP

#include <PMC/Config.hpp>
#include <PMC/PMC.hpp>
#include <string>
#include <iostream>

#include <boost/serialization/split_free.hpp>

namespace boost { namespace serialization {
template<class Archive>
void save(Archive & ar, const PMCC & t, unsigned int version)
{
    
}
template<class Archive>
void load(Archive & ar, PMCC & t, unsigned int version)
{
    
}
}}

BOOST_SERIALIZATION_SPLIT_FREE(PMCC)

//TODO have to serialize/deserialize null ones


//TODO check if its an intern and load/save that info

/*

PMC_API void PMCSerializeRegister(const std::string &type_id, const PMCC &p);

PMC_API const PMCC &PMCSerializeLookup(const std::string &type_id);

#define PMC_REGISTER(type) PMCSerializeRegister(typeid(type).name(), #type);

template<class Archive>
void PMCC::save(Archive &ar, const unsigned int) const
{
    const std::string type_id = this->type().name();
    std::cout << "save type id" << std::endl;
    ar & type_id; //TODO convert to id
    std::cout << "save item" << std::endl;
    ar & (*((*this)->item));
}

template<class Archive>
void PMCC::load(Archive &ar, const unsigned int)
{
    std::string type_id;
    ar & type_id;
    const PMCC &cloner = PMCSerializeLookup(type_id);
    this->reset(new PMCImpl());
    cloner->item->clone(this->get());
    ar & (*((*this)->item));
}
*/


#endif /*INCLUDED_PMC_SERIALIZE_HPP*/
