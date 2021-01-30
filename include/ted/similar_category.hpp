/*
          similar_category.hpp

       -- value category lifting --

original (c) 2021 theodoric e. stier
public domain

it is occasionally necessary to to form
a similarly categorized reference type

*/

#ifndef H_52960820_8B44_4427_A855_382E04C8E78C
#define H_52960820_8B44_4427_A855_382E04C8E78C

#include <type_traits>

namespace ted
{

template<
    typename T,
    typename U>
    struct similar_category
{
    using type =
        std::remove_reference_t<U> &&;
};

template<
    typename T,
    typename U>
    struct similar_category<T &, U>
{
    using type =
        std::remove_reference_t<U> &;
};

template<
    typename T,
    typename U>
using similar_category_t =
    typename similar_category<T, U>::type;

template<
    typename T,
    typename U>
    auto categorized_like(
        U &&x)
    noexcept -> decltype(
        static_cast<similar_category_t<T, U>>(x))
{
    return static_cast<similar_category_t<T, U>>(x);
}

}

#endif