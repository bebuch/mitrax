//-----------------------------------------------------------------------------
// Copyright (c) 2015-2016 Benjamin Buch
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


	template < typename T, size_t Cols, size_t Rows >
	class raw_matrix;

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
