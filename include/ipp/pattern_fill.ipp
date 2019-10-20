#include <limits>

#include "gsl_util.hpp"

namespace util {

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

    template<typename T, std::size_t leng>
    constexpr std::array<T,leng> sine() noexcept;

}
