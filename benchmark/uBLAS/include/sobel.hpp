//-----------------------------------------------------------------------------
// Copyright (c) 2016 Benjamin Buch
//
// https://github.com/bebuch/mitrax
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt)
//-----------------------------------------------------------------------------
#ifndef _mitrax__uBLAS__sobel__hpp_INCLUDED_
#define _mitrax__uBLAS__sobel__hpp_INCLUDED_

#include "convolution.hpp"


namespace uBLAS{


	template < typename ResultType, typename T >
	constexpr auto sobel_x(ublas::matrix< T > const& m){
		ublas::matrix< ResultType > cv(1, 3);
		cv(0, 0) = 1;
		cv(0, 1) = 2;
		cv(0, 2) = 1;

		ublas::matrix< ResultType > rv(3, 1);
		rv(0, 0) = -1;
		rv(1, 0) = 0;
		rv(2, 0) = 1;

		return convolution(m, cv, rv);
	}

	template < typename ResultType, typename T >
	constexpr auto sobel_y(ublas::matrix< T > const& m){
		ublas::matrix< ResultType > cv(1, 3);
		cv(0, 0) = -1;
		cv(0, 1) = 0;
		cv(0, 2) = 1;

		ublas::matrix< ResultType > rv(3, 1);
		rv(0, 0) = 1;
		rv(1, 0) = 2;
		rv(2, 0) = 1;

		return convolution(m, cv, rv);
	}


}


#endif
