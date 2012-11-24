// Copyright (C) by Josh Blum. See LICENSE.txt for licensing information.

#ifndef INCLUDED_PMC_POOL_HPP
#define INCLUDED_PMC_POOL_HPP

#include <PMC/PMC.hpp>
#include <vector>

/*!
 * A PMC pool holds homogeneous collection of PMCs.
 * The pool has all the same semantics as std::vector.
 * What is special here is that the pool is designed
 * to help with re-usable allocations of PMCs.
 * 
 * To use:
 * The user should push_back new PMCs into the pool.
 * When a PMC is needed, the user calls get();
 * Either a null PMC is returned (none available),
 * or an available PMC is returned for the user.
 */
class PMCPool : public std::vector<PMC>
{
public:
    //! Constructor for empty pool
    PMCPool(void);

    //! Destructor for pool
    ~PMCPool(void);

    //! Get a PMC in the pool if available, else null PMC
    PMC get(void);

private:
    size_t _next_i;
};

#include <PMC/Detail/PoolImpl.hpp>

#endif /*INCLUDED_PMC_POOL_HPP*/
