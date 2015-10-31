//-----------------------------------------------------------------------------
// Copyright (c) 2015 Benjamin Buch
//
// https://github.com/bebuch/mitrax
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt)
//-----------------------------------------------------------------------------
#include <mitrax/raw_matrix.hpp>

#include <boost/type_index.hpp>

#include <iostream>


int main()try{
	using boost::typeindex::type_id_runtime;
	using namespace mitrax;

	constexpr auto m3x3 = to_matrix< int, 3, 3 >({
		{0, 1, 2},
		{3, 4, 5},
		{6, 7, 8}
	});
	(void)m3x3;
	std::cout << type_id_runtime(m3x3).pretty_name() << std::endl;

	constexpr auto ms3x3 = to_square_matrix< int, 3 >({
		{0, 1, 2},
		{3, 4, 5},
		{6, 7, 8}
	});
	(void)ms3x3;
	std::cout << type_id_runtime(ms3x3).pretty_name() << std::endl;

	constexpr auto rv3 = to_row_vector< int, 3 >({0, 1, 2});
	(void)rv3;
	std::cout << type_id_runtime(rv3).pretty_name() << std::endl;

	constexpr auto cv3 = to_col_vector< int, 3 >({0, 1, 2});
	(void)cv3;
	std::cout << type_id_runtime(cv3).pretty_name() << std::endl;

	constexpr auto v = to_square_matrix< int, 1 >({{0}});
	(void)v;
	std::cout << type_id_runtime(v).pretty_name() << std::endl;

	constexpr int i = v;
	(void)i;

	auto ms0x3 = with_dynamic_cols(m3x3);
	(void)ms0x3;
	std::cout << type_id_runtime(ms0x3).pretty_name() << std::endl;

	auto ms3x0 = with_dynamic_rows(m3x3);
	(void)ms3x0;
	std::cout << type_id_runtime(ms3x0).pretty_name() << std::endl;

	auto ms0x0 = with_dynamic_dims(m3x3);
	(void)ms0x0;
	std::cout << type_id_runtime(ms0x0).pretty_name() << std::endl;
}catch(std::exception const& e){
	std::cerr
		<< "Exit with exception: ["
		<< boost::typeindex::type_id_runtime(e).pretty_name() << "] "
		<< e.what() << std::endl;
}catch(...){
	std::cerr << "Exit with unknown exception" << std::endl;
}
