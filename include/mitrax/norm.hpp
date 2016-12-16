//-----------------------------------------------------------------------------
// Copyright (c) 2015-2016 Benjamin Buch
//
// https://github.com/bebuch/mitrax
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt)
//-----------------------------------------------------------------------------
#ifndef _mitrax__norm__hpp_INCLUDED_
#define _mitrax__norm__hpp_INCLUDED_

#include "matrix.hpp"

#include <cmath>


namespace mitrax{


	template < typename M, col_t C, row_t R >
	value_type_t< M > vector_norm_2sqr(matrix< M, C, R > const& v){
		static_assert(
			C == 1_C || C == 0_C || R == 1_R || R == 0_R,
			"vector_norm_2 called with not a vector"
		);

		value_type_t< M > r = 0;
		if(v.cols() == 1){
			for(size_t i = 0; i < v.rows(); ++i){
				r += v(0, i) * v(0, i);
			}
		}else if(v.rows() == 1){
			for(size_t i = 0; i < v.cols(); ++i){
				r += v(i, 0) * v(i, 0);
			}
		}else{
			throw std::logic_error("vector_norm_2 called with not a vector");
		}

		return r;
	}

	template < typename M, col_t C, row_t R >
	value_type_t< M > vector_norm_2(matrix< M, C, R > const& v){
		using std::sqrt;
		return sqrt(vector_norm_2sqr(v));
	}


}


#endif
