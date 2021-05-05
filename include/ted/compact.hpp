#ifndef H_D9D093B8_EEB2_4D52_9BC6_ECD35253D216
#define H_D9D093B8_EEB2_4D52_9BC6_ECD35253D216

#include <utility>

namespace ted
{

template<
    typename Begin,
    typename End>
auto compact(
    Begin begin,
    End end)
noexcept -> Begin
{
    for (;;)
    {
        for(; *begin; ++begin);
        if (begin == end) return begin;
        for(; !*end; --end);
        std::swap(*begin, *end);
    }
}

}

#endif