#include <mitrax/matrix.hpp>

#include <iostream>


int main(){
	using namespace mitrax;
	using namespace mitrax::literals;

	auto dcc = dims(2_C, 4_R);
	auto drc = dims(2_C_rt, 4_R);
	auto dcr = dims(2_C, 4_R_rt);
	auto drr = dims(2_C_rt, 4_R_rt);

	auto mcc = make_matrix_v< std::uint8_t >(2_C, 4_R);
	auto mrc = make_matrix_v< std::uint8_t >(2_C_rt, 4_R);
	auto mcr = make_matrix_v< std::uint8_t >(2_C, 4_R_rt);
	auto mrr = make_matrix_v< std::uint8_t >(2_C_rt, 4_R_rt);

	auto hcc = make_matrix_v(2_C, 4_R, std::uint8_t(), maker::heap);

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
