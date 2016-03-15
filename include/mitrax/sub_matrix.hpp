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


namespace mitrax{


	namespace detail{


		template < typename M, size_t C, size_t R >
		struct sub_matrix_t{
			constexpr auto operator()(size_t dx, size_t dy)const{
				return m(x + dx, y + dy);
			}

			matrix< M, C, R > const& m;
			size_t x;
			size_t y;
		};


	}


	template <
		bool Cct1, size_t C1, bool Rct1, size_t R1,
		typename M, size_t C2, size_t R2
	>
	constexpr auto sub_matrix(
		matrix< M, C2, R2 > const& m,
		size_t x, size_t y, col_t< Cct1, C1 > c, row_t< Rct1, R1 > r
 	){
		if(x + c > m.cols() || y + r > m.rows()){
			throw std::out_of_range("sub_matrix");
		}

		return make_matrix_by_function(c, r,
			detail::sub_matrix_t< M, C2, R2 >{m, x, y});
	}

	template <
		size_t C1, size_t R1,
		typename M, size_t C2, size_t R2
	>
	constexpr auto sub_matrix(
		matrix< M, C2, R2 > const& m,
		size_t x, size_t y, dims_t< C1, R1 > dims
 	){
		return sub_matrix(m, x, y, dims.cols(), dims.rows());
	}

	template <
		bool Cct1, size_t C1, bool Rct1, size_t R1,
		typename M, size_t C2, size_t R2
	>
	constexpr auto sub_matrix(
		matrix< M, C2, R2 > const& m,
		point< size_t > xy, col_t< Cct1, C1 > c, row_t< Rct1, R1 > r
 	){
		return sub_matrix(m, xy.x(), xy.y(), c, r);
	}

	template <
		size_t C1, size_t R1,
		typename M, size_t C2, size_t R2
	>
	constexpr auto sub_matrix(
		matrix< M, C2, R2 > const& m,
		point< size_t > xy, dims_t< C1, R1 > dims
 	){
		return sub_matrix(m, xy.x(), xy.y(), dims.cols(), dims.rows());
	}


}


#endif
