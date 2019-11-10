#include <cstddef>
#include <cstdint>

#include <algorithm>
#include <array>
#include <atomic>
#include <chrono>

#include "portable.hpp"
#include "systick.hpp"

#include "periph_pw_bit.hpp"
#include "ws2812b.hpp"
#include "pattern_fill.hpp"
#include "vop.hpp"
#include "doom_fire.hpp"
#include "ripple.hpp"

periph::pw_bit* const pwb_1 = (periph::pw_bit*)(intptr_t)0x43C10020;

volatile std::atomic_bool run;

std::chrono::milliseconds next_run_time{ 0 };

template<std::size_t cycle_size, typename T, std::size_t palette_size>
void init_palette(
    std::array<T,palette_size>& red,
    std::array<T,palette_size>& green,
    std::array<T,palette_size>& blue
) {
    constexpr auto cycle = util::sine<
        T,
        cycle_size,
        std::numeric_limits<T>::max()/5,
        std::numeric_limits<T>::max()/5
    >( cycle_size / 4 );

    auto r_end = std::copy_n( cycle.cbegin(), cycle_size/2, red.begin() );
    auto g_end = vop::sample<2>( green.begin(), cycle.cbegin(), cycle.cbegin() + cycle_size/2 );
    auto b_end = vop::sample<1>( blue.begin(), cycle.cbegin(), cycle.cbegin() + cycle_size/2 );

    std::fill( r_end, red.end(), 0 );
    std::fill( g_end, green.end(), 0 );
    std::fill( b_end, blue.end(), 0 );
}

template<typename T>
void do_average( T& arr ) {
    for ( gsl::index i = 0; i < arr[0]->size(); ++i ) {
        typename std::remove_reference_t<decltype(*arr[0])>::value_type sum = 0;
        for ( gsl::index j = 1; j < arr.size(); ++j ) {
            sum += (*arr[j])[i];
        }
        (*arr[0])[i] = sum / (arr.size()-1);
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

    std::array<std::uint8_t,3000> palette_green;
    std::array<std::uint8_t,3000> palette_red;
    std::array<std::uint8_t,3000> palette_blue;
    init_palette<2000>( palette_red, palette_green, palette_blue );

    std::array<std::size_t,140> fire{ 0 };

    std::array<std::uint8_t,140> frame_g;
    std::array<std::uint8_t,140> frame_r;
    std::array<std::uint8_t,140> frame_b;

    std::mt19937 rd;
    std::uniform_int_distribution dist{ 0, 30 };

    led::ws2812b dev( *pwb_1 );
    while ( true ) {
        if ( run ) {
            effect::doom_fire(
                fire.begin(),
                fire.begin() + 70,
                3000-1,
                rd,
                dist
            );
            effect::doom_fire(
                fire.rbegin(),
                fire.rbegin() + 70,
                3000-1,
                rd,
                dist
            );

            vop::sample_by_index<1>(
                frame_g.begin(),
                fire.cbegin(),
                fire.cend(),
                palette_green.cbegin()
            );
            vop::sample_by_index<1>(
                frame_r.begin(),
                fire.cbegin(),
                fire.cend(),
                palette_red.cbegin()
            );
            vop::sample_by_index<1>(
                frame_b.begin(),
                fire.cbegin(),
                fire.cend(),
                palette_blue.cbegin()
            );
            dev.write_range( frame_g.cbegin(), frame_r.cbegin(), frame_b.cbegin(), fire.size() );

            run = false;
        } else {
            portable::sleep();
        }
    }
}
