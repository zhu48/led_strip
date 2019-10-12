#ifndef WS2812B_HPP
#define WS2812B_HPP

#include <iterator>
#include <type_traits>

#include "periph_pw_bit.hpp"

namespace led {

    class ws2812b {
        public:
            ws2812b( periph::pw_bit& peripheral );

            template<typename Itr>
            void write_range( Itr begin, Itr end );

            template<typename Itr>
            void write_range(
                Itr                                                 green_begin,
                Itr                                                 red_begin,
                Itr                                                 blue_begin,
                typename std::iterator_traits<Itr>::difference_type num_leds
            );

        private:
            periph::pw_bit& dev;
    };

}

#include "ws2812b.ipp"

#endif // #ifndef WS2812B_HPP
