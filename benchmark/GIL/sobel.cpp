#include "include/sobel.hpp"

#include <boost/gil/extension/io/png_io.hpp>


using namespace GIL;
using namespace boost::gil;


int main(){
	gray16_image_t m;
	png_read_image("../../examples/image_01.png", m);

	auto mx = GIL::sobel_x< float >(const_view(m));
	auto my = GIL::sobel_y< float >(const_view(m));

	png_write_view("image_X0.png", mx);
	png_write_view("image_Y0.png", my);
}
