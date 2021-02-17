#ifndef H_DF59A944_C040_4B86_B1A4_3546C94AC874
#define H_DF59A944_C040_4B86_B1A4_3546C94AC874

#include <ted/operator.hpp>

#include <utility>

namespace ted
{

template<
    typename Object,
    typename Value>
    auto load(
        Object &&object)
    noexcept -> decltype(auto)
{
    return same(object);
}

template<
    typename Object,
    typename Value>
    auto store(
        Object &&object,
        Value &&value)
    noexcept -> decltype(auto)
{
    return assign(
        same(object),
        same(value));
}

template<
    typename Object,
    typename Value>
    auto exchange(
        Object &&object,
        Value &&value)
    noexcept -> decltype(auto)
{
    auto result = std::move(object);

    assign(
        object, 
        same(value));

    return same(result);
}

}

#endif