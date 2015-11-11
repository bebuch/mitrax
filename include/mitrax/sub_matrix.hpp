//-----------------------------------------------------------------------------
// Copyright (c) 2015 Benjamin Buch
//
// https://github.com/bebuch/mitrax
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt)
//-----------------------------------------------------------------------------
#ifndef _mitrax__sub_matrix__hpp_INCLUDED_
#define _mitrax__sub_matrix__hpp_INCLUDED_

#include "integer.hpp"

#include <boost/container/vector.hpp>

#include <array>
#include <utility>


namespace mitrax{


	template < typename M, size_t Cols, size_t Rows >
	class matrix;


	namespace detail{


		template <
			typename T, size_t C1, size_t R1,
			typename M, size_t C2, size_t R2,
			size_t ... I
		>
		constexpr auto sub_matrix_to_array(
			size_t x,
			size_t y,
			col_t< C1 > /*c*/,
			row_t< R1 > /*r*/,
			matrix< M, C2, R2 > const& m,
			std::index_sequence< I ... >
		){
			return std::array< T, C1 * R1 >{{
				static_cast< T >(m(x + I % C1, y + I / C1)) ...
			}};
		}

		template <
			typename T,
			typename M, size_t C, size_t R
		>
		auto sub_matrix_to_vector(
			size_t x,
			size_t y,
			size_t c,
			size_t r,
			matrix< M, C, R > const& m
		){
			boost::container::vector< T > result;
			result.reserve(c * r);
			for(size_t yi = 0; yi < c; ++yi){
				for(size_t xi = 0; xi < r; ++xi){
					result.emplace_back(m(x + xi, y + yi));
				}
			}
			return result;
		}


		template <
			typename T, bool Cb, size_t C1, bool Rb, size_t R1,
			typename M, size_t C2, size_t R2
		>
		constexpr auto sub_matrix(
			std::true_type /*to_static*/,
			size_t x,
			size_t y,
			col_lit< Cb, C1 > c,
			row_lit< Rb, R1 > r,
			matrix< M, C2, R2 > const& m
		){
			return sub_matrix_to_array< T >(
				x, y, c.get(), r.get(), m,
				std::make_index_sequence< C1 * R1 >()
			);
		}

		template <
			typename T, bool Cb, size_t C1, bool Rb, size_t R1,
			typename M, size_t C2, size_t R2
		>
		auto sub_matrix(
			std::false_type /*to_static*/,
			size_t x,
			size_t y,
			col_lit< Cb, C1 > c,
			row_lit< Rb, R1 > r,
			matrix< M, C2, R2 > const& m
		){
			return sub_matrix_to_vector< T >(x, y, c, r, m);
		}

	}


	template <
		typename T, bool Cb, size_t C1, bool Rb, size_t R1,
		typename M, size_t C2, size_t R2
	>
	constexpr auto sub_matrix(
		size_t x,
		size_t y,
		col_lit< Cb, C1 > c,
		row_lit< Rb, R1 > r,
		matrix< M, C2, R2 > const& m
	){
		return detail::sub_matrix< T >(bool_t< Cb && Rb >(), x, y, c, r, m);
	}

}


#endif
