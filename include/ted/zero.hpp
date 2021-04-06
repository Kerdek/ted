/*
                zero.hpp

               -- zero --

original (c) 2021 theodoric e. stier
public domain

zero checks should customize.
don't just contextually convert things
to 'bool'!

*/

#ifndef H_EE342C3A_EB55_4B80_9A92_EE1B75243901
#define H_EE342C3A_EB55_4B80_9A92_EE1B75243901

#include <ted/operator.hpp>

namespace ted
{

template<
    typename T>
auto is_zero(
    T &&x)
-> decltype(auto)
{
    return equal(
        same(x),
        0);
}

template<
    typename T>
auto is_nonzero(
    T &&x)
-> decltype(auto)
{
    return unequal(
        same(x),
        0);
}

template<
    typename T>
auto is_positive(
    T &&x)
-> decltype(auto)
{
    return greater(
        same(x),
        0);
}

template<
    typename T>
auto is_negative(
    T &&x)
-> decltype(auto)
{
    return less(
        same(x),
        0);
}

template<
    typename T>
auto is_nonpositive(
    T &&x)
-> decltype(auto)
{
    return less_equal(
        same(x),
        0);
}

template<
    typename T>
auto is_nonnegative(
    T &&x)
-> decltype(auto)
{
    return greater_equal(
        same(x),
        0);
}

}

#endif