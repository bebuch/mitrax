//-----------------------------------------------------------------------------
// Copyright (c) 2016 Benjamin Buch
//
// https://github.com/bebuch/mitrax
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt)
//-----------------------------------------------------------------------------
#ifndef _mitrax__segmentation__hpp_INCLUDED_
#define _mitrax__segmentation__hpp_INCLUDED_

#include "make_matrix.hpp"

#include <vector>


namespace mitrax{


	template < size_t C, size_t R, bool EdgeNeighborhood >
	class segmentor{
	public:
		constexpr segmentor(dims_t< C, R > const& dims):
			used_(make_matrix_by_default< bool >(dims, false)) {}

		template < typename F >
		size_t operator()(size_t x, size_t y, F&& f){
			std::vector< point< size_t > > stack;
			stack.reserve(used_.point_count());

			size_t count = 0;

			stack.emplace_back(x, y);

			while(stack.size() > 0){
				size_t x = stack.back().x();
				size_t y = stack.back().y();
				stack.pop_back();

				if(
					x >= used_.cols() ||
					y >= used_.rows() ||
					used_(x, y) ||
					!f(x, y)
				){
					continue;
				}

				used_(x, y) = true;

				stack.emplace_back(x - 1, y);
				stack.emplace_back(x, y - 1);
				stack.emplace_back(x + 1, y);
				stack.emplace_back(x, y + 1);

				if(EdgeNeighborhood){
					stack.emplace_back(x - 1, y - 1);
					stack.emplace_back(x + 1, y - 1);
					stack.emplace_back(x - 1, y + 1);
					stack.emplace_back(x + 1, y + 1);
				}

				++count;
			}

			return count;
		};

		template < typename F >
		size_t operator()(point< size_t > const& p, F&& f){
			return (*this)(p.x(), p.y(), static_cast< F&& >(f));
		}


		constexpr raw_matrix< bool, C, R >& used()noexcept{
			return used_;
		}


	private:
		raw_matrix< bool, C, R > used_;
	};


	template < bool EdgeNeighborhood, size_t C, size_t R >
	constexpr auto make_segmentor(dims_t< C, R > const& dims){
		return segmentor< C, R, EdgeNeighborhood >(dims);
	}

	template < bool EdgeNeighborhood, bool Cct, size_t C, bool Rct, size_t R >
	constexpr auto make_segmentor(col_t< Cct, C > c, row_t< Rct, R > r){
		return make_segmentor< EdgeNeighborhood >(dims(c, r));
	}


}


#endif
