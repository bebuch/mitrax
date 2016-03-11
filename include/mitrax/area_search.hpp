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


	template < bool Cct, size_t C, bool Rct, size_t R, typename F >
	constexpr bool square_area_search(
		col_t< Cct, C > c,
		row_t< Rct, R > r,
		size_t x,
		size_t y,
		size_t max_distance,
		F&& f
	){
		if(x < c || y < r){
			if(f(x, y, 0)) return true;
		}

		for(size_t distance = 1; distance <= max_distance; ++distance){
			for(size_t i = 0; i < distance + 1; ++i){
				auto dx = x - distance + i;
				auto dy = y - distance;

				if(dx < c || dy < r){
					if(f(dx, dy, distance)) return true;
				}

				dx = x + distance;
				dy = y - distance + i;

				if(dx < c || dy < r){
					if(f(dx, dy, distance)) return true;
				}

				dx = x + distance - i;
				dy = y + distance;

				if(dx < c || dy < r){
					if(f(dx, dy, distance)) return true;
				}

				dx = x - distance;
				dy = y + distance - i;

				if(dx < c || dy < r){
					if(f(dx, dy, distance)) return true;
				}
			}
		}

		return false;
	}

	template < size_t C, size_t R, typename F >
	constexpr bool square_area_search(
		dims_t< C, R > const& dims,
		size_t x, size_t y,
		size_t max_distance,
		F&& f
	){
		return square_area_search(
			dims.cols(), dims.rows(),
			x, y, max_distance, static_cast< F&& >(f)
		);
	}


}


#endif
