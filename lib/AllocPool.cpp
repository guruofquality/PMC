// Copyright (C) by Josh Blum. See LICENSE.txt for licensing information.

#include <PMC/PMC.hpp>
#include <boost/smart_ptr/detail/spinlock.hpp>
#include <boost/circular_buffer.hpp>
#include <iostream>

#define MY_ALLOCATOR_CHUNK_SIZE 64
#define MY_ALLOCATOR_POOL_SIZE (MY_ALLOCATOR_CHUNK_SIZE * (1 << 14))

static struct AllocPool
{
    AllocPool(void)
    {
        const size_t N = MY_ALLOCATOR_POOL_SIZE/MY_ALLOCATOR_CHUNK_SIZE;
        queue.set_capacity(N);
        for (size_t i = 0; i < N; i++)
        {
            const ptrdiff_t pool_ptr = ptrdiff_t(pool) + i*MY_ALLOCATOR_CHUNK_SIZE;
            queue.push_back((void *)pool_ptr);
        }
        pool_end = ptrdiff_t(pool) + MY_ALLOCATOR_POOL_SIZE;
    }

    ~AllocPool(void)
    {
        //NOP
    }

    PMC_INLINE void *Allocate(const size_t size)
    {
        if (size <= MY_ALLOCATOR_CHUNK_SIZE)
        {
            spin_lock.lock();
            if (queue.empty())
            {
                spin_lock.unlock();
                return std::malloc(size);
            }
            void *memory = queue.front();
            queue.pop_front();
            spin_lock.unlock();
            return memory;
        }
        else
        {
            //std::cout << "malloc size " << size << std::endl;
            return std::malloc(size);
        }
    }

    PMC_INLINE void Free(void *const memory)
    {
        const bool in_pool = ptrdiff_t(memory) >= ptrdiff_t(pool) and ptrdiff_t(memory) < pool_end;
        if (in_pool)
        {
            spin_lock.lock();
            queue.push_front(memory);
            spin_lock.unlock();
        }
        else
        {
            std::free(memory);
        }
    }

    boost::circular_buffer<void *> queue;
    char pool[MY_ALLOCATOR_POOL_SIZE];
    ptrdiff_t pool_end;
    boost::detail::spinlock spin_lock;

} my_alloc;

void *PMCImpl::operator new(const size_t size)
{
    return my_alloc.Allocate(size);
}

void PMCImpl::operator delete(void *mem, const size_t)
{
    return my_alloc.Free(mem);
}
