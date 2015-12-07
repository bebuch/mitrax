//-----------------------------------------------------------------------------
// Copyright (c) 2015 Benjamin Buch
//
// https://github.com/bebuch/mitrax
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt)
//-----------------------------------------------------------------------------
#ifndef _mitrax__dim_io__hpp_INCLUDED_
#define _mitrax__dim_io__hpp_INCLUDED_

#include "dim.hpp"

#include <iostream>


namespace mitrax{


	template < typename charT, typename traits, size_t C >
	std::basic_ostream< charT, traits >& operator<<(
		std::basic_ostream< charT, traits >& os,
		col_t< C > col
	){
		return os << static_cast< size_t >(col);
	}

	template < typename charT, typename traits, size_t R >
	std::basic_ostream< charT, traits >& operator<<(
		std::basic_ostream< charT, traits >& os,
		row_t< R > row
	){
		return os << static_cast< size_t >(row);
	}

	template < typename charT, typename traits, bool Cct, size_t C >
	std::basic_ostream< charT, traits >& operator<<(
		std::basic_ostream< charT, traits >& os,
		col_init_t< Cct, C > col
	){
		return os << static_cast< size_t >(col);
	}

	template < typename charT, typename traits, bool Rct, size_t R >
	std::basic_ostream< charT, traits >& operator<<(
		std::basic_ostream< charT, traits >& os,
		row_init_t< Rct, R > row
	){
		return os << static_cast< size_t >(row);
	}

	template < typename charT, typename traits, bool Nct, size_t N >
	std::basic_ostream< charT, traits >& operator<<(
		std::basic_ostream< charT, traits >& os,
		dim_init_t< Nct, N > dim
	){
		return os << static_cast< size_t >(dim);
	}

	template < typename charT, typename traits, size_t C, size_t R >
	std::basic_ostream< charT, traits >& operator<<(
		std::basic_ostream< charT, traits >& os,
		dim_t< C, R > const& dim
	){
		return os << dim.cols() << "x" << dim.rows();
	}


}


#endif
