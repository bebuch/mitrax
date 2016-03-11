//-----------------------------------------------------------------------------
// Copyright (c) 2013-2016 Benjamin Buch
//
// https://github.com/bebuch/mitrax
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt)
//-----------------------------------------------------------------------------
#ifndef _mitrax__io__hpp_INCLUDED_
#define _mitrax__io__hpp_INCLUDED_

#include <iostream>


namespace mitrax{ namespace io{


	template < class charT, class traits >
	inline bool test(
		std::basic_istream< charT, traits >& is,
		charT const& should_be
	){
		charT in;
		if(is){
			if(is >> in && in == should_be) return true;
			is.putback(in);
		}
		return false;
	}

	template < class charT, class traits, class ShouldBe >
	inline bool equal(
		std::basic_istream< charT, traits >& is,
		ShouldBe const& should_be
	){
		ShouldBe in;
		if(is && is >> in && in == should_be) return true;
		is.setstate(std::ios_base::failbit);
		return false;
	}

	template < class charT, class traits >
	inline bool equal(
		std::basic_istream< charT, traits >& is,
		charT const& should_be
	){
		auto result = test(is, should_be);
		if(!result) is.setstate(std::ios_base::failbit);
		return result;
	}


} }

#endif
