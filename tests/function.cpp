#include <doctest/doctest.h>

#include <ted/operator.hpp>
#include <ted/function.hpp>
#include <type_traits>

using namespace ted;

#include <ted/same.hpp>

TEST_CASE("lambda")
{
    int x = 1516514;

    auto f = erase_function<int()>([x] { return x; });

    CHECK(invoke(f) == x);

    auto g = same(f);
    
    CHECK(invoke(g) == x);
}