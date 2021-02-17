#ifndef H_8A81B474_0A4D_4E21_96FE_04F3E2308619
#define H_8A81B474_0A4D_4E21_96FE_04F3E2308619

#include <exception>

namespace ted::async
{

struct noexcept_coro
{ };

[[noreturn]]
inline auto handle_exception(
    const noexcept_coro &)
noexcept -> void
{
    std::terminate();
}

}

#endif