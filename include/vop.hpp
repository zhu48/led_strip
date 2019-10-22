#ifndef VOP_HPP
#define VOP_HPP

#include <algorithm>

namespace vop {

    /**
     * Vector add two containers, putting the result into a third container.
     * 
     * \tparam itr_l   Iterator type of the left-hand-side addition operand container.
     * \tparam itr_r   Iterator type of the right-hand-side addition operand container.
     * \tparam itr_sum Iterator type of the addition result container.
     * 
     * \param sum  Iterator into the addition result container.
     * \param l    Iterator into the left-hand-side addition operand container.
     * \param r    Iterator into the right-hand-side addition operand container.
     * \param leng Number of elements to perform vector addition over.
     */
    template<typename itr_l, typename itr_r, typename itr_sum>
    constexpr void sum( itr_sum sum, itr_l l, itr_r r, std::size_t leng );

    /**
     * Take the vector minimum of two containers, putting the result into a third container.
     * 
     * \tparam itr_l   Iterator type of the left-hand-side minimization operand container.
     * \tparam itr_r   Iterator type of the right-hand-side minimization operand container.
     * \tparam itr_min Iterator type of the minimization result container.
     * 
     * \param min  Iterator into the minimization result container.
     * \param l    Iterator into the left-hand-side minimization operand container.
     * \param r    Iterator into the right-hand-side minimization operand container.
     * \param leng Number of elements to perform vector minimization over.
     */
    template<typename itr_l, typename itr_r, typename itr_min>
    constexpr void min( itr_min min, itr_l l, itr_r r, std::size_t leng );

    /**
     * Vector multiply a range by a scaler value.
     * 
     * \tparam itr        Iterator type of the range to multiply.
     * \tparam scale_type Type of the scaler to multiply by.
     * 
     * \param begin Iterator to the beginning of the range.
     * \param end   Iterator to one-past-the-end of the range.
     * \param s     The scaler to multiply by.
     */
    template<typename itr, typename scale_type>
    constexpr void mult( itr begin, itr end, scale_type s );

    /**
     * Take evenly-spaced samples from a range, and put the result into another range.
     * 
     * \tparam stride     The sample spacing.
     * \tparam itr        Iterator type of the range to sample.
     * \tparam output_itr Iterator type of the range to store samples to.
     * 
     * \param out_begin Iterator to the beginning of the range to write samples to.
     * \param begin     Iterator to the beginning of the range to take samples of.
     * \param end       Iterator to one-past-the-end of the range to take samples of.
     * 
     * \return Returns an iterator to the next position in the output range.
     */
    template<std::size_t stride, typename itr, typename output_itr>
    constexpr output_itr sample( output_itr out_begin, itr begin, itr end );

    /**
     * Take evenly-spaced samples through a range of indices.
     * 
     * Take evenly-spaced samples of the indices into a values range. For each sampled index, write
     * the value in the values range at that index into the results range.
     * 
     * \tparam stride     The sample spacing.
     * \tparam idx_itr    Iterator type of the range containing index-type objects.
     * \tparam val_itr    Iterator type of the range containing the values to sample.
     * \tparam output_itr Iterator type of the results range.
     * 
     * \param out_begin    Iterator to the beginning of the results range.
     * \param idx_begin    Iterator to the beginning of the index-containing range.
     * \param idx_end      Iterator to one-past-the-end of the index-containing range.
     * \param values_begin Iterator to the beginning of the values range.
     */
    template<std::size_t stride, typename idx_itr, typename val_itr, typename output_itr>
    constexpr output_itr sample_by_index(
        output_itr out_begin,
        idx_itr    idx_begin,
        idx_itr    idx_end,
        val_itr    values_begin
    );

}

#include "vop.ipp"

#endif // #ifndef VOP_HPP
