//-----------------------------------------------------------------------------
// Copyright (c) 2015 Benjamin Buch
//
// https://github.com/bebuch/mitrax
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt)
//-----------------------------------------------------------------------------
#ifndef _mitrax__output__hpp_INCLUDED_
#define _mitrax__output__hpp_INCLUDED_

#include "matrix.hpp"

#include <ostream>


namespace mitrax{


	template < typename M, size_t C, size_t R >
	std::ostream& operator<<(std::ostream& os, matrix< M, C, R > const& m){
		os << '[' << m.cols() << ',' << m.rows() << ']';
		os << '(';
		for(size_t y = 0; y < m.rows(); ++y){
			if(y > 0) os << ',';
			os << '(';
			for(size_t x = 0; x < m.cols(); ++x){
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
