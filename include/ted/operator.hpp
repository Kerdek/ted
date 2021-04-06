/*
             operator.hpp

        -- operator aliases --

original (c) 2021 theodoric e. stier
public domain

as a policy, we avoid monopolizing any
language feature other than a normal
function name as a customization point.
therefore, when an operation should be
customizable, we prefer to use one of
the below names. this file provides a
default implementation in terms of the
usual operator, and with the strongest
possible constraint.

significantly, this extends to function
objects. we do not invoke them directly,
but via an unqualified call to 'invoke'
with the below default.

*/

#ifndef H_268332FF_D181_42BC_A1A3_96F74BAC6571
#define H_268332FF_D181_42BC_A1A3_96F74BAC6571

#include <ted/same.hpp>

namespace ted
{

#define infix_alias(name, op)           \
template<                               \
    typename Lhs,                       \
    typename Rhs>                       \
constexpr auto name(                    \
    Lhs &&a,                          \
    Rhs &&b)                          \
-> decltype(same(a) op same(b))     \
{                                       \
    return same(a) op same(b);      \
}                                       \

infix_alias(assign, =)
infix_alias(plus_assign, +=)
infix_alias(minus_assign, -=)
infix_alias(times_assign, *=)
infix_alias(divide_assign, /=)
infix_alias(modulo_assign, %=)
infix_alias(bit_and_assign, &=)
infix_alias(bit_or_assign, |=)
infix_alias(bit_xor_assign, ^=)
infix_alias(left_shift_assign, <<=)
infix_alias(right_shift_assign, >>=)
infix_alias(plus, +)
infix_alias(minus, -)
infix_alias(times, *)
infix_alias(divide, /)
infix_alias(separator, /)
infix_alias(modulo, %)
infix_alias(bit_and, &)
infix_alias(bit_or, |)
infix_alias(bit_xor, ^)
infix_alias(right_shift, >>)
infix_alias(extract, >>)
infix_alias(left_shift, <<)
infix_alias(insert, <<)
infix_alias(equal, ==)
infix_alias(unequal, !=)
infix_alias(less, <)
infix_alias(greater, >)
infix_alias(less_equal, <=)
infix_alias(greater_equal, >=)

#undef infix_alias

#define prefix_alias(name, op)         \
template<                              \
    typename Object>                   \
constexpr auto name(                   \
    Object &&x)                   \
-> decltype(                           \
    op same(x))                   \
{                                      \
    return op same(x);            \
}                                      \

prefix_alias(plus, +)
prefix_alias(minus, -)
prefix_alias(follow, *)
prefix_alias(address, &)
prefix_alias(negate, !)
prefix_alias(bit_complement, ~)
prefix_alias(pre_increment, ++)
prefix_alias(pre_decrement, --)

#undef prefix_alias

/**
Post-increment `object`.
*/
template<
    typename Object>
constexpr auto increment(
    Object &&x)
-> decltype(
    same(x)++)
{
    return same(x)++;
}

/**
Post-decrement `object`.
*/
template<
    typename Object>
constexpr auto decrement(
    Object &&x)
-> decltype(
    same(x)--)
{
    return same(x)--;
}

/**
Subscript `object` with `index`.
*/
template<
    typename Object,
    typename Index>
constexpr auto subscript(
    Object &&x,
    Index &&i)
-> decltype(
    same(x)[
        same(i)])
{
    return same(x)[
        same(i)];
}

/**
Invoke `object` with `args`.
*/
template<
    typename Function,
    typename ...Args>
constexpr auto invoke(
    Function &&f,
    Args &&...x)
-> decltype(
    same(f)(
        same(x)...))
{
    return same(f)(
        same(x)...);
}

/**
Default-initialize an `Object` at
`address`.
*/
template<
    typename Object>
constexpr auto non_allocating_new_default(
    Object *p)
-> Object *
{
    return new (p) Object;
}

/**
Direct-initialize an `Object` at
`address`.
*/
template<
    typename Object,
    typename ...Args>
    constexpr auto non_allocating_new(
        Object *p,
        Args &&...x)
    -> Object *
{
    return new (p) Object(
        same(x)...);
}

/**
Direct-list-initialize an `Object` at
`address`.
*/
template<
    typename Object,
    typename ...Args>
    constexpr auto non_allocating_new_list(
        Object *p,
        Args &&...x)
    -> Object *
{
    return new (p) Object{
        same(x)... };
}

/**
Destroy `object`.
*/
template<
    typename Object>
    constexpr auto destroy(
        Object &x)
    noexcept -> void
{
    x.~Object();
}

}

#endif