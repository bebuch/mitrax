#include <mitrax/matrix.hpp>

#include <iostream>


int main(){
	using namespace mitrax;
	using namespace mitrax::literals;

	auto dcc = dim_pair(2_CS, 4_RS);
	auto drc = dim_pair(2_CD, 4_RS);
	auto dcr = dim_pair(2_CS, 4_RD);
	auto drr = dim_pair(2_CD, 4_RD);

	auto mcc = make_matrix_v< std::uint8_t >(2_CS, 4_RS);
	auto mrc = make_matrix_v< std::uint8_t >(2_CD, 4_RS);
	auto mcr = make_matrix_v< std::uint8_t >(2_CS, 4_RD);
	auto mrr = make_matrix_v< std::uint8_t >(2_CD, 4_RD);

	auto hcc = make_matrix_v(2_CS, 4_RS, std::uint8_t(), maker::heap);

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
