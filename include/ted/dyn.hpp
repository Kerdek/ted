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

#include <ted/address_of.hpp>
#include <ted/hyp.hpp>
#include <ted/ref.hpp>
#include <ted/similar_category.hpp>

#include <memory>
#include <type_traits>

#include <ted/same.hpp>

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
    virtual ~abstract_t() =
        default;
    
    virtual auto dyn_invoke(
        X &&...)
    & -> Y = 0;
    virtual auto dyn_invoke(
        X &&...)
    && -> Y = 0;
    virtual auto dyn_invoke(
        X &&...)
    const & -> Y = 0;
    virtual auto dyn_invoke(
        X &&...)
    const && -> Y = 0;
};

template<
    typename F,
    typename ...X>
    auto dyn_invoke(
        F &&f,
        X &&...x)
    -> decltype(
        same(f).dyn_invoke(
            same(x)...))
{
    return same(f).dyn_invoke(
        same(x)...);
}

template<
    typename F,
    typename G>
    struct concrete_t;

template<
    typename Y,
    typename ...X,
    typename G>
    struct concrete_t<Y(X...), G> :
        abstract_t<Y(X...)>
{
    static_assert(
        !std::is_reference_v<G>,
        "concrete function object type may not be a reference.");
    
    using Z1 = decltype(
        invoke(
            obj(hyp<G &>()),
            hyp<X>()...));
    using Z2 = decltype(
        invoke(
            obj(hyp<G &&>()),
            hyp<X>()...));
    using Z3 = decltype(
        invoke(
            obj(hyp<const G &>()),
            hyp<X>()...));
    using Z4 = decltype(
        invoke(
            obj(hyp<const G &&>()),
            hyp<X>()...));

    static constexpr bool P1 = 
        std::is_convertible_v<Y, Z1>;
    static constexpr bool P2 = 
        std::is_convertible_v<Y, Z2>;
    static constexpr bool P3 = 
        std::is_convertible_v<Y, Z3>;
    static constexpr bool P4 = 
        std::is_convertible_v<Y, Z4>;

    G g;

    concrete_t(G g) noexcept :
        g(same(g))
    { }

    auto dyn_invoke(
        X &&...x)
    & -> std::enable_if_t<P1, Y>
    override
    {
        return invoke(
            obj(g),
            same(x)...);
    }

    auto dyn_invoke(
        X &&...x)
    && -> std::enable_if_t<P2, Y>
    override
    {
        return invoke(
            obj(same((g))),
            same(x)...);
    }

    auto dyn_invoke(
        X &&...x)
    const & -> std::enable_if_t<P3, Y>
    override
    {
        return invoke(
            obj(g),
            same(x)...);
    }

    auto dyn_invoke(
        X &&...x)
    const && -> std::enable_if_t<P4, Y>
    override
    {
        return invoke(
            obj(same((g))),
            same(x)...);
    }
};

template<
    typename F>
using erasure_t =
    std::unique_ptr<abstract_t<F>>;

template<
    typename F>
    auto abstract(
        F &&f)
    noexcept -> decltype(auto)
{
    return categorized_like<F>(
        obj_at(same(f)));
}

template<
    typename F,
    typename ...X>
    auto invoke(
        F &&f,
        X &&...x)
    -> decltype(auto)
{
    return dyn_invoke(
        abstract(same(f)),
        same(x)...);
}

}

namespace ted
{

template<
    typename F,
    typename G>
    auto dyn(
        G &&g)
    -> erasure::erasure_t<F>
{
    using G1 =
        std::remove_reference_t<G>;
    using G2 = 
        erasure::concrete_t<F, G1>;

    return std::make_unique<G2>(
        same(g));
}

}

#include <ted/nosame.hpp>

#endif