//-----------------------------------------------------------------------------
// Copyright (c) 2016 Benjamin Buch
//
// https://github.com/bebuch/mitrax
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt)
//-----------------------------------------------------------------------------
#include <mitrax/png.hpp>
#include <mitrax/convert.hpp>
#include <mitrax/convolution.hpp>

#include <iostream>
#include <cmath>


int main(){
	using namespace mitrax;
	using namespace mitrax::literals;

	auto m = make_matrix_v< std::uint8_t >(3264_C_rt, 2448_R_rt);
	mitrax::png::load(m, "image_00.png");

	constexpr auto sobel_x = make_square_matrix< int >(3_D, {
		{1, 0, -1},
		{2, 0, -2},
		{1, 0, -1}
	});

	constexpr auto sobel_y = make_square_matrix< int >(3_D, {
		{ 1,  2,  1},
		{ 0,  0,  0},
		{-1, -2, -1}
	});

	auto mx = convolution(m, sobel_x);
	auto my = convolution(m, sobel_y);

	auto normalize = [](auto const& m){
		auto minmax_iters = std::minmax_element(m.begin(), m.end());
		auto min = *minmax_iters.first;
		auto max = *minmax_iters.second;
		auto diff = max - min;

		return make_matrix_fn(m.dims(), [&m, min, diff](auto x, auto y){
			return static_cast< std::uint8_t >(
				(m(x, y) - min) * 255 / diff
			);
		});
	};

	mitrax::png::save(normalize(mx), "image_0X.png");
	mitrax::png::save(normalize(my), "image_0Y.png");

	auto ma = make_matrix_fn(get_dims(mx, my), [&mx, &my](auto j, auto k){
		auto x = mx(j, k);
		auto y = my(j, k);
		return std::sqrt(x * x + y * y);
	});

	mitrax::png::save(normalize(ma), "image_0A.png");

	auto md = make_matrix_fn(get_dims(mx, my), [&mx, &my](auto j, auto k){
		return std::atan2(mx(j, k), my(j, k));
	});

	mitrax::png::save(normalize(md), "image_0D.png");
}
