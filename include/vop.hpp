#ifndef VOP_HPP
#define VOP_HPP

#include <algorithm>

namespace vop {

    template<typename itr_l, typename itr_r, typename itr_sum>
    constexpr void sum( itr_sum sum, itr_l l, itr_r r, std::size_t leng ) {
        for ( std::size_t i = 0; i < leng; ++i, ++l, ++r, ++sum ) {
            *sum = *l + *r;
        }
    }

    template<typename itr_l, typename itr_r, typename itr_min>
    constexpr void min( itr_min min, itr_l l, itr_r r, std::size_t leng ) {
        for ( std::size_t i = 0; i < leng; ++i, ++l, ++r, ++min ) {
            *min = std::min( *l, *r );
        }
    }

    template<typename itr, typename scale_type>
    constexpr void mult( itr begin, itr end, scale_type s ) {
        for ( ; begin != end; ++begin ) {
            *begin *= s;
        }
    }

    template<std::size_t stride, typename itr, typename output_itr>
    constexpr output_itr sample( output_itr out_begin, itr begin, itr end ) {
        for ( ; std::distance( begin, end ) > stride; begin += stride, ++out_begin ) {
            *out_begin = *begin;
        }

        return out_begin;
    }

    template<std::size_t stride, typename idx_itr, typename val_itr, typename output_itr>
    constexpr output_itr sample_by_index(
        output_itr out_begin,
        idx_itr idx_begin,
        idx_itr idx_end,
        val_itr values_begin
    ) {
        for ( ; std::distance( idx_begin, idx_end ) > stride; idx_begin += stride, ++out_begin ) {
            *out_begin = *( values_begin + *idx_begin );
        }

        return out_begin;
    }

}

#endif // #ifndef VOP_HPP
