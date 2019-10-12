#include "ws2812b.hpp"

using namespace led;

ws2812b::ws2812b( periph::pw_bit& peripheral ) : dev( peripheral ) {
    dev.set_active_bytes( 3 );
    dev.set_period( 125 );
    dev.set_1b_duty( 80 );
    dev.set_0b_duty( 40 );

    dev.enable();
}
