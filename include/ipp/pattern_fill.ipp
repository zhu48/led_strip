#include <cmath>

#include <limits>

#include "gsl_util.hpp"

namespace util {

    constexpr long double pi = std::acos( (long double){ -1.0 } ); //!< Pi constant.

    /**
     * constexpr type for generating a single compile-time symmetric triangle wave period.
     * 
     * The wave starts at zero at element zero, rises to the maximum value of `T` in the array's
     * middle, and falls back to zero at the last array element.
     * 
     * \tparam T    The numerical type to generate a triangle type using.
     * \tparam leng Then number of elements making up a triangle period.
     */
    template<typename T, std::size_t leng>
    struct triangle_gen {
        /**
         * constexpr-construct the triangle wave data member.
         */
        constexpr triangle_gen() noexcept {
            constexpr auto max_val = std::numeric_limits<T>::max();
            for ( std::size_t i = 0; i < leng/2; ++i ) {
                data[i] =
                    max_val *
                    (
                        gsl::narrow_cast<long double>( i ) /
                        ( gsl::narrow_cast<long double>( leng ) / 2.0 )
                    );
                data[leng-i-1] = data[i];
            }
        }
        std::array<T,leng> data; //!< The array storing a triangle wave period.
    };

    template<typename T, std::size_t leng>
    constexpr std::array<T,leng> triangle() noexcept {
        return triangle_gen<T,leng>{}.data;
    }

    /**
     * `constexpr` type for generating a single sine wave period.
     * 
     * \tparam T         The numeric type the array contains.
     * \tparam leng      The length of the array.
     * \tparam amplitude The amplitude of the sine wave.
     * \tparam offset    The offset of the sine wave.
     */
    template<typename T, std::size_t leng, std::intmax_t amplitude, std::intmax_t offset>
    struct sine_gen {
        /**
         * Construct the sine wave data member.
         * 
         * \param phase The phase offset to begin the wave at.
         */
        constexpr sine_gen( std::size_t phase ) noexcept : data( {} ) {
            for ( std::size_t i = 0; i < leng; ++i ) {
                auto angle_raw =
                    gsl::narrow_cast<long double>( i ) + gsl::narrow_cast<long double>( phase );
                auto cycle_ratio = angle_raw / (long double){ leng };
                auto angle_rad = (long double){ 2.0 } * pi * cycle_ratio;
                data[i] =
                    gsl::narrow_cast<T>(
                        (long double){ amplitude } * std::sin( angle_rad ) + (long double){ offset }
                    );
            }
        }
        std::array<T,leng> data; //!< The array storing a sine wave period.
    };

    template<
        typename      T,
        std::size_t   leng,
        std::intmax_t amplitude,
        std::intmax_t offset
    > constexpr std::array<T,leng> sine( std::size_t phase ) noexcept {
        return sine_gen<T,leng,amplitude,offset>( phase ).data;
    }

}
