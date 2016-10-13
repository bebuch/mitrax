//-----------------------------------------------------------------------------
// Copyright (c) 2015-2016 Benjamin Buch
//
// https://github.com/bebuch/mitrax
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt)
//-----------------------------------------------------------------------------
#ifndef _mitrax__matrix__heap_fwd__hpp_INCLUDED_
#define _mitrax__matrix__heap_fwd__hpp_INCLUDED_

#include "../matrix_interface.hpp"


namespace mitrax::detail{


	template < typename T, size_t C, size_t R >
	class heap_matrix_impl;


}


namespace mitrax{


	template < typename T, size_t Cols, size_t Rows >
	using heap_matrix =
		matrix< detail::heap_matrix_impl< T, Cols, Rows >, Cols, Rows >;

	template < typename T, size_t N >
	using heap_square_matrix = heap_matrix< T, N, N >;

	template < typename T, size_t Rows >
	using heap_col_vector = heap_matrix< T, 1, Rows >;

	template < typename T, size_t Cols >
	using heap_row_vector = heap_matrix< T, Cols, 1 >;


}


namespace mitrax::maker{


	struct heap_t{
		template < typename Iter, bool Cct, size_t C, bool Rct, size_t R >
		heap_matrix< iter_type_t< Iter >, Cct ? C : 0, Rct ? R : 0 >
		by_sequence(col_t< Cct, C > c, row_t< Rct, R > r, Iter iter)const;
	};


}


#endif
