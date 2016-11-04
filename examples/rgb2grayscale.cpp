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


int main(){
	using namespace mitrax;
	using namespace mitrax::literals;

	auto m = make_matrix_v< mitrax::pixel::rgb8u >(3264_Cd, 2448_Rd);
	mitrax::png::load(m, "image_00.png");

	auto g = make_matrix_fn(m.dims(), [&m](auto x, auto y){
		auto rgb = m(x, y);
		return std::uint16_t((rgb.r + rgb.g + rgb.b) * 256 / 3);
	});

	mitrax::png::save(g, "image_01.png");
}
