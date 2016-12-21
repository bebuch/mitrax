//-----------------------------------------------------------------------------
// Copyright (c) 2015-2016 Benjamin Buch
//
// https://github.com/bebuch/mitrax
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt)
//-----------------------------------------------------------------------------
#ifndef _mitrax__gaussian_elimination__hpp_INCLUDED_
#define _mitrax__gaussian_elimination__hpp_INCLUDED_

#include "convert.hpp"
#include "swap_matrix.hpp"


namespace mitrax{


	template < typename M, col_t C, row_t R >
	constexpr std_matrix< value_type_t< M >, C, R >
	upper_triangular_matrix(matrix< M, C, R > const& in){
		if(in.rows().as_dim() != in.cols().as_dim()){
			throw std::logic_error(
				"lower_triangular_matrix with non square matrix"
			);
		}

		// Compiler may optimize with the compile time dimension
		auto const size = C == 0_C ? in.rows().as_dim() : in.cols().as_dim();

		auto m = convert< value_type_t< M > >(in);

		for(auto d = 0_d; d < size; ++d){
			auto const ic = c_t(d);
			auto const ir = r_t(d);

			if(m(ic, ir) == 0){
				auto r = ir + 1_r;
				// swap lines
				for(; r < size.as_row(); ++r){
					if(m(ic, r) == 0) continue;
					swap_rows(m, ir, r);
					break;
				}

				// matrix is not invertible
				if(r == size.as_row()){
					throw std::logic_error(
						"lower_triangular_matrix with non invertible matrix"
					);
				}
			}

			// eliminate col in lower rows
			for(auto r = ir + 1_r; r < size.as_row(); ++r){
				auto factor = m(ic, r) / m(ic, ir);
				m(ic, r) = 0;
				for(auto c = ic + 1_c; c < size.as_col(); ++c){
					m(c, r) -= factor * m(c, ir);
				}
			}
		}

		return m;
	}


	template < typename M1, col_t C1, row_t R1, typename M2, row_t R2 >
	constexpr auto gaussian_elimination(
		matrix< M1, C1, R1 > m,
		col_vector< M2, R2 > v
	){
		using value_type = std::common_type_t<
			value_type_t< M1 >, value_type_t< M2 >
		>;

		if(m.cols().as_row() != m.rows() || m.rows() != v.rows()){
			throw std::logic_error(
				"gaussian_elimination: incompatible dimensions"
			);
		}

		auto b = convert< value_type >(v);

		// Compiler may optimize with the compile time dimension
		auto const size = C1 != 0_C ? m.cols().as_dim() :
			R1 != 0_R ? m.rows().as_dim() : b.rows().as_dim();

		for(auto d = 0_d; d < size; ++d){
			auto const ic = c_t(d);
			auto const ir = r_t(d);

			if(m(ic, ir) == 0){
				auto r = ir + 1_r;
				// swap lines
				for(; r < size.as_row(); ++r){
					if(m(ic, r) == 0) continue;
					swap_rows(m, ir, r);
					swap_rows(b, ir, r);
					break;
				}

				// matrix is not invertible
				if(r == size.as_row()){
					throw std::logic_error(
						"lower_triangular_matrix with non invertible matrix"
					);
				}
			}

			// eliminate col in lower rows
			for(auto r = ir + 1_r; r < size.as_row(); ++r){
				auto factor = m(ic, r) / m(ic, ir);
				m(ic, r) = 0;
				for(auto c = ic + 1_c; c < size.as_col(); ++c){
					m(c, r) -= factor * m(c, ir);
				}
				b[d_t(r)] -= factor * b[d];
			}
		}

		for(auto i = 1_c; i < size.as_col(); ++i){
			auto x = c_t(size.as_col()) - i;

			for(auto y = 0_r; y < r_t(x); ++y){
				auto factor = m(x, y) / m(x, r_t(x));
				b[d_t(y)] -= factor * b[d_t(x)];
			}
		}

		for(auto i = 0_d; i < size; ++i){
			b[i] /= m(c_t(i), r_t(i));
		}

		return b;
	}


// 	template <
// 		typename M1, col_t C1, row_t R1,
// 		typename M2, row_t R2,
// 		typename M3, row_t R3
// 	> constexpr auto gaussian_elimination(
// 		matrix< M1, C1, R1 > a,
// 		col_vector< M2, R2 > v,
// 		col_vector< M3, R3 > defaults
// 	){
// 		using value_type = std::common_type_t<
// 			value_type_t< M1 >, value_type_t< M2 >, value_type_t< M3 >
// 		>;
//
// 		if(
// 			a.rows() == v.rows() &&
// 			size_t(a.cols()) != size_t(v.rows() + defaults.rows())){
// 			throw std::logic_error(
// 				"gaussian_elimination: incompatible dimensions"
// 			);
// 		}
//
// 		auto b = make_vector_fn(v.rows() + defaults.rows(),
// 			[&v, &defaults](size_t i)->value_type{
// 				if(i < v.rows()){
// 					return v[i];
// 				}else{
// 					return defaults[i - v.rows()];
// 				}
// 			});
//
// 		for(size_t i = size_t(a.rows()); i < size_t(b.rows()); ++i){
// 			for(size_t y = 0; y < a.rows(); ++y){
// 				b[y] -= a(y, y) * b[i];
// 			}
// 		}
//
// 		auto m = make_matrix_fn(a.rows().as_col(), a.rows(),
// 			[&a](size_t x, size_t y)->value_type{
// 				return a(x, y);
// 			});
//
// 		// Compiler may optimize with the compile time dimension
// 		auto const size = C1 != 0_C ? m.cols().as_dim() :
// 			R1 != 0_R ? m.rows().as_dim() : b.rows().as_dim();
//
// 		size_t swap_count = 0;
// 		for(size_t i = 0; i < size; ++i){
// 			if(m(i, i) == 0){
// 				// swap lines
// 				size_t y = i + 1;
// 				for(; y < size; ++y){
// 					if(m(i, y) == 0) continue;
// 					swap_rows(m, i, y);
// 					swap_rows(b, i, y);
// 					++swap_count;
// 					break;
// 				}
//
// 				// matrix is not invertible
// 				if(y == size){
// 					throw std::logic_error(
// 						"gaussian_elimination with non invertible matrix"
// 					);
// 				}
// 			}
//
// 			// eliminate col in lower rows
// 			for(size_t y = i + 1; y < size; ++y){
// 				auto factor = m(i, y) / m(i, i);
// 				m(i, y) = 0;
// 				for(size_t x = i + 1; x < size; ++x){
// 					m(x, y) -= factor * m(x, i);
// 				}
// 				b[y] -= factor *b[i];
// 			}
// 		}
//
// 		for(size_t i = 1; i < size; ++i){
// 			auto x = size - i;
//
// 			for(size_t y = 0; y < x; ++y){
// 				auto factor = m(x, y) / m(x, x);
// 				b[y] -= factor * b[x];
// // 				m(x, y) = 0; // TODO: remove this line
// 			}
// 		}
//
// 		for(size_t i = 0; i < size; ++i){
// 			b[i] /= m(i, i);
// 		}
//
// 		return b;
// 	}


	template < typename M, col_t C, row_t R >
	constexpr std_matrix< value_type_t< M >, C, R >
	inverse(matrix< M, C, R > m){
		using value_type = value_type_t< M >;

		if(m.cols().as_dim() != m.rows().as_dim()){
			throw std::logic_error(
				"inverse with non square matrix"
			);
		}

		// Compiler may optimize with the compile time dimension
		auto const size = C == 0_C ? m.rows().as_dim() : m.cols().as_dim();

		auto r = make_matrix_v< value_type >(m.dims());
		for(auto i = 0_d; i < size; ++i){
			r(c_t(i), r_t(i)) = 1;
		}

		for(auto i = 0_d; i < size; ++i){
			if(m(c_t(i), r_t(i)) == 0){
				// swap lines
				auto y = r_t(i) + 1_r;
				for(; y < size.as_row(); ++y){
					if(m(c_t(i), y) == 0) continue;
					swap_rows(m, r_t(i), y);
					swap_rows(r, r_t(i), y);
					break;
				}

				// matrix is not invertible
				if(y == size.as_row()){
					throw std::logic_error(
						"inverse with non invertible matrix"
					);
				}
			}

			// eliminate col in lower rows
			for(auto y = r_t(i) + 1_r; y < size.as_row(); ++y){
				auto factor = m(c_t(i), y) / m(c_t(i), r_t(i));
				m(c_t(i), y) = 0;
				for(auto x = c_t(i) + 1_c; x < size.as_col(); ++x){
					m(x, y) -= factor * m(x, r_t(i));
				}
				for(auto x = 0_c; x < size.as_col(); ++x){
					r(x, y) -= factor * r(x, r_t(i));
				}
			}

			for(auto x = 0_c; x < size.as_col(); ++x){
				r(x, r_t(i)) /= m(c_t(i), r_t(i));
			}

			for(auto x = c_t(i) + 1_c; x < size.as_col(); ++x){
				m(x, r_t(i)) /= m(c_t(i), r_t(i));
			}
		}

		for(auto i = 0_d; i < size; ++i){
			auto j = d_t(size) - i - 1_d;

			for(auto y = 0_r; y < r_t(j); ++y){
				for(auto x = 0_c; x < size.as_col(); ++x){
					r(x, y) -= m(c_t(j), y) * r(x, r_t(j));
				}
			}
		}

		return r;
	}


	template < typename M, col_t C, row_t R >
	constexpr auto matrix_kernel(matrix< M, C, R > m){
		using value_type = value_type_t< M >;

		if(m.cols().as_dim() != m.rows().as_dim()){
			throw std::logic_error(
				"matrix_kernel does up to now only work for square matrices"
			);
		}

		auto result = make_vector_v< value_type >(
			m.cols().as_row()
		);

		// Compiler may optimize with the compile time dimension
		auto const size = C == 0_C ? m.rows().as_dim() : m.cols().as_dim();

		for(auto d = 0_d; d < size; ++d){
			auto const ic = c_t(d);
			auto const ir = r_t(d);

			if(m(ic, ir) == 0){
				auto r = ir + 1_r;
				// swap lines
				for(; r < size.as_row(); ++r){
					if(m(ic, r) == 0) continue;
					swap_rows(m, ir, r);
					break;
				}

				// matrix is not invertible
				if(r == size.as_row()){
					break;
				}
			}

			// eliminate col in lower rows
			for(auto r = ir + 1_r; r < size.as_row(); ++r){
				auto factor = m(ic, r) / m(ic, ir);
				m(ic, r) = 0;
				for(auto c = ic + 1_c; c < size.as_col(); ++c){
					m(c, r) -= factor * m(c, ir);
				}
			}
		}

		for(auto d = 0_r; d < size.as_row(); ++d){
			auto r = r_t(size.as_row()) - d - 1_r;

			for(auto c = c_t(r) + 1_c; c < size.as_col(); ++c){
				result[d_t(r)] += m(c, r) * result[d_t(c)];
			}

			if(m(c_t(r), r) == 0){
				result[d_t(r)] = 1;
			}else{
				result[d_t(r)] /= -m(c_t(r), r);
			}
		}

		return result;
	}


}


#endif
