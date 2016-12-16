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
		for(size_t y = 0; y < size_t(m.rows()); ++y){
			if(y > 0) os << ',';
			os << '(';
			for(size_t x = 0; x < size_t(m.cols()); ++x){
				if(x > 0) os << ',';
				os << m(x, y);
			}
			os << ')';
		}
		os << ')';
		return os;
	}


}


#endif
