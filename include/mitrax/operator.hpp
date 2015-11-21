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

#include "make_matrix.hpp"

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


		template < typename M, size_t C, size_t R, size_t ... I >
		constexpr auto transpose_static(
			matrix< M, C, R > const& m,
			std::index_sequence< I ... >
		){
			return matrix< raw_matrix_impl< value_type_t< M >, R, C >, R, C >(
				raw_matrix_impl< value_type_t< M >, R, C >(
					m.rows().as_col(), m.cols().as_row(),
					{{ m(I / R, I % R) ... }}
				)
			);
		}

		template < typename M, size_t C, size_t R >
		auto transpose_dynamic(matrix< M, C, R > const& m){
			boost::container::vector< value_type_t< M > > v;
			
			v.reserve(
				static_cast< size_t >(m.cols()) *
				static_cast< size_t >(m.rows())
			);

			for(size_t x = 0; x < m.cols(); ++x){
				for(size_t y = 0; y < m.rows(); ++y){
					v.emplace_back(m(x, y));
				}
			}
			
			return matrix< raw_matrix_impl< value_type_t< M >, R, C >, R, C >(
				raw_matrix_impl< value_type_t< M >, R, C >(
					m.rows().as_col(), m.cols().as_row(), std::move(v)
				)
			);
		}

		template < typename M, size_t C, size_t R >
		constexpr auto transpose(matrix< M, C, R > const& m){
			return transpose_static(m, std::make_index_sequence< C * R >());
		}

		template < typename M, size_t R >
		auto transpose(matrix< M, 0, R > const& m){
			return transpose_dynamic(m);
		}

		template < typename M, size_t C >
		auto transpose(matrix< M, C, 0 > const& m){
			return transpose_dynamic(m);
		}

		template < typename M >
		auto transpose(matrix< M, 0, 0 > const& m){
			return transpose_dynamic(m);
		}


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
		auto t = m.template convert< std::common_type_t<
				value_type_t< M >, T
			> >();
		return element_plus_assign(t, v);
	}

	template < typename M, size_t C, size_t R, typename T >
	constexpr auto element_minus(
		matrix< M, C, R > const& m,
		T const& v
	){
		auto t = m.template convert< std::common_type_t<
				value_type_t< M >, T
			> >();
		return element_minus_assign(t, v);
	}

	template < typename M, size_t C, size_t R, typename T >
	constexpr auto operator*(
		matrix< M, C, R > const& m,
		T const& v
	){
		auto t = m.template convert< std::common_type_t<
				value_type_t< M >, T
			> >();
		return t *= v;
	}

	template < typename M, size_t C, size_t R, typename T >
	constexpr auto operator/(
		matrix< M, C, R > const& m,
		T const& v
	){
		auto t = m.template convert< std::common_type_t<
				value_type_t< M >, T
			> >();
		return t /= v;
	}

	template < typename M, size_t C, size_t R, typename T >
	constexpr auto operator%(
		matrix< M, C, R > const& m,
		T const& v
	){
		auto t = m.template convert< std::common_type_t<
				value_type_t< M >, T
			> >();
		return t %= v;
	}



	template <
		typename M1, size_t C1, size_t R1,
		typename M2, size_t C2, size_t R2
	> constexpr auto operator+(
		matrix< M1, C1, R1 > const& m1,
		matrix< M2, C2, R2 > const& m2
	){
		auto t = m1.template convert< std::common_type_t<
				value_type_t< M1 >, value_type_t< M2 >
			> >();
		return t += m2;
	}

	template <
		typename M1, size_t C1, size_t R1,
		typename M2, size_t C2, size_t R2
	> constexpr auto operator-(
		matrix< M1, C1, R1 > const& m1,
		matrix< M2, C2, R2 > const& m2
	){
		auto t = m1.template convert< std::common_type_t<
				value_type_t< M1 >, value_type_t< M2 >
			> >();
		return t -= m2;
	}

	template <
		typename M1, size_t C1, size_t R1,
		typename M2, size_t C2, size_t R2
	> constexpr auto element_multiplies(
		matrix< M1, C1, R1 > const& m1,
		matrix< M2, C2, R2 > const& m2
	){
		auto t = m1.template convert< std::common_type_t<
				value_type_t< M1 >, value_type_t< M2 >
			> >();
		return element_multiplies_assign(t, m2);
	}

	template <
		typename M1, size_t C1, size_t R1,
		typename M2, size_t C2, size_t R2
	> constexpr auto element_divides(
		matrix< M1, C1, R1 > const& m1,
		matrix< M2, C2, R2 > const& m2
	){
		auto t = m1.template convert< std::common_type_t<
				value_type_t< M1 >, value_type_t< M2 >
			> >();
		return element_divides_assign(t, m2);
	}

	template <
		typename M1, size_t C1, size_t R1,
		typename M2, size_t C2, size_t R2
	> constexpr auto element_modulus(
		matrix< M1, C1, R1 > const& m1,
		matrix< M2, C2, R2 > const& m2
	){
		auto t = m1.template convert< std::common_type_t<
				value_type_t< M1 >, value_type_t< M2 >
			> >();
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

		auto m = make_matrix< value_type >(m2.cols().init(), m1.rows().init());

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
		return detail::transpose(m);
	}


}


#endif
