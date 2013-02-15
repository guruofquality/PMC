// Copyright (C) by Josh Blum. See LICENSE.txt for licensing information.

#ifndef INCLUDED_PMC_PMC_HPP
#define INCLUDED_PMC_PMC_HPP

#include <PMC/Config.hpp>
#include <typeinfo>
#include <ostream>

/*!
 * PMC: Just another polymorphic container for C++.
 *
 * The goal of PMC is to be a polymorphic container that holds primitive types such as
 * integers, floats, complex, string, and basic data structures like arrays and dicts.
 *
 * PMC is a reference counted object. Once created with a value, the value will not be copied.
 * This makes copying PMCs very cheap, and light-weight on the allocation overhead.
 * Also, the contained object will not be deleted until all references are deleted.
 */
struct PMCC : PMCBase
{
    //! Create a null or empty PMCC
    PMCC(void);

    //! empty virtual deconstructor
    virtual ~PMCC(void){}

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
    bool is(void) const;

    /*!
     * Cast the item held by this object to an arbitrary type.
     * This method will return a const reference to the object.
     * Only call if this object is not empty.
     */
    template <typename ValueType>
    const ValueType &as(void) const;

    /*!
     * Create an interned PMC object.
     *
     * Object interning ensures that there is only one unique
     * memory allocation for each unique object that is interned.
     * https://en.wikipedia.org/wiki/String_interning
     *
     * Interning a PMC has a high overhead cost due to lookup;
     * the advantage is that comparison of interned objects
     * has the equivalent overhead of comparing pointers.
     *
     * The implementation details:
     * Search for a duplicate object in the intern pool.
     * If found, return the entry already in the pool.
     * Otherwise, create a new entry in the intern pool.
     *
     * This method will return a PMC from the intern pool.
     * The PMC involved in the call will not be changed!
     * Interned objects are intentionally immutable.
     * To ensure immutability, the intern() returns PMCC.
     *
     * \return an object from the intern pool
     */
    PMC_API const PMCC &intern(void) const;

    //! True if this PMC object has been interned
    bool is_intern(void) const;

    /*!
     * Compare two PMC objects for equivalency.
     * The operator==() checks if the containers are idential.
     * The eq() method checks if the contents are identical.
     * If both objects are null, the result is also true.
     * \return true if they have the same contents
     */
    bool eq(const PMCC &rhs) const;
};

/*!
 * The read/write version of the PMC container.
 * Non-const references can be retrieved.
 */
struct PMC : PMCC
{
    //! Make an empty container
    PMC(void);

    /*!
     * Cast the item held by this object to an arbitrary type.
     * This method will return a reference to the object.
     * Use this method to read or write the contained value.
     * Only call if this object is not empty.
     */
    template <typename ValueType>
    ValueType &as(void) const;
};

//! Make a new container holding a copy of the given value
template <typename ValueType>
PMC PMC_M(const ValueType &value);

//! Special make overload to create std::string from char *
PMCC PMC_M(const char *);

//! PMCC stream operator for iostream printing
std::ostream& operator <<(std::ostream &os, const PMCC &obj);

#include <PMC/Detail/PMCImpl.hpp>

#endif /*INCLUDED_PMC_PMC_HPP*/
