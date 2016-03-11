//-----------------------------------------------------------------------------
// Copyright (c) 2015-2016 Benjamin Buch
//
// https://github.com/bebuch/mitrax
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt)
//-----------------------------------------------------------------------------
#ifndef _mitrax__convert__hpp_INCLUDED_
#define _mitrax__convert__hpp_INCLUDED_

#include "make_matrix.hpp"


namespace mitrax{


	namespace detail{


		template < typename T, typename M >
		struct convert_fn{
			M m;

			constexpr T operator()(size_t x, size_t y){
				return m(x, y);
			}
		};

		template < typename T, typename M >
		constexpr auto make_convert_fn(M&& m){
			return convert_fn< T, M&& >{static_cast< M&& >(m)};
		}


	}


	template <
		typename T, bool Cct1, size_t C1, bool Rct1, size_t R1,
		typename M, size_t C2, size_t R2
	>
	constexpr auto convert(
		matrix< M, C2, R2 >& m,
		col_t< Cct1, C1 > c,
		row_t< Rct1, R1 > r
	){
		auto fn = detail::make_convert_fn< T >(m);
		return make_matrix_by_function(c, r, fn);
	}

	template <
		typename T, bool Cct1, size_t C1, bool Rct1, size_t R1,
		typename M, size_t C2, size_t R2
	>
	constexpr auto convert(
		matrix< M, C2, R2 > const& m,
		col_t< Cct1, C1 > c,
		row_t< Rct1, R1 > r
	){
		auto fn = detail::make_convert_fn< T >(m);
		return make_matrix_by_function(c, r, fn);
	}

	template <
		typename T, bool Cct1, size_t C1, bool Rct1, size_t R1,
		typename M, size_t C2, size_t R2
	>
	constexpr auto convert(
		matrix< M, C2, R2 >&& m,
		col_t< Cct1, C1 > c,
		row_t< Rct1, R1 > r
	){
		auto fn = detail::make_convert_fn< T >(std::move(m));
		return make_matrix_by_function(c, r, fn);
	}


	template <
		bool Cct1, size_t C1, bool Rct1, size_t R1,
		typename M, size_t C2, size_t R2
	>
	constexpr auto convert(
		matrix< M, C2, R2 >& m,
		col_t< Cct1, C1 > c,
		row_t< Rct1, R1 > r
	){
		auto fn = detail::make_convert_fn< fn_xy< M > >(m);
		return make_matrix_by_function(c, r, fn);
	}

	template <
		bool Cct1, size_t C1, bool Rct1, size_t R1,
		typename M, size_t C2, size_t R2
	>
	constexpr auto convert(
		matrix< M, C2, R2 > const& m,
		col_t< Cct1, C1 > c,
		row_t< Rct1, R1 > r
	){
		auto fn = detail::make_convert_fn< fn_xy< M > >(m);
		return make_matrix_by_function(c, r, fn);
	}

	template <
		bool Cct1, size_t C1, bool Rct1, size_t R1,
		typename M, size_t C2, size_t R2
	>
	constexpr auto convert(
		matrix< M, C2, R2 >&& m,
		col_t< Cct1, C1 > c,
		row_t< Rct1, R1 > r
	){
		auto fn = detail::make_convert_fn< fn_xy< M > >(std::move(m));
		return make_matrix_by_function(c, r, fn);
	}

	template < typename T, typename M, size_t C, size_t R >
	constexpr auto convert(matrix< M, C, R >& m){
		auto fn = detail::make_convert_fn< T >(m);
		return make_matrix_by_function(m.dims(), fn);
	}

	template < typename T, typename M, size_t C, size_t R >
	constexpr auto convert(matrix< M, C, R > const& m){
		auto fn = detail::make_convert_fn< T >(m);
		return make_matrix_by_function(m.dims(), fn);
	}

	template < typename T, typename M, size_t C, size_t R >
	constexpr auto convert(matrix< M, C, R >&& m){
		auto fn = detail::make_convert_fn< T >(std::move(m));
		return make_matrix_by_function(m.dims(), fn);
	}

	template < typename M, size_t C, size_t R >
	constexpr auto as_raw_matrix(matrix< M, C, R >& m){
		auto fn = detail::make_convert_fn< fn_xy< M > >(m);
		return make_matrix_by_function(m.dims(), fn);
	}

	template < typename M, size_t C, size_t R >
	constexpr auto as_raw_matrix(matrix< M, C, R > const& m){
		auto fn = detail::make_convert_fn< fn_xy< M > >(m);
		return make_matrix_by_function(m.dims(), fn);
	}

	template < typename M, size_t C, size_t R >
	constexpr auto as_raw_matrix(matrix< M, C, R >&& m){
		auto fn = detail::make_convert_fn< fn_xy< M > >(std::move(m));
		return make_matrix_by_function(m.dims(), fn);
	}



}


#endif
