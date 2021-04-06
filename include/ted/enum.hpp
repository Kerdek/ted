/*
                enum.hpp

		  -- underlying type --

original (c) 2021 theodoric e. stier
public domain

*/

#ifndef H_AE55A568_1CFB_4F4D_A36F_370D5F2D356A
#define H_AE55A568_1CFB_4F4D_A36F_370D5F2D356A

#include <type_traits>

namespace ted
{

using std::underlying_type_t;

template<
    typename K>
constexpr
auto from_enum(
    K k)
noexcept
-> underlying_type_t<K>
{
    return static_cast<
        underlying_type_t<K>>(
        k);
}

template<
    typename K>
constexpr
auto to_enum(
    underlying_type_t<K> x)
noexcept
-> K
{
    return static_cast<
        K>(
        x);
}

}

#endif