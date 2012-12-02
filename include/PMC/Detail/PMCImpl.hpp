// Copyright (C) by Josh Blum. See LICENSE.txt for licensing information.

#ifndef INCLUDED_PMC_DETAIL_PMC_IMPL_HPP
#define INCLUDED_PMC_DETAIL_PMC_IMPL_HPP

/***********************************************************************
 * Implementation details of the underlying PMCImpl structure
 **********************************************************************/
#include <boost/detail/atomic_count.hpp>
#include <boost/format.hpp>
#include <new> //in-place new
#include <cstddef> //null
#include <stdexcept>
#include <string>

struct PMCImpl
{
    PMCImpl(void):
        count(0),
        item(NULL),
        buff(NULL)
    {
        //NOP
    }

    void reset(void)
    {
        if (item) item->reset();
        if (buff) delete [] buff;
    }

    boost::detail::atomic_count count;

    struct Item
    {
        virtual void reset(void) = 0;
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

    char *buff;
};

/***********************************************************************
 * Implementation details of PMC constructors and methods
 **********************************************************************/
PMC_INLINE void PMC_impl_assert_not_null(const PMCC *p)
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
        impl->reset();
    }
}

/***********************************************************************
 * PMCC base type
 **********************************************************************/
PMC_INLINE bool PMCC::unique(void) const
{
    PMC_impl_assert_not_null(this);
    return (*this)->count == 1;
}

PMC_INLINE size_t PMCC::use_count(void) const
{
    PMC_impl_assert_not_null(this);
    return (*this)->count;
}

PMC_INLINE const std::type_info &PMCC::type(void) const
{
    PMC_impl_assert_not_null(this);
    return (*this)->item->type();
}

template <typename ValueType>
PMC_INLINE bool PMCC::is(void) const
{
    if (not *this) return false;
    return this->type() == typeid(ValueType);
}

PMC_INLINE PMCC::PMCC(void)
{
    //NOP
}

template <typename ValueType>
PMC_INLINE const ValueType &PMCC::as(void) const
{
    PMC_impl_assert_not_null(this);
    return (*this)->cast<ValueType>();
}

/***********************************************************************
 * PMC read/write type
 **********************************************************************/
PMC_INLINE PMC::PMC(void)
{
    //NOP
}

template <typename ValueType>
PMC_INLINE ValueType &PMC::as(void) const
{
    PMC_impl_assert_not_null(this);
    return (*this)->cast<ValueType>();
}

/***********************************************************************
 * PMC Factory function
 **********************************************************************/
template <typename ValueType>
PMC_INLINE PMC PMC_M(const ValueType &value)
{
    //create a buffer that can hold a PMCImpl + container
    char *buff = new char[sizeof(PMCImpl)+sizeof(PMCImpl::Container<ValueType>)];

    //create a new impl object at the start of this buffer
    PMC p; p.reset(new (buff) PMCImpl());

    //store a pointer to this buffer so it can clean up later
    p->buff = buff;

    //create a container in the came buffer + offset
    p->item = new (buff + sizeof(PMCImpl)) PMCImpl::Container<ValueType>(value);

    return p;
}

PMC_INLINE const PMCC &PMC_M(const char *s)
{
    return PMC_M(std::string(s)).intern();
}

/***********************************************************************
 * PMC Comparable stuff
 **********************************************************************/
PMC_INLINE bool PMCC::eq(const PMCC &rhs) const
{
    const PMCC &lhs = *this;
    //equal pointers mean same obj or both null
    if (lhs.get() == rhs.get()) return true;
    //both non-null so perform equals compare
    if (lhs and rhs and lhs.type() == rhs.type())
    {
        return lhs->item->equal(rhs->item);
    }
    return false;
}

/***********************************************************************
 * PMC stream stuff
 **********************************************************************/
PMC_INLINE std::ostream& operator <<(std::ostream &os, const PMCC &obj)
{
    if (not obj) os << "PMC<NULL>";
    else os << "PMC<" << obj.type().name() << ">";
    return os;
}

#endif /*INCLUDED_PMC_DETAIL_PMC_IMPL_HPP*/
