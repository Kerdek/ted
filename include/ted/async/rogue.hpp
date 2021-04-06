/*
            async/rogue.hpp

       -- rogue async function --

original (c) 2021 theodoric e. stier
public domain

async function type which returns
nothing and has initial or final task

*/

#ifndef H_CF2485A8_2FE6_4873_B150_5A67F640FC23
#define H_CF2485A8_2FE6_4873_B150_5A67F640FC23

#include <ted/async/done_task.hpp>
#include <ted/async/noexcept_coro.hpp>
#include <ted/async/coroutine.hpp>

namespace ted::async
{

/**
A `coro` whose `sync_result` is `void`,
`initial_task` and `final_task` are
`done_task`, does not `co_return` a
value, and `std::terminate`s when
an exception is uncaught.
*/
struct rogue : noexcept_coro
{ };

constexpr auto sync_result(
    const rogue &)
noexcept -> coroutine<rogue>
{
    return { };
}

constexpr auto initial_operation(
    const rogue &)
noexcept -> done_task_t
{
    return done_task;
}

constexpr auto final_operation(
    const rogue &)
noexcept -> done_task_t
{
    return done_task;
}

constexpr auto handle_return(
    const rogue &)
noexcept -> void
{ }

}

#endif