#ifndef H_B604BCC2_011A_435D_8DA1_D63710FAD37E
#define H_B604BCC2_011A_435D_8DA1_D63710FAD37E

#include <ted/same.hpp>
#include <ted/ref.hpp>

#define memfnd(pre, suf) \
    pre & suf;\
    pre && suf;\
    pre const & suf;\
    pre const && suf;

#define memfn(pre, suf, op, member, ...) \
    pre & suf { return op(obj(member) __VA_OPT__(,) __VA_ARGS__); }\
    pre && suf { return op(obj(same(member)) __VA_OPT__(,) __VA_ARGS__); }\
    pre const & suf { return op(obj(member) __VA_OPT__(,) __VA_ARGS__); }\
    pre const && suf { return op(obj(same_const(member)) __VA_OPT__(,) __VA_ARGS__); }

#define $comma ,

#endif