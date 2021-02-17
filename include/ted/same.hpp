/*
                same.hpp

            -- same macro --

original (c) 2021 theodoric e. stier
public domain

a feverishly employed shorthand for 
'std::forward'

*/

#ifndef H_45464788_8B72_423F_AA8F_02400AD674ED
#define H_45464788_8B72_423F_AA8F_02400AD674ED

#define same(x) static_cast<decltype(x) &&>(x)
#define same_const(x) static_cast<const decltype(x) &&>(x)

#endif