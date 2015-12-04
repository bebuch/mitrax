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

#include "matrix.hpp"


namespace mitrax{


	namespace detail{


		template < typename F, typename S, typename ... T >
		struct transform_t{
			constexpr transform_t(
				F const& f, S const& single_call, T const& ... arg
			): f_(f), single_call_(single_call), arg_(arg ...) {}

			F const& f_;
			S const& single_call_;
			std::tuple< T const& ... > arg_;

			template < typename ... A >
			constexpr auto operator()(A&& ... arg)const{
				return (*this)(std::index_sequence_for< T ... >(), arg ...);
			}

			template < size_t ... I, typename ... A >
			constexpr auto operator()(
				std::index_sequence< I ... >, A&& ... arg
			)const{
				return f_(single_call_(std::get< I >(arg_), arg ...) ...);
			}
		};

		template < typename F, typename S, typename ... T >
		constexpr auto
		make_invoke(F const& f, S const& single_call, T const& ... arg){
			return transform_t< F, S, T ... >(f, single_call, arg ...);
		}

		struct call_func_operator{
			template < typename M >
			constexpr auto operator()(M const& m, size_t x, size_t y)const{
				return m(x, y);
			}
		};

		template < size_t Co, size_t Ro >
		struct call_sub_matrix{
			dim_t< Co, Ro > dims;

			template < typename M >
			constexpr auto operator()(M const& m, size_t x, size_t y)const{
				return m.sub_matrix(x, y, dims);
			}
		};

		template < size_t Co, size_t Ro >
		constexpr auto make_call_sub_matrix(dim_t< Co, Ro > const& dims){
			return call_sub_matrix< Co, Ro >{dims};
		}


	}


	template < typename F, typename ... M, size_t ... C, size_t ... R >
	constexpr auto transform(F const& f, matrix< M, C, R > const& ... images){
		return make_matrix_by_function(get_dims(images ...),
			detail::make_invoke(f, detail::call_func_operator(), images ...));
	}


	template <
		typename F, size_t Co, size_t Ro, 
		typename ... M, size_t ... C, size_t ... R
	> constexpr auto transform_per_view(
		F const& f,
		dim_t< Co, Ro > const& view_dims,
		matrix< M, C, R > const& ... images
	){
		using namespace literals;
		return make_matrix_by_function(
			get_dims(images ...) + dims(1_C, 1_R) - view_dims,
			detail::make_invoke(
				f, detail::make_call_sub_matrix(view_dims),
				images ...
			));
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
