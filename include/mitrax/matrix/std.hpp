//-----------------------------------------------------------------------------
// Copyright (c) 2015-2016 Benjamin Buch
//
// https://github.com/bebuch/mitrax
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt)
//-----------------------------------------------------------------------------
#ifndef _mitrax__matrix__std__hpp_INCLUDED_
#define _mitrax__matrix__std__hpp_INCLUDED_

#include "stack.hpp"
#include "heap.hpp"


namespace mitrax{


	template < typename T, col_ct C, row_ct R >
	using std_matrix = std::conditional_t< C != 0_C && R != 0_R,
		stack_matrix< T, C, R >, heap_matrix< T, C, R > >;

	template < typename T, dim_ct D >
	using std_square_matrix = std_matrix< T, col_ct(D), row_ct(D) >;

	template < typename T, row_ct R >
	using std_col_vector = std_matrix< T, 1_C, R >;

	template < typename T, col_ct C >
	using std_row_vector = std_matrix< T, C, 1_R >;

	template < typename T >
	using std_bitmap = std_matrix< T, 0_C, 0_R >;


}


namespace mitrax::maker{


	struct std_t: key{
		template < typename Iter, bool Cct, col_ct C, bool Rct, row_ct R >
		constexpr
		std_matrix< iter_type_t< Iter >, Cct ? C : 0_C, Rct ? R : 0_R >
		by_sequence(col_t< Cct, C > c, row_t< Rct, R > r, Iter iter)const;
	};


	template < typename Iter, bool Cct, col_ct C, bool Rct, row_ct R >
	constexpr std_matrix< iter_type_t< Iter >, Cct ? C : 0_C, Rct ? R : 0_R >
	std_t::by_sequence(col_t< Cct, C > c, row_t< Rct, R > r, Iter iter)const{
		if constexpr(Cct && Rct){
			return stack.by_sequence(c, r, iter);
		}else{
			return heap.by_sequence(c, r, iter);
		}
	}

	constexpr auto std = std_t();


}


#endif
