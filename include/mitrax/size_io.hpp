//-----------------------------------------------------------------------------
// Copyright (c) 2009-2015 Benjamin Buch
//
// https://github.com/bebuch/mitrax
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt)
//-----------------------------------------------------------------------------
#ifndef _mitrax__size_io__hpp_INCLUDED_
#define _mitrax__size_io__hpp_INCLUDED_

#include "io.hpp"
#include "size.hpp"

#include <iostream>


namespace mitrax{


	template < typename charT, typename traits, typename T >
	std::basic_ostream< charT, traits >& operator<<(
		std::basic_ostream< charT, traits >& os,
		size< T > const& data
	){
		return os << data.width() << "x" << data.height();
	}


	template < typename charT, typename traits, typename T >
	std::basic_istream< charT, traits >& operator>>(
		std::basic_istream< charT, traits >& is,
		size< T >& data
	){
		size< T > tmp;
		is >> tmp.width();
		if(!io::equal(is, 'x')) return is;
		is >> tmp.height();

		data = std::move(tmp);

		return is;
	}


}


#endif
