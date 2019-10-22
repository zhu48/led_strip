#ifndef RIPPLE_HPP
#define RIPPLE_HPP

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
    class ripple : std::array<T,period*num_periods> {
        public:
            using parent_type = std::array<T,period*num_periods>;

            using parent_type::const_iterator;
            using parent_type::const_reverse_iterator;

            using parent_type::cbegin;
            using parent_type::cend;
            using parent_type::crbegin;
            using parent_type::crend;

            /**
             * Construct a ripple object that pulses up to the maximum value of `T`.
             */
            constexpr ripple() noexcept;

            /**
             * Construct a ripple that pulses up to the given peak value.
             * 
             * \param peak The peak value in the ripple wave.
             */
            constexpr ripple( T peak ) noexcept;

            /**
             * Perform a ripple iteration.
             * 
             * \param n The number of steps to iterate.
             */
            void iterate( std::size_t n ) noexcept;
    };

}

#include "ripple.ipp"

#endif // #ifndef RIPPLE_HPP
