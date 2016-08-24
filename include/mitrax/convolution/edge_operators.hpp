//-----------------------------------------------------------------------------
// Copyright (c) 2016 Benjamin Buch
//
// https://github.com/bebuch/mitrax
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt)
//-----------------------------------------------------------------------------
#ifndef _mitrax__convolution_edge_operators__hpp_INCLUDED_
#define _mitrax__convolution_edge_operators__hpp_INCLUDED_

#include "../convolution.hpp"

#include <cmath>


namespace mitrax{


	template < typename M, size_t C, size_t R >
	constexpr auto roberts_cross_x(matrix< M, C, R > const& m){
		return convolution(
			m,
			make_square_matrix< std::int8_t >(dims< 2 >(), {{1, 0}, {0, -1}})
		);
	}

	template < typename M, size_t C, size_t R >
	constexpr auto roberts_cross_y(matrix< M, C, R > const& m){
		return convolution(
			m,
			make_square_matrix< std::int8_t >(dims< 2 >(), {{0, 1}, {-1, 0}})
		);
	}


	template < typename M, size_t C, size_t R >
	constexpr auto prewitt_x(matrix< M, C, R > const& m){
		return convolution(
			m,
			make_col_vector< std::int8_t >(rows< 3 >(), {1, 1, 1}),
			make_row_vector< std::int8_t >(cols< 3 >(), {-1, 0, 1})
		);
	}

	template < typename M, size_t C, size_t R >
	constexpr auto prewitt_y(matrix< M, C, R > const& m){
		return convolution(
			m,
			make_col_vector< std::int8_t >(rows< 3 >(), {-1, 0, 1}),
			make_row_vector< std::int8_t >(cols< 3 >(), {1, 1, 1})
		);
	}


	template < typename M, size_t C, size_t R >
	constexpr auto sobel_x(matrix< M, C, R > const& m){
		return convolution(
			m,
			make_col_vector< std::int8_t >(rows< 3 >(), {1, 2, 1}),
			make_row_vector< std::int8_t >(cols< 3 >(), {-1, 0, 1})
		);
	}

	template < typename M, size_t C, size_t R >
	constexpr auto sobel_y(matrix< M, C, R > const& m){
		return convolution(
			m,
			make_col_vector< std::int8_t >(rows< 3 >(), {-1, 0, 1}),
			make_row_vector< std::int8_t >(cols< 3 >(), {1, 2, 1})
		);
	}


	template < typename M, size_t C, size_t R >
	constexpr auto scharr_x(matrix< M, C, R > const& m){
		return convolution(
			m,
			make_col_vector< std::int8_t >(rows< 3 >(), {3, 10, 3}),
			make_row_vector< std::int8_t >(cols< 3 >(), {-1, 0, 1})
		);
	}

	template < typename M, size_t C, size_t R >
	constexpr auto scharr_y(matrix< M, C, R > const& m){
		return convolution(
			m,
			make_col_vector< std::int8_t >(rows< 3 >(), {-1, 0, 1}),
			make_row_vector< std::int8_t >(cols< 3 >(), {3, 10, 3})
		);
	}


	template <
		typename M1, size_t C1, size_t R1,
		typename M2, size_t C2, size_t R2
	> constexpr auto gradient_magnitude(
		matrix< M1, C1, R1 > const& mx,
		matrix< M2, C2, R2 > const& my
	){
		return make_matrix_fn(get_dims(mx, my), [&mx, &my](auto j, auto k){
			auto x = mx(j, k);
			auto y = my(j, k);
			return std::sqrt(x * x + y * y);
		});
	}

	template <
		typename M1, size_t C1, size_t R1,
		typename M2, size_t C2, size_t R2
	> constexpr auto gradient_direction(
		matrix< M1, C1, R1 > const& mx,
		matrix< M2, C2, R2 > const& my
	){
		return make_matrix_fn(get_dims(mx, my), [&mx, &my](auto j, auto k){
			return std::atan2(my(j, k), mx(j, k));
		});
	}



}

#endif
