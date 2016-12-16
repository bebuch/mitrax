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

#include <disposer/log.hpp>
#include <disposer/log_tag.hpp>

#include <iostream>
#include <cmath>


struct info: disposer::log_tag_base{};


int main(){
	using namespace mitrax;
	using namespace mitrax::literals;
	using disposer::log;

	auto m = make_matrix_v< std::uint16_t >(3264_CD, 2448_RD);
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
		auto mx = log(
			[](info& os){ os << "roberts_cross_x"; },
			[&m]{ return roberts_cross_x< float >(m); }
		);
		auto my = log(
			[](info& os){ os << "roberts_cross_y"; },
			[&m]{ return roberts_cross_y< float >(m); }
		);
		auto mm = log(
			[](info& os){ os << "gradient_magnitude"; },
			[&mx, &my]{ return gradient_magnitude(mx, my); }
		);
		auto ma = log(
			[](info& os){ os << "gradient_magnitude_approximately"; },
			[&mx, &my]{ return gradient_magnitude_approximately(mx, my); }
		);
		auto md = log(
			[](info& os){ os << "gradient_direction"; },
			[&mx, &my]{ return gradient_direction(mx, my); }
		);

		mitrax::png::save(normalize(mx), "image_X0.png");
		mitrax::png::save(normalize(my), "image_Y0.png");
		mitrax::png::save(normalize(mm), "image_M0.png");
		mitrax::png::save(normalize(ma), "image_A0.png");
		mitrax::png::save(normalize(md), "image_d0.png");
	}

	{
		auto mx = log(
			[](info& os){ os << "prewitt_x"; },
			[&m]{ return prewitt_x< float >(m); }
		);
		auto my = log(
			[](info& os){ os << "prewitt_y"; },
			[&m]{ return prewitt_y< float >(m); }
		);
		auto mm = log(
			[](info& os){ os << "gradient_magnitude"; },
			[&mx, &my]{ return gradient_magnitude(mx, my); }
		);
		auto ma = log(
			[](info& os){ os << "gradient_magnitude_approximately"; },
			[&mx, &my]{ return gradient_magnitude_approximately(mx, my); }
		);
		auto md = log(
			[](info& os){ os << "gradient_direction"; },
			[&mx, &my]{ return gradient_direction(mx, my); }
		);

		mitrax::png::save(normalize(mx), "image_X1.png");
		mitrax::png::save(normalize(my), "image_Y1.png");
		mitrax::png::save(normalize(mm), "image_M1.png");
		mitrax::png::save(normalize(ma), "image_A1.png");
		mitrax::png::save(normalize(md), "image_d1.png");
	}

	{
		auto mx = log(
			[](info& os){ os << "sobel_x"; },
			[&m]{ return sobel_x< float >(m); }
		);
		auto my = log(
			[](info& os){ os << "sobel_y"; },
			[&m]{ return sobel_y< float >(m); }
		);
		auto mm = log(
			[](info& os){ os << "gradient_magnitude"; },
			[&mx, &my]{ return gradient_magnitude(mx, my); }
		);
		auto ma = log(
			[](info& os){ os << "gradient_magnitude_approximately"; },
			[&mx, &my]{ return gradient_magnitude_approximately(mx, my); }
		);
		auto md = log(
			[](info& os){ os << "gradient_direction"; },
			[&mx, &my]{ return gradient_direction(mx, my); }
		);

		mitrax::png::save(normalize(mx), "image_X2.png");
		mitrax::png::save(normalize(my), "image_Y2.png");
		mitrax::png::save(normalize(mm), "image_M2.png");
		mitrax::png::save(normalize(ma), "image_A2.png");
		mitrax::png::save(normalize(md), "image_d2.png");
	}

	{
		auto mx = log(
			[](info& os){ os << "scharr_x"; },
			[&m]{ return scharr_x< float >(m); }
		);
		auto my = log(
			[](info& os){ os << "scharr_y"; },
			[&m]{ return scharr_y< float >(m); }
		);
		auto mm = log(
			[](info& os){ os << "gradient_magnitude"; },
			[&mx, &my]{ return gradient_magnitude(mx, my); }
		);
		auto ma = log(
			[](info& os){ os << "gradient_magnitude_approximately"; },
			[&mx, &my]{ return gradient_magnitude_approximately(mx, my); }
		);
		auto md = log(
			[](info& os){ os << "gradient_direction"; },
			[&mx, &my]{ return gradient_direction(mx, my); }
		);

		mitrax::png::save(normalize(mx), "image_X3.png");
		mitrax::png::save(normalize(my), "image_Y3.png");
		mitrax::png::save(normalize(mm), "image_M3.png");
		mitrax::png::save(normalize(ma), "image_A3.png");
		mitrax::png::save(normalize(md), "image_d3.png");
	}
}
