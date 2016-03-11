//-----------------------------------------------------------------------------
// Copyright (c) 2015-2016 Benjamin Buch
//
// https://github.com/bebuch/mitrax
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt)
//-----------------------------------------------------------------------------
#ifndef _mitrax__swap_matrix__hpp_INCLUDED_
#define _mitrax__swap_matrix__hpp_INCLUDED_

#include "matrix_interface.hpp"

#include <type_traits>
#include <utility>


// TODO: Faster implementation
namespace mitrax{


	struct swap_rows_t{
		constexpr swap_rows_t(){}

		template <
			typename M1, size_t C1, size_t R1,
			typename M2, size_t C2, size_t R2,
			std::enable_if_t<
				std::is_same< value_type_t< M1 >, value_type_t< M2 > >::value
			>* = nullptr
		> constexpr void operator()(
			matrix< M1, C1, R1 >& m1,
			size_t i1,
			matrix< M2, C2, R2 >& m2,
			size_t i2
		)const{
			if(m1.rows() <= i1 || m2.rows() <= i2){
				throw std::out_of_range("matrix swap_rows");
			}

			auto cols = get_cols(m1, m2);

			for(size_t i = 0; i < cols; ++i){
				using std::swap;
				swap(m1(i, i1), m2(i, i2));
			}
		}

		template < typename M, size_t C, size_t R >
		constexpr void
		operator()(matrix< M, C, R >& m, size_t i1, size_t i2)const{
			(*this)(m, i1, m, i2);
		}
	};

	constexpr swap_rows_t swap_rows;


	struct swap_cols_t{
		constexpr swap_cols_t(){}

		template <
			typename M1, size_t C1, size_t R1,
			typename M2, size_t C2, size_t R2,
			std::enable_if_t<
				std::is_same< value_type_t< M1 >, value_type_t< M2 > >::value
			>* = nullptr
		> constexpr void operator()(
			matrix< M1, C1, R1 >& m1,
			size_t i1,
			matrix< M2, C2, R2 >& m2,
			size_t i2
		)const{
			if(m1.cols() <= i1 || m2.cols() <= i2){
				throw std::out_of_range("matrix swap_cols");
			}

			auto rows = get_rows(m1, m2);

			for(size_t i = 0; i < rows; ++i){
				using std::swap;
				swap(m1(i1, i), m2(i2, i));
			}
		}

		template < typename M, size_t C, size_t R >
		constexpr void
		operator()(matrix< M, C, R >& m, size_t i1, size_t i2)const{
			operator()(m, i1, m, i2);
		}
	};

	constexpr swap_cols_t swap_cols;


}


#endif
