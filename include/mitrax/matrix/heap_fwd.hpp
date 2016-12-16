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


	template < typename T, col_t C, row_t R >
	class heap_matrix_impl;


}


namespace mitrax{


	template < typename T, col_t C, row_t R >
	using heap_matrix =
		matrix< detail::heap_matrix_impl< T, C, R >, C, R >;

	template < typename T, dim_t D >
	using heap_square_matrix = heap_matrix< T, col_t(D), row_t(D) >;

	template < typename T, row_t R >
	using heap_col_vector = heap_matrix< T, 1_C, R >;

	template < typename T, col_t C >
	using heap_row_vector = heap_matrix< T, C, 1_R >;


}


namespace mitrax::maker{


	struct heap_t: key{
		template < typename Iter, bool Cct, col_t C, bool Rct, row_t R >
		heap_matrix< iter_type_t< Iter >, Cct ? C : 0_C, Rct ? R : 0_R >
		by_sequence(col< Cct, C > c, row< Rct, R > r, Iter iter)const;
	};


}


#endif
