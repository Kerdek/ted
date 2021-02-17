/*
            pending_task.hpp

      -- pending trivial task --

original (c) 2021 theodoric e. stier
public domain

*/

#ifndef H_8F0490A4_7BF6_4F9F_8586_66B7FA2C3A93
#define H_8F0490A4_7BF6_4F9F_8586_66B7FA2C3A93

#include <ted/async/void_task.hpp>

namespace ted::async
{

struct pending_task_t :
    void_task_t
{ };

constexpr auto done(
    pending_task_t) 
noexcept -> bool
{
    return false;
}

}

#endif