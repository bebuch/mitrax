//-----------------------------------------------------------------------------
// Copyright (c) 2015-2016 Benjamin Buch
//
// https://github.com/bebuch/mitrax
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt)
//-----------------------------------------------------------------------------
#ifndef _mitrax__io__dim__hpp_INCLUDED_
#define _mitrax__io__dim__hpp_INCLUDED_

#include "../dim.hpp"

#include <iostream>


namespace mitrax{


	template < typename charT, typename traits, bool Cct, col_t C >
	std::basic_ostream< charT, traits >& operator<<(
		std::basic_ostream< charT, traits >& os, col< Cct, C > c
	){
		return os << size_t(c);
	}

	template < typename charT, typename traits, bool Rct, row_t R >
	std::basic_ostream< charT, traits >& operator<<(
		std::basic_ostream< charT, traits >& os, row< Rct, R > r
	){
		return os << size_t(r);
	}

	template < typename charT, typename traits, bool Dct, dim_t D >
	std::basic_ostream< charT, traits >& operator<<(
		std::basic_ostream< charT, traits >& os, dim< Dct, D > d
	){
		return os << size_t(d);
	}

	template < typename charT, typename traits,
		bool Cct, col_t C, bool Rct, row_t R >
	std::basic_ostream< charT, traits >& operator<<(
		std::basic_ostream< charT, traits >& os,
		dim_pair_t< Cct, C, Rct, R > const& dp
	){
		return os << size_t(dp.cols()) << "x" << size_t(dp.rows());
	}


}


#endif
