/*
              assuming.hpp

          -- assuming macro --

original (c) 2021 theodoric e. stier
public domain

used for simultaneous debug asserting
and release optimizing.

*/

#ifndef H_FA974A37_AA1C_4C49_940A_62409C48B32F
#define H_FA974A37_AA1C_4C49_940A_62409C48B32F

#include <cassert>

#define assuming(x) assert(x); if(x)

#endif