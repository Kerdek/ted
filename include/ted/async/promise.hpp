/*
              promise.hpp

             -- promises --

original (c) 2021 theodoric e. stier
public domain

generate language-compatible promises
from things satisfying `ted::suspends`.

*/

#ifndef H_C894CDE7_725D_4EF9_9FDB_BE7C06135E4E
#define H_C894CDE7_725D_4EF9_9FDB_BE7C06135E4E

namespace ted::async
{

template<
    typename Coroutine>
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
        return initial_operation(
            coroutine);
    }

    auto initial_suspend()
    && -> decltype(auto)
    {
        return initial_operation(
            same(coroutine));
    }

    auto initial_suspend()
    const & -> decltype(auto)
    {
        return initial_operation(
            coroutine);
    }

    auto initial_suspend()
    const && -> decltype(auto)
    {
        return initial_operation(
            same_const(coroutine));
    }

    auto final_suspend()
    & noexcept -> decltype(auto)
    {
        return final_operation(
            coroutine);
    }

    auto final_suspend()
    && noexcept -> decltype(auto)
    {
        return final_operation(
            same(coroutine));
    }

    auto final_suspend()
    const & noexcept -> decltype(auto)
    {
        return final_operation(
            coroutine);
    }

    auto final_suspend()
    const && noexcept -> decltype(auto)
    {
        return final_operation(
            same_const(coroutine));
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