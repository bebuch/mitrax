//-----------------------------------------------------------------------------
// Copyright (c) 2016-2018 Benjamin Buch
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


	template < col_t Cols, row_t Rows, bool EdgeNeighborhood >
	class segmentor{
	public:
		template < bool Cct, col_t C, bool Rct, row_t R >
		constexpr segmentor(dim_pair_t< Cct, C, Rct, R > const& dims):
			used_(make_matrix_v< bool >(dims, false)) {}

		template < typename F >
		size_t operator()(size_t x, size_t y, F&& f){
			std::vector< point_t > stack;
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
		size_t operator()(point_t const& p, F&& f){
			return (*this)(p.x(), p.y(), static_cast< F&& >(f));
		}


		constexpr std_matrix< bool, Cols, Rows >& used()noexcept{
			return used_;
		}


	private:
		std_matrix< bool, Cols, Rows > used_;
	};


	template < bool EdgeNeighborhood, bool Cct, col_t C, bool Rct, row_t R >
	constexpr auto make_segmentor(dim_pair_t< Cct, C, Rct, R > const& dims){
		return
			segmentor< Cct ? C : 0_C, Rct ? R : 0_R, EdgeNeighborhood >(dims);
	}

	template < bool EdgeNeighborhood, bool Cct, col_t C, bool Rct, row_t R >
	constexpr auto make_segmentor(col< Cct, C > c, row< Rct, R > r){
		return make_segmentor< EdgeNeighborhood >(dim_pair(c, r));
	}


}


#endif
