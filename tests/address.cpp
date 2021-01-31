#include <doctest/doctest.h>

#include <ted/address_of.hpp>

using namespace ted;

TEST_CASE("'obj_at(address_of(x))' is 'x'")
{
    int x;
    int *p = address_of(x);
    CHECK(p);
    int &y = obj_at(p);
    CHECK(&x == &y);
}