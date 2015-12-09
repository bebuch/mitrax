//-----------------------------------------------------------------------------
// Copyright (c) 2013-2015 Benjamin Buch
//
// https://github.com/bebuch/mitrax
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt)
//-----------------------------------------------------------------------------
#ifndef _mitrax__io_debug__hpp_INCLUDED_
#define _mitrax__io_debug__hpp_INCLUDED_

#include <ostream>
#include <utility>

#include <boost/container/vector.hpp>


namespace mitrax{


	template < typename X, typename Y >
	std::ostream& operator<<(std::ostream& os, std::pair< X, Y > const& p){
		os << '(';
		os << p.first;
		os << ';';
		os << p.second;
		os << ')';
		return os;
	}

	template < typename T >
	std::ostream& operator<<(
		std::ostream& os,
		boost::container::vector< T > const& p
	){
		os << '{';
		if(p.size() > 0) os << p[0];
		for(std::size_t i = 1; i < p.size(); ++i){
			os << ',' << p[i];
		}
		os << '}';
		return os;
	}



}

#endif
