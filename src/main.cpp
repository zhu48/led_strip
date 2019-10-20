#include <cstddef>
#include <cstdint>

#include <atomic>
#include <algorithm>
#include <array>
#include <chrono>

#include "portable.hpp"
#include "systick.hpp"

#include "periph_pw_bit.hpp"
#include "ws2812b.hpp"
#include "pattern_fill.hpp"

periph::pw_bit* const pwb_1 = (periph::pw_bit*)(intptr_t)0x43C10020;

volatile std::atomic_bool run;

std::chrono::milliseconds next_run_time{ 0 };

template<typename itr_l, typename itr_r, typename itr_sum>
constexpr void v_sum( itr_sum sum, itr_l l, itr_r r, std::size_t leng ) {
    for ( std::size_t i = 0; i < leng; ++i, ++l, ++r, ++sum ) {
        *sum = *l + *r;
    }
}

template<typename itr_l, typename itr_r, typename itr_min>
constexpr void v_min( itr_min min, itr_l l, itr_r r, std::size_t leng ) {
    for ( std::size_t i = 0; i < leng; ++i, ++l, ++r, ++min ) {
        *min = std::min( *l, *r );
    }
}

template<typename itr, typename scale_type>
constexpr void v_mult( itr begin, itr end, scale_type s ) {
    for ( ; begin != end; ++begin ) {
        *begin *= s;
    }
}

void iterate() {
    if ( portable::systick::uptime() >= next_run_time ) {
        run = true;
        next_run_time += std::chrono::milliseconds{ 10 };
    }
}

int main( int argc, char* argv[] ) {
    portable::systick::init( portable::systick::period_base::us_3, 10, iterate );

    auto red   = util::triangle<std::uint8_t,512>();
    auto green = util::triangle<std::uint8_t,512>();
    auto blue  = util::triangle<std::uint8_t,512>();
    auto red_2   = util::triangle<std::uint8_t,512>();
    auto green_2 = util::triangle<std::uint8_t,512>();
    auto blue_2  = util::triangle<std::uint8_t,512>();

    v_mult( blue.begin(), blue.end(), 0.2 );
    v_mult( blue_2.begin(), blue_2.end(), 0.2 );

    decltype(red) buff;
    decltype(red) frame_r;
    decltype(red) frame_g;
    decltype(red) frame_b;

    led::ws2812b dev( *pwb_1 );
    while ( true ) {
        if ( run ) {
            std::rotate_copy( red.begin(), red.begin()+1, red.end(), buff.begin() );
            red = buff;
            std::rotate_copy( green.begin(), green.begin()+1, green.end(), buff.begin() );
            green = buff;
            std::rotate_copy( blue.begin(), blue.begin()+1, blue.end(), buff.begin() );
            blue = buff;

            std::rotate_copy( red_2.begin(), red_2.begin()+2, red_2.end(), buff.begin() );
            red_2 = buff;
            std::rotate_copy( green_2.begin(), green_2.begin()+2, green_2.end(), buff.begin() );
            green_2 = buff;
            std::rotate_copy( blue_2.begin(), blue_2.begin()+2, blue_2.end(), buff.begin() );
            blue_2 = buff;

            v_min( frame_r.begin(), red.begin(), red_2.begin(), frame_r.size() );
            v_min( frame_g.begin(), green.begin(), green_2.begin(), frame_g.size() );
            v_min( frame_b.begin(), blue.begin(), blue_2.begin(), frame_b.size() );

            dev.write_range( frame_g.cbegin(), frame_r.cbegin(), frame_b.cbegin(), buff.size() );

            run = false;
        } else {
            portable::sleep();
        }
    }
}
