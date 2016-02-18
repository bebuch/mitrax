//-----------------------------------------------------------------------------
// Copyright (c) 2015 Benjamin Buch
//
// https://github.com/bebuch/mitrax
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt)
//-----------------------------------------------------------------------------
#ifndef _mitrax__transform__hpp_INCLUDED_
#define _mitrax__transform__hpp_INCLUDED_

#include "multi_invoke_adapter.hpp"
#include "matrix.hpp"


namespace mitrax{


	namespace detail{


		struct call_func_operator{
			template < typename M >
			constexpr auto operator()(M const& m, size_t x, size_t y)const{
				return m(x, y);
			}
		};

		template < size_t Co, size_t Ro >
		struct call_sub_matrix{
			dims_t< Co, Ro > dims;

			template < typename M >
			constexpr auto operator()(M const& m, size_t x, size_t y)const{
				return m.sub_matrix(x, y, dims);
			}
		};

		template < size_t Co, size_t Ro >
		constexpr auto make_call_sub_matrix(dims_t< Co, Ro > const& dims){
			return call_sub_matrix< Co, Ro >{dims};
		}


	}


	template < typename F, typename ... M, size_t ... C, size_t ... R >
	constexpr auto transform(F const& f, matrix< M, C, R > const& ... images){
		return make_matrix_by_function(get_dims(images ...),
			make_multi_invoke_adapter(
				f, detail::call_func_operator(), images ...
			)
		);
	}


	template <
		typename F, size_t Co, size_t Ro, 
		typename ... M, size_t ... C, size_t ... R
	> constexpr auto transform_per_view(
		F const& f,
		dims_t< Co, Ro > const& view_dims,
		matrix< M, C, R > const& ... images
	){
		using namespace literals;
		return make_matrix_by_function(
			get_dims(images ...) + dims(1_C, 1_R) - view_dims,
			make_multi_invoke_adapter(
				f, detail::make_call_sub_matrix(view_dims), images ...
			)
		);
	}


	template <
		typename F, bool Ccto, size_t Co, bool Rcto, size_t Ro, 
		typename ... M, size_t ... C, size_t ... R
	> constexpr auto transform_per_view(
		F const& f,
		col_init_t< Ccto, Co > view_cols,
		row_init_t< Rcto, Ro > view_rows,
		matrix< M, C, R > const& ... images
	){
		return transform_per_view(f, dims(view_cols, view_rows), images ...);
	}


}


#endif
