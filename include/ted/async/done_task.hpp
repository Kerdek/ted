/*
              done_task.hpp

        -- done trivial task --

original (c) 2021 theodoric e. stier
public domain

*/

#ifndef H_1B4A3C5E_DA6F_423A_A001_D7DA280CF649
#define H_1B4A3C5E_DA6F_423A_A001_D7DA280CF649

#include <ted/async/void_task.hpp>

namespace ted::async
{

struct done_task_t :
    void_task_t
{ };

constexpr auto done(
    const done_task_t &)
noexcept -> bool
{
    return true;
}

template<
    typename Resumer>
constexpr auto then(
    const done_task_t &,
    Resumer &&)
noexcept -> void
{ }

constexpr done_task_t done_task;

}

#endif