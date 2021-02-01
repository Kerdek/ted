#include <ted/dyn.hpp>
#include <ted/ref.hpp>

#include <doctest/doctest.h>

using namespace ted;

TEST_CASE("dyn")
{
    long x = 0x1a'f6'51'bd'4a'65'8d'79;
    auto f = [=] { return x; };
    erasure::erasure_t<long()> g;
    SUBCASE("by value")
    {
        g = dyn<long()>(f);
    }
    SUBCASE("by reference object")
    {        
        g = dyn<long()>(ref(f));
    }
    REQUIRE(g);
    long y = invoke(g);
    CHECK(x == y);
}