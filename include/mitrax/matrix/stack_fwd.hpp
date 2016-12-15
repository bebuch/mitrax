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


	template < typename T, col_ct C, row_ct R >
	class stack_matrix_impl;


}


namespace mitrax{


	template < typename T, col_ct C, row_ct R >
	using stack_matrix =
		matrix< detail::stack_matrix_impl< T, C, R >, C, R >;

	template < typename T, dim_ct D >
	using stack_square_matrix = stack_matrix< T, col_ct(D), row_ct(D) >;

	template < typename T, row_ct R >
	using stack_col_vector = stack_matrix< T, 1_C, R >;

	template < typename T, col_ct C >
	using stack_row_vector = stack_matrix< T, C, 1_R >;


}


namespace mitrax::maker{


	struct stack_t: key{
		template < typename Iter, bool Cct, col_ct C, bool Rct, row_ct R >
		constexpr
		stack_matrix< iter_type_t< Iter >, Cct ? C : 0_C, Rct ? R : 0_R >
		by_sequence(col_t< Cct, C > c, row_t< Rct, R > r, Iter iter)const;
	};


}


#endif
