//-----------------------------------------------------------------------------
// Copyright (c) 2015-2016 Benjamin Buch
//
// https://github.com/bebuch/mitrax
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt)
//-----------------------------------------------------------------------------
#ifndef _mitrax__get_binaryop__hpp_INCLUDED_
#define _mitrax__get_binaryop__hpp_INCLUDED_

#include "parse_argv.hpp"

#include <iostream>


namespace mitrax{


	enum class op{
		unknown,
		plus,
		mul
	};

	op get_binaryop(int argc, char** argv){
		for(int i = 1; i < argc; ++i){
			auto pair = parse_argv(argv[i]);

			if(pair.first != "op") continue;

			if(pair.second == "+"){
				return op::plus;
			}else if(pair.second == "*"){
				return op::mul;
			}else{
				break;
			}
		}
		std::cerr << "--op=X with X=[+,*]" << std::endl;
		return op::unknown;
	}


}


#endif
