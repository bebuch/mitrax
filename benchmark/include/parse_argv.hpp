//-----------------------------------------------------------------------------
// Copyright (c) 2015-2016 Benjamin Buch
//
// https://github.com/bebuch/mitrax
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt)
//-----------------------------------------------------------------------------
#ifndef _mitrax__parse_argv__hpp_INCLUDED_
#define _mitrax__parse_argv__hpp_INCLUDED_

#include <string>
#include <utility>


namespace mitrax{


std::pair< std::string, std::string > parse_argv(std::string const& in){
	if(in.size() < 3) return {};
	if(in[0] != '-' || in[1] != '-') return {};

	auto pos = in.find('=', 2);
	if(pos == std::string::npos){
		return {in.substr(2), ""};
	}else{
		return {in.substr(2, pos - 2), in.substr(pos + 1)};
	}
}


}

#endif
