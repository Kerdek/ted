/*
              function.hpp

         -- erased functions --

original (c) 2021 theodoric e. stier
public domain

std::function but without some fluff 
trimmed and done up to work with the
customization practices use throughout
the rest of libted

*/

#ifndef H_88B7B750_A12C_4B1B_AD4A_DB4DDD39F14B
#define H_88B7B750_A12C_4B1B_AD4A_DB4DDD39F14B

#include <ted/address_of.hpp>
#include <ted/hyp.hpp>
#include <ted/ref.hpp>
#include <ted/similar_category.hpp>

#include <memory>

#include <ted/same.hpp>
#include <type_traits>

namespace ted::function
{

template<
    typename F>
    struct abstract_t;

template<
    typename R,
    typename ...A>
    struct abstract_t<
        R(A...)>
{
    virtual ~abstract_t() =
        default;
    
    virtual auto dyn_invoke(
        A &&...args)
    & -> R = 0;
    virtual auto dyn_invoke(
        A &&...args)
    && -> R = 0;
    virtual auto dyn_invoke(
        A &&...args)
    const & -> R = 0;
    virtual auto dyn_invoke(
        A &&...args)
    const && -> R = 0;
};

template<
    typename AbstractFunction,
    typename ...Args>
    auto dyn_invoke(
        AbstractFunction &&self,
        Args &&...args)
    -> decltype(
        same(self).dyn_invoke(
            same(args)...))
{
    return same(self).dyn_invoke(
        same(args)...);
}

template<
    typename F,
    typename G>
    struct concrete_t;

template<
    typename R,
    typename ...A,
    typename G>
    struct concrete_t<R(A...), G> :
        abstract_t<R(A...)>
{
    static_assert(
        !std::is_reference_v<G>,
        "erased function object type may not be a reference.");
    
    static_assert(
        std::is_convertible_v<R, decltype(invoke(obj(hyp<G &>()), hyp<A>()...))> &&
        std::is_convertible_v<R, decltype(invoke(obj(hyp<G &&>()), hyp<A>()...))> &&
        std::is_convertible_v<R, decltype(invoke(obj(hyp<const G &>()), hyp<A>()...))> &&
        std::is_convertible_v<R, decltype(invoke(obj(hyp<const G &&>()), hyp<A>()...))>,
        "erased function object return type must be convertible to erasure return type.");

    G g;

    concrete_t(G g) noexcept :
        g(same(g))
    { }

    auto dyn_invoke(
        A &&...args)
    & -> R override
    {
        return invoke(
            obj(g),
            same(args)...);
    }

    auto dyn_invoke(
        A &&...args)
    && -> R override
    {
        return invoke(
            obj(same((g))),
            same(args)...);
    }

    auto dyn_invoke(
        A &&...args)
    const & -> R override
    {
        return invoke(
            obj(g),
            same(args)...);
    }

    auto dyn_invoke(
        A &&...args)
    const && -> R override
    {
        return invoke(
            obj(same((g))),
            same(args)...);
    }
};

template<
    typename ErasedFunction>
    auto control_block(
        ErasedFunction &&self)
    noexcept -> decltype(auto)
{
    return categorized_like<ErasedFunction>(
        obj_at(same(self)));
}

template<
    typename ErasedFunction,
    typename ...Args>
    auto invoke(
        ErasedFunction &&self,
        Args &&...args)
    -> decltype(auto)
{
    return dyn_invoke(
        control_block(same(self)),
        same(args)...);
}

}

namespace ted
{

template<
    typename F,
    typename G>
    auto erase_function(
        G &&g)
    -> std::unique_ptr<function::abstract_t<F>>
{
    using value_G =
        std::remove_reference_t<G>;
    using concrete_t = 
        function::concrete_t<F, value_G>;

    return std::make_unique<concrete_t>(
        same(g));
}

}

#include <ted/nosame.hpp>

#endif