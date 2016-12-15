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


	template < typename M, col_ct C, row_ct R, typename T >
	constexpr matrix< M, C, R >& element_plus_assign(
		matrix< M, C, R >& m, T const& v
	){
		for(auto& c: m) c += v;
		return m;
	}

	template < typename M, col_ct C, row_ct R, typename T >
	constexpr matrix< M, C, R >& element_minus_assign(
		matrix< M, C, R >& m, T const& v
	){
		for(auto& c: m) c -= v;
		return m;
	}

	template < typename M, col_ct C, row_ct R, typename T >
	constexpr matrix< M, C, R >& operator*=(matrix< M, C, R >& m, T const& v){
		for(auto& c: m) c *= v;
		return m;
	}

	template < typename M, col_ct C, row_ct R, typename T >
	constexpr matrix< M, C, R >& operator/=(matrix< M, C, R >& m, T const& v){
		for(auto& c: m) c /= v;
		return m;
	}

	template < typename M, col_ct C, row_ct R, typename T >
	constexpr matrix< M, C, R >& operator%=(matrix< M, C, R >& m, T const& v){
		for(auto& c: m) c %= v;
		return m;
	}


	template <
		typename M1, col_ct C1, row_ct R1,
		typename M2, col_ct C2, row_ct R2
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
		typename M1, col_ct C1, row_ct R1,
		typename M2, col_ct C2, row_ct R2
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
		typename M1, col_ct C1, row_ct R1,
		typename M2, col_ct C2, row_ct R2
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
		typename M1, col_ct C1, row_ct R1,
		typename M2, col_ct C2, row_ct R2
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
		typename M1, col_ct C1, row_ct R1,
		typename M2, col_ct C2, row_ct R2
	> constexpr matrix< M1, C1, R1 >& element_modulus_assign(
		matrix< M1, C1, R1 >& m1,
		matrix< M2, C2, R2 > const& m2
	){
		get_dims(m1, m2);
		auto iter = m2.begin();
		for(auto& c: m1) c %= *iter++;
		return m1;
	}


	template < typename M, col_ct C, row_ct R, typename T >
	constexpr auto element_plus(matrix< M, C, R > const& m, T const& v){
		return make_matrix_fn(m.dims(), [&m, &v](size_t x, size_t y){
				return m(x, y) + v;
			});
	}

	template < typename M, col_ct C, row_ct R, typename T >
	constexpr auto element_minus(matrix< M, C, R > const& m, T const& v){
		return make_matrix_fn(m.dims(), [&m, &v](size_t x, size_t y){
				return m(x, y) - v;
			});
	}

	template < typename M, col_ct C, row_ct R, typename T >
	constexpr auto operator*(matrix< M, C, R > const& m, T const& v){
		return make_matrix_fn(m.dims(), [&m, &v](size_t x, size_t y){
				return m(x, y) * v;
			});
	}

	template < typename M, col_ct C, row_ct R, typename T >
	constexpr auto operator*(T const& v, matrix< M, C, R > const& m){
		return m * v;
	}

	template < typename M, col_ct C, row_ct R, typename T >
	constexpr auto operator/(matrix< M, C, R > const& m, T const& v){
		return make_matrix_fn(m.dims(), [&m, &v](size_t x, size_t y){
				return m(x, y) / v;
			});

	}

	template < typename M, col_ct C, row_ct R, typename T >
	constexpr auto operator%(matrix< M, C, R > const& m, T const& v){
		return make_matrix_fn(m.dims(), [&m, &v](size_t x, size_t y){
				return m(x, y) % v;
			});

	}


	template <
		typename M1, col_ct C1, row_ct R1,
		typename M2, col_ct C2, row_ct R2
	> constexpr auto operator+(
		matrix< M1, C1, R1 > const& m1,
		matrix< M2, C2, R2 > const& m2
	){
		return make_matrix_fn(get_dims(m1, m2), [&m1, &m2](size_t x, size_t y){
				return m1(x, y) + m2(x, y);
			});
	}

	template <
		typename M1, col_ct C1, row_ct R1,
		typename M2, col_ct C2, row_ct R2
	> constexpr auto operator-(
		matrix< M1, C1, R1 > const& m1,
		matrix< M2, C2, R2 > const& m2
	){
		return make_matrix_fn(get_dims(m1, m2), [&m1, &m2](size_t x, size_t y){
				return m1(x, y) - m2(x, y);
			});
	}

	template <
		typename M1, col_ct C1, row_ct R1,
		typename M2, col_ct C2, row_ct R2
	> constexpr auto element_multiplies(
		matrix< M1, C1, R1 > const& m1,
		matrix< M2, C2, R2 > const& m2
	){
		return make_matrix_fn(get_dims(m1, m2), [&m1, &m2](size_t x, size_t y){
				return m1(x, y) * m2(x, y);
			});
	}

	template <
		typename M1, col_ct C1, row_ct R1,
		typename M2, col_ct C2, row_ct R2
	> constexpr auto element_divides(
		matrix< M1, C1, R1 > const& m1,
		matrix< M2, C2, R2 > const& m2
	){
		return make_matrix_fn(get_dims(m1, m2), [&m1, &m2](size_t x, size_t y){
				return m1(x, y) / m2(x, y);
			});
	}

	template <
		typename M1, col_ct C1, row_ct R1,
		typename M2, col_ct C2, row_ct R2
	> constexpr auto element_modulus(
		matrix< M1, C1, R1 > const& m1,
		matrix< M2, C2, R2 > const& m2
	){
		return make_matrix_fn(get_dims(m1, m2), [&m1, &m2](size_t x, size_t y){
				return m1(x, y) % m2(x, y);
			});
	}


	template <
		typename M1, col_ct C1, row_ct R1,
		typename M2, col_ct C2, row_ct R2
	> constexpr auto operator*(
		matrix< M1, C1, R1 > const& m1,
		matrix< M2, C2, R2 > const& m2
	){
		static_assert(
			C1 == 0_C || R2 == 0_R || size_t(C1) == size_t(R2),
			"Matrix dimensions not compatible"
		);

		// Compiler should skip this for compile time dimensions
		if(size_t(m1.cols()) != size_t(m2.rows())){
			throw std::logic_error(
				"matrix dimensions not compatible while comparing"
			);
		}

		using value_type =
			std::common_type_t< value_type_t< M1 >, value_type_t< M2 > >;

		// Compiler may optimize with the compile time dimension
		size_t const size = C1 == 0_C ? size_t(m2.rows()) : size_t(m1.cols());

		auto m = make_matrix_v< value_type >(m2.cols(), m1.rows());

		for(size_t r1 = 0; r1 < size_t(m1.rows()); ++r1){
			for(size_t c2 = 0; c2 < size_t(m2.cols()); ++c2){
				for(size_t i = 0; i < size; ++i){
					m(c2, r1) +=
						static_cast< value_type >(m1(i, r1)) * m2(c2, i);
				}
			}
		}

		return m;
	}


	template < typename M, col_ct C, row_ct R >
	constexpr auto transpose(matrix< M, C, R > const& m){
		return make_matrix_fn(
			m.rows().as_col(), m.cols().as_row(),
			[&m](size_t x, size_t y){ return m(y, x); }
		);
	}


	template < typename M, col_ct C, row_ct R >
	constexpr auto operator+(matrix< M, C, R > const& m){
		return as_std_matrix(m);
	}

	template < typename M, col_ct C, row_ct R >
	constexpr auto operator-(matrix< M, C, R > const& m){
		return make_matrix_fn(m.dims(), [&m](size_t x, size_t y){
				return -m(x, y);
			});
	}

	template < typename M, col_ct C, row_ct R >
	constexpr auto abs(matrix< M, C, R > const& m){
		return make_matrix_fn(m.dims(), [&m](size_t x, size_t y){
				using std::abs;
				return abs(m(x, y));
			});
	}


	template < typename M1, row_ct R1, typename M2, row_ct R2 >
	constexpr auto cross_product(
		col_vector< M1, R1 > const& m1,
		col_vector< M2, R2 > const& m2
	){
		static_assert(
			(R1 == 3_R || R1 == 0_R) && (R2 == 3_R || R2 == 0_R),
			"Matrix dimensions not compatible"
		);

		// Compiler should skip this for compile time dimensions
		if(m1.rows() != m2.rows() || m1.rows() != 3_r){
			throw std::logic_error(
				"matrix dimensions not compatible while comparing"
			);
		}

		using value_type =
			std::common_type_t< value_type_t< M1 >, value_type_t< M2 > >;

		// TODO: Use the compile time size from m1 or m2, if one is ct
		return make_vector< value_type >(3_r, {
			m1[1] * m2[2] - m1[2] * m2[1],
			m1[2] * m2[0] - m1[0] * m2[2],
			m1[0] * m2[1] - m1[1] * m2[0]
		});
	}

	template < typename M1, col_ct C1, typename M2, col_ct C2 >
	constexpr auto cross_product(
		row_vector< M1, C1 > const& m1,
		row_vector< M2, C2 > const& m2
	){
		static_assert(
			(C1 == 3_C || C1 == 0_C) && (C2 == 3_C || C2 == 0_C),
			"Matrix dimensions not compatible"
		);

		// Compiler should skip this for compile time dimensions
		if(m1.cols() != m2.cols() || m1.cols() != 3_r){
			throw std::logic_error(
				"matrix dimensions not compatible while comparing"
			);
		}

		using value_type =
			std::common_type_t< value_type_t< M1 >, value_type_t< M2 > >;

		return make_vector< value_type >(3_c, {
			m1[1] * m2[2] - m1[2] * m2[1],
			m1[2] * m2[0] - m1[0] * m2[2],
			m1[0] * m2[1] - m1[1] * m2[0]
		});
	}


	template < typename M1, row_ct R1, typename M2, row_ct R2 >
	constexpr auto dot_product(
		col_vector< M1, R1 > const& m1,
		col_vector< M2, R2 > const& m2
	){
		using value_type =
			std::common_type_t< value_type_t< M1 >, value_type_t< M2 > >;

		auto rows = get_rows(m1, m2);

		value_type res = 0;
		for(size_t i = 0; i < size_t(rows); ++i){
			res += m1[i] * m2[i];
		}

		return res;
	}

	template < typename M1, col_ct C1, typename M2, col_ct C2 >
	constexpr auto dot_product(
		row_vector< M1, C1 > const& m1,
		row_vector< M2, C2 > const& m2
	){
		using value_type =
			std::common_type_t< value_type_t< M1 >, value_type_t< M2 > >;

		auto cols = get_cols(m1, m2);

		value_type res = 0;
		for(size_t i = 0; i < size_t(cols); ++i){
			res += m1[i] * m2[i];
		}

		return res;
	}


}


#endif
