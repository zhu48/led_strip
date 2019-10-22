#ifndef DOOM_FIRE_HPP
#define DOOM_FIRE_HPP

#include <cstddef>

#include <array>

namespace effect {

    template<typename itr, typename rand_eng, typename rand_dist>
    itr doom_fire(
        itr                                            begin,
        itr                                            end,
        typename std::iterator_traits<itr>::value_type clamp,
        rand_eng&                                      engine,
        rand_dist&                                     dist
    ) noexcept;

}

#include "doom_fire.ipp"

#endif // #ifndef DOOM_FIRE_HPP
