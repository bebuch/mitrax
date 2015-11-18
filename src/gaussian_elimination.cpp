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
#include <mitrax/gaussian_elimination.hpp>
#include <mitrax/output.hpp>
#include <iostream>


using boost::typeindex::type_id;
using boost::typeindex::type_id_runtime;
using namespace mitrax;
using namespace mitrax::literals;


BOOST_AUTO_TEST_SUITE(test_suite_gaussian_elimination)


namespace{


	constexpr auto ref1 = make_square_matrix< float >(3_D, {
		{1, 2, 3},
		{1, 1, 1},
		{3, 3, 1}
	});

	constexpr auto ref2 = make_square_matrix< float >(3_D, {
		{1, 2, 3},
		{4, 5, 6},
		{7, 8, 9}
	});

	constexpr auto ref3 = make_square_matrix< float >(3_D, {
		{-1,  2, 0},
		{ 1,  0, 1},
		{ 2, -4, 0}
	});


}


BOOST_AUTO_TEST_CASE(test_upper_triangular_matrix){
	auto m = upper_triangular_matrix(ref1);

	BOOST_TEST((
		m.cols() == 3 &&
		m.rows() == 3 &&
		m(0, 0) ==  1 &&
		m(1, 0) ==  2 &&
		m(2, 0) ==  3 &&
		m(0, 1) ==  0 &&
		m(1, 1) == -1 &&
		m(2, 1) == -2 &&
		m(0, 2) ==  0 &&
		m(1, 2) ==  0 &&
		m(2, 2) == -2
	));
}

BOOST_AUTO_TEST_CASE(test_matrix_kernel_3x3_1){
	auto const v = matrix_kernel(ref2);

	BOOST_TEST((
		v.cols() == 1 &&
		v.rows() == 3 &&
		v[0] ==  1 &&
		v[1] == -2 &&
		v[2] ==  1
	));
}

BOOST_AUTO_TEST_CASE(test_matrix_kernel_3x3_2){
	auto const v = matrix_kernel(ref3);

	BOOST_TEST((
		v.cols() == 1 &&
		v.rows() == 3 &&
		v[0] == -1 &&
		v[1] == -0.5 &&
		v[2] ==  1
	));
}


BOOST_AUTO_TEST_SUITE_END()
