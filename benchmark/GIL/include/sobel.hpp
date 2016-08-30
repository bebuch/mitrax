//-----------------------------------------------------------------------------
// Copyright (c) 2016 Benjamin Buch
//
// https://github.com/bebuch/mitrax
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt)
//-----------------------------------------------------------------------------
#ifndef _mitrax__GIL__sobel__hpp_INCLUDED_
#define _mitrax__GIL__sobel__hpp_INCLUDED_

#include <boost/gil/gil_all.hpp>
#include <boost/gil/extension/numeric/kernel.hpp>
#include <boost/gil/extension/numeric/convolve.hpp>


namespace GIL{


	namespace gil = boost::gil;

	template < typename ResultType, typename T >
	auto sobel_x(gil::image_view< T > const& m){
		using result_pixel_t = gil::pixel< ResultType, gil::gray_layout_t >;

		constexpr ResultType cvd[3] = {1, 2, 1};
		constexpr ResultType rvd[3] = {-1, 0, 1};

		gil::kernel_1d_fixed< ResultType, 3 > cv(cvd, 1);
		gil::kernel_1d_fixed< ResultType, 3 > rv(rvd, 1);

		gil::image< result_pixel_t, true > res(m.width(), m.height());
		gil::convolve_rows_fixed< result_pixel_t >(m, cv, gil::view(res));
		gil::convolve_cols_fixed< result_pixel_t >(gil::const_view(res), rv, gil::view(res));

		return res;
	}

	template < typename ResultType, typename T >
	auto sobel_y(gil::image_view< T > const& m){
		using result_pixel_t = gil::pixel< ResultType, gil::gray_layout_t >;

		constexpr ResultType cvd[3] = {-1, 0, 1};
		constexpr ResultType rvd[3] = {1, 2, 1};

		gil::kernel_1d_fixed< ResultType, 3 > cv(cvd, 1);
		gil::kernel_1d_fixed< ResultType, 3 > rv(rvd, 1);

		gil::image< result_pixel_t, true > res(m.width(), m.height());
		gil::convolve_rows_fixed< result_pixel_t >(m, cv, gil::view(res));
		gil::convolve_cols_fixed< result_pixel_t >(gil::const_view(res), rv, gil::view(res));

		return res;
	}


}


#endif
