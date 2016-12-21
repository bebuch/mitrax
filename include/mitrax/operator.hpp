//-----------------------------------------------------------------------------
// Copyright (c) 2015-2016 Benjamin Buch
//
// https://github.com/bebuch/mitrax
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt)
//-----------------------------------------------------------------------------
#ifndef _mitrax__operator__hpp_INCLUDED_
#define _mitrax__operator__hpp_INCLUDED_

#include "convert.hpp"

#include <algorithm>
#include <stdexcept>
#include <cmath>


namespace mitrax{


	template < typename M, col_t C, row_t R, typename T >
	constexpr matrix< M, C, R >& element_plus_assign(
		matrix< M, C, R >& m, T const& v
	){
		for(auto& c: m) c += v;
		return m;
	}

	template < typename M, col_t C, row_t R, typename T >
	constexpr matrix< M, C, R >& element_minus_assign(
		matrix< M, C, R >& m, T const& v
	){
		for(auto& c: m) c -= v;
		return m;
	}

	template < typename M, col_t C, row_t R, typename T >
	constexpr matrix< M, C, R >& operator*=(matrix< M, C, R >& m, T const& v){
		for(auto& c: m) c *= v;
		return m;
	}

	template < typename M, col_t C, row_t R, typename T >
	constexpr matrix< M, C, R >& operator/=(matrix< M, C, R >& m, T const& v){
		for(auto& c: m) c /= v;
		return m;
	}

	template < typename M, col_t C, row_t R, typename T >
	constexpr matrix< M, C, R >& operator%=(matrix< M, C, R >& m, T const& v){
		for(auto& c: m) c %= v;
		return m;
	}


	template <
		typename M1, col_t C1, row_t R1,
		typename M2, col_t C2, row_t R2
	> constexpr matrix< M1, C1, R1 >& operator+=(
		matrix< M1, C1, R1 >& m1,
		matrix< M2, C2, R2 > const& m2
	){
		get_dims(m1, m2);
		auto iter = m2.begin();
		for(auto& c: m1) c += *iter++;
		return m1;
	}

	template <
		typename M1, col_t C1, row_t R1,
		typename M2, col_t C2, row_t R2
	> constexpr matrix< M1, C1, R1 >& operator-=(
		matrix< M1, C1, R1 >& m1,
		matrix< M2, C2, R2 > const& m2
	){
		get_dims(m1, m2);
		auto iter = m2.begin();
		for(auto& c: m1) c -= *iter++;
		return m1;
	}

	template <
		typename M1, col_t C1, row_t R1,
		typename M2, col_t C2, row_t R2
	> constexpr matrix< M1, C1, R1 >& element_multiplies_assign(
		matrix< M1, C1, R1 >& m1,
		matrix< M2, C2, R2 > const& m2
	){
		get_dims(m1, m2);
		auto iter = m2.begin();
		for(auto& c: m1) c *= *iter++;
		return m1;
	}

	template <
		typename M1, col_t C1, row_t R1,
		typename M2, col_t C2, row_t R2
	> constexpr matrix< M1, C1, R1 >& element_divides_assign(
		matrix< M1, C1, R1 >& m1,
		matrix< M2, C2, R2 > const& m2
	){
		get_dims(m1, m2);
		auto iter = m2.begin();
		for(auto& c: m1) c /= *iter++;
		return m1;
	}

	template <
		typename M1, col_t C1, row_t R1,
		typename M2, col_t C2, row_t R2
	> constexpr matrix< M1, C1, R1 >& element_modulus_assign(
		matrix< M1, C1, R1 >& m1,
		matrix< M2, C2, R2 > const& m2
	){
		get_dims(m1, m2);
		auto iter = m2.begin();
		for(auto& c: m1) c %= *iter++;
		return m1;
	}


	template < typename M, col_t C, row_t R, typename T >
	constexpr auto element_plus(matrix< M, C, R > const& m, T const& v){
		return make_matrix_fn(m.dims(), [&m, &v](c_t c, r_t r){
				return m(c, r) + v;
			});
	}

	template < typename M, col_t C, row_t R, typename T >
	constexpr auto element_minus(matrix< M, C, R > const& m, T const& v){
		return make_matrix_fn(m.dims(), [&m, &v](c_t c, r_t r){
				return m(c, r) - v;
			});
	}

	template < typename M, col_t C, row_t R, typename T >
	constexpr auto operator*(matrix< M, C, R > const& m, T const& v){
		return make_matrix_fn(m.dims(), [&m, &v](c_t c, r_t r){
				return m(c, r) * v;
			});
	}

	template < typename M, col_t C, row_t R, typename T >
	constexpr auto operator*(T const& v, matrix< M, C, R > const& m){
		return m * v;
	}

	template < typename M, col_t C, row_t R, typename T >
	constexpr auto operator/(matrix< M, C, R > const& m, T const& v){
		return make_matrix_fn(m.dims(), [&m, &v](c_t c, r_t r){
				return m(c, r) / v;
			});

	}

	template < typename M, col_t C, row_t R, typename T >
	constexpr auto operator%(matrix< M, C, R > const& m, T const& v){
		return make_matrix_fn(m.dims(), [&m, &v](c_t c, r_t r){
				return m(c, r) % v;
			});

	}


	template <
		typename M1, col_t C1, row_t R1,
		typename M2, col_t C2, row_t R2
	> constexpr auto operator+(
		matrix< M1, C1, R1 > const& m1,
		matrix< M2, C2, R2 > const& m2
	){
		return make_matrix_fn(get_dims(m1, m2), [&m1, &m2](c_t c, r_t r){
				return m1(c, r) + m2(c, r);
			});
	}

	template <
		typename M1, col_t C1, row_t R1,
		typename M2, col_t C2, row_t R2
	> constexpr auto operator-(
		matrix< M1, C1, R1 > const& m1,
		matrix< M2, C2, R2 > const& m2
	){
		return make_matrix_fn(get_dims(m1, m2), [&m1, &m2](c_t c, r_t r){
				return m1(c, r) - m2(c, r);
			});
	}

	template <
		typename M1, col_t C1, row_t R1,
		typename M2, col_t C2, row_t R2
	> constexpr auto element_multiplies(
		matrix< M1, C1, R1 > const& m1,
		matrix< M2, C2, R2 > const& m2
	){
		return make_matrix_fn(get_dims(m1, m2), [&m1, &m2](c_t c, r_t r){
				return m1(c, r) * m2(c, r);
			});
	}

	template <
		typename M1, col_t C1, row_t R1,
		typename M2, col_t C2, row_t R2
	> constexpr auto element_divides(
		matrix< M1, C1, R1 > const& m1,
		matrix< M2, C2, R2 > const& m2
	){
		return make_matrix_fn(get_dims(m1, m2), [&m1, &m2](c_t c, r_t r){
				return m1(c, r) / m2(c, r);
			});
	}

	template <
		typename M1, col_t C1, row_t R1,
		typename M2, col_t C2, row_t R2
	> constexpr auto element_modulus(
		matrix< M1, C1, R1 > const& m1,
		matrix< M2, C2, R2 > const& m2
	){
		return make_matrix_fn(get_dims(m1, m2), [&m1, &m2](c_t c, r_t r){
				return m1(c, r) % m2(c, r);
			});
	}


	template <
		typename M1, col_t C1, row_t R1,
		typename M2, col_t C2, row_t R2
	> constexpr auto operator*(
		matrix< M1, C1, R1 > const& m1,
		matrix< M2, C2, R2 > const& m2
	){
		static_assert(
			C1 == 0_C || R2 == 0_R || dim_t(C1) == dim_t(R2),
			"Matrix dimensions not compatible"
		);

		// Compiler should skip this for compile time dimensions
		if(m1.cols().as_dim() != m2.rows().as_dim()){
			throw std::logic_error(
				"matrix dimensions not compatible while comparing"
			);
		}

		using value_type =
			std::common_type_t< value_type_t< M1 >, value_type_t< M2 > >;

		// Compiler may optimize with the compile time dimension
		auto const size = C1 == 0_C ? m2.rows().as_dim() : m1.cols().as_dim();

		auto m = make_matrix_v< value_type >(m2.cols(), m1.rows());

		for(auto r1 = 0_r; r1 < m1.rows(); ++r1){
			for(auto c2 = 0_c; c2 < m2.cols(); ++c2){
				for(auto d = 0_d; d < size; ++d){
					m(c2, r1) += static_cast< value_type >
						(m1(c_t(d), r1)) * m2(c2, r_t(d));
				}
			}
		}

		return m;
	}


	template < typename M, col_t C, row_t R >
	constexpr auto transpose(matrix< M, C, R > const& m){
		return make_matrix_fn(
			m.rows().as_col(), m.cols().as_row(),
			[&m](c_t c, r_t r){ return m(c_t(r), r_t(c)); }
		);
	}


	template < typename M, col_t C, row_t R >
	constexpr auto operator+(matrix< M, C, R > const& m){
		return as_std_matrix(m);
	}

	template < typename M, col_t C, row_t R >
	constexpr auto operator-(matrix< M, C, R > const& m){
		return make_matrix_fn(m.dims(), [&m](c_t c, r_t r){
				return -m(c, r);
			});
	}

	template < typename M, col_t C, row_t R >
	constexpr auto abs(matrix< M, C, R > const& m){
		return make_matrix_fn(m.dims(), [&m](c_t c, r_t r){
				using std::abs;
				return abs(m(c, r));
			});
	}


	template < typename M1, row_t R1, typename M2, row_t R2 >
	constexpr auto cross_product(
		col_vector< M1, R1 > const& m1,
		col_vector< M2, R2 > const& m2
	){
		using value_type =
			std::common_type_t< value_type_t< M1 >, value_type_t< M2 > >;

		auto size = get_dim(dim_pair(1_CS, 3_RS), m1, m2);

		return make_matrix< value_type >(size, {
			{ m1(0_c, 1_r) * m2(0_c, 2_r) - m1(0_c, 2_r) * m2(0_c, 1_r) },
			{ m1(0_c, 2_r) * m2(0_c, 0_r) - m1(0_c, 0_r) * m2(0_c, 2_r) },
			{ m1(0_c, 0_r) * m2(0_c, 1_r) - m1(0_c, 1_r) * m2(0_c, 0_r) }
		});
	}

	template < typename M1, col_t C1, typename M2, col_t C2 >
	constexpr auto cross_product(
		row_vector< M1, C1 > const& m1,
		row_vector< M2, C2 > const& m2
	){
		using value_type =
			std::common_type_t< value_type_t< M1 >, value_type_t< M2 > >;

		auto size = get_dim(dim_pair(3_CS, 1_RS), m1, m2);

		return make_matrix< value_type >(size, {{
			m1(1_c, 0_r) * m2(2_c, 0_r) - m1(2_c, 0_r) * m2(1_c, 0_r),
			m1(2_c, 0_r) * m2(0_c, 0_r) - m1(0_c, 0_r) * m2(2_c, 0_r),
			m1(0_c, 0_r) * m2(1_c, 0_r) - m1(1_c, 0_r) * m2(0_c, 0_r)
		}});
	}


	template < typename M1, row_t R1, typename M2, row_t R2 >
	constexpr auto dot_product(
		col_vector< M1, R1 > const& m1,
		col_vector< M2, R2 > const& m2
	){
		using value_type =
			std::common_type_t< value_type_t< M1 >, value_type_t< M2 > >;

		auto rows = get_rows(m1, m2);

		auto res = value_type();
		for(auto r = 0_r; r < rows; ++r){
			res += m1(0_c, r) * m2(0_c, r);
		}

		return res;
	}

	template < typename M1, col_t C1, typename M2, col_t C2 >
	constexpr auto dot_product(
		row_vector< M1, C1 > const& m1,
		row_vector< M2, C2 > const& m2
	){
		using value_type =
			std::common_type_t< value_type_t< M1 >, value_type_t< M2 > >;

		auto cols = get_cols(m1, m2);

		auto res = value_type();
		for(auto c = 0_c; c < cols; ++c){
			res += m1(c, 0_r) * m2(c, 0_r);
		}

		return res;
	}


}


#endif
