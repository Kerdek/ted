#include <doctest/doctest.h>

#include <ted/find.hpp>
#include <ted/span.hpp>

#include <string>

using namespace ted;

#define TEST_ALL(range, data)                                                   \
    std::decay_t<decltype(*begin(range))> data;                                 \
    for(auto &in : range)                                                       \
    {                                                                           \
        SUBCASE((std::string(#range "[") +                                      \
                        std::to_string(in) + "]").c_str())                      \
        {                                                                       \
            data = in;                                                          \
        }                                                                       \
    }

TEST_CASE("find")
{
    constexpr auto n = 3;

    using X = 
        const long[n];
    using I = 
        std::decay_t<X>;
    using S =
        span::span_t<I, I>;

    constexpr X x{
        0x04'2b'1c'03'cf'5d'79'd3,
        0x5d'94'26'b4'43'6c'86'69,
        0x29'11'ab'61'd5'ee'3b'a8
    };

    S s = make_span(x, x + n);

    TEST_ALL(s, e);

    I i = find(s, e);
    I b = end(s);

    REQUIRE(i != b);
    CHECK(*i == e);
}