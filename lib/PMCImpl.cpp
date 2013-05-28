// Copyright (C) by Josh Blum. See LICENSE.txt for licensing information.

#include <PMC/PMC.hpp>
#include <boost/format.hpp>
#include <stdexcept>
#include <string>

/***********************************************************************
 * Helper functions for templated implementations
 **********************************************************************/
void intrusive_ptr_add_ref(PMCImpl *impl)
{
    ++impl->count;
}

void intrusive_ptr_release(PMCImpl *impl)
{
    if (--impl->count == 0)
    {
        delete impl;
    }
}

void PMC_impl_check_types(const PMCC *p, const std::type_info &t)
{
    if (p->type() == t) return;
    throw std::invalid_argument(str(boost::format(
        "Cannot cast %s to result type %s!"
    ) % (*p) % t.name()));
}

void PMC_impl_assert_not_null(const PMCC *p)
{
    if (not *p) throw std::invalid_argument("Calling method on a null PMC object!");
}

/***********************************************************************
 * PMCC base type
 **********************************************************************/
PMCC::PMCC(void)
{
    //NOP
}

PMCC::~PMCC(void)
{
    //NOP
}

bool PMCC::unique(void) const
{
    PMC_impl_assert_not_null(this);
    return (*this)->count == 1;
}

size_t PMCC::use_count(void) const
{
    PMC_impl_assert_not_null(this);
    return (*this)->count;
}

const std::type_info &PMCC::type(void) const
{
    PMC_impl_assert_not_null(this);
    return (*this)->type();
}

bool PMCC::is_intern(void) const
{
    return (*this)->intern;
}

/***********************************************************************
 * PMC read/write type
 **********************************************************************/
PMC::PMC(void)
{
    //NOP
}

PMC::~PMC(void)
{
    //NOP
}

/***********************************************************************
 * PMC implementation type
 **********************************************************************/
PMCImpl::PMCImpl(void):
    count(0),
    intern(false)
{
    //NOP
}

PMCImpl::~PMCImpl(void)
{
    //NOP
}

/***********************************************************************
 * PMC Factory function
 **********************************************************************/
PMCC PMC_M(const char *s)
{
    return PMC_M(std::string(s)).intern();
}

/***********************************************************************
 * PMC Comparable stuff
 **********************************************************************/
bool PMCC::eq(const PMCC &rhs) const
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
std::ostream& operator <<(std::ostream &os, const PMCC &obj)
{
    if (not obj) os << "PMC<NULL>";
    else os << "PMC<" << obj.type().name() << ">";
    return os;
}
