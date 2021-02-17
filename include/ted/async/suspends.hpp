/*
              suspends.hpp

        -- coroutine adapters --

original (c) 2021 theodoric e. stier
public domain

*/

#ifndef H_8D7404EA_8BAC_43AC_A510_C053145CAC64
#define H_8D7404EA_8BAC_43AC_A510_C053145CAC64

namespace ted::async
{

template<
    typename Coroutine>
concept suspends = requires (
    Coroutine c)
{
    sync_result(c);
    initial_operation(c);
    final_operation(c);
};

}

#endif