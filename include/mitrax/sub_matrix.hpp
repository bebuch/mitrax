//-----------------------------------------------------------------------------
// Copyright (c) 2015-2016 Benjamin Buch
//
// https://github.com/bebuch/mitrax
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt)
//-----------------------------------------------------------------------------
#ifndef _mitrax__sub_matrix__hpp_INCLUDED_
#define _mitrax__sub_matrix__hpp_INCLUDED_

#include "make_matrix.hpp"

#include <string>


namespace mitrax::detail{


	template < typename M >
	struct sub_matrix_t{
		constexpr decltype(auto) operator()(c_t dx, r_t dy)const{
			return m(x + dx, y + dy);
		}

		M m;
		c_t x;
		r_t y;
	};

	template <
		bool Cct1, col_t C1, bool Rct1, row_t R1,
		typename M
	> constexpr auto make_sub_matrix_t(
		M&& m,
		c_t x, r_t y, col< Cct1, C1 > c, row< Rct1, R1 > r
	){
		if(
			x >= m.cols() || x + c_t(c) > m.cols() ||
			y >= m.rows() || y + r_t(r) > m.rows()
		){
			throw std::out_of_range("sub_matrix out of range (matrix: " +
				std::to_string(size_t(m.cols())) + "x" +
				std::to_string(size_t(m.rows())) + "; sub-pos: " +
				std::to_string(size_t(x)) + "x" +
				std::to_string(size_t(y)) + "; sub-dims: " +
				std::to_string(size_t(c)) + "x" +
				std::to_string(size_t(r)) + ")");
		}

		auto ref = forward_ref(static_cast< M&& >(m));
		return sub_matrix_t< decltype(ref) >{ref, x, y};
	}


}


namespace mitrax{


	template <
		bool Cct1, col_t C1, bool Rct1, row_t R1,
		typename M, col_t C2, row_t R2
	> constexpr auto sub_matrix(
		matrix< M, C2, R2 > const& m,
		c_t x, r_t y, col< Cct1, C1 > c, row< Rct1, R1 > r
 	){
		return make_matrix_fn(c, r, detail::make_sub_matrix_t(m, x, y, c, r));
	}

	template <
		bool Cct1, col_t C1, bool Rct1, row_t R1,
		typename M, col_t C2, row_t R2
	> constexpr auto sub_matrix(
		matrix< M, C2, R2 >&& m,
		c_t x, r_t y, col< Cct1, C1 > c, row< Rct1, R1 > r
 	){
		return make_matrix_fn(c, r,
			detail::make_sub_matrix_t(std::move(m), x, y, c, r));
	}

	template <
		bool Cct1, col_t C1, bool Rct1, row_t R1,
		typename M, col_t C2, row_t R2
	> constexpr auto sub_matrix(
		matrix< M, C2, R2 > const& m,
		c_t x, r_t y, dim_pair_t< Cct1, C1, Rct1, R1 > const& dims
 	){
		return sub_matrix(m, x, y, dims.cols(), dims.rows());
	}

	template <
		bool Cct1, col_t C1, bool Rct1, row_t R1,
		typename M, col_t C2, row_t R2
	> constexpr auto sub_matrix(
		matrix< M, C2, R2 >&& m,
		c_t x, r_t y, dim_pair_t< Cct1, C1, Rct1, R1 > const& dims
 	){
		return sub_matrix(std::move(m), x, y, dims.cols(), dims.rows());
	}

	template <
		bool Cct1, col_t C1, bool Rct1, row_t R1,
		typename M, col_t C2, row_t R2
	> constexpr auto sub_matrix(
		matrix< M, C2, R2 > const& m,
		point_t xy, col< Cct1, C1 > c, row< Rct1, R1 > r
 	){
		return sub_matrix(m, xy.x(), xy.y(), c, r);
	}

	template <
		bool Cct1, col_t C1, bool Rct1, row_t R1,
		typename M, col_t C2, row_t R2
	> constexpr auto sub_matrix(
		matrix< M, C2, R2 >&& m,
		point_t xy, col< Cct1, C1 > c, row< Rct1, R1 > r
 	){
		return sub_matrix(std::move(m), xy.x(), xy.y(), c, r);
	}

	template <
		bool Cct1, col_t C1, bool Rct1, row_t R1,
		typename M, col_t C2, row_t R2
	> constexpr auto sub_matrix(
		matrix< M, C2, R2 > const& m,
		point_t xy, dim_pair_t< Cct1, C1, Rct1, R1 > const& dims
 	){
		return sub_matrix(m, xy.x(), xy.y(), dims.cols(), dims.rows());
	}

	template <
		bool Cct1, col_t C1, bool Rct1, row_t R1,
		typename M, col_t C2, row_t R2
	> constexpr auto sub_matrix(
		matrix< M, C2, R2 >&& m,
		point_t xy, dim_pair_t< Cct1, C1, Rct1, R1 > const& dims
 	){
		return
			sub_matrix(std::move(m), xy.x(), xy.y(), dims.cols(), dims.rows());
	}


}


#endif
