//-----------------------------------------------------------------------------
// Copyright (c) 2015-2018 Benjamin Buch
//
// https://github.com/bebuch/mitrax
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt)
//-----------------------------------------------------------------------------
#ifndef _mitrax__compare__hpp_INCLUDED_
#define _mitrax__compare__hpp_INCLUDED_

#include "matrix_interface.hpp"

#include <stdexcept>


namespace mitrax{


	template <
		typename M1, col_t C1, row_t R1,
		typename M2, col_t C2, row_t R2
	> constexpr bool operator==(
		matrix< M1, C1, R1 > const& m1,
		matrix< M2, C2, R2 > const& m2
	){
		auto size = get_dims(m2, m1);

		for(auto r = 0_r; r < size.rows(); ++r){
			for(auto c = 0_c; c < size.cols(); ++c){
				if(m1(c, r) != m2(c, r)) return false;
			}
		}

		return true;
	}

	template <
		typename M1, col_t C1, row_t R1,
		typename M2, col_t C2, row_t R2
	> constexpr bool operator!=(
		matrix< M1, C1, R1 > const& m1,
		matrix< M2, C2, R2 > const& m2
	){
		return !(m1 == m2);
	}


}


#endif
