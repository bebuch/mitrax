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

#include <stdexcept>
#include <cmath>


namespace mitrax{


	namespace detail{


		struct plus_assign{
			template < typename T, typename U >
			constexpr void operator()(T& a, U const& b)const{
				a += b;
			}
		};

		struct minus_assign{
			template < typename T, typename U >
			constexpr void operator()(T& a, U const& b)const{
				a -= b;
			}
		};

		struct multiplies_assign{
			template < typename T, typename U >
			constexpr void operator()(T& a, U const& b)const{
				a *= b;
			}
		};

		struct divides_assign{
			template < typename T, typename U >
			constexpr void operator()(T& a, U const& b)const{
				a /= b;
			}
		};

		struct modulus_assign{
			template < typename T, typename U >
			constexpr void operator()(T& a, U const& b)const{
				a %= b;
			}
		};


		template < typename M, size_t C, size_t R, typename T, typename O >
		constexpr void m1op(
			matrix< M, C, R >& m,
			T const& v,
			O const& operation
		){
			for(size_t y = 0; y < m.rows(); ++y){
				for(size_t x = 0; x < m.cols(); ++x){
					operation(m(x, y), v);
				}
			}
		}


		template <
			typename M1, size_t C1, size_t R1,
			typename M2, size_t C2, size_t R2,
			typename O
		> constexpr void m2op(
			matrix< M1, C1, R1 >& m1,
			matrix< M2, C2, R2 > const& m2,
			O const& operation
		){
			auto size = get_dims(m1, m2);

			for(size_t y = 0; y < size.rows(); ++y){
				for(size_t x = 0; x < size.cols(); ++x){
					operation(m1(x, y), m2(x, y));
				}
			}
		}


		template < typename M, size_t C, size_t R >
		class unary_op{
		public:
			constexpr unary_op(matrix< M, C, R > const& m): m_(m) {}

		protected:
			matrix< M, C, R > const& m_;
		};

		template < typename M, size_t C, size_t R >
		struct transpose_f: unary_op< M, C, R >{
			using unary_op< M, C, R >::unary_op;

			constexpr auto operator()(size_t x, size_t y)const{
				return this->m_(y, x);
			}
		};

		template < typename M, size_t C, size_t R >
		struct unary_minus_op: unary_op< M, C, R >{
			using unary_op< M, C, R >::unary_op;

			constexpr auto operator()(size_t x, size_t y)const{
				return -this->m_(x, y);
			}
		};

		template < typename M, size_t C, size_t R >
		struct abs_op: unary_op< M, C, R >{
			using unary_op< M, C, R >::unary_op;

			constexpr auto operator()(size_t x, size_t y)const{
				using std::abs;
				return abs(this->m_(x, y));
			}
		};


	}


	template < typename M, size_t C, size_t R, typename T >
	constexpr auto& element_plus_assign(
		matrix< M, C, R >& m,
		T const& v
	){
		detail::m1op(m, v, detail::plus_assign());
		return m;
	}


	template < typename M, size_t C, size_t R, typename T >
	constexpr auto& element_minus_assign(
		matrix< M, C, R >& m,
		T const& v
	){
		detail::m1op(m, v, detail::minus_assign());
		return m;
	}


	template < typename M, size_t C, size_t R, typename T >
	constexpr auto& operator*=(
		matrix< M, C, R >& m,
		T const& v
	){
		detail::m1op(m, v, detail::multiplies_assign());
		return m;
	}


	template < typename M, size_t C, size_t R, typename T >
	constexpr auto& operator/=(
		matrix< M, C, R >& m,
		T const& v
	){
		detail::m1op(m, v, detail::divides_assign());
		return m;
	}


	template < typename M, size_t C, size_t R, typename T >
	constexpr auto& operator%=(
		matrix< M, C, R >& m,
		T const& v
	){
		detail::m1op(m, v, detail::modulus_assign());
		return m;
	}



	template <
		typename M1, size_t C1, size_t R1,
		typename M2, size_t C2, size_t R2
	> constexpr auto& operator+=(
		matrix< M1, C1, R1 >& m1,
		matrix< M2, C2, R2 > const& m2
	){
		detail::m2op(m1, m2, detail::plus_assign());
		return m1;
	}


	template <
		typename M1, size_t C1, size_t R1,
		typename M2, size_t C2, size_t R2
	> constexpr auto& operator-=(
		matrix< M1, C1, R1 >& m1,
		matrix< M2, C2, R2 > const& m2
	){
		detail::m2op(m1, m2, detail::minus_assign());
		return m1;
	}


	template <
		typename M1, size_t C1, size_t R1,
		typename M2, size_t C2, size_t R2
	> constexpr auto& element_multiplies_assign(
		matrix< M1, C1, R1 >& m1,
		matrix< M2, C2, R2 > const& m2
	){
		detail::m2op(m1, m2, detail::multiplies_assign());
		return m1;
	}


	template <
		typename M1, size_t C1, size_t R1,
		typename M2, size_t C2, size_t R2
	> constexpr auto& element_divides_assign(
		matrix< M1, C1, R1 >& m1,
		matrix< M2, C2, R2 > const& m2
	){
		detail::m2op(m1, m2, detail::divides_assign());
		return m1;
	}


	template <
		typename M1, size_t C1, size_t R1,
		typename M2, size_t C2, size_t R2
	> constexpr auto& element_modulus_assign(
		matrix< M1, C1, R1 >& m1,
		matrix< M2, C2, R2 > const& m2
	){
		detail::m2op(m1, m2, detail::modulus_assign());
		return m1;
	}



	template < typename M, size_t C, size_t R, typename T >
	constexpr auto element_plus(
		matrix< M, C, R > const& m,
		T const& v
	){
		auto t = convert< std::common_type_t< value_type_t< M >, T > >(m);
		return element_plus_assign(t, v);
	}

	template < typename M, size_t C, size_t R, typename T >
	constexpr auto element_minus(
		matrix< M, C, R > const& m,
		T const& v
	){
		auto t = convert< std::common_type_t< value_type_t< M >, T > >(m);
		return element_minus_assign(t, v);
	}

	template < typename M, size_t C, size_t R, typename T >
	constexpr auto operator*(
		matrix< M, C, R > const& m,
		T const& v
	){
		auto t = convert< std::common_type_t< value_type_t< M >, T > >(m);
		return t *= v;
	}

	template < typename M, size_t C, size_t R, typename T >
	constexpr auto operator*(
		T const& v,
		matrix< M, C, R > const& m
	){
		return m * v;
	}

	template < typename M, size_t C, size_t R, typename T >
	constexpr auto operator/(
		matrix< M, C, R > const& m,
		T const& v
	){
		auto t = convert< std::common_type_t< value_type_t< M >, T > >(m);
		return t /= v;
	}

	template < typename M, size_t C, size_t R, typename T >
	constexpr auto operator%(
		matrix< M, C, R > const& m,
		T const& v
	){
		auto t = convert< std::common_type_t< value_type_t< M >, T > >(m);
		return t %= v;
	}



	template <
		typename M1, size_t C1, size_t R1,
		typename M2, size_t C2, size_t R2
	> constexpr auto operator+(
		matrix< M1, C1, R1 > const& m1,
		matrix< M2, C2, R2 > const& m2
	){
		auto t = convert< std::common_type_t<
				value_type_t< M1 >, value_type_t< M2 >
			> >(m1);
		return t += m2;
	}

	template <
		typename M1, size_t C1, size_t R1,
		typename M2, size_t C2, size_t R2
	> constexpr auto operator-(
		matrix< M1, C1, R1 > const& m1,
		matrix< M2, C2, R2 > const& m2
	){
		auto t = convert< std::common_type_t<
				value_type_t< M1 >, value_type_t< M2 >
			> >(m1);
		return t -= m2;
	}

	template <
		typename M1, size_t C1, size_t R1,
		typename M2, size_t C2, size_t R2
	> constexpr auto element_multiplies(
		matrix< M1, C1, R1 > const& m1,
		matrix< M2, C2, R2 > const& m2
	){
		auto t = convert< std::common_type_t<
				value_type_t< M1 >, value_type_t< M2 >
			> >(m1);
		return element_multiplies_assign(t, m2);
	}

	template <
		typename M1, size_t C1, size_t R1,
		typename M2, size_t C2, size_t R2
	> constexpr auto element_divides(
		matrix< M1, C1, R1 > const& m1,
		matrix< M2, C2, R2 > const& m2
	){
		auto t = convert< std::common_type_t<
				value_type_t< M1 >, value_type_t< M2 >
			> >(m1);
		return element_divides_assign(t, m2);
	}

	template <
		typename M1, size_t C1, size_t R1,
		typename M2, size_t C2, size_t R2
	> constexpr auto element_modulus(
		matrix< M1, C1, R1 > const& m1,
		matrix< M2, C2, R2 > const& m2
	){
		auto t = convert< std::common_type_t<
				value_type_t< M1 >, value_type_t< M2 >
			> >(m1);
		return element_modulus_assign(t, m2);
	}


	template <
		typename M1, size_t C1, size_t R1,
		typename M2, size_t C2, size_t R2
	> constexpr auto operator*(
		matrix< M1, C1, R1 > const& m1,
		matrix< M2, C2, R2 > const& m2
	){
		static_assert(
			C1 == 0 || R2 == 0 || C1 == R2,
			"Matrix dimensions not compatible"
		);

		// Compiler should skip this for compile time dimensions
		if(m1.cols() != m2.rows()){
			throw std::logic_error(
				"matrix dimensions not compatible while comparing"
			);
		}

		using value_type =
			std::common_type_t< value_type_t< M1 >, value_type_t< M2 > >;

		// Compiler may optimize with the compile time dimension
		size_t size = C1 == 0 ? m2.rows() : m1.cols();

		auto m = make_matrix< value_type >(m2.cols(), m1.rows());

		for(size_t r1 = 0; r1 < m1.rows(); ++r1){
			for(size_t c2 = 0; c2 < m2.cols(); ++c2){
				for(size_t i = 0; i < size; ++i){
					m(c2, r1) +=
						static_cast< value_type >(m1(i, r1)) * m2(c2, i);
				}
			}
		}

		return m;
	}


	template < typename M, size_t C, size_t R >
	constexpr auto transpose(matrix< M, C, R > const& m){
		return make_matrix_by_function(
			m.rows().as_col(), m.cols().as_row(),
			detail::transpose_f< M, C, R >(m)
		);
	}


	template < typename M, size_t C, size_t R >
	constexpr auto operator+(matrix< M, C, R > const& m){
		return as_raw_matrix(m);
	}

	template < typename M, size_t C, size_t R >
	constexpr auto operator-(matrix< M, C, R > const& m){
		return make_matrix_by_function(m.dims(),
			detail::unary_minus_op< M, C, R >(m));
	}

	template < typename M, size_t C, size_t R >
	constexpr auto abs(matrix< M, C, R > const& m){
		return make_matrix_by_function(m.dims(), detail::abs_op< M, C, R >(m));
	}


	template < typename M1, size_t R1, typename M2, size_t R2 >
	constexpr auto cross_product(
		col_vector< M1, R1 > const& m1,
		col_vector< M2, R2 > const& m2
	){
		static_assert(
			(R1 == 3 || R1 == 0) && (R2 == 3 || R2 == 0),
			"Matrix dimensions not compatible"
		);

		// Compiler should skip this for compile time dimensions
		if(m1.rows() != m2.rows() || m1.rows() != 3){
			throw std::logic_error(
				"matrix dimensions not compatible while comparing"
			);
		}

		using value_type =
			std::common_type_t< value_type_t< M1 >, value_type_t< M2 > >;

		// TODO: Use the compile time size from m1 or m2, if one is ct
		return make_col_vector< value_type >(rows< 3 >(), {
			m1[1] * m2[2] - m1[2] * m2[1],
			m1[2] * m2[0] - m1[0] * m2[2],
			m1[0] * m2[1] - m1[1] * m2[0]
		});
	}

	template < typename M1, size_t C1, typename M2, size_t C2 >
	constexpr auto cross_product(
		row_vector< M1, C1 > const& m1,
		row_vector< M2, C2 > const& m2
	){
		static_assert(
			(C1 == 3 || C1 == 0) && (C2 == 3 || C2 == 0),
			"Matrix dimensions not compatible"
		);

		// Compiler should skip this for compile time dimensions
		if(m1.cols() != m2.cols() || m1.cols() != 3){
			throw std::logic_error(
				"matrix dimensions not compatible while comparing"
			);
		}

		using value_type =
			std::common_type_t< value_type_t< M1 >, value_type_t< M2 > >;

		return make_row_vector< value_type >(cols< 3 >(), {
			m1[1] * m2[2] - m1[2] * m2[1],
			m1[2] * m2[0] - m1[0] * m2[2],
			m1[0] * m2[1] - m1[1] * m2[0]
		});
	}


	template < typename M1, size_t R1, typename M2, size_t R2 >
	constexpr auto dot_product(
		col_vector< M1, R1 > const& m1,
		col_vector< M2, R2 > const& m2
	){
		using value_type =
			std::common_type_t< value_type_t< M1 >, value_type_t< M2 > >;

		auto size = get_rows(m1, m2);

		value_type res = 0;
		for(size_t i = 0; i < size; ++i){
			res += m1[i] * m2[i];
		}

		return res;
	}

	template < typename M1, size_t C1, typename M2, size_t C2 >
	constexpr auto dot_product(
		row_vector< M1, C1 > const& m1,
		row_vector< M2, C2 > const& m2
	){
		using value_type =
			std::common_type_t< value_type_t< M1 >, value_type_t< M2 > >;

		auto size = get_cols(m1, m2);

		value_type res = 0;
		for(size_t i = 0; i < size; ++i){
			res += m1[i] * m2[i];
		}

		return res;
	}


}


#endif
