#include <ted/dumb.hpp>
#include <ted/null.hpp>
#include <ted/operator.hpp>

#include <doctest/doctest.h>

#include <memory>

using namespace ted;

TEST_CASE("dumb")
{
    INFO("lol dumb");
    
    auto p = new int;
    CHECK(equal(p, (dumb(p))));
    delete p;
}
TEST_CASE("unique")
{
    auto p = std::make_unique<int>();
    CHECK(equal(p.get(), dumb(p)));
}
TEST_CASE("shared")
{
    auto p = std::make_shared<int>();
    CHECK(equal(p.get(), dumb(p)));
}