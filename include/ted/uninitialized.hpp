/*
            uninitialized.hpp

        -- uninitialized memory --

original (c) 2021 theodoric e. stier
public domain

since we never directly use `new` in
libted, the non-allocating forms would
be pretty ugly too.

*/

#ifndef H_2E81082C_A1C5_4E15_909A_D5879888AAB7
#define H_2E81082C_A1C5_4E15_909A_D5879888AAB7

#include <ted/operator.hpp>
#include <ted/pointer.hpp>

namespace ted
{

/**

default-initialize `object` in
uninitialized storage.

*/
template<
    typename Object>
    auto initialize_default(
        Object &object)
    -> Object &
{
    return ted::indirect(
        non_allocating_new_default(
            ted::address_of(object)));
}

/**

direct-initialize `object` in
uninitialized storage with `args`

*/
template<
    typename Object,
    typename ...Args>
    auto initialize(
        Object &object,
        Args &&...args)
    -> Object &
{
    return ted::indirect(
        non_allocating_new(
            ted::address_of(object),
            same(args)...));
}

/**

list-initialize `object` in
uninitialized storage with `args`.

*/
template<
    typename Object,
    typename ...Args>
    auto initialize_list(
        Object &object,
        Args &&...args)
    -> Object &
{
    return ted::indirect(
        non_allocating_new_list(
            ted::address_of(object), 
            same(args)...));
}

/**

move from `object` into the result, 
then destroy `object`.

*/
template<
    typename Object>
    auto move_destroy(
        Object &object)
    noexcept -> Object
{
    auto value = std::move(object);
    destroy(object);
    return value;
}

}

#endif