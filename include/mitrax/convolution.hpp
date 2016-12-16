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


		template <
			typename M1, col_t C1, row_t R1,
			typename M2, col_t C2, row_t R2,
			typename SumOp, typename MulOp
		> struct convolution_worker{
			constexpr auto operator()(size_t x, size_t y)const{
				auto v = std::decay_t< decltype(
					sum(mul(i(0, 0), m(0, 0)), mul(i(0, 0), m(0, 0)))) >();
				for(size_t b = 0; b < size_t(m.rows()); ++b){
					for(size_t a = 0; a < size_t(m.cols()); ++a){
						v = sum(v, mul(i(x + a, y + b), m(a, b)));
					}
				}
				return v;
			}

			matrix< M1, C1, R1 > const& i;
			matrix< M2, C2, R2 > const& m;
			SumOp const& sum;
			MulOp const& mul;
		};


	}


	template <
		typename M1, col_t C1, row_t R1,
		typename M2, col_t C2, row_t R2,
		typename SumOp = std::plus<>,
		typename MulOp = std::multiplies<>
	> constexpr auto convolution(
		matrix< M1, C1, R1 > const& i,
		matrix< M2, C2, R2 > const& m,
		SumOp const& sum = std::plus<>(),
		MulOp const& mul = std::multiplies<>()
	){
		static_assert(
			(C1 == 0_C || C2 == 0_C || C1 >= C2) &&
			(R1 == 0_R || R2 == 0_R || R1 >= R2),
			"convolution matrix is bigger then image"
		);

		if(i.cols() < m.cols() || i.rows() < m.rows()){
			throw std::logic_error("convolution matrix is bigger then image");
		}

		return make_matrix_fn(
			1_c + i.cols() - m.cols(),
			1_r + i.rows() - m.rows(),
			detail::convolution_worker< M1, C1, R1, M2, C2, R2, SumOp, MulOp >{
				i, m, sum, mul
			});
	}


	template <
		typename M1, col_t C1, row_t R1,
		typename M2, row_t R2,
		typename M3, col_t C3,
		typename SumOp = std::plus<>,
		typename MulOp = std::multiplies<>
	> constexpr auto convolution(
		matrix< M1, C1, R1 > const& image,
		col_vector< M2, R2 > const& vc,
		row_vector< M3, C3 > const& vr,
		SumOp const& sum = std::plus<>(),
		MulOp const& mul = std::multiplies<>()
	){
		return convolution(convolution(image, vr, sum, mul), vc, sum, mul);
	}


}


#endif
