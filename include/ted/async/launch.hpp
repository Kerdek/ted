/*

               launch.hpp

  -- just run a thread already mate --

*/

#ifndef H_4E715342_813A_42FD_B924_185B0D03789F
#define H_4E715342_813A_42FD_B924_185B0D03789F

#include <ted/same.hpp>

#include <thread>

namespace ted::async
{

/**
starts a `std::thread` with `function`
*/
template<
    typename Function>
    auto launch(
        Function f)
    -> std::thread
{
    return std::thread{ same(f) };
}

}

#endif