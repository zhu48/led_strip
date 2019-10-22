#include <algorithm>
#include <limits>

#include "gsl_util.hpp"

#include "pattern_fill.hpp"
#include "vop.hpp"

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
    constexpr ripple<T,period,num_periods>::ripple( T peak ) noexcept {
        auto single_period = util::sine<
            T,
            period,
            std::numeric_limits<T>::max()/2,
            std::numeric_limits<T>::max()/2
        >();
        vop::mult(
            single_period.begin(),
            single_period.end(),
            gsl::narrow_cast<long double>( peak ) / std::numeric_limits<T>::max()
        );

        auto data_itr = this->begin();
        for ( decltype(num_periods) i = 0; i < num_periods; ++i ) {
            data_itr = std::copy( single_period.cbegin(), single_period.cend(), data_itr );
        }
    }

    template<typename T, std::size_t period, std::size_t num_periods>
    void ripple<T,period,num_periods>::iterate( std::size_t n ) noexcept {
        std::array<T,period*num_periods> temp;
        std::rotate_copy( this->cbegin(), this->cbegin() + n, this->cend(), temp.begin() );
        std::copy( temp.cbegin(), temp.cend(), this->begin() );
    }

    template<typename T, std::size_t period, std::size_t num_periods>
    constexpr typename ripple<T,period,num_periods>::const_reference
    ripple<T,period,num_periods>::at( size_type pos ) const {
        return parent_type::at( pos );
    }

    template<typename T, std::size_t period, std::size_t num_periods>
    constexpr typename ripple<T,period,num_periods>::const_reference
    ripple<T,period,num_periods>::operator[]( size_type pos ) const {
        return parent_type::operator[]( pos );
    }

    template<typename T, std::size_t period, std::size_t num_periods>
    constexpr typename ripple<T,period,num_periods>::const_reference
    ripple<T,period,num_periods>::front() const {
        return parent_type::front();
    }

    template<typename T, std::size_t period, std::size_t num_periods>
    constexpr typename ripple<T,period,num_periods>::const_reference
    ripple<T,period,num_periods>::back() const {
        return parent_type::back();
    }

    template<typename T, std::size_t period, std::size_t num_periods>
    constexpr const T* ripple<T,period,num_periods>::data() const {
        return parent_type::data();
    }

}
