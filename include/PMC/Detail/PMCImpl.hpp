// Copyright (C) by Josh Blum. See LICENSE.txt for licensing information.

#ifndef INCLUDED_PMC_DETAIL_PMC_IMPL_HPP
#define INCLUDED_PMC_DETAIL_PMC_IMPL_HPP

/***********************************************************************
 * Implementation details of the underlying PMCImpl structure
 **********************************************************************/
#include <boost/detail/atomic_count.hpp>
#include <boost/format.hpp>
#include <stdexcept>
#include <string>

/***********************************************************************
 * Implementation base class, holds ref count
 **********************************************************************/
struct PMCImpl
{
    PMCImpl(void):
        count(0)
    {
        //NOP
    }

    virtual const std::type_info &type(void) const = 0;
    virtual bool equal(const PMCImpl *item) const = 0;

    boost::detail::atomic_count count;
};

/***********************************************************************
 * Templated container for holding the object
 **********************************************************************/
template <typename ValueType>
struct PMCImplContainer : PMCImpl
{
    PMCImplContainer(void)
    {
        //NOP
    }

    PMCImplContainer(const ValueType &value):
        value(value)
    {
        //NOP
    }

    const std::type_info &type(void) const
    {
        return typeid(ValueType);
    }

    bool equal(const PMCImpl *item) const
    {
        return value == static_cast<const PMCImplContainer<ValueType> *>(item)->value;
    }

    ValueType value;
};

/***********************************************************************
 * The cast implementation
 **********************************************************************/
template <typename CastType>
PMC_INLINE CastType &PMCImplCast(PMCImpl *item)
{
    const std::type_info &result_type = typeid(CastType);
    if (item->type() != result_type)
    {
        throw std::invalid_argument(str(boost::format(
            "Cannot cast object of type %s to result type %s!"
        ) % item->type().name() % result_type.name()));
    }
    return static_cast<PMCImplContainer<CastType> *>(item)->value;
}

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
        delete impl;
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
    return (*this)->type();
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
    return PMCImplCast<ValueType>(this->get());
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
    return PMCImplCast<ValueType>(this->get());
}

/***********************************************************************
 * PMC Factory function
 **********************************************************************/
template <typename ValueType>
PMC_INLINE PMC PMC_M(const ValueType &value)
{
    PMC p;
    p.reset(new PMCImplContainer<ValueType>(value));
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
        return lhs->equal(rhs.get());
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
