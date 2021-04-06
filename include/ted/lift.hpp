#ifndef H_F7F1992B_DC2D_469E_966F_14691BE7260A
#define H_F7F1992B_DC2D_469E_966F_14691BE7260A

#include <ted/same.hpp>

#define lift(...) [](auto &&...x) -> decltype(auto) { return __VA_ARGS__(same(x)...); }

#endif