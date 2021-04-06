/* 
                ref.hpp

        -- reference wrappers --

original (c) 2021 theodoric e. stier
public domain

unfortunate events in the vintage of
c++ render necessary a separate
non-pointer facility for expressing
reference semantics for problems onto
which value category alone does not map.

call 'ref' to make a reference wrapper
object referring to the operand.

call 'obj' to refer to the object. the
value category is conserved. for generic
contexts, 'obj' defaults to the value-
identity function.

this allows the user to answer the
following questions independently
when passing arguments to a function
which will store them:

1) do we store the object or a pointer?
2) can we move from the operand?

boost.asio fucks this up by refusing
to copy to a handler stored by value or
explain that a handler should be stored
by reference and optionally moved from
when invoked.

*/

#ifndef H_C18F11C6_324A_42F5_925B_C0B3AE1A7BA0
#define H_C18F11C6_324A_42F5_925B_C0B3AE1A7BA0

#include <ted/iterator.hpp>

#include <type_traits>

namespace ted
{

/**
return the argument.
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
reference wrapper for use with
containers and boxes.
*/
template<
    typename Reference>
    struct ref_obj
{
    using pointer_t =
        std::add_pointer_t<
            std::remove_reference_t<
                Reference>>;

    pointer_t pointer;
};

/**
unwrap a reference wrapper.
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
wrap a reference.
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
static cast a reference wrapper.
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
dynamic cast a reference wrapper.
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