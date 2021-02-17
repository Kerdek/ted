#include <ted/async/coroutine.hpp>
#include <ted/async/done_task.hpp>
#include <ted/async/pending_task.hpp>
#include <ted/async/operation.hpp>
#include <ted/async/rogue.hpp>
#include <ted/ref.hpp>
#include <ted/operator.hpp>

#include <doctest/doctest.h>

#include <coroutine>

using namespace ted;
using namespace ted::async;

template<
    typename T>
    struct my_task_0 : 
        done_task_t
{
    T x;
};

template<
    typename T>
constexpr auto result(
    my_task_0<T> t)
    noexcept -> T
{
    return t.x;
}

TEST_CASE("")
{
    using X = long;
    using F = my_task_0<X>;

    X x = 0x13'89'0e'3d'cd'26'73'26;
    F f{ .x = x };

    [x, f]() -> coroutine<rogue>
    {
        CHECK(equal(x, co_await f));
    }();
}

// template<
//     typename Resumer>
//     struct my_task_1 : 
//         pending_task_t
// {
//     Resumer r;
// };

// template<
//     typename Resumer>
// constexpr auto wait(
//     my_task_1<Resumer> &t,
//     Resumer r)
//     noexcept -> void
// {
//     t.r = r;
// }

// TEST_CASE("")
// {
//     using R = std::coroutine_handle<promise<rogue>>;
//     using F = pending_task_t;

//     F f;

//     [&f]() -> coroutine<rogue>
//     {
//         co_await ref(f);
//         CHECK(true);
//     }();
//     f.r();
// }