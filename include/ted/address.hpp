/* 
              address.hpp
   
           -- indirections --
   
original (c) 2021 theodoric e. stier
public domain

fixes a massively broken thing about
cpp and is actually just std functions
in disguise!
   
*/

#ifndef H_68C63DFA_8F3F_4238_AA8B_6BB10A544AFE
#define H_68C63DFA_8F3F_4238_AA8B_6BB10A544AFE

#include <memory>
#include <type_traits>

namespace ted
{

template<
    typename T>
    auto address(
        T &&x)
    noexcept -> decltype(std::addressof(same(x)))
{
    return std::addressof(same(x));
}

}

#endif