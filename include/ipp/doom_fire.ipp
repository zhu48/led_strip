#include <iterator>
#include <random>

namespace effect {

    template<typename itr, typename rand_eng, typename rand_dist>
    itr doom_fire(
        itr                                            begin,
        itr                                            end,
        typename std::iterator_traits<itr>::value_type clamp,
        rand_eng&                                      engine,
        rand_dist&                                     dist
    ) noexcept {
        for ( --end; begin < end; --end ) {
            auto stride = dist( engine );
            auto last_val = *( end - 1 );
            if ( ( clamp - last_val ) < stride ) {
                *end = clamp;
            } else {
                *end = last_val + stride;
            }
        }

        return begin;
    }

}
