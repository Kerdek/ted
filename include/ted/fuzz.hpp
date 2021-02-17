/*
                fuzz.hpp

       -- deterministic fuzzing --

original (c) 2021 theodoric e. stier
public domain
*/

#ifndef H_526586BE_63E0_455A_875D_B7EA34B8AA99
#define H_526586BE_63E0_455A_875D_B7EA34B8AA99

#include <ted/assuming.hpp>
#include <ted/operator.hpp>
#include <ted/same.hpp>
#include <ted/zero.hpp>

#include <type_traits>

namespace ted
{

template<
    typename F>
    auto repeat(
        F &&f)
    -> void
{
    static_assert(
        std::is_convertible_v<decltype(invoke(f)), bool>,
        "'invoke(f)' must be convertible to bool");

    while(invoke(f));
}

template<
    typename F,
    typename N>
    auto repeat_n_positive(
        F &&f,
        N n)
    -> void
{
    static_assert(
        std::is_void_v<decltype(invoke(f))>,
        "invoke(f) or f() must return void");

    assuming(is_nonzero(n))
    {
        auto g = [&]
        {
            invoke(f);
            decrement(n);
            return is_nonzero(n);
        };

        repeat(g);
    }
}

template<
    typename F,
    typename Size>
    auto repeat_n(
        F &&f,
        Size n)
    -> void
{
    if(is_nonzero(n))
    {
        repeat_n_positive(
            same(f), 
            same(n));
    }
}

template<
    typename FuzzCase,
    typename NoiseSource>
    auto fuzz(
        FuzzCase &&f,
        NoiseSource &&g)
    -> decltype(auto)
{
    return invoke(
        same(f),
        invoke(same(g)));
}

template<
    typename FuzzCase,
    typename NoiseSource,
    typename Size>
    auto fuzz_n(
        FuzzCase &&f,
        NoiseSource &&g,
        Size n)
    -> void
{
    auto h = [&]
    {
        fuzz(f, g); 
    };

    repeat_n(
        h,
        n);
}

}

#endif