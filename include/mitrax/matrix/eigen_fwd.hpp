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


	template < typename T, col_ct C, row_ct R >
	class eigen_matrix_impl;


}


namespace mitrax{


	template < typename T, col_ct C, row_ct R >
	using eigen_matrix =
		matrix< detail::eigen_matrix_impl< T, C, R >, C, R >;

	template < typename T, dim_ct D >
	using eigen_square_matrix = eigen_matrix< T, col_ct(D), row_ct(D) >;

	template < typename T, row_ct R >
	using eigen_col_vector = eigen_matrix< T, 1_C, R >;

	template < typename T, col_ct C >
	using eigen_row_vector = eigen_matrix< T, C, 1_R >;


}


namespace mitrax::maker{


	struct eigen_t: key{
		template < typename Iter, bool Cct, col_ct C, bool Rct, row_ct R >
		eigen_matrix< iter_type_t< Iter >, Cct ? C : 0_C, Rct ? R : 0_R >
		by_sequence(col< Cct, C > c, row< Rct, R > r, Iter iter)const;
	};


}


#endif
