/*
              provider.hpp

         -- providing storage --

original (c) 2021 theodoric e. stier
public domain

some idioms for uninitialized memory.

*/

#ifndef H_0D4052DE_06A6_4A21_BA56_AD5FEA56B7CF
#define H_0D4052DE_06A6_4A21_BA56_AD5FEA56B7CF

#include <ted/ref.hpp>
#include <ted/uninitialized.hpp>

#include <new>

namespace ted
{

/**

Given `Provider p`, requires that
`dirty_contents(p)` be well-formed,
non-throwing, and return a pointer.

TODO: Check that the return is indeed
a pointer.

*/
template<
    typename Provider>
concept provides = requires (
    Provider p)
{
    { dirty_contents(p) } noexcept;
};

/**

Gets the contents of `provider`.
`provider` must be nonempty.

*/
template<
    provides Provider>
    constexpr auto naked_contents(
        Provider &self)
    noexcept -> decltype(auto)
{
    return ted::indirect(std::launder(
            ted::address_of(dirty_contents(self))));
}

/**

Gets the contents of `provider`. Unwraps
reference wrappers. `provider` must be
nonempty.

*/
template<
    provides Provider>
    constexpr auto contents(
        Provider &provider)
    noexcept -> decltype(auto)
{
    return obj(
        naked_contents(provider));
}

/**

Default-initializes the contents
of `provider`.
`provider` must be empty.

*/
template<
    provides Provider,
    typename ...Args>
    auto emplace_default_contents(
        Provider &provider,
        Args &&...x)
    -> decltype(auto)
{
    return emplace_default(
        naked_contents(provider));
}

/**

Direct-initializes the contents
of `provider` with `x...`.
`provider` must be empty.

*/
template<
    provides Provider,
    typename ...Args>
    auto emplace_contents(
        Provider &provider,
        Args &&...x)
    -> decltype(auto)
{
    return emplace(
        naked_contents(provider),
        same(x)...);
}

/**

Direct-list-initializes the contents
of `provider` with `x...`.
`provider` must be empty.

*/
template<
    provides Provider,
    typename ...Args>
    auto emplace_list_contents(
        Provider &provider,
        Args &&...x)
    -> decltype(auto)
{
    return emplace_list(
        naked_contents(provider),
        same(x)...);
}

/**

Destroys the contents of `provider`.
`provider` must be nonempty.

*/
template<
    provides Provider>
    auto destroy_contents(
        Provider &provider)
    noexcept -> void
{
    destroy(
        naked_contents(provider));
}

/**

Moves from `provider` into the result
object and destroys the contents.
`provider` must be nonempty.

*/
template<
    provides Provider>
    auto extract_contents(
        Provider &provider)
    noexcept -> decltype(auto)
{
    return obj(ted::move_destroy(
        naked_contents(provider)));
}

/**

The suggested implementations of the
`ted::provides` concept.

*/
template<
    typename Object>
    struct provider_t
{
    alignas(Object)
    unsigned char storage[
        sizeof(Object)];

    provider_t(
        const provider_t &)
    = delete;
    provider_t(
        provider_t &&)
    = delete;

    auto operator=(
        const provider_t &)
    = delete;
    auto operator=(
        provider_t &&)
    = delete;
};

/**

Gets an unlaundered reference to the
contents of `self`.

*/
template<
    typename Object>
    auto dirty_contents(
        provider_t<Object> &self)
    noexcept -> Object *
{
    return reinterpret_cast<
        Object *>(
        self.storage);
}

/**

Gets an unlaundered reference to the
contents of `self`.

*/
template<
    typename Object>
    auto dirty_contents(
        const provider_t<Object> &self)
    noexcept -> const Object *
{
    return reinterpret_cast<
        const Object *>(
        self.storage);
}

}

#endif