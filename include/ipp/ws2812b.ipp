#include <type_traits>

namespace led {

    template<typename Itr>
    void ws2812b::write_range( Itr begin, Itr end ) {
        static_assert(
            std::is_integral_v<typename std::iterator_traits<Itr>::value_type>,
            "Iterator value type must be an integer type"
        );
        static_assert(
            sizeof(std::iterator_traits<Itr>::value_type) >= 3,
            "Iterator value type must be at least 24-bits wide"
        );

        for ( ; begin != end; ++begin ) {
            while ( dev.fifo_full() );
            dev.write( *begin );
        }
    }

    template<typename Itr>
    void ws2812b::write_range(
        Itr                                                 green_begin,
        Itr                                                 red_begin,
        Itr                                                 blue_begin,
        typename std::iterator_traits<Itr>::difference_type num_leds
    ) {
        static_assert(
            std::is_integral_v<typename std::iterator_traits<Itr>::value_type>,
            "Iterator value type must be an integer type"
        );

        for ( decltype(num_leds) i = 0; i < num_leds; ++i, ++red_begin, ++green_begin, ++blue_begin ) {
            while ( dev.fifo_full() );
            dev.write(
                static_cast<std::uint8_t>( *green_begin ) << 16 |
                static_cast<std::uint8_t>( *red_begin )   <<  8 |
                static_cast<std::uint8_t>( *blue_begin )
            );
        }
    }

}
