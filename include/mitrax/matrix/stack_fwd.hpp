//-----------------------------------------------------------------------------
// Copyright (c) 2015-2016 Benjamin Buch
//
// https://github.com/bebuch/mitrax
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt)
//-----------------------------------------------------------------------------
#ifndef _mitrax__matrix__stack_fwd__hpp_INCLUDED_
#define _mitrax__matrix__stack_fwd__hpp_INCLUDED_

#include "../matrix_interface.hpp"


namespace mitrax::detail{


	template < typename T, size_t C, size_t R >
	class stack_matrix_impl;


}


namespace mitrax{


	template < typename T, size_t Cols, size_t Rows >
	using stack_matrix =
		matrix< detail::stack_matrix_impl< T, Cols, Rows >, Cols, Rows >;

	template < typename T, size_t N >
	using stack_square_matrix = stack_matrix< T, N, N >;

	template < typename T, size_t Rows >
	using stack_col_vector = stack_matrix< T, 1, Rows >;

	template < typename T, size_t Cols >
	using stack_row_vector = stack_matrix< T, Cols, 1 >;


}


namespace mitrax::maker{


	struct stack_t{
		template < typename Iter, bool Cct, size_t C, bool Rct, size_t R >
		constexpr stack_matrix< iter_type_t< Iter >, Cct ? C : 0, Rct ? R : 0 >
		by_sequence(col_t< Cct, C > c, row_t< Rct, R > r, Iter iter)const;
	};


}


#endif
