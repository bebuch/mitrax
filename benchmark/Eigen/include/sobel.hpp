//-----------------------------------------------------------------------------
// Copyright (c) 2016 Benjamin Buch
//
// https://github.com/bebuch/mitrax
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt)
//-----------------------------------------------------------------------------
#ifndef _mitrax__Eigen__sobel__hpp_INCLUDED_
#define _mitrax__Eigen__sobel__hpp_INCLUDED_

#include "convolution.hpp"


namespace Eigen{


	template < typename ResultType, typename DerivedM >
	constexpr auto sobel_x(MatrixBase< DerivedM > const& m){
		Matrix< ResultType, 1, 3 > ck;
		ck << -1, 0, 1;

		Matrix< ResultType, 3, 1 > rk;
		rk << 1, 2, 1;

		return convolution(m, ck, rk);
	}

	template < typename ResultType, typename DerivedM >
	constexpr auto sobel_y(MatrixBase< DerivedM > const& m){
		Matrix< ResultType, 1, 3 > ck;
		ck << 1, 2, 1;

		Matrix< ResultType, 3, 1 > rk;
		rk << -1, 0, 1;

		return convolution(m, ck, rk);
	}


}


#endif
