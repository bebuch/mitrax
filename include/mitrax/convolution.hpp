//-----------------------------------------------------------------------------
// Copyright (c) 2015-2016 Benjamin Buch
//
// https://github.com/bebuch/mitrax
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt)
//-----------------------------------------------------------------------------
#ifndef _mitrax__convolution__hpp_INCLUDED_
#define _mitrax__convolution__hpp_INCLUDED_

#include "make_matrix.hpp"


namespace mitrax{


	namespace detail{


		struct multiply_op{
			template < typename T, typename U >
			constexpr auto operator()(T const& a, U const& b)const{
				return a * b;
			}
		};

		template <
			typename M1, size_t C1, size_t R1,
			typename M2, size_t C2, size_t R2,
			typename Op
		> struct convolution_worker{
			using value_type = std::decay_t< decltype(
					std::declval< Op >()(
						std::declval< value_type_t< M1 > >(),
						std::declval< value_type_t< M2 > >()
					)
				) >;

			constexpr value_type operator()(size_t x, size_t y)const{
				auto v = value_type();
				for(std::size_t b = 0; b < m.rows(); ++b){
					for(std::size_t a = 0; a < m.cols(); ++a){
						v += op(i(x + a, y + b), m(a, b));
					}
				}
				return v;
			}

			matrix< M1, C1, R1 > const& i;
			matrix< M2, C2, R2 > const& m;
			Op const& op;
		};


	}


	template <
		typename M1, size_t C1, size_t R1,
		typename M2, size_t C2, size_t R2,
		typename Op = detail::multiply_op
	> constexpr auto convolution(
		matrix< M1, C1, R1 > const& i,
		matrix< M2, C2, R2 > const& m,
		Op const& op = detail::multiply_op()
	){
		static_assert(
			(C1 == 0 || C2 == 0 || C1 >= C2) &&
			(R1 == 0 || R2 == 0 || R1 >= R2),
			"convolution matrix is bigger then image"
		);

		if(i.cols() < m.cols() || i.rows() < m.rows()){
			throw std::logic_error("convolution matrix is bigger then image");
		}

		return make_matrix_fn(
			cols< 1 >() + i.cols() - m.cols(),
			rows< 1 >() + i.rows() - m.rows(),
			detail::convolution_worker< M1, C1, R1, M2, C2, R2, Op >{
				i, m, op
			});
	}


	template <
		typename M1, size_t C1, size_t R1,
		typename M2, size_t R2,
		typename M3, size_t C3,
		typename Op = detail::multiply_op
	> constexpr auto convolution(
		matrix< M1, C1, R1 > const& image,
		col_vector< M2, R2 > const& vc,
		row_vector< M3, C3 > const& vr,
		Op const& op = detail::multiply_op()
	){
		return convolution(convolution(image, vr, op), vc, op);
	}


}


#endif
