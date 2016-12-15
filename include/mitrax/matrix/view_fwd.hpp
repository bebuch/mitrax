//-----------------------------------------------------------------------------
// Copyright (c) 2016 Benjamin Buch
//
// https://github.com/bebuch/mitrax
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt)
//-----------------------------------------------------------------------------
#ifndef _mitrax__matrix__view_fwd__hpp_INCLUDED_
#define _mitrax__matrix__view_fwd__hpp_INCLUDED_

#include "../matrix_interface.hpp"


namespace mitrax::detail{


	template < typename T, bool RowOrder, col_ct C, row_ct R >
	class view_matrix_impl;

	template < typename T, bool RowOrder, col_ct C, row_ct R >
	class const_view_matrix_impl;


}


namespace mitrax{


	template < typename T, bool RowOrder, col_ct C, row_ct R >
	using view_matrix = matrix< detail::view_matrix_impl
		< T, RowOrder, C, R >, C, R >;

	template < typename T, bool RowOrder, dim_ct D >
	using view_square_matrix =
		view_matrix< T, RowOrder, col_ct(D), row_ct(D) >;

	template < typename T, bool RowOrder, row_ct R >
	using view_col_vector = view_matrix< T, RowOrder, 1_C, R >;

	template < typename T, bool RowOrder, col_ct C >
	using view_row_vector = view_matrix< T, RowOrder, C, 1_R >;

	template < typename T, bool RowOrder >
	using view_bitmap = view_matrix< T, RowOrder, 0_C, 0_R >;


	template < typename T, bool RowOrder, col_ct C, row_ct R >
	using const_view_matrix = matrix< detail::const_view_matrix_impl
		< T, RowOrder, C, R >, C, R >;

	template < typename T, bool RowOrder, dim_ct D >
	using const_view_square_matrix =
		const_view_matrix< T, RowOrder, col_ct(D), row_ct(D) >;

	template < typename T, bool RowOrder, row_ct R >
	using const_view_col_vector = const_view_matrix< T, RowOrder, 1_C, R >;

	template < typename T, bool RowOrder, col_ct C >
	using const_view_row_vector = const_view_matrix< T, RowOrder, C, 1_R >;

	template < typename T, bool RowOrder >
	using const_view_bitmap = const_view_matrix< T, RowOrder, 0_C, 0_R >;


}


namespace mitrax::maker{


	struct view_t: key{
		template < typename T, typename MemoryOrder = memory_order::row_t,
			bool Cct, col_ct C, bool Rct, row_ct R >
		constexpr auto by_object(
			col_t< Cct, C > c, row_t< Rct, R > r,
			T& object, MemoryOrder = memory_order::row
		)const;
	};

	struct const_view_t: key{
		template < typename T, typename MemoryOrder = memory_order::row_t,
			bool Cct, col_ct C, bool Rct, row_ct R >
		constexpr auto by_object(
			col_t< Cct, C > c, row_t< Rct, R > r,
			T const& object, MemoryOrder = memory_order::row
		)const;
	};


}


#endif
