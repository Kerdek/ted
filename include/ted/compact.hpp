#ifndef H_D9D093B8_EEB2_4D52_9BC6_ECD35253D216
#define H_D9D093B8_EEB2_4D52_9BC6_ECD35253D216

#include <utility>

namespace ted
{

template<
    typename Begin,
    typename End,
    typename Relocate>
auto compact(
    Begin begin,
    End end,
    Relocate relocate)
noexcept -> Begin
{
    for (;;)
    {
        for(; *begin; ++begin);
        if (begin == end) return begin;
        for(; !*end; --end);
        relocate(begin, end);
    }
}

}

#endif