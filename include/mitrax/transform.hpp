//-----------------------------------------------------------------------------
// Copyright (c) 2015-2016 Benjamin Buch
//
// https://github.com/bebuch/mitrax
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt)
//-----------------------------------------------------------------------------
#ifndef _mitrax__transform__hpp_INCLUDED_
#define _mitrax__transform__hpp_INCLUDED_

#include "multi_invoke_adapter.hpp"
#include "sub_matrix.hpp"


namespace mitrax::detail{


	struct call_func_operator{
		template < typename M >
		constexpr auto operator()(M const& m, size_t x, size_t y)const{
			return m(x, y);
		}
	};

	template < bool Ccto, col_ct Co, bool Rcto, row_ct Ro >
	struct call_sub_matrix{
		dim_pair_t< Ccto, Co, Rcto, Ro > dims;

		template < typename M >
		constexpr auto operator()(M const& m, size_t x, size_t y)const{
			return sub_matrix(m, x, y, dims);
		}
	};

	template < bool Ccto, col_ct Co, bool Rcto, row_ct Ro >
	constexpr auto make_call_sub_matrix(
		dim_pair_t< Ccto, Co, Rcto, Ro > const& dims
	){
		return call_sub_matrix< Ccto, Co, Rcto, Ro >{dims};
	}


}


namespace mitrax{


	template < typename F, typename ... M, size_t ... C, size_t ... R >
	constexpr auto transform(F&& f, matrix< M, C, R > const& ... images){
		return make_matrix_fn(get_dims(images ...), make_multi_invoke_adapter(
			static_cast< F&& >(f), detail::call_func_operator(), images ...
		));
	}


	template <
		typename F, bool Ccto, col_ct Co, bool Rcto, row_ct Ro,
		typename ... M, size_t ... C, size_t ... R
	> constexpr auto transform_per_view(
		F&& f,
		dim_pair_t< Ccto, Co, Rcto, Ro > const& view_dims,
		matrix< M, C, R > const& ... images
	){
		using namespace literals;
		return make_matrix_fn(
			get_dims(images ...) + dim_pair(1_c, 1_r) - view_dims,
			make_multi_invoke_adapter(
				static_cast< F&& >(f),
				detail::make_call_sub_matrix(view_dims),
				images ...
			)
		);
	}


	template <
		typename F, bool Ccto, col_ct Co, bool Rcto, row_ct Ro,
		typename ... M, size_t ... C, size_t ... R
	> constexpr auto transform_per_view(
		F&& f,
		col< Ccto, Co > view_cols,
		row< Rcto, Ro > view_rows,
		matrix< M, C, R > const& ... images
	){
		return transform_per_view(
			static_cast< F&& >(f),
			dim_pair(view_cols, view_rows),
			images ...
		);
	}


}


#endif
