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


	template < typename T, size_t Cols, size_t Rows >
	using std_matrix = std::conditional_t< Cols != 0 && Rows != 0,
		stack_matrix< T, Cols, Rows >, heap_matrix< T, Cols, Rows > >;

	template < typename T, size_t N >
	using std_square_matrix = std_matrix< T, N, N >;

	template < typename T, size_t Rows >
	using std_col_vector = std_matrix< T, 1, Rows >;

	template < typename T, size_t Cols >
	using std_row_vector = std_matrix< T, Cols, 1 >;

	template < typename T >
	using std_bitmap = std_matrix< T, 0, 0 >;


}


namespace mitrax::maker{


	struct std_t{
		template < typename Iter, bool Cct, size_t C, bool Rct, size_t R >
		constexpr std_matrix< iter_type_t< Iter >, Cct ? C : 0, Rct ? R : 0 >
		by_sequence(col_t< Cct, C > c, row_t< Rct, R > r, Iter iter)const;
	};


	template < typename Iter, bool Cct, size_t C, bool Rct, size_t R >
	constexpr std_matrix< iter_type_t< Iter >, Cct ? C : 0, Rct ? R : 0 >
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
