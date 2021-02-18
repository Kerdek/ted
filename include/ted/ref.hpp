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

#include <ted/assuming.hpp>
#include <ted/iterator.hpp>
#include <ted/null.hpp>

#include <type_traits>

namespace ted
{

/**
Default implementation of `obj` which
simply returns the argument.
*/
template<
    typename Object>
    auto obj(
        Object x)
    noexcept -> Object
{
    return same(x);
}

/**
Stores a pointer and provides good
idioms for reference-semantic
subobjects.
*/
template<
    typename Reference>
    struct ref_obj
{
    using pointer_t = 
        std::remove_reference_t<
            Reference> *;

    pointer_t pointer;
};

/**
Unwrap the `ref_obj`.
*/
template<
    typename Reference>
    auto obj(
        ref_obj<Reference> object)
    noexcept -> Reference
{
    return static_cast<Reference>(
        ted::peek(same(object).pointer));
}

/**
Wrap `object` in a `ref_obj`.
*/
template<
    typename Object>
    auto ref(
        Object &&object)
    noexcept -> ref_obj<
        Object &&>
{
    return { &object };
}

/**
Obtain a `ref_obj` of a related type.
*/
template<
    typename Destination,
    typename Source>
    auto static_ref_cast(
        ref_obj<Source> r)
    noexcept -> ref_obj<
        Destination>
{
    return ref(
        static_cast<Destination &>(
            obj(r)));
}

/**
Obtain a `ref_obj` of a related type
with dynamic type checking.
*/
template<
    typename Destination,
    typename Source>
    auto dynamic_ref_cast(
        ref_obj<Source> r)
    -> ref_obj<Destination>
{
    return ref(
        dynamic_cast<Destination &>(
            obj(r)));
}

}

#endif