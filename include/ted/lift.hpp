#ifndef H_F7F1992B_DC2D_469E_966F_14691BE7260A
#define H_F7F1992B_DC2D_469E_966F_14691BE7260A

#include <ted/same.hpp>

#define lift(f) [](auto &&...x) -> decltype(auto) { return f(same(x)...); }

#endif