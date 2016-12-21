//-----------------------------------------------------------------------------
// Copyright (c) 2015-2016 Benjamin Buch
//
// https://github.com/bebuch/mitrax
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt)
//-----------------------------------------------------------------------------
#ifndef _mitrax__io__matrix__hpp_INCLUDED_
#define _mitrax__io__matrix__hpp_INCLUDED_

#include "../matrix_interface.hpp"

#include <ostream>


namespace mitrax{


	template < typename M, col_t C, row_t R >
	std::ostream& operator<<(std::ostream& os, matrix< M, C, R > const& m){
		os << '[' << m.cols() << ',' << m.rows() << ']';
		os << '(';
		for(auto y = 0_r; y < m.rows(); ++y){
			if(y > 0_r) os << ',';
			os << '(';
			for(auto x = 0_c; x < m.cols(); ++x){
				if(x > 0_c) os << ',';
				os << m(x, y);
			}
			os << ')';
		}
		os << ')';
		return os;
	}


}


#endif
