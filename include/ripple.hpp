#ifndef EFFECT_HPP
#define EFFECT_HPP

#include <cstddef>

#include <array>

namespace effect {

    /**
     * Ripple wave generator.
     * 
     * \tparam T           The numeric type to create a ripple based on.
     * \tparam period      The ripple repetition period.
     * \tparam num_periods The number of periods in a single ripple object.
     */
    template<typename T, std::size_t period, std::size_t num_periods>
    class ripple : public std::array<T,period*num_periods> {
        public:
            /**
             * Construct a ripple object.
             */
            constexpr ripple() noexcept;

            /**
             * Perform a ripple iteration.
             * 
             * \param n The number of steps to iterate.
             */
            void iterate( std::size_t n ) noexcept;
    };

}

#include "ripple.ipp"

#endif // #ifndef EFFECT_HPP
