/* This program is free software. It comes without any warranty, to
* the extent permitted by applicable law. You can redistribute it
* and/or modify it under the terms of the Do What The Fuck You Want
* To Public License, Version 2, as published by Sam Hocevar. See
* http://sam.zoy.org/wtfpl/COPYING for more details. */

#ifndef INCLUDED_PMC_PMC_HPP
#define INCLUDED_PMC_PMC_HPP

#include <PMC/Config.hpp>
#include <boost/intrusive_ptr.hpp>
#include <stdexcept>
#include <typeinfo>

/*!
* PMC: Just another polymorphic container for C++.
*
* The goal of PMC is to be a polymorphic container that holds primitive types such as
* integers, floats, complex, string, and basic data structures like arrays and dicts.
*
* PMC is a reference counted object. Once created with a value, the value will not be copied.
* This makes copying PMCs very cheap, and light-weight on the allocation overhead.
* Also, the contained object will not be deleted until all references are deleted.
* TODO: create fixed size allocation pool for PMCImpl allocations/frees.
*
* A PMC can contain any primitive or STL object - as long as that object fits.
* PMC uses a fixed size buffer of PMC_FIXED_BUFF_SIZE bytes to hold the object.
*/
struct PMC : boost::intrusive_ptr<PMCImpl>
{
    //! Make an empty container
    PMC(void);

    //! Make a new container holding a copy of the given value
    template <typename ValueType>
    PMC(const ValueType &value);

    //! empty virtual deconstructor
    virtual ~PMC(void){}

    /*!
    * Cast the item held by this object to an arbitrary type.
    * This method will return a const reference to the object.
    * Only call if this object is not empty.
    */
    template <typename ValueType>
    const ValueType &ccast(void) const;

    /*!
    * Cast the item held by this object to an arbitrary type.
    * This method will return a reference to the object.
    * Use this method to modify the contained value.
    * Only call if this object is not empty.
    */
    template <typename ValueType>
    ValueType &cast(void);

    //! Unique if caller holds the only reference count
    bool unique(void) const;

    //! Get the number of reference holders
    size_t use_count(void) const;

    /*!
    * Get the type of the item held.
    * Only call if this object is not empty.
    */
    const std::type_info &type(void) const;

    //! Check if the container type matches
    template <typename ValueType>
    bool is_type(void) const;
};

/*!
* A readonly version of the PMC container. Only const references can be retrieved.
* A PMCC can be created from a PMC, but the other way around is not possible.
* All of the methods available to the PMC object are available to PMCC as well.
* However, the non-const cast method will throw because of constness restrictions.
*/
struct PMCC : PMC
{
    //! Create a null or empty PMCC
    PMCC(void);

    //! Create a PMCC from an existing PMC
    PMCC(const PMC &p);

    //! Make a new container holding a copy of the given value
    template <typename ValueType>
    PMCC(const ValueType &value);
};

#include <PMC/Detail/PMCImpl.hpp>

#endif /*INCLUDED_PMC_PMC_HPP*/
