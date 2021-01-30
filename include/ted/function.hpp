/*
              function.hpp
   
original (c) 2021 theodoric e. stier
public domain

std::function but with some fluff 
trimmed and done up to work with the
customization practices use throughout
the rest of libted

*/

#ifndef H_88B7B750_A12C_4B1B_AD4A_DB4DDD39F14B
#define H_88B7B750_A12C_4B1B_AD4A_DB4DDD39F14B

#include <ted/address.hpp>
#include <ted/hyp.hpp>
#include <ted/ref.hpp>
#include <ted/similar_category.hpp>

#include <memory>

#include <ted/same.hpp>

namespace ted::function
{

template<
    typename F>
    struct basic_control_block_t;
    
template<
    typename R,
    typename ...A>
    struct basic_control_block_t<
        R(A...)>
{
    virtual ~basic_control_block_t() =
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
    typename F,
    typename G>
    struct control_block_t;

template<
    typename R,
    typename ...A,
    typename G>
    struct control_block_t<
        R(A...),
        G> :
        basic_control_block_t<R(A...)>
{
    G g;

    control_block_t(G g) noexcept :
        g(same(g))
    { }

    auto dyn_invoke(
        A &&...args)
    & -> decltype(
        invoke(
            obj(g),
            same(args)...))
    override
    {
        return invoke(
            obj(g),
            same(args)...);
    }

    auto dyn_invoke(
        A &&...args)
    && -> decltype(
        invoke(
            obj(same(g)),
            same(args)...))
    override
    {
        return invoke(
            obj(same(g)),
            same(args)...);
    }

    auto dyn_invoke(
        A &&...args)
    const & -> decltype(
        invoke(
            obj(g),
            same(args)...))
    override
    {
        return invoke(
            obj(g),
            same(args)...);
    }

    auto dyn_invoke(
        A &&...args)
    const && -> decltype(
        invoke(
            obj(same(g)),
            same(args)...))
    override
    {
        return invoke(
            obj(same(g)),
            same(args)...);
    }
};

template<
    typename Self,
    typename ...Args>
    auto dyn_invoke(
        Self &&self,
        Args &&...args)
    -> decltype(
        same(self).dyn_invoke(
            same(args)...))
{
    return same(self).dyn_invoke(
        same(args)...);
}

template<
    typename F>
    struct function_t
{
    using basic_block_t =
        basic_control_block_t<F>;
    template<
        typename G>
    using block_t = 
        control_block_t<F, G>;
    using smart_ptr_t = std::unique_ptr<
        basic_block_t>;

    template<
        typename G>
        function_t(
            G &&g) :
        control_block(
            make_unique<block_t<G>>(
                same(g)))
    { }

    smart_ptr_t control_block;
};

template<
    typename Function>
    auto control_block(
        Function &&self)
    noexcept -> decltype(auto)
{
    return similar<Function>(
        obj(same(self).control_block));
}

template<
    typename Self,
    typename ...Args>
    auto invoke(
        Self &&self,
        Args &&...args)
    -> decltype(invoke_control_block(
        control_block(same(self)),
        same(args)...))
{
    return invoke_control_block(
        control_block(same(self)),
        same(args)...);
}

}

namespace ted
{

template<
    typename F,
    typename G>
    auto make_function(
        G &&g)
    -> function::function_t<F>
{
    using block_t =
        function::control_block_t<F, G>;
        
    return 
    {
        std::make_unique<block_t>(
            same(g))
    };
}

}

#include <ted/nosame.hpp>

#endif