// Copyright (C) by Josh Blum. See LICENSE.txt for licensing information.

#include <PMC/Serialize.hpp>

#include <boost/archive/polymorphic_binary_oarchive.hpp>
#include <boost/archive/polymorphic_binary_iarchive.hpp>

#include <boost/archive/polymorphic_text_oarchive.hpp>
#include <boost/archive/polymorphic_text_iarchive.hpp>

#include <boost/archive/polymorphic_xml_oarchive.hpp>
#include <boost/archive/polymorphic_xml_iarchive.hpp>

#include <sstream>
#include <stdexcept>

std::string PMCC::serialize(const PMCC &object, const std::string &format)
{
    std::stringstream ss;

    if (format == "BINARY")
    {
        boost::archive::polymorphic_binary_oarchive oa(ss);
        oa << object;
    }
    else if (format == "TEXT")
    {
        boost::archive::polymorphic_text_oarchive oa(ss);
        oa << object;
    }
    else if (format == "XML")
    {
        boost::archive::polymorphic_xml_oarchive oa(ss);
        oa << object;
    }
    else throw std::invalid_argument("PMCC::serialize unknown format: " + format);

    return ss.str();
}

PMCC PMCC::deserialize(const std::string &data, const std::string &format)
{
    std::stringstream ss(data);
    PMCC object;

    if (format == "BINARY")
    {
        boost::archive::polymorphic_binary_iarchive ia(ss);
        ia >> object;
    }
    else if (format == "TEXT")
    {
        boost::archive::polymorphic_text_iarchive ia(ss);
        ia >> object;
    }
    else if (format == "XML")
    {
        boost::archive::polymorphic_xml_iarchive ia(ss);
        ia >> object;
    }
    else throw std::invalid_argument("PMCC::serialize unknown format: " + format);

    return object;
}
