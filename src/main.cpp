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
	using namespace mitrax;

	constexpr auto m3x3 = to_matrix< int, 3, 3 >({
		{0, 1, 2},
		{3, 4, 5},
		{6, 7, 8}
	});
	(void)m3x3;

	constexpr auto ms3x3 = to_square_matrix< int, 3 >({
		{0, 1, 2},
		{3, 4, 5},
		{6, 7, 8}
	});
	(void)ms3x3;

	constexpr auto rv3 = to_row_vector< int, 3 >({0, 1, 2});
	(void)rv3;

	constexpr auto cv3 = to_col_vector< int, 3 >({0, 1, 2});
	(void)cv3;
}catch(std::exception const& e){
	std::cerr
		<< "Exit with exception: ["
		<< boost::typeindex::type_id_runtime(e).pretty_name() << "] "
		<< e.what() << std::endl;
}catch(...){
	std::cerr << "Exit with unknown exception" << std::endl;
}
