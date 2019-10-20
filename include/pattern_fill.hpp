#ifndef PATTERN_FILL_HPP
#define PATTERN_FILL_HPP

#include <array>

namespace util {

    /**
     * Generate an array containing a single symmetric triangle wave period.
     * 
     * The wave starts at zero at element zero, rises to the maximum value of `T` in the array's
     * middle, and falls back to zero at the last array element.
     * 
     * \tparam T    The numeric type the array contains.
     * \tparam leng The length of the array.
     * 
     * \return Returns an array holding a single symmetric triangle wave period.
     */
    template<typename T, std::size_t leng>
    constexpr std::array<T,leng> triangle() noexcept;

    template<typename T, std::size_t leng>
    constexpr std::array<T,leng> sine() noexcept;

}

#include "pattern_fill.ipp"

#endif // #ifndef PATTERN_FILL_HPP
