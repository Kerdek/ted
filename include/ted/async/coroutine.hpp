/*
          async/coroutine.hpp

      -- coroutine return types --

original (c) 2021 theodoric e. stier
public domain

types usable as coroutine return types
are generated from types satisfying
'ted::async::coro'.

*/

#ifndef H_0493F53E_EFBF_465E_91AD_4A7A12CC8AB0
#define H_0493F53E_EFBF_465E_91AD_4A7A12CC8AB0

#include <ted/async/promise.hpp>

namespace ted::async
{

template<
    typename Coroutine>
    struct coroutine
{
    using promise_type = promise<
        Coroutine>;
};

}

#endif