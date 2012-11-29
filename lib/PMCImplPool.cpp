// Copyright (C) by Josh Blum. See LICENSE.txt for licensing information.

#include <boost/smart_ptr/detail/spinlock.hpp>
#include <boost/circular_buffer.hpp>

static boost::detail::spinlock pool_lock;
//static boost::circular_buffer<
