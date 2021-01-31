#include <doctest/doctest.h>

#include <ted/find.hpp>
#include <ted/span.hpp>

#include <string>
#include <numeric>

using namespace ted;

#define TEST_ALL(range, data)                                                   \
    std::remove_reference_t<decltype(*begin(range))> data;                      \
    for(auto &in : range)                                                       \
    {                                                                           \
        DOCTEST_SUBCASE((std::string(#range "[") +                              \
                        std::to_string(in) + "]").c_str())                      \
        {                                                                       \
            data = in;                                                          \
        }                                                                       \
    }

TEST_CASE("'find' accepts 'span'")
{
    constexpr std::size_t n = 3;
    int x[n];
    auto s = make_span(x, x + n);
    std::iota(
        begin(s),
        end(s),
        0);

    TEST_ALL(
        s,
        e);

    auto it = find(
        s,
        e);

    REQUIRE(it != end(s));
    CHECK(*it == e);
}