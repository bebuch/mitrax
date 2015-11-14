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


using boost::typeindex::type_id;
using boost::typeindex::type_id_runtime;
using namespace mitrax;
using namespace mitrax::literals;


BOOST_AUTO_TEST_SUITE(gaussian_elimination)


namespace{


	constexpr auto ref1 = make_square_matrix< int >(3_D, {
		{1, 2, 3},
		{1, 1, 1},
		{3, 3, 1}
	});


}


BOOST_AUTO_TEST_CASE(test_upper_triangular_matrix){
	auto m = upper_triangular_matrix(ref1);

	auto eq =
		m(0, 0) ==  1 &&
		m(1, 0) ==  2 &&
		m(2, 0) ==  3 &&
		m(0, 1) ==  0 &&
		m(1, 1) == -1 &&
		m(2, 1) == -2 &&
		m(0, 2) ==  0 &&
		m(1, 2) ==  0 &&
		m(2, 2) == -2;

	BOOST_TEST(eq);
}

BOOST_AUTO_TEST_CASE(test_matrix_kernel){
	auto const v = matrix_kernel(ref1);

	auto eq =
		v[0] ==  1 &&
		v[1] == -1 &&
		v[2] == -2;

	BOOST_TEST(eq);
}


BOOST_AUTO_TEST_SUITE_END()
