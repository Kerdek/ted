/*
              exchange.hpp

     -- non-atomic doppelgangers --

original (c) 2021 theodoric e. stier
public domain

some algorithms need to work with
both atomic and non-atomic objects.

*/

#ifndef H_DF59A944_C040_4B86_B1A4_3546C94AC874
#define H_DF59A944_C040_4B86_B1A4_3546C94AC874

#include <ted/operator.hpp>

#include <utility>

namespace ted
{

/**
return the value of `x`.
*/
template<
    typename Object>
auto load(
    Object &&x)
noexcept -> auto
{
    return same(x);
}

/**
assign `x` with `y`.
return `x`.
*/
template<
    typename Object,
    typename Value>
auto store(
    Object &&x,
    Value &&y)
noexcept -> decltype(auto)
{
    return assign(
        same(x),
        same(y));
}

/**
assign `x` with `y`.
return the old value of `x`.

if `x` is an lvalue, the value is
copied.
if `x` is an rvalue, the value is moved.
*/
template<
    typename Object,
    typename Value>
auto exchange(
    Object &&x,
    Value &&y)
noexcept -> auto
{
    auto z =
        same(x);

    using ted::assign;
    assign(
        x, 
        same(y));

    return same(z);
}

}

#endif