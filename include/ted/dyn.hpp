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
#include <ted/hyp.hpp>
#include <ted/iterator.hpp>
#include <ted/pointer.hpp>
#include <ted/ref.hpp>
#include <ted/same.hpp>

#include <memory>
#include <type_traits>


namespace ted::erasure
{

template<
    typename F>
    struct abstract_t;

template<
    typename Y,
    typename ...X>
    struct abstract_t<
        Y(X...)>
{
    virtual ~abstract_t()
    = default;

    virtual auto invoke_dyn(
        X &&...)
    & -> Y = 0;
    virtual auto invoke_dyn(
        X &&...)
    && -> Y = 0;
    virtual auto invoke_dyn(
        X &&...)
    const & -> Y = 0;
    virtual auto invoke_dyn(
        X &&...)
    const && -> Y = 0;
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
    typename F,
    typename Invocable>
    struct concrete_t;

template<
    typename Y,
    typename ...X,
    typename InvocableObject>
    struct concrete_t<
        Y(X...),
        InvocableObject> :
        abstract_t<Y(X...)>
{
    static_assert(
        !std::is_reference_v<InvocableObject>,
        "invocable type must be an\
        object type.");

    InvocableObject f;

    concrete_t(InvocableObject f) noexcept :
        f(same(f))
    { }

    auto invoke_dyn(
        X &&...x)
    & -> Y
    override
    {
        return invoke(
            obj(f),
            same(x)...);
    }

    auto invoke_dyn(
        X &&...x)
    && -> Y
    override
    {
        return invoke(
            obj(same(f)),
            same(x)...);
    }

    auto invoke_dyn(
        X &&...x)
    const & -> Y
    override
    {
        return invoke(
            obj(f),
            same(x)...);
    }

    auto invoke_dyn(
        X &&...x)
    const && -> Y
    override
    {
        return invoke(
            obj(same_const(f)),
            same(x)...);
    }
};

template<
    typename Invocable>
using erasure_t =
    std::unique_ptr<
        abstract_t<Invocable>>;

template<
    typename Erasure>
    auto abstract(
        Erasure &&f)
    noexcept -> decltype(auto)
{
    return categorize_like<Erasure>(
        ted::peek(same(f)));
}

template<
    typename Erasure,
    typename ...Args>
    auto invoke(
        Erasure &&f,
        Args &&...x)
    -> decltype(auto)
{
    return invoke_dyn(
        abstract(same(f)),
        same(x)...);
}

}

namespace ted
{

template<
    typename Signature,
    typename Invocable>
    auto dyn(
        Invocable &&f)
    -> erasure::erasure_t<
        Signature>
{
    using InvocableObject =
        std::remove_reference_t<
            Invocable>;
    using Concrete = 
        erasure::concrete_t<
            Signature,
            InvocableObject>;

    return std::make_unique<Concrete>(
        same(f));
}

}

#endif