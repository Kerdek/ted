/*
                dumb.hpp

       -- pointer brainwashing --

original (c) 2021 theodoric e. stier
public domain

in order to handle smart pointers,
iterators, and dumb pointers generically,
we occasionally convert uniformly to
a dumb pointer. these are the default
implementations for those customization
points.

*/

#ifndef H_8B0BE2A5_D261_4AB8_AA1D_479DBE2D4F6C
#define H_8B0BE2A5_D261_4AB8_AA1D_479DBE2D4F6C

#include <ted/hyp.hpp>

#include <ted/same.hpp>

namespace ted
{

template<
    typename Self>
    auto dumb(
        Self *self)
    noexcept -> Self *
{
    return self;
}

template<
    typename Self>
    auto dumb(
        Self &&self)
    noexcept -> decltype(same(self).get())
{
    return same(self).get();
}

}

#include <ted/nosame.hpp>

#endif