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

#include <algorithm>

namespace ted
{    

template<
    typename Range,
    typename Value>
auto find(
    Range &&range,
    Value &&value)
-> bool
{
    using std::find;

    return find(
        begin(range),
        end(range),
        value);
}

template<
    typename Range,
    typename Value>
auto contains(
    Range &&range,
    Value &&value)
-> bool
{
    return end(range) == find(
        range,
        value);
}

}

#endif