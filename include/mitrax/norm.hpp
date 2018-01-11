//-----------------------------------------------------------------------------
// Copyright (c) 2015-2018 Benjamin Buch
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
			"v is not a vector"
		);

		value_type_t< M > res = 0;
		if(v.cols() == 1_CS){
			for(auto r = 0_r; r < v.rows(); ++r){
				res += v(0_c, r) * v(0_c, r);
			}
		}else if(v.rows() == 1_RS){
			for(auto c = 0_c; c < v.cols(); ++c){
				res += v(c, 0_r) * v(c, 0_r);
			}
		}else{
			throw std::logic_error("vector_norm_2 called with not a vector");
		}

		return res;
	}

	template < typename M, col_t C, row_t R >
	value_type_t< M > vector_norm_2(matrix< M, C, R > const& v){
		using std::sqrt;
		return sqrt(vector_norm_2sqr(v));
	}


}


#endif
