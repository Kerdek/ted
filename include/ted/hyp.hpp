/*
                hyp.hpp

           -- hypothetical --

original (c) 2021 theodoric e. stier
public domain

'std::declval' but shorter to type
and making more sense. additional
value category conversion functions
for decltype expressions.

*/

#ifndef H_1980FBDD_9B93_4581_A138_B0DF977C9133
#define H_1980FBDD_9B93_4581_A138_B0DF977C9133

#include <type_traits>

#define hyp(T) (static_cast<T>(*static_cast<std::remove_reference_t<T> *>(nullptr)))

#endif