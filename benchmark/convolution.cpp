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
#include <mitrax/convolution/edge_operators.hpp>

#include <iostream>
#include <cmath>


int main(){
	using namespace mitrax;
	using namespace mitrax::literals;

	auto m = make_matrix_v< std::uint8_t >(3264_C_rt, 2448_R_rt);
	mitrax::png::load(m, "image_01.png");

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

	{
		auto mx = roberts_cross_x(m);
		auto my = roberts_cross_y(m);
		auto ma = gradient_magnitude(mx, my);
		auto md = gradient_direction(mx, my);

		mitrax::png::save(normalize(mx), "image_X0.png");
		mitrax::png::save(normalize(my), "image_Y0.png");
		mitrax::png::save(normalize(ma), "image_A0.png");
		mitrax::png::save(normalize(md), "image_D0.png");
	}

	{
		auto mx = prewitt_x(m);
		auto my = prewitt_y(m);
		auto ma = gradient_magnitude(mx, my);
		auto md = gradient_direction(mx, my);

		mitrax::png::save(normalize(mx), "image_X1.png");
		mitrax::png::save(normalize(my), "image_Y1.png");
		mitrax::png::save(normalize(ma), "image_A1.png");
		mitrax::png::save(normalize(md), "image_D1.png");
	}

	{
		auto mx = sobel_x(m);
		auto my = sobel_y(m);
		auto ma = gradient_magnitude(mx, my);
		auto md = gradient_direction(mx, my);

		mitrax::png::save(normalize(mx), "image_X2.png");
		mitrax::png::save(normalize(my), "image_Y2.png");
		mitrax::png::save(normalize(ma), "image_A2.png");
		mitrax::png::save(normalize(md), "image_D2.png");
	}

	{
		auto mx = scharr_x(m);
		auto my = scharr_y(m);
		auto ma = gradient_magnitude(mx, my);
		auto md = gradient_direction(mx, my);

		mitrax::png::save(normalize(mx), "image_X3.png");
		mitrax::png::save(normalize(my), "image_Y3.png");
		mitrax::png::save(normalize(ma), "image_A3.png");
		mitrax::png::save(normalize(md), "image_D3.png");
	}
}
