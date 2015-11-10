//-----------------------------------------------------------------------------
// Copyright (c) 2015 Benjamin Buch
//
// https://github.com/bebuch/mitrax
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt)
//-----------------------------------------------------------------------------
#ifndef _mitrax__matrix_swap__hpp_INCLUDED_
#define _mitrax__matrix_swap__hpp_INCLUDED_

#include "matrix.hpp"

#include <type_traits>
#include <utility>


// TODO: Faster implementation
namespace mitrax{


	struct swap_rows_t{
		constexpr swap_rows_t(){}

		template <
			typename M1,
			size_t C1,
			size_t R1,
			typename M2,
			size_t C2,
			size_t R2,
			std::enable_if_t<
				std::is_same< value_type_t< M1 >, value_type_t< M2 > >::value
			>* = nullptr
		> constexpr void operator()(
			matrix< M1, C1, R1 >& m1,
			size_t i1,
			matrix< M2, C2, R2 >& m2,
			size_t i2
		)const{
			static_assert(
				(C1 == 0 || C2 == 0 || C1 == C2),
				"Matrix dimensions not compatible"
			);

			// Compiler should skip this for compile time dimensions
			if(m1.cols() != m2.cols()){
				throw std::logic_error(
					"matrix dimensions not compatible while comparing"
				);
			}

			if(m1.rows() <= i1 || m2.rows() <= i2){
				throw std::out_of_range("matrix swap_rows");
			}

			for(size_t i = 0; i < m1.cols(); ++i){
				using std::swap;
				swap(m1(i, i1), m2(i, i2));
			}
		}

		template <
			typename M,
			size_t C,
			size_t R
		> constexpr void operator()(
			matrix< M, C, R >& m,
			size_t i1,
			size_t i2
		)const{
			operator()(m, i1, m, i2);
		}
	};

	constexpr swap_rows_t swap_rows;


	struct swap_cols_t{
		constexpr swap_cols_t(){}

		template <
			typename M1,
			size_t C1,
			size_t R1,
			typename M2,
			size_t C2,
			size_t R2,
			std::enable_if_t<
				std::is_same< value_type_t< M1 >, value_type_t< M2 > >::value
			>* = nullptr
		> constexpr void operator()(
			matrix< M1, C1, R1 >& m1,
			size_t i1,
			matrix< M2, C2, R2 >& m2,
			size_t i2
		)const{
			static_assert(
				(R1 == 0 || R2 == 0 || R1 == R2),
				"Matrix dimensions not compatible"
			);

			// Compiler should skip this for compile time dimensions
			if(m1.row() != m2.row()){
				throw std::logic_error(
					"matrix dimensions not compatible while comparing"
				);
			}

			if(m1.cols() <= i1 || m2.cols() <= i2){
				throw std::out_of_range("matrix swap_cols");
			}

			for(size_t i = 0; i < m1.row(); ++i){
				using std::swap;
				swap(m1(i, i1), m2(i, i2));
			}
		}

		template <
			typename M,
			size_t C,
			size_t R
		> constexpr void operator()(
			matrix< M, C, R >& m,
			size_t i1,
			size_t i2
		)const{
			operator()(m, i1, m, i2);
		}
	};

	constexpr swap_cols_t swap_cols;


}


#endif
