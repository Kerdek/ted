#include <ted/pointer.hpp>

#include <doctest/doctest.h>

TEST_CASE("'obj_at(address_of(x))' is 'x'")
{
    int x;
    int *p = ted::address_of(x);
    CHECK(p);
    int &y = ted::indirect(p);
    CHECK(&x == &y);
}