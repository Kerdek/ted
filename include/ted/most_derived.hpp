/*
            most_derived.hpp

        -- most derived object --
*/

#ifndef H_3A57D319_D753_4353_94FC_B7871A4BFA15
#define H_3A57D319_D753_4353_94FC_B7871A4BFA15

#include <type_traits>

namespace ted
{

/**
get a pointer to the most derived
object.
*/
template<
    typename T>
auto most_derived(
    T *p)
noexcept -> void *
{
    if constexpr (
        std::is_polymorphic_v<
            std::remove_cv_t<
                T>>)
    {
        return dynamic_cast<
            void *>(
            p);
    }
    else
    {
        return static_cast<
            void *>(
            p);
    }
}

}

#endif