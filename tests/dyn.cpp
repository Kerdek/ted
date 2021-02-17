#include <ted/dyn.hpp>

#include <doctest/doctest.h>

#include <utility>

using namespace ted;

TEST_CASE("dyn")
{
    long x = 0x1a'f6'51'bd'4a'65'8d'79;
    long y;

    auto f = [=] { return x; };
    erasure::erasure_t<long()> g;

    SUBCASE("by value")
    {
        g = dyn<long()>(f);
        REQUIRE(g);
        
        SUBCASE("invoked as lvalue")
        {
            y = invoke(g);
        }
        SUBCASE("invoked as rvalue")
        {
            y = invoke(std::move(g));
        }
    }
    SUBCASE("by reference object")
    {
        g = dyn<long()>(ref(f));
        REQUIRE(g);

        SUBCASE("invoked as lvalue")
        {
            y = invoke(g);
        }
        SUBCASE("invoked as rvalue")
        {
            y = invoke(std::move(g));
        }
    }

    CHECK(x == y);
}