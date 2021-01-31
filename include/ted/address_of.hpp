/* 
             address_of.hpp

           -- indirections --

original (c) 2021 theodoric e. stier
public domain

fixes a massively broken thing about
cpp and is actually just std functions
in disguise!

*/

#ifndef H_68C63DFA_8F3F_4238_AA8B_6BB10A544AFE
#define H_68C63DFA_8F3F_4238_AA8B_6BB10A544AFE

#include <ted/operator.hpp>

#include <memory>
#include <type_traits>

#include <ted/same.hpp>

namespace ted
{

template<
    typename T>
    auto address_of(
        T &&x)
    noexcept -> auto *
{
    return std::addressof(x);
}

template<
    typename T>
    auto obj_at(
        T &&x)
    noexcept -> decltype(auto)
{
    return deref(same(x));
}

}

#include <ted/nosame.hpp>

#endif