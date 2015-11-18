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


	template < typename M, size_t C, size_t R >
	constexpr auto matrix_kernel(matrix< M, C, R > m){
		using value_type = value_type_t< M >;

		if(m.cols() != m.rows()){
			throw std::logic_error(
				"matrix_kernel does up to now only work for square matrices"
			);
		}

		auto result = make_col_vector< value_type >(
			m.cols().as_row().init()
		);

		auto ref = result.
			template convert< std::reference_wrapper< value_type > >();

		// Compiler may optimize with the compile time dimension
		size_t const size = C == 0 ? m.rows() : m.cols();

		for(size_t i = 0; i < size; ++i){
			if(m(i, i) == 0){
				// swap lines
				size_t y = i + 1;
				for(; y < size; ++y){
					if(m(i, y) == 0) continue;
					swap_rows(m, i, y);
					swap_rows(ref, i, y);
					break;
				}

				// matrix is not invertible
				if(y == size){
					break;
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

		for(size_t i = 0; i < size; ++i){
			auto y = size - i - 1;
			for(size_t x = y + 1; x < size; ++x){
				ref[y] += m(x, y) * ref[x];
			}

			if(m(y, y) == 0){
				ref[y].get() = 1;
			}else{
				ref[y] /= -m(y, y);
			}
		}

		return result;
	}


}


#endif
