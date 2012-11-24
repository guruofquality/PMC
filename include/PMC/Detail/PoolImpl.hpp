// Copyright (C) by Josh Blum. See LICENSE.txt for licensing information.

#ifndef INCLUDED_PMC_DETAIL_POOL_IMPL_HPP
#define INCLUDED_PMC_DETAIL_POOL_IMPL_HPP

PMCPool::PMCPool(void)
{
    _next_i = 0;
}

PMCPool::~PMCPool(void)
{
    this->clear();
}

PMC PMCPool::get(void)
{
    //minor optimization, look at the last index + 1
    if (_next_i < this->size() and this->at(_next_i).unique())
    {
        return this->at(_next_i);
    }
    for (size_t i = 0; i < this->size(); i++)
    {
        if (this->at(i).unique())
        {
            _next_i = i+1;
            return this->at(i);
        }
    }
    return PMC(); //NULL
};

#endif /*INCLUDED_PMC_DETAIL_POOL_IMPL_HPP*/
