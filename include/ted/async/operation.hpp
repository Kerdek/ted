/*
           async/awaitable.hpp

            -- awaitables --

original (c) 2021 theodoric e. stier
public domain

libted phrases asynchronous
operations in terms of tasks. here,
we generate coroutine awaitable types
from task types.

reference wrappers are unwrapped
using unqualified 'obj'

*/

#ifndef H_9DA38D24_556B_4030_A811_83A582F37C2E
#define H_9DA38D24_556B_4030_A811_83A582F37C2E

#include <ted/ref.hpp>
#include <ted/memfn.hpp>

#ifdef __clang__
#include <experimental/coroutine>
#endif

namespace ted::async
{

template<
    typename T>
concept operation =
    requires (T x)
{
    done(x);
    result(same(x));
};

template<
    typename T>
concept nothrow_result =
    requires (T x)
{
    { result(same(x)) } noexcept;
};

template<
    typename T>
concept nothrow_operation =
    operation<T> &&
    nothrow_result<T>;

template<
    operation Task>
struct awaitable_t
{
    Task task;

    memfn(
        auto await_ready(),
        noexcept -> decltype(auto),
        done, task)

    memfn(
        template<
            typename Continuation>
        auto await_suspend(
            Continuation &&f),
        -> decltype(auto),
        then, task, same(f))

    memfn(
        auto await_resume(),
        -> decltype(auto),
        result, task)
};

template<
    nothrow_operation Task>
struct nothrow_awaitable_t
{
    Task task;

    memfn(
        auto await_ready(),
        noexcept -> decltype(auto),
        done, task)

    memfn(
        template<
            typename Continuation>
        auto await_suspend(
            Continuation &&f),
        noexcept -> decltype(auto),
        then, task, same(f))

    memfn(
        auto await_resume(),
        noexcept -> decltype(auto),
        result, task)
};

template<
    operation Operation>
auto operator co_await(
    Operation &&operation)
noexcept -> awaitable_t<
    std::remove_reference_t<
        Operation>>
{
    return { same(operation) };
}

template<
    nothrow_operation Operation>
auto operator co_await(
    Operation &&operation)
noexcept -> nothrow_awaitable_t<
    std::remove_reference_t<
        Operation>>
{
    return { same(operation) };
}

}

#endif