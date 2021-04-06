/*
               category.hpp

       -- value category cloning --

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
    typename Source,
    typename Object>
    struct similar_category
{
    using type =
        std::remove_reference_t<
            Object> &&;
};

template<
    typename Source,
    typename Object>
    struct similar_category<
        Source &,
        Object>
{
    using type =
        Object &;
};

template<
    typename Source,
    typename Object>
using similar_category_t =
    typename similar_category<
        Source,
        Object>::type;

template<
    typename Source,
    typename Object>
    auto categorize_like(
        Object &&self)
    noexcept -> decltype(auto)
{
    using Destination =
        similar_category_t<
            Source,
            Object>;

    return static_cast<Destination>(
        self);
}

}

#endif