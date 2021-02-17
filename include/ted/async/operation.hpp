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

#include <coroutine>

namespace ted::async
{

template<
    typename Resume,
    typename Operation>
concept operation = requires (
    Operation self,
    Resume r)
{
    static_cast<bool>(done(self));
    then(self, r);
    result(same(self));
};

template<
    typename Resume,
    operation<Resume> Task>
struct awaitable_t
{
    Task task;

    auto await_ready()
    & -> decltype(auto)
    {
        return done(
            obj(task));
    }

    auto await_ready()
    && -> decltype(auto)
    {
        return done(
            obj(same(task)));
    }

    auto await_ready()
    const & -> decltype(auto)
    {
        return done(
            obj(task));
    }

    auto await_ready()
    const && -> decltype(auto)
    {
        return done(
            obj(same_const(task)));
    }

    auto await_suspend(
        Resume &&resume)
    & -> decltype(auto)
    {
        return then(
            obj(task),
            same(resume));
    }

    auto await_suspend(
        Resume &&resume)
    && -> decltype(auto)
    {
        return then(
            obj(same(task)),
            same(resume));
    }

    auto await_suspend(
        Resume &&resume)
    const & -> decltype(auto)
    {
        return then(
            obj(task),
            same(resume));
    }

    auto await_suspend(
        Resume &&resume)
    const && -> decltype(auto)
    {
        return then(
            obj(same_const(task)),
            same(resume));
    }

    auto await_resume()
    & -> decltype(auto)
    {
        return result(
            obj(task));
    }

    auto await_resume()
    && -> decltype(auto)
    {
        return result(
            obj(same(task)));
    }
    auto await_resume()
    const & -> decltype(auto)
    {
        return result(
            obj(task));
    }
    auto await_resume()
    const && -> decltype(auto)
    {
        return result(
            obj(same_const(task)));
    }
};

template<
    typename Resume,
    operation<Resume> Operation>
    auto operator co_await(
        Operation &&operation)
    noexcept -> awaitable_t<
        Resume,
        std::remove_reference_t<
            Operation>>
{
    return { same(operation) };
}

}

#endif