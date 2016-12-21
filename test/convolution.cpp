//-----------------------------------------------------------------------------
// Copyright (c) 2015-2016 Benjamin Buch
//
// https://github.com/bebuch/mitrax
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt)
//-----------------------------------------------------------------------------
#define BOOST_TEST_MODULE mitrax convolution
#include <boost/test/unit_test.hpp>

#include <mitrax/convolution.hpp>

#include <iostream>


using boost::typeindex::type_id;
using boost::typeindex::type_id_runtime;
using namespace mitrax;
using namespace mitrax::literals;


constexpr auto image = make_matrix< int >(5_DS, {
	{1, 2, 3, 4, 5},
	{2, 3, 4, 5, 6},
	{3, 4, 5, 6, 7},
	{4, 5, 6, 7, 8},
	{5, 6, 7, 8, 9}
});

constexpr auto sobel_x = make_matrix< int >(3_DS, {
	{1, 0, -1},
	{2, 0, -2},
	{1, 0, -1}
});


BOOST_AUTO_TEST_SUITE(suite_convolution)


BOOST_AUTO_TEST_CASE(test_convolution){
	constexpr auto m = convolution(image, sobel_x);

	auto eq =
		m.cols() == 3_CS &&
		m.rows() == 3_RS &&
		m(0_c, 0_r) == -8 &&
		m(1_c, 0_r) == -8 &&
		m(2_c, 0_r) == -8 &&
		m(0_c, 1_r) == -8 &&
		m(1_c, 1_r) == -8 &&
		m(2_c, 1_r) == -8 &&
		m(0_c, 2_r) == -8 &&
		m(1_c, 2_r) == -8 &&
		m(2_c, 2_r) == -8;

	BOOST_TEST(eq);

	BOOST_TEST(type_id_runtime(m) == (type_id< std_matrix< int, 3_C, 3_R > >()));
}


BOOST_AUTO_TEST_SUITE_END()
