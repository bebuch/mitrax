#include <mitrax/matrix.hpp>

#include <iostream>


int main(){
	using namespace mitrax;
	using namespace mitrax::literals;

	auto dcc = dim_pair(2_c, 4_r);
	auto drc = dim_pair(2_cd, 4_r);
	auto dcr = dim_pair(2_c, 4_rd);
	auto drr = dim_pair(2_cd, 4_rd);

	auto mcc = make_matrix_v< std::uint8_t >(2_c, 4_r);
	auto mrc = make_matrix_v< std::uint8_t >(2_cd, 4_r);
	auto mcr = make_matrix_v< std::uint8_t >(2_c, 4_rd);
	auto mrr = make_matrix_v< std::uint8_t >(2_cd, 4_rd);

	auto hcc = make_matrix_v(2_c, 4_r, std::uint8_t(), maker::heap);

	std::cout << "sizeof(dcc) = " << sizeof(dcc) << std::endl;
	std::cout << "sizeof(drc) = " << sizeof(drc) << std::endl;
	std::cout << "sizeof(dcr) = " << sizeof(dcr) << std::endl;
	std::cout << "sizeof(drr) = " << sizeof(drr) << std::endl;

	std::cout << "sizeof(mcc) = " << sizeof(mcc) << std::endl;
	std::cout << "sizeof(hcc) = " << sizeof(hcc) << std::endl;
	std::cout << "sizeof(mrc) = " << sizeof(mrc) << std::endl;
	std::cout << "sizeof(mcr) = " << sizeof(mcr) << std::endl;
	std::cout << "sizeof(mrr) = " << sizeof(mrr) << std::endl;
}
