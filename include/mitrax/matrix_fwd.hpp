//-----------------------------------------------------------------------------
// Copyright (c) 2015 Benjamin Buch
//
// https://github.com/bebuch/mitrax
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt)
//-----------------------------------------------------------------------------
#ifndef _mitrax__matrix_fwd__hpp_INCLUDED_
#define _mitrax__matrix_fwd__hpp_INCLUDED_

#include "dim.hpp"


namespace mitrax{


	template < typename M, size_t Cols, size_t Rows >
	class matrix;

	template < typename M, size_t N >
	using square_matrix = matrix< M, N, N >;

	template < typename M, size_t Rows >
	using col_vector = matrix< M, 1, Rows >;

	template < typename M, size_t Cols >
	using row_vector = matrix< M, Cols, 1 >;

	template < typename M >
	using bitmap = matrix< M, 0, 0 >;


	namespace detail{

		template < typename T, size_t Cols, size_t Rows >
		class raw_matrix_impl;

	}

	template < typename T, size_t Cols, size_t Rows >
	using raw_matrix =
		matrix< detail::raw_matrix_impl< T, Cols, Rows >, Cols, Rows >;

	template < typename T, size_t N >
	using raw_square_matrix = raw_matrix< T, N, N >;

	template < typename T, size_t Rows >
	using raw_col_vector = raw_matrix< T, 1, Rows >;

	template < typename T, size_t Cols >
	using raw_row_vector = raw_matrix< T, Cols, 1 >;

	template < typename T >
	using raw_bitmap = raw_matrix< T, 0, 0 >;


	using bitmap_col_t = col_t< false, 0 >;

	using bitmap_row_t = row_t< false, 0 >;

	using bitmap_dims_t = dims_t< 0, 0 >;


}


#endif
