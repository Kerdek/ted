/* 
               pointer.hpp

        -- built-in indirection --

original (c) 2021 theodoric e. stier
public domain

*/

#ifndef H_68C63DFA_8F3F_4238_AA8B_6BB10A544AFE
#define H_68C63DFA_8F3F_4238_AA8B_6BB10A544AFE

#include <memory>
#include <type_traits>

namespace ted
{

/**

Get the address of an object `x`.
Effectively an alias of
`std::addressof`.

*/
template<
    typename T>
    auto address_of(
        T &x)
    noexcept -> decltype(
        std::addressof(x))
{
    return std::addressof(x);
}

/**

Dereference a pointer `x` with no null
check. Refuses anything which is not
actually a pointer.

*/
template<
    typename T>
    auto indirect(
        T &&x)
    noexcept -> decltype(
        *x)
{
    static_assert(std::is_pointer_v<std::remove_reference_t<T>>);

    return *x;
}

}

#endif