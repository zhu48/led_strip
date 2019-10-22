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

            using value_type             = typename parent_type::value_type;
            using size_type              = typename parent_type::size_type;
            using difference_type        = typename parent_type::difference_type;
            using const_reference        = typename parent_type::const_reference;
            using const_pointer          = typename parent_type::const_pointer;
            using const_iterator         = typename parent_type::const_iterator;
            using const_reverse_iterator = typename parent_type::const_reverse_iterator;

            using parent_type::cbegin;
            using parent_type::cend;
            using parent_type::crbegin;
            using parent_type::crend;

            using parent_type::empty;
            using parent_type::size;
            using parent_type::max_size;

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

            constexpr const_reference at( size_type pos ) const;
            constexpr const_reference operator[]( size_type pos ) const;
            constexpr const_reference front() const;
            constexpr const_reference back() const;
            constexpr const T* data() const noexcept;

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
