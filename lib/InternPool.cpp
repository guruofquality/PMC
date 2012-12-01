// Copyright (C) by Josh Blum. See LICENSE.txt for licensing information.

#include <PMC/PMC.hpp>
#include <boost/smart_ptr/detail/spinlock.hpp>
#include <boost/foreach.hpp>
#include <list>

static boost::detail::spinlock pool_lock;
static std::list<PMCC> intern_pool;

const PMCC &PMCC::intern(void) const
{
    pool_lock.lock();
    BOOST_FOREACH(const PMCC &p, intern_pool)
    {
        if (this->eq(p))
        {
            pool_lock.unlock();
            return p;
        }
    }
    intern_pool.push_back(*this);
    pool_lock.unlock();
    return *this;
}
