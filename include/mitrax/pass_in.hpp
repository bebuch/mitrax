//-----------------------------------------------------------------------------
// Copyright (c) 2015 Benjamin Buch
//
// https://github.com/bebuch/mitrax
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt)
//-----------------------------------------------------------------------------
#ifndef _mitrax__pass_in__hpp_INCLUDED_
#define _mitrax__pass_in__hpp_INCLUDED_

#include "matrix.hpp"


namespace mitrax{


	template <
		bool Ccto, size_t Co, bool Rcto, size_t Ro,
		typename M, size_t C, size_t R
	> constexpr auto pass_in(
		col_init_t< Ccto, Co > c,
		row_init_t< Rcto, Ro > r,
		matrix< M, C, R > const& m,
		value_type_t< M > const& default_value
	){
		using value_type = value_type_t< M >;

		size_t x_offset = c - m.cols();
		size_t y_offset = r - m.rows();

		bool x_even = x_offset % 2 == 0;
		bool y_even = y_offset % 2 == 0;

		x_offset /= 2;
		y_offset /= 2;

		auto g = [&m, default_value](size_t x, size_t y){
			if(x >= m.cols() || y >= m.rows()) return default_value;
			return m(x, y);
		};

		return make_matrix_by_function(c, r, [&](size_t x, size_t y){
			if(x_even){
				if(y_even){
					return g(x - x_offset, y - y_offset);
				}else{
					auto a = 0.5f * g(x - x_offset, y - y_offset);
					auto b = 0.5f * g(x - x_offset, y - y_offset + 1);
					return static_cast< value_type >(a + b);
				}
			}else{
				if(y_even){
					auto a = 0.5f * g(x - x_offset, y - y_offset);
					auto b = 0.5f * g(x - x_offset + 1, y - y_offset);
					return static_cast< value_type >(a + b);
				}else{
					auto aa = 0.25f * g(x - x_offset, y - y_offset);
					auto ab = 0.25f * g(x - x_offset, y - y_offset + 1);
					auto ba = 0.25f * g(x - x_offset + 1, y - y_offset);
					auto bb = 0.25f * g(x - x_offset + 1, y - y_offset + 1);
					return static_cast< value_type >(aa + ab + ba + bb);
				}
			}
		});
	}

	template < size_t Co, size_t Ro, typename M, size_t C, size_t R >
	constexpr auto pass_in(
		dim_t< Co, Ro > const& dims,
		matrix< M, C, R > const& m,
		value_type_t< M > const& default_value
	){
		return pass_in(
			dims.cols().init(), dims.rows().init(), m, default_value
		);
	}


}


#endif
