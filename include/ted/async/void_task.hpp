/*
          async/void_task.hpp

        -- void trivial task --

original (c) 2021 theodoric e. stier
public domain

*/

#ifndef H_8C27B839_F202_45D9_AA7B_30A8505802D2
#define H_8C27B839_F202_45D9_AA7B_30A8505802D2

namespace ted::async
{

struct void_task_t { };

constexpr auto result(
    const void_task_t &)
noexcept -> void
{ }

}

#endif