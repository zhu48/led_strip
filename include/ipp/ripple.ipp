#include <algorithm>
#include <limits>

#include "pattern_fill.hpp"

namespace effect {

    template<typename T, std::size_t period, std::size_t num_periods>
    constexpr ripple<T,period,num_periods>::ripple() noexcept {
        constexpr auto single_period = util::sine<
            T,
            period,
            std::numeric_limits<T>::max()/2,
            std::numeric_limits<T>::max()/2
        >();

        auto data_itr = this->begin();
        for ( decltype(num_periods) i = 0; i < num_periods; ++i ) {
            data_itr = std::copy( single_period.cbegin(), single_period.cend(), data_itr );
        }
    }

    template<typename T, std::size_t period, std::size_t num_periods>
    void ripple<T,period,num_periods>::iterate( std::size_t n ) noexcept {
        static_assert( n < period, "cannot iterate more than a single period" );

        decltype(*this) temp;
        std::rotate_copy( this->cbegin, this->cbegin() + n, this->cend(), temp.begin() );
        std::copy( temp.cbegin(), temp.cend(), this->end() );
    }

}
