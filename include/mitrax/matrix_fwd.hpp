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


	template < typename M, col_ct C, row_ct R >
	class matrix;

	template < typename M, dim_ct D >
	using square_matrix = matrix< M, col_ct(D), row_ct(D) >;

	template < typename M, row_ct R >
	using col_vector = matrix< M, 1_C, R >;

	template < typename M, col_ct C >
	using row_vector = matrix< M, C, 1_R >;

	template < typename M >
	using bitmap = matrix< M, 0_C, 0_R >;


}


#endif
