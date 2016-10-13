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


}


#endif
