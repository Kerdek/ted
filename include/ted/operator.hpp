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
    auto name(                          \
        Lhs &&lhs,                      \
        Rhs &&rhs)                      \
    -> decltype(same(lhs) op same(rhs)) \
{                                       \
    return same(lhs) op same(rhs);      \
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
infix_alias(less, <)
infix_alias(greater, >)
infix_alias(less_equal, <=)
infix_alias(greater_equal, >=)
infix_alias(not_equal, !=)

#undef infix_alias

#define prefix_alias(name, op)          \
template<                               \
    typename Operand>                   \
    auto name(                          \
        Operand &&operand)              \
    -> decltype(op same(operand))       \
{                                       \
    return op same(operand);            \
}                                       \

prefix_alias(plus, +)
prefix_alias(minus, -)
prefix_alias(deref, *)
prefix_alias(address, &)
prefix_alias(negate, !)
prefix_alias(bit_complement, ~)
prefix_alias(pre_increment, ++)
prefix_alias(pre_decrement, --)

#undef prefix_alias

template<
    typename Operand>
    auto increment(
        Operand &&operand)
    -> decltype(same(operand)++)
{
    return same(operand)++;
}

template<
    typename Operand>
    auto decrement(
        Operand &&operand)
    -> decltype(same(operand)--)
{
    return same(operand)--;
}

template<
    typename Self,
    typename Index>
    auto subscript(
        Self &&self,
        Index &&i)
    -> decltype(
        same(self)[
            same(i)])
{
    return same(self)[
        same(i)];
}

template<
    typename Self,
    typename ...Args>
    auto invoke(
        Self &&self,
        Args &&...args)
    -> decltype(
        same(self)(
            same(args)...))
{
    return same(self)(
        same(args)...);
}

}

#include <ted/nosame.hpp>

#endif