#include "include/sobel.hpp"
#include "include/convert.hpp"

#include <mitrax/png.hpp>


using namespace uBLAS;


int main(){
	using namespace mitrax::literals;

	auto in = mitrax::make_matrix_v< std::uint16_t >(3264_C_rt, 2448_R_rt);
	mitrax::png::load(in, "../../examples/image_01.png");

	auto m = convert(in);

	auto mx = mitrax::convert(uBLAS::sobel_x< float >(m));
	auto my = mitrax::convert(uBLAS::sobel_y< float >(m));

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

	mitrax::png::save(normalize(mx), "image_X0.png");
	mitrax::png::save(normalize(my), "image_Y0.png");
}
