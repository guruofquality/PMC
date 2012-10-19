/* This program is free software. It comes without any warranty, to
* the extent permitted by applicable law. You can redistribute it
* and/or modify it under the terms of the Do What The Fuck You Want
* To Public License, Version 2, as published by Sam Hocevar. See
* http://sam.zoy.org/wtfpl/COPYING for more details. */

#ifndef PCOP_HPP
#define PCOP_HPP

#include <boost/intrusive_ptr.hpp>
#include <stdexcept>
#include <typeinfo>

#define PCOP_FIXED_BUFF_SIZE 64 //bytes
#define PCOP_INLINE inline

struct PCoPImpl;

/*!
* PCoP: The polymorphic container of primitives.
*
* The goal of PCoP is to be a polymorphic container that holds primitive types such as
* integers, floats, complex, string, and basic data structures like arrays and dicts.
*
* PCoP is a reference counted object. Once created with a value, the value will not be copied.
* This makes copying PCoPs very cheap, and light-weight on the allocation overhead.
* Also, the contained object will not be deleted until all references are deleted.
* TODO: create fixed size allocation pool for PCoPImpl allocations/frees.
*
* A PCoP can contain any primitive or STL object - as long as that object fits.
* PCoP uses a fixed size buffer of PCOP_FIXED_BUFF_SIZE bytes to hold the object.
*/
struct PCoP : boost::intrusive_ptr<PCoPImpl>
{
    //! Make an empty container
    PCoP(void);

    //! Make a new container holding a copy of the given value
    template <typename ValueType>
    PCoP(const ValueType &value);

    //! empty virtual deconstructor
    virtual ~PCoP(void){}

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
* A readonly version of the PCoP container. Only const references can be retrieved.
* A PCoPConst can be created from a PCoP, but the other way around is not possible.
* All of the methods available to the PCoP object are available to PCoPConst as well.
* However, the non-const cast method will throw because of constness restrictions.
*/
struct PCoPConst : PCoP
{
    //! Create a null or empty PCoPConst
    PCoPConst(void);

    //! Create a PCoPConst from an existing PCoP
    PCoPConst(const PCoP &p);

    //! Make a new container holding a copy of the given value
    template <typename ValueType>
    PCoPConst(const ValueType &value);
};

/***********************************************************************
* Common typedefs for stl container classes of PCoPs
**********************************************************************/
#include <vector> //array type
#include <map> //dictionary type
#include <utility> //key/value pair type

/*!
* A linear array of PCoP objects.
*/
typedef std::vector<PCoP> PCoPArray;

/*!
* A tuple of const only PCoPs
*/
typedef std::vector<PCoPConst> PCoPTuple;

/*!
* A pair of PCoP objects, used w/ Dict.
*/
typedef std::pair<PCoP, PCoP> PCoPPair;

/*!
* A dictionary/mapping of PCoP objects.
*/
typedef std::map<PCoP, PCoP> PCoPDict;

/*!
* A blob is a chunk of memory and a length.
*/
typedef std::vector<unsigned char> PCoPBlob;

/***********************************************************************
* Implementation details of the underlying PCoPImpl structure
**********************************************************************/
#include <boost/detail/atomic_count.hpp>
#include <boost/format.hpp>
#include <new> //in-place new
#include <cstddef> //null

struct PCoPImpl
{
    PCoPImpl(void):
        count(0),
        item(NULL)
    {
        //NOP
    }

    ~PCoPImpl(void)
    {
        if (item) item->reset();
    }

    boost::detail::atomic_count count;

    struct Item
    {
        virtual void reset(void) = 0;
        virtual Item *clone(void *) const = 0;
        virtual const std::type_info &type(void) const = 0;
        virtual bool equal(const Item *item) const = 0;
    } *item;

    template <typename ValueType>
    struct Container : Item
    {
        Container(const ValueType &value):
            value(value)
        {
            //NOP
        }

        void reset(void)
        {
            value = ValueType();
        }

        const std::type_info &type(void) const
        {
            return typeid(ValueType);
        }

        Item *clone(void *buff) const
        {
            return new (buff) Container<ValueType>(value);
        }

        bool equal(const Item *item) const
        {
            return value == static_cast<const Container<ValueType> *>(item)->value;
        }

        ValueType value;
    };

    template <typename CastType>
    CastType &cast(void) const
    {
        const std::type_info &result_type = typeid(CastType);
        if (item->type() != result_type)
        {
            throw std::invalid_argument(str(boost::format(
                "Cannot cast object of type %s to result type %s!"
            ) % item->type().name() % result_type.name()));
        }
        return static_cast<Container<CastType> *>(item)->value;
    }

    //! The fixed size storage buffer
    char buff[PCOP_FIXED_BUFF_SIZE];
};

/***********************************************************************
* Implementation details of PCoP constructors and methods
**********************************************************************/
PCOP_INLINE void pcop_impl_assert_not_null(const PCoP *p)
{
    if (not *p) throw std::runtime_error("Calling method on a null PCoP object!");
}


PCOP_INLINE void intrusive_ptr_add_ref(PCoPImpl *impl)
{
    ++impl->count;
}

PCOP_INLINE void intrusive_ptr_release(PCoPImpl *impl)
{
    if (--impl->count == 0)
    {
        delete impl;
    }
}

PCOP_INLINE PCoP::PCoP(void)
{
    //NOP
}

template <typename ValueType>
PCOP_INLINE PCoP::PCoP(const ValueType &value)
{
    if (sizeof(ValueType) > PCOP_FIXED_BUFF_SIZE)
    {
        throw std::runtime_error(str(boost::format(
            "Object of type %s (%u bytes) is too large for PCoP (max %u bytes)!"
        ) % typeid(ValueType).name() % sizeof(ValueType) % PCOP_FIXED_BUFF_SIZE));
    }
    this->reset(new PCoPImpl());
    void *buff = (void *)(*this)->buff;
    (*this)->item = new (buff) PCoPImpl::Container<ValueType>(value);
}

template <typename ValueType>
PCOP_INLINE const ValueType &PCoP::ccast(void) const
{
    pcop_impl_assert_not_null(this);
    return (*this)->cast<ValueType>();
}

template <typename ValueType>
PCOP_INLINE ValueType &PCoP::cast(void)
{
    pcop_impl_assert_not_null(this);
    if (dynamic_cast<PCoPConst *>(this))
    {
        throw std::runtime_error("PCoP constness prevents cast to non-const reference!");
    }
    return (*this)->cast<ValueType>();
}

PCOP_INLINE bool PCoP::unique(void) const
{
    pcop_impl_assert_not_null(this);
    return (*this)->count == 1;
}

PCOP_INLINE size_t PCoP::use_count(void) const
{
    pcop_impl_assert_not_null(this);
    return (*this)->count;
}

PCOP_INLINE const std::type_info &PCoP::type(void) const
{
    pcop_impl_assert_not_null(this);
    return (*this)->item->type();
}

template <typename ValueType>
bool PCoP::is_type(void) const
{
    if (not *this) return false;
    return this->type() == typeid(ValueType);
}

PCOP_INLINE bool PCoPEquals(const PCoPConst &lhs, const PCoPConst &rhs)
{
    //both null so its the same
    if (not lhs and not rhs) return true;
    //both non-null so perform equals compare
    if (lhs and rhs and lhs.type() == rhs.type())
    {
        return lhs->item->equal(rhs->item);
    }
    return false;
}

PCOP_INLINE PCoPConst::PCoPConst(void):
    PCoP()
{
    //NOP
}

PCOP_INLINE PCoPConst::PCoPConst(const PCoP &p)
{
    this->reset(p.get());
}

template <typename ValueType>
PCOP_INLINE PCoPConst::PCoPConst(const ValueType &value):
    PCoP(value)
{
    //NOP
}

/*
#include <iostream>

int main(void)
{
PCoP foo;
PCoP bar(1);
PCoP s0(std::string("hello"));
PCoP s1(std::string("hello"));
PCoP s2(std::string("bye"));
std::cout << "s0 == s1 " << (s0 == s1) << std::endl;
std::cout << "s0 == s2 " << (s0 == s2) << std::endl;
std::cout << "s0 == foo " << (s0 == foo) << std::endl;

PCoP::Array a0(2);
a0[0] = 24;
a0[1] = 42;

PCoP::Array a1(2);
a1[0] = 24;
a1[1] = 42;

PCoP a0c(a0);
PCoP a1c(a1);
std::cout << "a0c == a1c " << (a0c == a1c) << std::endl;

std::cout << "a0c.cast<PCoP::Array>().size() " << a0c.cast<PCoP::Array>().size() << std::endl;

PCoPConst a0c_const(a0c);

const PCoP::Array &bob = a0c_const.ccast<PCoP::Array>();

std::cout << "a0c_const count " << a0c_const.use_count() << std::endl;
a0c_const.reset();
std::cout << "a0c count " << a0c.use_count() << std::endl;
}
*/

#endif /*PCOP_HPP*/
