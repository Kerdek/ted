/*
                dyn.hpp

         -- erased functions --

original (c) 2021 theodoric e. stier
public domain

std::function but without some fluff 
trimmed and done up to work with the
customization practices use throughout
the rest of libted. not callable with
'operator()', just with 'invoke'.

*/

#ifndef H_88B7B750_A12C_4B1B_AD4A_DB4DDD39F14B
#define H_88B7B750_A12C_4B1B_AD4A_DB4DDD39F14B

#include <ted/category.hpp>
#include <ted/pointer.hpp>
#include <ted/ref.hpp>
#include <ted/same.hpp>
#include <ted/memfn.hpp>

#include <memory>
#include <type_traits>


namespace ted
{

template<
    typename Function>
struct abstract_function;

template<
    typename Y,
    typename ...X>
struct abstract_function<
    Y(X...)>
{
    virtual ~abstract_function()
    = default;

    memfnd(
        virtual auto invoke_dyn(X &&...),
        -> Y = 0)
};

template<
    typename Abstract,
    typename ...Args>
auto invoke_dyn(
    Abstract &&self,
    Args &&...x)
-> decltype(auto)
{
    return same(self).invoke_dyn(
        same(x)...);
}

template<
    typename Function,
    typename Invocable>
struct concrete_function;

template<
    typename Y,
    typename ...X,
    typename Invocable>
struct concrete_function<
    Y(X...),
    Invocable> :
    abstract_function<
        Y(X...)>
{
    Invocable f;

    concrete_function(
        Invocable f) :
        f(same(f))
    { }

    memfn(
        auto invoke_dyn(X &&...x),
        -> Y override,
        invoke, f, same(x)...)
};

template<
    typename Erasure,
    typename ...Args>
auto invoke(
    Erasure &&f,
    Args &&...x)
-> decltype(auto)
{
    return invoke_dyn(
        ted::categorize_like<Erasure>(
            ted::peek(same(f))),
        same(x)...);
}

template<
    typename Signature,
    typename Invocable>
auto dyn(
    Invocable &&f)
-> decltype(auto)
{
    return std::make_unique<
        concrete_function<
            Signature,
            std::remove_reference_t<
                Invocable>>>(
        same(f));
}

}

#endif