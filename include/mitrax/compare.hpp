//-----------------------------------------------------------------------------
// Copyright (c) 2015 Benjamin Buch
//
// https://github.com/bebuch/mitrax
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt)
//-----------------------------------------------------------------------------
#ifndef _mitrax__compare__hpp_INCLUDED_
#define _mitrax__compare__hpp_INCLUDED_

#include "matrix.hpp"


namespace mitrax{


	template < typename M1, typename M2, std::size_t Cols, std::size_t Rows >
	constexpr bool operator==(
		matrix< M1, Cols, Rows > const& m1,
		matrix< M2, Cols, Rows > const& m2
	){
		static_assert(Cols > 0 && Rows > 0, "Need static dimensioned matrix");
		for(std::size_t y = 0; y < Rows; ++y){
			for(std::size_t x = 0; x < Cols; ++x){
				if(m1(x, y) != m2(x, y)) return false;
			}
		}
		return true;
	}

	template < typename M1, typename M2, std::size_t Cols, std::size_t Rows >
	constexpr bool operator!=(
		matrix< M1, Cols, Rows > const& m1,
		matrix< M2, Cols, Rows > const& m2
	){
		return !(m1 == m2);
	}


}


#endif
