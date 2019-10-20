#include <cstddef>
#include <cstdint>

#include <atomic>
#include <array>
#include <chrono>

#include "portable.hpp"
#include "systick.hpp"

#include "periph_pw_bit.hpp"
#include "ws2812b.hpp"
#include "pattern_fill.hpp"
#include "vop.hpp"
#include "ripple.hpp"

periph::pw_bit* const pwb_1 = (periph::pw_bit*)(intptr_t)0x43C10020;

volatile std::atomic_bool run;

std::chrono::milliseconds next_run_time{ 0 };

void iterate() {
    if ( portable::systick::uptime() >= next_run_time ) {
        run = true;
        next_run_time += std::chrono::milliseconds{ 10 };
    }
}

int main( int argc, char* argv[] ) {
    portable::systick::init( portable::systick::period_base::us_3, 10, iterate );

    std::array<std::uint8_t,160>      zero = { 0 };
    effect::ripple<std::uint8_t,40,4> blue;

    led::ws2812b dev( *pwb_1 );
    while ( true ) {
        if ( run ) {
            blue.iterate( 1 );
            dev.write_range( zero.cbegin(), zero.cbegin(), blue.cbegin(), blue.size() );

            run = false;
        } else {
            portable::sleep();
        }
    }
}
