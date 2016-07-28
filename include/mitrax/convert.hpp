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
		typename M, typename = enable_matrix_t< M >
	> constexpr auto convert(
		M& m,
		col_t< Cct1, C1 > c,
		row_t< Rct1, R1 > r
	){
		return make_matrix_fn(c, r, detail::make_convert_fn< T >(m));
	}

	template <
		typename T, bool Cct1, size_t C1, bool Rct1, size_t R1,
		typename M, typename = enable_matrix_t< M >
	> constexpr auto convert(
		M const& m,
		col_t< Cct1, C1 > c,
		row_t< Rct1, R1 > r
	){
		return make_matrix_fn(c, r, detail::make_convert_fn< T >(m));
	}

	template <
		typename T, bool Cct1, size_t C1, bool Rct1, size_t R1,
		typename M, typename = enable_matrix_t< M >
	> constexpr auto convert(
		M&& m,
		col_t< Cct1, C1 > c,
		row_t< Rct1, R1 > r
	){
		return make_matrix_fn(c, r,
			detail::make_convert_fn< T >(std::move(m)));
	}


	template <
		bool Cct1, size_t C1, bool Rct1, size_t R1,
		typename M, typename = enable_matrix_t< M >
	> constexpr auto convert(
		M& m,
		col_t< Cct1, C1 > c,
		row_t< Rct1, R1 > r
	){
		return make_matrix_fn(c, r, detail::make_convert_fn< fn_xy< M > >(m));
	}

	template <
		bool Cct1, size_t C1, bool Rct1, size_t R1,
		typename M, typename = enable_matrix_t< M >
	> constexpr auto convert(
		M const& m,
		col_t< Cct1, C1 > c,
		row_t< Rct1, R1 > r
	){
		return make_matrix_fn(c, r, detail::make_convert_fn< fn_xy< M > >(m));
	}

	template <
		bool Cct1, size_t C1, bool Rct1, size_t R1,
		typename M, typename = enable_matrix_t< M >
	> constexpr auto convert(
		M&& m,
		col_t< Cct1, C1 > c,
		row_t< Rct1, R1 > r
	){
		return make_matrix_fn(c, r,
			detail::make_convert_fn< fn_xy< M > >(std::move(m)));
	}

	template < typename T, typename M, typename = enable_matrix_t< M > >
	constexpr auto convert(M& m){
		return make_matrix_fn(m.dims(), detail::make_convert_fn< T >(m));
	}

	template < typename T, typename M, typename = enable_matrix_t< M > >
	constexpr auto convert(M const& m){
		return make_matrix_fn(m.dims(), detail::make_convert_fn< T >(m));
	}

	template < typename T, typename M, typename = enable_matrix_t< M > >
	constexpr auto convert(M&& m){
		return make_matrix_fn(m.dims(),
			detail::make_convert_fn< T >(std::move(m)));
	}

	template < typename M, typename = enable_matrix_t< M > >
	constexpr auto as_raw_matrix(M& m){
		return make_matrix_fn(m.dims(),
			detail::make_convert_fn< fn_xy< M > >(m));
	}

	template < typename M, typename = enable_matrix_t< M > >
	constexpr auto as_raw_matrix(M const& m){
		return make_matrix_fn(m.dims(),
			detail::make_convert_fn< fn_xy< M > >(m));
	}

	template < typename M, typename = enable_matrix_t< M > >
	constexpr auto as_raw_matrix(M&& m){
		return make_matrix_fn(m.dims(),
			detail::make_convert_fn< fn_xy< M > >(std::move(m)));
	}



}


#endif
