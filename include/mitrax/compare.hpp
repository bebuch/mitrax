//-----------------------------------------------------------------------------
// Copyright (c) 2015-2016 Benjamin Buch
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
		typename M1, col_ct C1, row_ct R1,
		typename M2, col_ct C2, row_ct R2
	> constexpr bool operator==(
		matrix< M1, C1, R1 > const& m1,
		matrix< M2, C2, R2 > const& m2
	){
		auto size = get_dims(m2, m1);

		for(size_t y = 0; y < size_t(size.rows()); ++y){
			for(size_t x = 0; x < size_t(size.cols()); ++x){
				if(m1(x, y) != m2(x, y)) return false;
			}
		}

		return true;
	}

	template <
		typename M1, col_ct C1, row_ct R1,
		typename M2, col_ct C2, row_ct R2
	> constexpr bool operator!=(
		matrix< M1, C1, R1 > const& m1,
		matrix< M2, C2, R2 > const& m2
	){
		return !(m1 == m2);
	}


}


#endif
