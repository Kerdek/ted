#include <ted/dyn.hpp>

#include <doctest/doctest.h>

#include <utility>
#include <memory>

using namespace ted;

TEST_CASE("dyn")
{
    long x = 0x1a'f6'51'bd'4a'65'8d'79;
    long y;

    auto f = [=] { return x; };
    abstract_function<long>* a;

    SUBCASE("by value")
    {
        auto g = dyn(f);
        a = &g;

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
        auto g = dyn(ref(f));
        a = &g;

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