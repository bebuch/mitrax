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

			constexpr T operator()(size_t x, size_t y)const{
				return m(x, y);
			}
		};

		template < typename T, typename M >
		constexpr auto make_convert_fn(M&& m){
			auto ref = forward_ref(static_cast< M&& >(m));
			return convert_fn< T, decltype(ref) >{ref};
		}


	}


	template <
		typename T, bool Cct1, col_ct C1, bool Rct1, row_ct R1,
		typename M, col_ct C2, row_ct R2
	> constexpr auto convert(
		matrix< M, C2, R2 >& m,
		col< Cct1, C1 > c,
		row< Rct1, R1 > r
	){
		return make_matrix_fn(c, r, detail::make_convert_fn< T >(m));
	}

	template <
		typename T, bool Cct1, col_ct C1, bool Rct1, row_ct R1,
		typename M, col_ct C2, row_ct R2
	> constexpr auto convert(
		matrix< M, C2, R2 > const& m,
		col< Cct1, C1 > c,
		row< Rct1, R1 > r
	){
		return make_matrix_fn(c, r, detail::make_convert_fn< T >(m));
	}

	template <
		typename T, bool Cct1, col_ct C1, bool Rct1, row_ct R1,
		typename M, col_ct C2, row_ct R2
	> constexpr auto convert(
		matrix< M, C2, R2 >&& m,
		col< Cct1, C1 > c,
		row< Rct1, R1 > r
	){
		return make_matrix_fn(c, r,
			detail::make_convert_fn< T >(std::move(m)));
	}


	template <
		bool Cct1, col_ct C1, bool Rct1, row_ct R1,
		typename M, col_ct C2, row_ct R2
	> constexpr auto convert(
		matrix< M, C2, R2 >& m,
		col< Cct1, C1 > c,
		row< Rct1, R1 > r
	){
		return make_matrix_fn(c, r,
			detail::make_convert_fn< value_type_t< M > >(m));
	}

	template <
		bool Cct1, col_ct C1, bool Rct1, row_ct R1,
		typename M, col_ct C2, row_ct R2
	> constexpr auto convert(
		matrix< M, C2, R2 > const& m,
		col< Cct1, C1 > c,
		row< Rct1, R1 > r
	){
		return make_matrix_fn(c, r,
			detail::make_convert_fn< value_type_t< M > >(m));
	}

	template <
		bool Cct1, col_ct C1, bool Rct1, row_ct R1,
		typename M, col_ct C2, row_ct R2
	> constexpr auto convert(
		matrix< M, C2, R2 >&& m,
		col< Cct1, C1 > c,
		row< Rct1, R1 > r
	){
		return make_matrix_fn(c, r,
			detail::make_convert_fn< value_type_t< M > >(std::move(m)));
	}

	template < typename T, typename M, col_ct C, row_ct R >
	constexpr auto convert(matrix< M, C, R >& m){
		return make_matrix_fn(m.dims(), detail::make_convert_fn< T >(m));
	}

	template < typename T, typename M, col_ct C, row_ct R >
	constexpr auto convert(matrix< M, C, R > const& m){
		return make_matrix_fn(m.dims(), detail::make_convert_fn< T >(m));
	}

	template < typename T, typename M, col_ct C, row_ct R >
	constexpr auto convert(matrix< M, C, R >&& m){
		return make_matrix_fn(m.dims(),
			detail::make_convert_fn< T >(std::move(m)));
	}

	template < typename M, col_ct C, row_ct R >
	constexpr auto as_std_matrix(matrix< M, C, R >& m){
		return make_matrix_fn(m.dims(),
			detail::make_convert_fn< value_type_t< M > >(m));
	}

	template < typename M, col_ct C, row_ct R >
	constexpr auto as_std_matrix(matrix< M, C, R > const& m){
		return make_matrix_fn(m.dims(),
			detail::make_convert_fn< value_type_t< M > >(m));
	}

	template < typename M, col_ct C, row_ct R >
	constexpr auto as_std_matrix(matrix< M, C, R >&& m){
		return make_matrix_fn(m.dims(),
			detail::make_convert_fn< value_type_t< M > >(std::move(m)));
	}



}


#endif
