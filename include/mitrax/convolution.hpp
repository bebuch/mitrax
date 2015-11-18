//-----------------------------------------------------------------------------
// Copyright (c) 2015 Benjamin Buch
//
// https://github.com/bebuch/mitrax
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt)
//-----------------------------------------------------------------------------
#ifndef _mitrax__convolution__hpp_INCLUDED_
#define _mitrax__convolution__hpp_INCLUDED_

#include "raw_matrix.hpp"


namespace mitrax{


	// TODO: Implement as constexpr
	template <
		typename M1, size_t C1, size_t R1,
		typename M2, size_t C2, size_t R2
	> auto convolution(
		mitrax::matrix< M1, C1, R1 > const& image,
		mitrax::matrix< M2, C2, R2 > const& m
	){
		static_assert(
			(C1 == 0 || C2 == 0 || C1 >= C2) &&
			(R1 == 0 || R2 == 0 || R1 >= R2),
			"Matrix dimensions are not compatible"
		);

		if(image.cols() < m.cols() || image.rows() < m.rows()){
			throw std::logic_error("convolution matrix is bigger then image");
		}

		using value_type =
			std::common_type_t< value_type_t< M1 >, value_type_t< M2 > >;

		auto result = make_matrix< value_type >(dims(
				cols< 1 >().get() + image.cols() - m.cols(),
				rows< 1 >().get() + image.rows() - m.rows()
			));

		for(std::size_t y = 0; y < result.rows(); ++y){
			for(std::size_t x = 0; x < result.cols(); ++x){
				for(std::size_t b = 0; b < m.rows(); ++b){
					for(std::size_t a = 0; a < m.cols(); ++a){
						result(x, y) += image(x + a, y + b) * m(a, b);
					}
				}
			}
		}

		return result;
	}


	// TODO: Implement as constexpr
	template <
		typename M1, size_t C1, size_t R1,
		typename M2, size_t C2,
		typename M3, size_t R3
	> auto convolution(
		mitrax::matrix< M1, C1, R1 > const& image,
		mitrax::row_vector< M2, C2 > const& vr,
		mitrax::col_vector< M3, R3 > const& vc
	){
		return convolution(convolution(image, vr), vc);
	}


}


#endif
