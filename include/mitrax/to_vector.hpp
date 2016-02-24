//-----------------------------------------------------------------------------
// Copyright (c) 2015 Benjamin Buch
//
// https://github.com/bebuch/mitrax
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt)
//-----------------------------------------------------------------------------
#ifndef _mitrax__to_vector__hpp_INCLUDED_
#define _mitrax__to_vector__hpp_INCLUDED_

#include "dyn_array.hpp"

#include <utility>


namespace mitrax{


	template < typename T, size_t N >
	auto to_vector(T(&&v)[N]){
		return dyn_array< T >(std::move(v));
	}

	template < typename T, size_t N >
	auto to_vector(T const(&v)[N]){
		return dyn_array< T >(v);
	}


	template < typename T, size_t C, size_t R >
	auto to_vector(T(&&v)[R][C]){
		return dyn_array< T >(std::move(v));
	}

	template < typename T, size_t C, size_t R >
	auto to_vector(T const(&v)[R][C]){
		return dyn_array< T >(v);
	}

	template < typename F, bool Nct, size_t N >
	auto function_i_to_vector(dim_t< Nct, N > n, F const& f){
		return dyn_array< fn_i< F > >(n, f);
	}

	template < typename F, bool Cct, size_t C, bool Rct, size_t R >
	auto function_xy_to_vector(
		col_t< Cct, C > c, row_t< Rct, R > r, F const& f
	){
		return dyn_array< fn_xy< F > >(c, r, f);
	}


}


#endif
