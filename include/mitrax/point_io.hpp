//-----------------------------------------------------------------------------
// Copyright (c) 2009-2016 Benjamin Buch
//
// https://github.com/bebuch/mitrax
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt)
//-----------------------------------------------------------------------------
#ifndef _mitrax__point_io__hpp_INCLUDED_
#define _mitrax__point_io__hpp_INCLUDED_

#include "io.hpp"
#include "point.hpp"

#include <iostream>


namespace mitrax{


	template < typename charT, typename traits, typename TX, typename TY >
	std::basic_ostream< charT, traits >& operator<<(
		std::basic_ostream< charT, traits >& os,
		point< TX, TY > const& data
	){
		return os << data.x() << "x" << data.y();
	}


	template < typename charT, typename traits, typename TX, typename TY >
	std::basic_istream< charT, traits >& operator>>(
		std::basic_istream< charT, traits >& is,
		point< TX, TY >& data
	){
		point< TX, TY > tmp;
		is >> tmp.x();
		if(!io::equal(is, 'x')) return is;
		is >> tmp.y();

		data = std::move(tmp);

		return is;
	}


}


#endif
