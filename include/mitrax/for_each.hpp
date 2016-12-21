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

// TODO: Unit-Tests!!!


namespace mitrax{


	template < typename F, typename ... M, col_t ... C, row_t ... R >
	constexpr void for_each(F&& f, matrix< M, C, R > const& ... images){
		auto size = get_dims(images ...);
		for(auto r = 0_r; r < size.rows(); ++r){
			for(auto c = 0_c; c < size.cols(); ++c){
				f(images(c, r) ...);
			}
		}
	}


	template <
		typename F, bool Ccto, col_t Co, bool Rcto, row_t Ro,
		typename ... M, col_t ... C, row_t ... R
	> constexpr void for_each_view(
		F&& f,
		col< Ccto, Co > view_cols,
		row< Rcto, Ro > view_rows,
		matrix< M, C, R > const& ... images
	){
		auto cols = get_cols(images ...);
		auto rows = get_rows(images ...);
		for(auto r = 0; r < rows - view_rows; ++r){
			for(auto c = 0; c < cols - view_cols; ++c){
				f(sub_matrix(images, c, r, view_cols, view_rows) ...);
			}
		}
	}

	template <
		typename F, bool Ccto, col_t Co, bool Rcto, row_t Ro,
		typename ... M, col_t ... C, row_t ... R
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
