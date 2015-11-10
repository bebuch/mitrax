//-----------------------------------------------------------------------------
// Copyright (c) 2015 Benjamin Buch
//
// https://github.com/bebuch/mitrax
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt)
//-----------------------------------------------------------------------------
#ifndef _mitrax__compare__hpp_INCLUDED_
#define _mitrax__compare__hpp_INCLUDED_

#include "matrix.hpp"

#include <stdexcept>


namespace mitrax{


	template <
		typename M1,
		typename M2,
		size_t C1,
		size_t R1,
		size_t C2,
		size_t R2
	> constexpr bool operator==(
		matrix< M1, C1, R1 > const& m1,
		matrix< M2, C2, R2 > const& m2
	){
		static_assert(
			(C1 == 0 || C2 == 0 || C1 == C2) &&
			(R1 == 0 || R2 == 0 || R1 == R2),
			"Matrix dimensions not compatible"
		);

		// Compiler should skip this for compile time dimensions
		if(m1.cols() != m2.cols() || m1.rows() != m2.rows()){
			throw std::logic_error(
				"matrix dimensions not compatible while comparing"
			);
		}

		// Compiler may optimize with the compile time dimension
		size_t cols = C1 == 0 ? m2.cols() : m1.cols();
		size_t rows = R1 == 0 ? m2.rows() : m1.rows();

		for(size_t y = 0; y < rows; ++y){
			for(size_t x = 0; x < cols; ++x){
				if(m1(x, y) != m2(x, y)) return false;
			}
		}

		return true;
	}

	template <
		typename M1,
		typename M2,
		size_t C1,
		size_t R1,
		size_t C2,
		size_t R2
	> constexpr bool operator!=(
		matrix< M1, C1, R1 > const& m1,
		matrix< M2, C2, R2 > const& m2
	){
		return !(m1 == m2);
	}


}


#endif
