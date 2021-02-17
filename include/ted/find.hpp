/*
                find.hpp

         -- find & contains --

original (c) 2021 theodoric e. stier
public domain

in order to handle smart pointers,
iterators, and dumb pointers generically,
we occasionally convert uniformly to
a dumb pointer. these are the default
implementations for those customization
points.

*/

#ifndef H_F92F023D_95D7_43BC_9A83_FC66880F2AB4
#define H_F92F023D_95D7_43BC_9A83_FC66880F2AB4

#include <ted/operator.hpp>

#include <algorithm>

namespace ted
{

template<
    typename Range,
    typename Value>
auto find(
    Range &&self,
    Value &&x)
-> auto
{
    using std::find;

    return find(
        begin(self),
        end(self),
        same(x));
}

template<
    typename Range,
    typename Value>
auto contains(
    Range &&self,
    Value &&x)
-> bool
{
    return equal(
        end(same(self)),
        find(
            self,
            same(x)));
}

}

#endif