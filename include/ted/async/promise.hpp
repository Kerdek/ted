/*
              promise.hpp

             -- promises --

original (c) 2021 theodoric e. stier
public domain

generate language-conformant promises
from things satisfying `ted::suspends`.

*/

#ifndef H_C894CDE7_725D_4EF9_9FDB_BE7C06135E4E
#define H_C894CDE7_725D_4EF9_9FDB_BE7C06135E4E

#include <ted/async/suspends.hpp>

namespace ted::async
{

template<
    suspends Coroutine>
    struct promise
{
   Coroutine coroutine;

    auto get_return_object()
    & -> decltype(auto)
    {
        return sync_result(
            coroutine);
    }

    auto get_return_object()
    && -> decltype(auto)
    {
        return sync_result(
            same(coroutine));
    }

    auto get_return_object()
    const & -> decltype(auto)
    {
        return sync_result(
            coroutine);
    }

    auto get_return_object()
    const && -> decltype(auto)
    {
        return sync_result(
            same_const(coroutine));
    }

    auto initial_suspend()
    & -> decltype(auto)
    {
        return initial_task(
            coroutine);
    }

    auto initial_suspend()
    && -> decltype(auto)
    {
        return initial_task(
            same(coroutine));
    }

    auto initial_suspend()
    const & -> decltype(auto)
    {
        return initial_task(
            coroutine);
    }

    auto initial_suspend()
    const && -> decltype(auto)
    {
        return initial_task(
            same_const(coroutine));
    }

    auto final_suspend()
    & -> decltype(auto)
    {
        return final_task(
            coroutine);
    }

    auto final_suspend()
    && -> decltype(auto)
    {
        return final_task(
            same(coroutine));
    }

    auto final_suspend()
    const & -> decltype(auto)
    {
        return final_task(
            coroutine);
    }

    auto final_suspend()
    const && -> decltype(auto)
    {
        return until(final_task(
            same_const(coroutine)));
    }

    auto return_void()
    & -> decltype(auto)
    {
        return handle_return(
            coroutine);
    }

    auto return_void()
    && -> decltype(auto)
    {
        return handle_return(
            same(coroutine));
    }

    auto return_void()
    const & -> decltype(auto)
    {
        return handle_return(
            coroutine);
    }

    auto return_void()
    const && -> decltype(auto)
    {
        return handle_return(
            same_const(coroutine));
    }

    auto unhandled_exception()
    & -> decltype(auto)
    {
        return handle_exception(
            coroutine);
    }

    auto unhandled_exception()
    && -> decltype(auto)
    {
        return handle_exception(
            same(coroutine));
    }

    auto unhandled_exception()
    const & -> decltype(auto)
    {
        return handle_exception(
            coroutine);
    }

    auto unhandled_exception()
    const && -> decltype(auto)
    {
        return handle_exception(
            same_const(coroutine));
    }
};

}

#endif