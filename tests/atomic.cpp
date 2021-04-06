#include <ted/atomic.hpp>

#include <doctest/doctest.h>

using namespace ted;

TEST_CASE("")
{
    std::atomic<int> x;
    store(relaxed(x), 4);
    int expected = 12;
    CHECK(equal(exchange(relaxed(x), expected), 4));
    CHECK(compare_exchange_strong(relaxed(relaxed(x)), expected, 20));
    CHECK(equal(expected, 12));
    CHECK(equal(load(relaxed(x)), 20));
}