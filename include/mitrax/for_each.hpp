//-----------------------------------------------------------------------------
// Copyright (c) 2015-2016 Benjamin Buch
//
// https://github.com/bebuch/mitrax
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt)
//-----------------------------------------------------------------------------
#ifndef _mitrax__for_each__hpp_INCLUDED_
#define _mitrax__for_each__hpp_INCLUDED_

#include "sub_matrix.hpp"


namespace mitrax{


	template < typename F, typename ... M, size_t ... C, size_t ... R >
	constexpr void for_each(F&& f, matrix< M, C, R > const& ... images){
		auto size = get_dims(images ...);
		for(std::size_t y = 0; y < size.rows(); ++y){
			for(std::size_t x = 0; x < size.cols(); ++x){
				f(images(x, y) ...);
			}
		}
	}


	template <
		typename F, bool Ccto, col_ct Co, bool Rcto, row_ct Ro,
		typename ... M, size_t ... C, size_t ... R
	> constexpr void for_each_view(
		F&& f,
		col< Ccto, Co > view_cols,
		row< Rcto, Ro > view_rows,
		matrix< M, C, R > const& ... images
	){
		auto cols = get_cols(images ...);
		auto rows = get_rows(images ...);
		for(std::size_t y = 0; y < rows - view_rows; ++y){
			for(std::size_t x = 0; x < cols - view_cols; ++x){
				f(sub_matrix(images, x, y, view_cols, view_rows) ...);
			}
		}
	}

	template <
		typename F, bool Ccto, col_ct Co, bool Rcto, row_ct Ro,
		typename ... M, size_t ... C, size_t ... R
	> constexpr void for_each_view(
		F&& f,
		dim_pair_t< Ccto, Co, Rcto, Ro > const& view_dims,
		matrix< M, C, R > const& ... images
	){
		for_each_view(
			static_cast< F&& >(f),
			view_dims.cols(),
			view_dims.rows(),
			images ...
		);
	}


}


#endif
