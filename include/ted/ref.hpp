/* 
               ref_obj.hpp
               
        -- reference wrappers --
   
original (c) 2021 theodoric e. stier
public domain

unfortunate events in the vintage of
c++ render the necessity of a 
separate non-pointer facility for
expressing reference semantics in 
contexts where lvalue-ness does not 
map onto the problem.
call 'ref' with a 'E' to get
a 'ref_obj<T>' around the operand.
for lvalue operands, T = E &
for rvalue operands, T = E &&
call 'obj' with a 'ref_obj<T>'
to refer to the object. the value
category is conserved.
for generic contexts, 'obj' defaults
to the value identity function.
this is important for decoupling a 
couple of important pieces of
information about how the user wants
our lib to store and use things:

1) should we store a value or a 
   reference?
2) should we initialize with lvalue
   or rvalue?

boost.asio fucks this up by not 
letting us copy to a handler stored
by value or explain that a handler
should be stored by reference and
optionally moved from when invoked.

*/

#ifndef H_C18F11C6_324A_42F5_925B_C0B3AE1A7BA0
#define H_C18F11C6_324A_42F5_925B_C0B3AE1A7BA0

#include <ted/address.hpp>

#include <type_traits>

#include <ted/assuming.hpp>

namespace ted
{

template<
    typename T>
    struct ref_obj
{
    std::remove_reference_t<T> *x;
};

template<
    typename T>
    auto obj(
        T x)
    noexcept -> T
{
    return same(x);
}

template<
    typename T>
    auto obj(
        ref_obj<T> r)
    noexcept -> T
{
    assuming(r.x)
    {
        return static_cast<T>(*r.x);
    }
}

template<
    typename T>
    auto ref(
        T &&x)
    noexcept -> ref_obj<T &&>
{
    return { &x };
}

template<
    typename U,
    typename T>
    auto static_ref_cast(
        ref_obj<T> r)
    noexcept -> ref_obj<U>
{
    return ref(static_cast<U&>(obj(r)));
}

template<
    typename U,
    typename T>
    auto dynamic_ref_cast(
        ref_obj<T> r)
    -> ref_obj<U>
{
    return ref(dynamic_cast<U&>(obj(r)));
}

}

#include <ted/noassuming.hpp>

#endif