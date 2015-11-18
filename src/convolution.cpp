//-----------------------------------------------------------------------------
// Copyright (c) 2015 Benjamin Buch
//
// https://github.com/bebuch/mitrax
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt)
//-----------------------------------------------------------------------------
#include <boost/test/unit_test.hpp>

#include <mitrax/raw_matrix.hpp>
#include <mitrax/convolution.hpp>
#include <mitrax/output.hpp>

#include <iostream>


using boost::typeindex::type_id;
using boost::typeindex::type_id_runtime;
using namespace mitrax;
using namespace mitrax::literals;


BOOST_AUTO_TEST_SUITE(test_suite_convolution)


namespace{


	constexpr auto image = make_square_matrix< int >(5_D, {
		{1, 2, 3, 4, 5},
		{2, 3, 4, 5, 6},
		{3, 4, 5, 6, 7},
		{4, 5, 6, 7, 8},
		{5, 6, 7, 8, 9}
	});

	constexpr auto sobel_x = make_square_matrix< int >(3_D, {
		{1, 0, -1},
		{2, 0, -2},
		{1, 0, -1}
	});


}


BOOST_AUTO_TEST_CASE(test_convolution){
	auto m = convolution(image, sobel_x);

	auto eq =
		m.cols() == 3 &&
		m.rows() == 3 &&
		m(0, 0) == -8 &&
		m(1, 0) == -8 &&
		m(2, 0) == -8 &&
		m(0, 1) == -8 &&
		m(1, 1) == -8 &&
		m(2, 1) == -8 &&
		m(0, 2) == -8 &&
		m(1, 2) == -8 &&
		m(2, 2) == -8;

	BOOST_TEST(eq);

	BOOST_TEST(type_id_runtime(m) == (type_id< raw_matrix< int, 3, 3 > >()));
}


BOOST_AUTO_TEST_SUITE_END()
