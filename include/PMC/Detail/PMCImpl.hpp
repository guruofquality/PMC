// Copyright (C) by Josh Blum. See LICENSE.txt for licensing information.

#ifndef INCLUDED_PMC_DETAIL_PMC_IMPL_HPP
#define INCLUDED_PMC_DETAIL_PMC_IMPL_HPP

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning (disable:4251)  // needs to have dll interface
#endif //_MSC_VER

/***********************************************************************
 * Implementation details of the underlying PMCImpl structure
 **********************************************************************/
#include <boost/detail/atomic_count.hpp>

/***********************************************************************
 * Implementation base class, holds ref count
 **********************************************************************/
struct PMC_API PMCImpl
{
    PMCImpl(void);

    virtual ~PMCImpl(void);

    virtual const std::type_info &type(void) const = 0;
    virtual bool equal(const PMCImpl *item) const = 0;

    void *operator new(const size_t size);
    void operator delete(void *mem, const size_t size);

    boost::detail::atomic_count count;
    bool intern;
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

    ~PMCImplContainer(void)
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
 * Helper functions for templated implementations
 **********************************************************************/
extern PMC_API void PMC_impl_assert_not_null(const PMCC *p);

extern PMC_API void intrusive_ptr_add_ref(PMCImpl *impl);

extern PMC_API void intrusive_ptr_release(PMCImpl *impl);

extern PMC_API void PMC_impl_check_types(const PMCC *p, const std::type_info &t);

extern PMC_API PMCC PMC_impl_safe_convert(const PMCC *p, const std::type_info &t);

/***********************************************************************
 * The cast implementation
 **********************************************************************/
template <typename CastType>
PMC_INLINE CastType &PMCImplCast(const PMCC *p)
{
    PMCImpl *item = p->get();
    return reinterpret_cast<PMCImplContainer<CastType> *>(item)->value;
}

/***********************************************************************
 * PMCC base type
 **********************************************************************/
template <typename ValueType>
PMC_INLINE bool PMCC::is(void) const
{
    if (not *this) return false;
    return this->type() == typeid(ValueType);
}

template <typename ValueType>
PMC_INLINE const ValueType &PMCC::as(void) const
{
    PMC_impl_assert_not_null(this);
    PMC_impl_check_types(this, typeid(ValueType));
    return PMCImplCast<ValueType>(this);
}

template <typename ValueType>
PMC_INLINE ValueType PMCC::safe_as(void) const
{
    PMC_impl_assert_not_null(this);
    PMCC p = PMC_impl_safe_convert(this, typeid(ValueType));
    return p.as<ValueType>();
}

/***********************************************************************
 * PMC read/write type
 **********************************************************************/
template <typename ValueType>
PMC_INLINE ValueType &PMC::as(void) const
{
    PMC_impl_assert_not_null(this);
    PMC_impl_check_types(this, typeid(ValueType));
    return PMCImplCast<ValueType>(this);
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

#ifdef _MSC_VER
#pragma warning(pop)
#endif //_MSC_VER

#endif /*INCLUDED_PMC_DETAIL_PMC_IMPL_HPP*/
