//-----------------------------------------------------------------------------
// Copyright (c) 2015 Benjamin Buch
//
// https://github.com/bebuch/mitrax
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt)
//-----------------------------------------------------------------------------
#ifndef _mitrax__operator__hpp_INCLUDED_
#define _mitrax__operator__hpp_INCLUDED_

#include "matrix.hpp"

#include <stdexcept>


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


		template <
			typename M,
			typename T,
			size_t C,
			size_t R,
			typename Operation
		> constexpr void m1op(
			matrix< M, C, R >& m,
			T const& v,
			Operation const& operation
		){
			for(size_t y = 0; y < m.rows(); ++y){
				for(size_t x = 0; x < m.cols(); ++x){
					operation(m(x, y), v);
				}
			}
		}


		template <
			typename M1,
			typename M2,
			size_t C1,
			size_t R1,
			size_t C2,
			size_t R2,
			typename Operation
		> constexpr void m2op(
			matrix< M1, C1, R1 >& m1,
			matrix< M2, C2, R2 > const& m2,
			Operation const& operation
		){
			static_assert(
				(C1 == 0 || C2 == 0 || C1 == C2) &&
				(R1 == 0 || R2 == 0 || R1 == R2),
				"Matrix dimensions not compatible"
			);

			// Compiler should skip this for compile time dimensions
			if(m1.cols() != m2.cols() || m1.rows() != m2.rows()){
				throw std::logic_error(
					"matrix dimensions not compatible while comparing"
				);
			}

			// Compiler may optimize with the compile time dimension
			size_t cols = C1 == 0 ? m2.cols() : m1.cols();
			size_t rows = R1 == 0 ? m2.rows() : m1.rows();

			for(size_t y = 0; y < rows; ++y){
				for(size_t x = 0; x < cols; ++x){
					operation(m1(x, y), m2(x, y));
				}
			}
		}


	}


	template <
		typename M,
		typename T,
		size_t C,
		size_t R
	> constexpr auto& element_plus_assign(
		matrix< M, C, R >& m,
		T const& v
	){
		detail::m1op(m, v, detail::plus_assign());
		return m;
	}


	template <
		typename M,
		typename T,
		size_t C,
		size_t R
	> constexpr auto& element_minus_assign(
		matrix< M, C, R >& m,
		T const& v
	){
		detail::m1op(m, v, detail::minus_assign());
		return m;
	}


	template <
		typename M,
		typename T,
		size_t C,
		size_t R
	> constexpr auto& operator*=(
		matrix< M, C, R >& m,
		T const& v
	){
		detail::m1op(m, v, detail::multiplies_assign());
		return m;
	}


	template <
		typename M,
		typename T,
		size_t C,
		size_t R
	> constexpr auto& operator/=(
		matrix< M, C, R >& m,
		T const& v
	){
		detail::m1op(m, v, detail::divides_assign());
		return m;
	}


	template <
		typename M,
		typename T,
		size_t C,
		size_t R
	> constexpr auto& operator%=(
		matrix< M, C, R >& m,
		T const& v
	){
		detail::m1op(m, v, detail::modulus_assign());
		return m;
	}



	template <
		typename M1,
		typename M2,
		size_t C1,
		size_t R1,
		size_t C2,
		size_t R2
	> constexpr auto& operator+=(
		matrix< M1, C1, R1 >& m1,
		matrix< M2, C2, R2 > const& m2
	){
		detail::m2op(m1, m2, detail::plus_assign());
		return m1;
	}


	template <
		typename M1,
		typename M2,
		size_t C1,
		size_t R1,
		size_t C2,
		size_t R2
	> constexpr auto& operator-=(
		matrix< M1, C1, R1 >& m1,
		matrix< M2, C2, R2 > const& m2
	){
		detail::m2op(m1, m2, detail::minus_assign());
		return m1;
	}


	template <
		typename M1,
		typename M2,
		size_t C1,
		size_t R1,
		size_t C2,
		size_t R2
	> constexpr auto& element_multiplies_assign(
		matrix< M1, C1, R1 >& m1,
		matrix< M2, C2, R2 > const& m2
	){
		detail::m2op(m1, m2, detail::multiplies_assign());
		return m1;
	}


	template <
		typename M1,
		typename M2,
		size_t C1,
		size_t R1,
		size_t C2,
		size_t R2
	> constexpr auto& element_divides_assign(
		matrix< M1, C1, R1 >& m1,
		matrix< M2, C2, R2 > const& m2
	){
		detail::m2op(m1, m2, detail::divides_assign());
		return m1;
	}


	template <
		typename M1,
		typename M2,
		size_t C1,
		size_t R1,
		size_t C2,
		size_t R2
	> constexpr auto& element_modulus_assign(
		matrix< M1, C1, R1 >& m1,
		matrix< M2, C2, R2 > const& m2
	){
		detail::m2op(m1, m2, detail::modulus_assign());
		return m1;
	}



	template <
		typename M,
		typename T,
		size_t C,
		size_t R
	> constexpr auto element_plus(
		matrix< M, C, R > const& m,
		T const& v
	){
		auto t = m.template as_raw_matrix< std::common_type_t<
				value_type_t< matrix< M, C, R > >, T
			>, C, R >();
		return element_plus_assign(t, v);
	}

	template <
		typename M,
		typename T,
		size_t C,
		size_t R
	> constexpr auto element_minus(
		matrix< M, C, R > const& m,
		T const& v
	){
		auto t = m.template as_raw_matrix< std::common_type_t<
				value_type_t< matrix< M, C, R > >, T
			>, C, R >();
		return element_minus_assign(t, v);
	}

	template <
		typename M,
		typename T,
		size_t C,
		size_t R
	> constexpr auto operator*(
		matrix< M, C, R > const& m,
		T const& v
	){
		auto t = m.template as_raw_matrix< std::common_type_t<
				value_type_t< matrix< M, C, R > >, T
			>, C, R >();
		return t *= v;
	}

	template <
		typename M,
		typename T,
		size_t C,
		size_t R
	> constexpr auto operator/(
		matrix< M, C, R > const& m,
		T const& v
	){
		auto t = m.template as_raw_matrix< std::common_type_t<
				value_type_t< matrix< M, C, R > >, T
			>, C, R >();
		return t /= v;
	}

	template <
		typename M,
		typename T,
		size_t C,
		size_t R
	> constexpr auto operator%(
		matrix< M, C, R > const& m,
		T const& v
	){
		auto t = m.template as_raw_matrix< std::common_type_t<
				value_type_t< matrix< M, C, R > >, T
			>, C, R >();
		return t %= v;
	}



	template <
		typename M1,
		typename M2,
		size_t C1,
		size_t R1,
		size_t C2,
		size_t R2
	> constexpr auto operator+(
		matrix< M1, C1, R1 > const& m1,
		matrix< M2, C2, R2 > const& m2
	){
		auto t = m1.template as_raw_matrix< std::common_type_t<
				value_type_t< matrix< M1, C1, R1 > >,
				value_type_t< matrix< M2, C2, R2 > >
			>, C1, R1 >();
		return t += m2;
	}

	template <
		typename M1,
		typename M2,
		size_t C1,
		size_t R1,
		size_t C2,
		size_t R2
	> constexpr auto operator-(
		matrix< M1, C1, R1 > const& m1,
		matrix< M2, C2, R2 > const& m2
	){
		auto t = m1.template as_raw_matrix< std::common_type_t<
				value_type_t< matrix< M1, C1, R1 > >,
				value_type_t< matrix< M2, C2, R2 > >
			>, C1, R1 >();
		return t -= m2;
	}

	template <
		typename M1,
		typename M2,
		size_t C1,
		size_t R1,
		size_t C2,
		size_t R2
	> constexpr auto element_multiplies(
		matrix< M1, C1, R1 > const& m1,
		matrix< M2, C2, R2 > const& m2
	){
		auto t = m1.template as_raw_matrix< std::common_type_t<
				value_type_t< matrix< M1, C1, R1 > >,
				value_type_t< matrix< M2, C2, R2 > >
			>, C1, R1 >();
		return element_multiplies_assign(t, m2);
	}

	template <
		typename M1,
		typename M2,
		size_t C1,
		size_t R1,
		size_t C2,
		size_t R2
	> constexpr auto element_divides(
		matrix< M1, C1, R1 > const& m1,
		matrix< M2, C2, R2 > const& m2
	){
		auto t = m1.template as_raw_matrix< std::common_type_t<
				value_type_t< matrix< M1, C1, R1 > >,
				value_type_t< matrix< M2, C2, R2 > >
			>, C1, R1 >();
		return element_divides_assign(t, m2);
	}

	template <
		typename M1,
		typename M2,
		size_t C1,
		size_t R1,
		size_t C2,
		size_t R2
	> constexpr auto element_modulus(
		matrix< M1, C1, R1 > const& m1,
		matrix< M2, C2, R2 > const& m2
	){
		auto t = m1.template as_raw_matrix< std::common_type_t<
				value_type_t< matrix< M1, C1, R1 > >,
				value_type_t< matrix< M2, C2, R2 > >
			>, C1, R1 >();
		return element_modulus_assign(t, m2);
	}




}


#endif
