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

#include <ted/hyp.hpp>
#include <ted/ref.hpp>
#include <ted/same.hpp>
#include <ted/memfn.hpp>

#include <type_traits>

namespace ted
{

template<
    typename Result,
    typename ...Args>
struct abstract_function
{
    virtual ~abstract_function()
    = default;

    memfnd(
        virtual auto invoke_dyn(
            Args &&...),
        -> Result = 0)
};

template<
    typename Invocable,
    typename ...Args>
struct concrete_function :
    abstract_function<
        decltype(invoke(
            obj(hyp(Invocable)),
            hyp(Args)...)),
        Args...>
{
    Invocable f;

    concrete_function(
        Invocable f) :
        f(same(f))
    { }

    memfn(
        auto invoke_dyn(Args &&...x),
        -> decltype(invoke(
            obj(f),
            same(x)...)) override,
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
    return same(f).invoke_dyn(
        same(x)...);
}

template<
    typename ...Args,
    typename Invocable>
auto dyn(
    Invocable &&f)
-> concrete_function<
    std::remove_reference_t<
        Invocable>,
    Args...>
{
    return { same(f) };
}

}

#endif