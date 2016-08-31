//-----------------------------------------------------------------------------
// Copyright (c) 2015-2016 Benjamin Buch
//
// https://github.com/bebuch/mitrax
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt)
//-----------------------------------------------------------------------------
#ifndef _mitrax__random_vector__hpp_INCLUDED_
#define _mitrax__random_vector__hpp_INCLUDED_

#include <vector>
#include <random>


namespace mitrax{


	template < typename T >
	std::vector< T > random_vector(std::size_t size){
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution< T > dis(
			std::numeric_limits< T >::min(),
			std::numeric_limits< T >::max()
		);

		std::vector< T > res;
		res.reserve(size);
		for(std::size_t i = 0; i < size; ++i){
			res.emplace_back(dis(gen));
		}

		return res;
	}


}


#endif
