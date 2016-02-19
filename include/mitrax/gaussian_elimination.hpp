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

#include "make_matrix.hpp"
#include "swap_matrix.hpp"


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


	template < typename M1, size_t C1, size_t R1, typename M2, size_t R2 >
	constexpr auto gaussian_elimination(
		matrix< M1, C1, R1 > m,
		col_vector< M2, R2 > v
	){
		using value_type = std::common_type_t<
			value_type_t< M1 >, value_type_t< M2 >
		>;

		if(m.cols() != m.rows() || m.rows() != v.rows()){
			throw std::logic_error(
				"gaussian_elimination: incompatible dimensions"
			);
		}

		auto b = v.template convert< value_type >();

		// Compiler may optimize with the compile time dimension
		size_t const size = C1 != 0 ? m.cols() : R1 != 0 ? m.rows() : b.rows();

		size_t swap_count = 0;
		for(size_t i = 0; i < size; ++i){
			if(m(i, i) == 0){
				// swap lines
				size_t y = i + 1;
				for(; y < size; ++y){
					if(m(i, y) == 0) continue;
					swap_rows(m, i, y);
					swap_rows(b, i, y);
					++swap_count;
					break;
				}

				// matrix is not invertible
				if(y == size){
					throw std::logic_error(
						"gaussian_elimination with non invertible matrix"
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
				b[y] -= factor *b[i];
			}
		}

		for(size_t i = 1; i < size; ++i){
			auto x = size - i;

			for(size_t y = 0; y < x; ++y){
				auto factor = m(x, y) / m(x, x);
				b[y] -= factor * b[x];
// 				m(x, y) = 0; // TODO: remove this line
			}
		}

		for(size_t i = 0; i < size; ++i){
			b[i] /= m(i, i);
		}

		return b;
	}


	template <
		typename M1, size_t C1, size_t R1,
		typename M2, size_t R2,
		typename M3, size_t R3
	> constexpr auto gaussian_elimination(
		matrix< M1, C1, R1 > a,
		col_vector< M2, R2 > v,
		col_vector< M3, R3 > defaults
	){
		using value_type = std::common_type_t<
			value_type_t< M1 >, value_type_t< M2 >, value_type_t< M3 >
		>;

		if(a.rows() == v.rows() && a.cols() != v.rows() + defaults.rows()){
			throw std::logic_error(
				"gaussian_elimination: incompatible dimensions"
			);
		}

		auto b = make_col_vector_by_function(
			v.rows() + defaults.rows(),
			[&v, &defaults](size_t i)->value_type{
				if(i < v.rows()){
					return v[i];
				}else{
					return defaults[i - v.rows()];
				}
			});

		for(size_t i = a.rows(); i < b.rows(); ++i){
			for(size_t y = 0; y < a.rows(); ++y){
				b[y] -= a(y, y) * b[i];
			}
		}

		auto m = make_matrix_by_function(
			a.rows().as_col(), a.rows(),
			[&a](size_t x, size_t y)->value_type{
				return a(x, y);
			});

		// Compiler may optimize with the compile time dimension
		size_t const size = C1 != 0 ? m.cols() : R1 != 0 ? m.rows() : b.rows();

		size_t swap_count = 0;
		for(size_t i = 0; i < size; ++i){
			if(m(i, i) == 0){
				// swap lines
				size_t y = i + 1;
				for(; y < size; ++y){
					if(m(i, y) == 0) continue;
					swap_rows(m, i, y);
					swap_rows(b, i, y);
					++swap_count;
					break;
				}

				// matrix is not invertible
				if(y == size){
					throw std::logic_error(
						"gaussian_elimination with non invertible matrix"
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
				b[y] -= factor *b[i];
			}
		}

		for(size_t i = 1; i < size; ++i){
			auto x = size - i;

			for(size_t y = 0; y < x; ++y){
				auto factor = m(x, y) / m(x, x);
				b[y] -= factor * b[x];
// 				m(x, y) = 0; // TODO: remove this line
			}
		}

		for(size_t i = 0; i < size; ++i){
			b[i] /= m(i, i);
		}

		return b;
	}


	template < typename M, size_t C, size_t R >
	constexpr raw_matrix< value_type_t< M >, C, R >
	inverse(matrix< M, C, R > m){
		using value_type = value_type_t< M >;

		if(m.cols() != m.rows()){
			throw std::logic_error(
				"inverse with non square matrix"
			);
		}

		// Compiler may optimize with the compile time dimension
		size_t const size = C == 0 ? m.rows() : m.cols();

		auto r = make_matrix< value_type >(m.dims());
		for(size_t i = 0; i < size; ++i){
			r(i, i) = 1;
		}

		size_t swap_count = 0;
		for(size_t i = 0; i < size; ++i){
			if(m(i, i) == 0){
				// swap lines
				size_t y = i + 1;
				for(; y < size; ++y){
					if(m(i, y) == 0) continue;
					swap_rows(m, i, y);
					swap_rows(r, i, y);
					++swap_count;
					break;
				}

				// matrix is not invertible
				if(y == size){
					throw std::logic_error(
						"inverse with non invertible matrix"
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
				for(size_t x = 0; x < size; ++x){
					r(x, y) -= factor * r(x, i);
				}
			}

			for(size_t x = 0; x < size; ++x){
				r(x, i) /= m(i, i);
			}

			for(size_t x = i + 1; x < size; ++x){
				m(x, i) /= m(i, i);
			}

// 			m(i, i) = 1; // TODO: remove this line
		}

		for(size_t i = 0; i < size; ++i){
			auto j = size - i - 1;

			for(size_t y = 0; y < j; ++y){
				for(size_t x = 0; x < size; ++x){
					r(x, y) -= m(j, y) * r(x, j);
				}

// 				m(j, y) = 0; // TODO: remove this line
			}
		}

		return r;
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
			m.cols().as_row()
		);

		// Compiler may optimize with the compile time dimension
		size_t const size = C == 0 ? m.rows() : m.cols();

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
				result[y] += m(x, y) * result[x];
			}

			if(m(y, y) == 0){
				result[y] = 1;
			}else{
				result[y] /= -m(y, y);
			}
		}

		return result;
	}


}


#endif
