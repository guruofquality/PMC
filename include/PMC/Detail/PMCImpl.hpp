/* This program is free software. It comes without any warranty, to
* the extent permitted by applicable law. You can redistribute it
* and/or modify it under the terms of the Do What The Fuck You Want
* To Public License, Version 2, as published by Sam Hocevar. See
* http://sam.zoy.org/wtfpl/COPYING for more details. */

#ifndef INCLUDED_PMC_DETAIL_PMC_IMPL_HPP
#define INCLUDED_PMC_DETAIL_PMC_IMPL_HPP

/***********************************************************************
 * Implementation details of the underlying PMCImpl structure
 **********************************************************************/
#include <boost/detail/atomic_count.hpp>
#include <boost/format.hpp>
#include <new> //in-place new
#include <cstddef> //null

struct PMCImpl
{
    PMCImpl(void):
        count(0),
        item(NULL)
    {
        //NOP
    }

    ~PMCImpl(void)
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
    char buff[PMC_FIXED_BUFF_SIZE];
};

/***********************************************************************
 * Implementation details of PMC constructors and methods
 **********************************************************************/
PMC_INLINE void PMC_impl_assert_not_null(const PMC *p)
{
    if (not *p) throw std::invalid_argument("Calling method on a null PMC object!");
}


PMC_INLINE void intrusive_ptr_add_ref(PMCImpl *impl)
{
    ++impl->count;
}

PMC_INLINE void intrusive_ptr_release(PMCImpl *impl)
{
    if (--impl->count == 0)
    {
        delete impl;
    }
}

PMC_INLINE PMC::PMC(void)
{
    //NOP
}

template <typename ValueType>
PMC_INLINE PMC PMC::make(const ValueType &value)
{
    if (sizeof(ValueType) > PMC_FIXED_BUFF_SIZE)
    {
        throw std::invalid_argument(str(boost::format(
            "Object of type %s (%u bytes) is too large for PMC (max %u bytes)!"
        ) % typeid(ValueType).name() % sizeof(ValueType) % PMC_FIXED_BUFF_SIZE));
    }
    PMC p;
    p.reset(new PMCImpl());
    void *buff = (void *)p->buff;
    p->item = new (buff) PMCImpl::Container<ValueType>(value);
    return p;
}

template <typename ValueType>
PMC_INLINE const ValueType &PMC::cast(void) const
{
    PMC_impl_assert_not_null(this);
    return (*this)->cast<ValueType>();
}

template <typename ValueType>
PMC_INLINE ValueType &PMC::cast(void)
{
    PMC_impl_assert_not_null(this);
    return (*this)->cast<ValueType>();
}

PMC_INLINE bool PMC::unique(void) const
{
    PMC_impl_assert_not_null(this);
    return (*this)->count == 1;
}

PMC_INLINE size_t PMC::use_count(void) const
{
    PMC_impl_assert_not_null(this);
    return (*this)->count;
}

PMC_INLINE const std::type_info &PMC::type(void) const
{
    PMC_impl_assert_not_null(this);
    return (*this)->item->type();
}

template <typename ValueType>
PMC_INLINE bool PMC::is_type(void) const
{
    if (not *this) return false;
    return this->type() == typeid(ValueType);
}

/***********************************************************************
 * PMC const type
 **********************************************************************/
PMC_INLINE PMCC::PMCC(void)
{
    //NOP
}

PMC_INLINE PMCC::PMCC(const PMC &p)
{
    this->reset(p.get());
}

template <typename ValueType>
PMC_INLINE const ValueType &PMCC::cast(void)
{
    PMC_impl_assert_not_null(this);
    return (*this)->cast<ValueType>();
}

template <typename ValueType>
PMC_INLINE const ValueType &PMCC::cast(void) const
{
    PMC_impl_assert_not_null(this);
    return (*this)->cast<ValueType>();
}

/***********************************************************************
 * PMC Comparable stuff
 **********************************************************************/
PMC_INLINE bool PMCCompare(const PMCC &lhs, const PMCC &rhs)
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

PMC_INLINE bool operator==(const PMC &lhs, const PMC &rhs)
{
    return PMCCompare(lhs, rhs);
}

PMC_INLINE bool operator==(const PMC &lhs, const PMCC &rhs)
{
    return PMCCompare(lhs, rhs);
}

PMC_INLINE bool operator==(const PMCC &lhs, const PMC &rhs)
{
    return PMCCompare(lhs, rhs);
}

PMC_INLINE bool operator==(const PMCC &lhs, const PMCC &rhs)
{
    return PMCCompare(lhs, rhs);
}

#endif /*INCLUDED_PMC_DETAIL_PMC_IMPL_HPP*/
