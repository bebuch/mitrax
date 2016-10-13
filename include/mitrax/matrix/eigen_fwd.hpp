//-----------------------------------------------------------------------------
// Copyright (c) 2016 Benjamin Buch
//
// https://github.com/bebuch/mitrax
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt)
//-----------------------------------------------------------------------------
#ifndef _mitrax__matrix__eigen_fwd__hpp_INCLUDED_
#define _mitrax__matrix__eigen_fwd__hpp_INCLUDED_

#include "../matrix_interface.hpp"


namespace mitrax::detail{


	template < typename T, size_t C, size_t R >
	class eigen_matrix_impl;


}


namespace mitrax{


	template < typename T, size_t Cols, size_t Rows >
	using eigen_matrix =
		matrix< detail::eigen_matrix_impl< T, Cols, Rows >, Cols, Rows >;

	template < typename T, size_t N >
	using eigen_square_matrix = eigen_matrix< T, N, N >;

	template < typename T, size_t Rows >
	using eigen_col_vector = eigen_matrix< T, 1, Rows >;

	template < typename T, size_t Cols >
	using eigen_row_vector = eigen_matrix< T, Cols, 1 >;


}


namespace mitrax::maker{


	struct eigen_t{
		template < typename Iter, bool Cct, size_t C, bool Rct, size_t R >
		eigen_matrix< iter_type_t< Iter >, Cct ? C : 0, Rct ? R : 0 >
		by_sequence(col_t< Cct, C > c, row_t< Rct, R > r, Iter iter)const;
	};


}


#endif
