#include <ted/operator.hpp>
#include <ted/provider.hpp>

#include <doctest/doctest.h>

#include <memory>
#include <vector>
#include <type_traits>

using namespace ted;

// TEST_CASE("provider copy")
// {
//     auto p = ted::make_empty_provider<int>();
//     emplace_contents(
//         p,
//         5);
//     CHECK(equal(5, contents(p)));
//     auto q =
//         p;
//     CHECK(equal(5, contents(q)));
//     destroy_contents(
//         q);
// }

// TEST_CASE("provider move")
// {
//     using provider::provider_t;

//     using P = provider_t<
//         std::unique_ptr<int>>;

//     P p0;

//     emplace_contents(
//         p0,
//         std::make_unique<int>(5));

//     CHECK(equal(5, obj_at(contents(p0))));

//     P p1;

//     emplace_contents(
//         p1,
//         extract_contents(
//             p0));

//     CHECK(equal(5, obj_at(contents(p1))));

//     destroy_contents(
//         p1);
// }


// TEST_CASE("provider copy")
// {
//     auto p = ted::make_empty_provider<int>();
//     emplace_contents(
//         p,
//         5);
//     CHECK(equal(5, contents(p)));
//     auto q =
//         p;
//     CHECK(equal(5, contents(q)));
//     destroy_contents(
//         q);
// }