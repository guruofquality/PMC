// Copyright (C) by Josh Blum. See LICENSE.txt for licensing information.

#include <PMC/PMC.hpp>
#include <boost/smart_ptr/detail/spinlock.hpp>
#include <boost/foreach.hpp>
#include <list>

static boost::detail::spinlock pool_lock;
static std::list<PMCC> &get_intern_pool(void)
{
    static std::list<PMCC> intern_pool;
    return intern_pool;
}

const PMCC &PMCC::intern(void) const
{
    pool_lock.lock();
    BOOST_FOREACH(const PMCC &p, get_intern_pool())
    {
        if (this->eq(p))
        {
            pool_lock.unlock();
            return p;
        }
    }
    get_intern_pool().push_back(*this);
    (*this)->intern = true;
    pool_lock.unlock();
    return *this;
}
