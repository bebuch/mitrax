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
#include <mitrax/operator.hpp>

#include <cmath>


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

	constexpr auto ref4 = make_square_matrix< float >(3_D, {
		{1, 2, 3},
		{4, 5, 6},
		{0, 0, 0}
	});

	template < typename M, size_t C, size_t R >
	constexpr bool near_null(
		matrix< M, C, R > const& m,
		value_type_t< M > const& threshold
	){
		for(auto& v: m) if(threshold < v) return false;
		return true;
	}

	template < typename T, typename U >
	constexpr bool equal(T const& a, U const& b){
		return std::abs(a - b) < 0.00001;
	}


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

BOOST_AUTO_TEST_CASE(test_matrix_kernel_3x3_3){
	auto const v = matrix_kernel(ref4);

	BOOST_TEST((
		v.cols() == 1 &&
		v.rows() == 3 &&
		v[0] ==  1 &&
		v[1] == -2 &&
		v[2] ==  1
	));
}

BOOST_AUTO_TEST_CASE(test_matrix_kernel_numeric){
	for(size_t i = 0; i < 10; ++i){
		auto m = make_square_matrix< double >(dims(i + 1));
		size_t j = 5;
		for(auto& v: m) v = ++j;

		auto k = matrix_kernel(m);

		BOOST_TEST(near_null(m * k, 0));
	}
}

BOOST_AUTO_TEST_CASE(test_gaussian_elimination){
	constexpr auto m = make_square_matrix< float >(3_D, {
		{ 1  , -0.2, -0.2},
		{-0.4,  0.8, -0.1},
		{ 0  , -0.5,  0.9}
	});

	constexpr auto v = make_col_vector< float >(3_R, {7, 12.5, 16.5});

	auto res = gaussian_elimination(m, v);

	BOOST_TEST((
		res.cols() == 1 &&
		res.rows() == 3 &&
		res[0] == 20 &&
		res[1] == 30 &&
		res[2] == 35
	));
}

BOOST_AUTO_TEST_CASE(test_inverse_2x2){
	constexpr auto m = make_square_matrix< float >(2_D, {
		{2, 5},
		{1, 3}
	});

	auto i = inverse(m);

	BOOST_TEST((
		i.cols() == 2 &&
		i.rows() == 2 &&
		i(0, 0) ==  3 &&
		i(1, 0) == -5 &&
		i(0, 1) == -1 &&
		i(1, 1) ==  2
	));
}

BOOST_AUTO_TEST_CASE(test_inverse_3x3_1){
	constexpr auto m = make_square_matrix< float >(3_D, {
		{1, 2, 0},
		{2, 4, 1},
		{2, 1, 0}
	});

	auto i = inverse(m) * 3;

	std::cout << i << std::endl;

	BOOST_TEST((
		i.cols() == 3 &&
		i.rows() == 3 &&
		equal(i(0, 0), -1) &&
		equal(i(1, 0),  0) &&
		equal(i(2, 0),  2) &&
		equal(i(0, 1),  2) &&
		equal(i(1, 1),  0) &&
		equal(i(2, 1), -1) &&
		equal(i(0, 2), -6) &&
		equal(i(1, 2),  3) &&
		equal(i(2, 2),  0)
	));
}

BOOST_AUTO_TEST_CASE(test_inverse_3x3_2){
	constexpr auto m = make_square_matrix< float >(3_D, {
		{ 2, -1,  0},
		{-1,  2, -1},
		{ 0, -1,  2}
	});

	auto i = inverse(m) * 4;

	std::cout << i << std::endl;

	BOOST_TEST((
		i.cols() == 3 &&
		i.rows() == 3 &&
		equal(i(0, 0), 3) &&
		equal(i(1, 0), 2) &&
		equal(i(2, 0), 1) &&
		equal(i(0, 1), 2) &&
		equal(i(1, 1), 4) &&
		equal(i(2, 1), 2) &&
		equal(i(0, 2), 1) &&
		equal(i(1, 2), 2) &&
		equal(i(2, 2), 3)
	));
}

BOOST_AUTO_TEST_CASE(test_inverse_3x3_3){
	constexpr auto m = make_square_matrix< float >(3_D, {
		{ 2, -1,  0},
		{ 1,  2, -2},
		{ 0, -1,  1}
	});

	auto i = inverse(m);

	std::cout << i << std::endl;

	BOOST_TEST((
		i.cols() == 3 &&
		i.rows() == 3 &&
		equal(i(0, 0),  0) &&
		equal(i(1, 0),  1) &&
		equal(i(2, 0),  2) &&
		equal(i(0, 1), -1) &&
		equal(i(1, 1),  2) &&
		equal(i(2, 1),  4) &&
		equal(i(0, 2), -1) &&
		equal(i(1, 2),  2) &&
		equal(i(2, 2),  5)
	));
}


BOOST_AUTO_TEST_SUITE_END()
