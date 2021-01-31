#include <doctest/doctest.h>

#include <ted/dumb.hpp>

#include <memory>

using namespace ted;

TEST_CASE("'dumb' accepts 'unique_ptr'")
{
    auto p = std::make_unique<int>();
    CHECK(dumb(p));
}

TEST_CASE("'dumb' accepts 'shared_ptr'")
{
    auto p = std::make_shared<int>();
    CHECK(dumb(p));
}