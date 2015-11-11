//-----------------------------------------------------------------------------
// Copyright (c) 2015 Benjamin Buch
//
// https://github.com/bebuch/mitrax
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt)
//-----------------------------------------------------------------------------
#ifndef _mitrax__gaussian_elimination__hpp_INCLUDED_
#define _mitrax__gaussian_elimination__hpp_INCLUDED_

#include "raw_matrix.hpp"
#include "matrix_swap.hpp"


namespace mitrax{


	template < typename M, size_t C, size_t R >
	constexpr raw_matrix< value_type_t< M >, C, R >
	upper_triangular_matrix(matrix< M, C, R > const& in){
		if(in.rows() != in.cols()){
			throw std::logic_error(
				"lower_triangular_matrix with non square matrix"
			);
		}

		// Compiler may optimize with the compile time dimension
		size_t const size = C == 0 ? in.rows() : in.cols();

		auto m = in.template convert< value_type_t< M > >();

		for(size_t i = 0; i < size; ++i){
			if(m(i, i) == 0){
				// swap lines
				size_t y = i + 1;
				for(; y < size; ++y){
					if(m(i, y) == 0) continue;
					swap_rows(m, i, y);
					break;
				}

				// matrix is not invertible
				if(y == size){
					throw std::logic_error(
						"lower_triangular_matrix with non invertible matrix"
					);
				}
			}

			// eliminate col in lower rows
			for(size_t y = i + 1; y < size; ++y){
				auto factor = m(i, y) / m(i, i);
				m(i, y) = 0;
				for(size_t x = i + 1; x < size; ++x){
					m(x, y) -= factor * m(x, i);
				}
			}
		}

		return m;
	}


}


#endif
