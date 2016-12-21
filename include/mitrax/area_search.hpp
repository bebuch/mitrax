//-----------------------------------------------------------------------------
// Copyright (c) 2016 Benjamin Buch
//
// https://github.com/bebuch/mitrax
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt)
//-----------------------------------------------------------------------------
#ifndef _mitrax__area_search__hpp_INCLUDED_
#define _mitrax__area_search__hpp_INCLUDED_

#include "dim.hpp"


namespace mitrax{


	template < bool Cct, col_t C, bool Rct, row_t R, typename F >
	constexpr bool square_area_search(
		col< Cct, C > c, row< Rct, R > r,
		c_t x, r_t y, size_t max_distance, F&& f
	){
		if(x < c || y < r){
			if(f(x, y, 0)) return true;
		}

		for(size_t distance = 1; distance <= max_distance; ++distance){
			for(size_t i = 0; i < distance + 1; ++i){
				auto dx = size_t(x) - distance + i;
				auto dy = size_t(y) - distance;

				if(dx < c || dy < r){
					if(f(dx, dy, distance)) return true;
				}

				dx = size_t(x) + distance;
				dy = size_t(y) - distance + i;

				if(dx < c || dy < r){
					if(f(dx, dy, distance)) return true;
				}

				dx = size_t(x) + distance - i;
				dy = size_t(y) + distance;

				if(dx < c || dy < r){
					if(f(dx, dy, distance)) return true;
				}

				dx = size_t(x) - distance;
				dy = size_t(y) + distance - i;

				if(dx < c || dy < r){
					if(f(dx, dy, distance)) return true;
				}
			}
		}

		return false;
	}

	template < bool Cct, col_t C, bool Rct, row_t R, typename F >
	constexpr bool square_area_search(
		dim_pair_t< Cct, C, Rct, R > const& dims,
		c_t x, r_t y, size_t max_distance, F&& f
	){
		return square_area_search(
			dims.cols(), dims.rows(),
			x, y, max_distance, static_cast< F&& >(f)
		);
	}


}


#endif
