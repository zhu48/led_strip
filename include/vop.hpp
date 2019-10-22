#ifndef VOP_HPP
#define VOP_HPP

#include <algorithm>

namespace vop {

    template<typename itr_l, typename itr_r, typename itr_sum>
    constexpr void sum( itr_sum sum, itr_l l, itr_r r, std::size_t leng );

    template<typename itr_l, typename itr_r, typename itr_min>
    constexpr void min( itr_min min, itr_l l, itr_r r, std::size_t leng );

    template<typename itr, typename scale_type>
    constexpr void mult( itr begin, itr end, scale_type s );

    template<std::size_t stride, typename itr, typename output_itr>
    constexpr output_itr sample( output_itr out_begin, itr begin, itr end );

    template<std::size_t stride, typename idx_itr, typename val_itr, typename output_itr>
    constexpr output_itr sample_by_index(
        output_itr out_begin,
        idx_itr idx_begin,
        idx_itr idx_end,
        val_itr values_begin
    );

}

#include "vop.ipp"

#endif // #ifndef VOP_HPP
