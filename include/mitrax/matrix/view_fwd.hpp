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


	template < typename Object, bool RowOrder, size_t C, size_t R >
	class view_matrix_impl;

	template < typename Object, bool RowOrder, size_t C, size_t R >
	class const_view_matrix_impl;


}


namespace mitrax{


	template < typename Object, bool RowOrder, size_t Cols, size_t Rows >
	using view_matrix = matrix< detail::view_matrix_impl
		< Object, RowOrder, Cols, Rows >, Cols, Rows >;

	template < typename Object, bool RowOrder, size_t N >
	using view_square_matrix =
		view_matrix< Object, RowOrder, N, N >;

	template < typename Object, bool RowOrder, size_t Rows >
	using view_col_vector =
		view_matrix< Object, RowOrder, 1, Rows >;

	template < typename Object, bool RowOrder, size_t Cols >
	using view_row_vector =
		view_matrix< Object, RowOrder, Cols, 1 >;

	template < typename Object, bool RowOrder >
	using view_bitmap = view_matrix< Object, RowOrder, 0, 0 >;


	template < typename Object, bool RowOrder, size_t Cols, size_t Rows >
	using const_view_matrix = matrix< detail::const_view_matrix_impl
		< Object, RowOrder, Cols, Rows >, Cols, Rows >;

	template < typename Object, bool RowOrder, size_t N >
	using const_view_square_matrix =
		const_view_matrix< Object, RowOrder, N, N >;

	template < typename Object, bool RowOrder, size_t Rows >
	using const_view_col_vector =
		const_view_matrix< Object, RowOrder, 1, Rows >;

	template < typename Object, bool RowOrder, size_t Cols >
	using const_view_row_vector =
		const_view_matrix< Object, RowOrder, Cols, 1 >;

	template < typename Object, bool RowOrder >
	using const_view_bitmap = const_view_matrix< Object, RowOrder, 0, 0 >;


}


namespace mitrax::maker{


	struct view_t{
		template < typename Object, typename MemoryOrder = memory_order::row_t,
		bool Cct, size_t C, bool Rct, size_t R >
		constexpr auto by_object(
			col_t< Cct, C > c, row_t< Rct, R > r,
			Object& object, MemoryOrder = memory_order::row
		)const;
	};

	struct const_view_t{
		template < typename Object, typename MemoryOrder = memory_order::row_t,
		bool Cct, size_t C, bool Rct, size_t R >
		constexpr auto by_object(
			col_t< Cct, C > c, row_t< Rct, R > r,
			Object const& object, MemoryOrder = memory_order::row
		)const;
	};


}


#endif
