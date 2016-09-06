//-----------------------------------------------------------------------------
// Copyright (c) 2015-2016 Benjamin Buch
//
// https://github.com/bebuch/mitrax
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt)
//-----------------------------------------------------------------------------
#define BOOST_TEST_MODULE mitrax swap_matrix
#include <boost/test/unit_test.hpp>

#include <mitrax/matrix.hpp>
#include <mitrax/swap_matrix.hpp>


using boost::typeindex::type_id;
using boost::typeindex::type_id_runtime;
using namespace mitrax;
using namespace mitrax::literals;


constexpr int data1[3][3] = {
	{0, 1, 2},
	{3, 4, 5},
	{6, 7, 8}
};

constexpr int data2[3][3] = {
	{10, 11, 12},
	{13, 14, 15},
	{16, 17, 18}
};


BOOST_AUTO_TEST_SUITE(suite_swap_matrix)


BOOST_AUTO_TEST_CASE(test_swap_rows_m_0_m_1){
	auto m1 = make_matrix(3_C, 3_R, data1);
	auto m2 = make_matrix(3_C_rt, 3_R, data1);
	auto m3 = make_matrix(3_C, 3_R_rt, data1);
	auto m4 = make_matrix(3_C_rt, 3_R_rt, data1);

	swap_rows(m1, 0, 1);
	swap_rows(m2, 0, 1);
	swap_rows(m3, 0, 1);
	swap_rows(m4, 0, 1);

	auto check = [](auto const& m){
		return
			m(0, 0) == 3 &&
			m(1, 0) == 4 &&
			m(2, 0) == 5 &&
			m(0, 1) == 0 &&
			m(1, 1) == 1 &&
			m(2, 1) == 2 &&
			m(0, 2) == 6 &&
			m(1, 2) == 7 &&
			m(2, 2) == 8;
	};

	BOOST_TEST(check(m1));
	BOOST_TEST(check(m2));
	BOOST_TEST(check(m3));
	BOOST_TEST(check(m4));
}

BOOST_AUTO_TEST_CASE(test_swap_rows_m_0_m_2){
	auto m1 = make_matrix(3_C, 3_R, data1);
	auto m2 = make_matrix(3_C_rt, 3_R, data1);
	auto m3 = make_matrix(3_C, 3_R_rt, data1);
	auto m4 = make_matrix(3_C_rt, 3_R_rt, data1);

	swap_rows(m1, 0, 2);
	swap_rows(m2, 0, 2);
	swap_rows(m3, 0, 2);
	swap_rows(m4, 0, 2);

	auto check = [](auto const& m){
		return
			m(0, 0) == 6 &&
			m(1, 0) == 7 &&
			m(2, 0) == 8 &&
			m(0, 1) == 3 &&
			m(1, 1) == 4 &&
			m(2, 1) == 5 &&
			m(0, 2) == 0 &&
			m(1, 2) == 1 &&
			m(2, 2) == 2;

	};

	BOOST_TEST(check(m1));
	BOOST_TEST(check(m2));
	BOOST_TEST(check(m3));
	BOOST_TEST(check(m4));
}

BOOST_AUTO_TEST_CASE(test_swap_rows_m1_1_m2_2){
	auto m111 = make_matrix(3_C, 3_R, data1);
	auto m112 = make_matrix(3_C, 3_R, data1);
	auto m113 = make_matrix(3_C, 3_R, data1);
	auto m114 = make_matrix(3_C, 3_R, data1);
	auto m121 = make_matrix(3_C_rt, 3_R, data1);
	auto m122 = make_matrix(3_C_rt, 3_R, data1);
	auto m123 = make_matrix(3_C_rt, 3_R, data1);
	auto m124 = make_matrix(3_C_rt, 3_R, data1);
	auto m131 = make_matrix(3_C, 3_R_rt, data1);
	auto m132 = make_matrix(3_C, 3_R_rt, data1);
	auto m133 = make_matrix(3_C, 3_R_rt, data1);
	auto m134 = make_matrix(3_C, 3_R_rt, data1);
	auto m141 = make_matrix(3_C_rt, 3_R_rt, data1);
	auto m142 = make_matrix(3_C_rt, 3_R_rt, data1);
	auto m143 = make_matrix(3_C_rt, 3_R_rt, data1);
	auto m144 = make_matrix(3_C_rt, 3_R_rt, data1);
	auto m211 = make_matrix(3_C, 3_R, data2);
	auto m212 = make_matrix(3_C, 3_R, data2);
	auto m213 = make_matrix(3_C, 3_R, data2);
	auto m214 = make_matrix(3_C, 3_R, data2);
	auto m221 = make_matrix(3_C_rt, 3_R, data2);
	auto m222 = make_matrix(3_C_rt, 3_R, data2);
	auto m223 = make_matrix(3_C_rt, 3_R, data2);
	auto m224 = make_matrix(3_C_rt, 3_R, data2);
	auto m231 = make_matrix(3_C, 3_R_rt, data2);
	auto m232 = make_matrix(3_C, 3_R_rt, data2);
	auto m233 = make_matrix(3_C, 3_R_rt, data2);
	auto m234 = make_matrix(3_C, 3_R_rt, data2);
	auto m241 = make_matrix(3_C_rt, 3_R_rt, data2);
	auto m242 = make_matrix(3_C_rt, 3_R_rt, data2);
	auto m243 = make_matrix(3_C_rt, 3_R_rt, data2);
	auto m244 = make_matrix(3_C_rt, 3_R_rt, data2);

	swap_rows(m111, 1, m211, 2);
	swap_rows(m112, 1, m221, 2);
	swap_rows(m113, 1, m231, 2);
	swap_rows(m114, 1, m241, 2);
	swap_rows(m121, 1, m212, 2);
	swap_rows(m122, 1, m222, 2);
	swap_rows(m123, 1, m232, 2);
	swap_rows(m124, 1, m242, 2);
	swap_rows(m131, 1, m213, 2);
	swap_rows(m132, 1, m223, 2);
	swap_rows(m133, 1, m233, 2);
	swap_rows(m134, 1, m243, 2);
	swap_rows(m141, 1, m214, 2);
	swap_rows(m142, 1, m224, 2);
	swap_rows(m143, 1, m234, 2);
	swap_rows(m144, 1, m244, 2);

	auto check = [](auto const& m1, auto const& m2){
		return
			m1(0, 0) == 0 &&
			m1(1, 0) == 1 &&
			m1(2, 0) == 2 &&
			m1(0, 1) == 16 &&
			m1(1, 1) == 17 &&
			m1(2, 1) == 18 &&
			m1(0, 2) == 6 &&
			m1(1, 2) == 7 &&
			m1(2, 2) == 8 &&
			m2(0, 0) == 10 &&
			m2(1, 0) == 11 &&
			m2(2, 0) == 12 &&
			m2(0, 1) == 13 &&
			m2(1, 1) == 14 &&
			m2(2, 1) == 15 &&
			m2(0, 2) == 3 &&
			m2(1, 2) == 4 &&
			m2(2, 2) == 5;
	};

	BOOST_TEST(check(m111, m211));
	BOOST_TEST(check(m112, m221));
	BOOST_TEST(check(m113, m231));
	BOOST_TEST(check(m114, m241));
	BOOST_TEST(check(m121, m212));
	BOOST_TEST(check(m122, m222));
	BOOST_TEST(check(m123, m232));
	BOOST_TEST(check(m124, m242));
	BOOST_TEST(check(m131, m213));
	BOOST_TEST(check(m132, m223));
	BOOST_TEST(check(m133, m233));
	BOOST_TEST(check(m134, m243));
	BOOST_TEST(check(m141, m214));
	BOOST_TEST(check(m142, m224));
	BOOST_TEST(check(m143, m234));
	BOOST_TEST(check(m144, m244));
}

BOOST_AUTO_TEST_CASE(test_swap_cols_m_0_m_1){
	auto m1 = make_matrix(3_C, 3_R, data1);
	auto m2 = make_matrix(3_C_rt, 3_R, data1);
	auto m3 = make_matrix(3_C, 3_R_rt, data1);
	auto m4 = make_matrix(3_C_rt, 3_R_rt, data1);

	swap_cols(m1, 0, 1);
	swap_cols(m2, 0, 1);
	swap_cols(m3, 0, 1);
	swap_cols(m4, 0, 1);

	auto check = [](auto const& m){
		return
			m(0, 0) == 1 &&
			m(1, 0) == 0 &&
			m(2, 0) == 2 &&
			m(0, 1) == 4 &&
			m(1, 1) == 3 &&
			m(2, 1) == 5 &&
			m(0, 2) == 7 &&
			m(1, 2) == 6 &&
			m(2, 2) == 8;
	};

	BOOST_TEST(check(m1));
	BOOST_TEST(check(m2));
	BOOST_TEST(check(m3));
	BOOST_TEST(check(m4));
}

BOOST_AUTO_TEST_CASE(test_swap_cols_m_0_m_2){
	auto m1 = make_matrix(3_C, 3_R, data1);
	auto m2 = make_matrix(3_C_rt, 3_R, data1);
	auto m3 = make_matrix(3_C, 3_R_rt, data1);
	auto m4 = make_matrix(3_C_rt, 3_R_rt, data1);

	swap_cols(m1, 0, 2);
	swap_cols(m2, 0, 2);
	swap_cols(m3, 0, 2);
	swap_cols(m4, 0, 2);

	auto check = [](auto const& m){
		return
			m(0, 0) == 2 &&
			m(1, 0) == 1 &&
			m(2, 0) == 0 &&
			m(0, 1) == 5 &&
			m(1, 1) == 4 &&
			m(2, 1) == 3 &&
			m(0, 2) == 8 &&
			m(1, 2) == 7 &&
			m(2, 2) == 6;

	};

	BOOST_TEST(check(m1));
	BOOST_TEST(check(m2));
	BOOST_TEST(check(m3));
	BOOST_TEST(check(m4));
}

BOOST_AUTO_TEST_CASE(test_swap_cols_m1_1_m2_2){
	auto m111 = make_matrix(3_C, 3_R, data1);
	auto m112 = make_matrix(3_C, 3_R, data1);
	auto m113 = make_matrix(3_C, 3_R, data1);
	auto m114 = make_matrix(3_C, 3_R, data1);
	auto m121 = make_matrix(3_C_rt, 3_R, data1);
	auto m122 = make_matrix(3_C_rt, 3_R, data1);
	auto m123 = make_matrix(3_C_rt, 3_R, data1);
	auto m124 = make_matrix(3_C_rt, 3_R, data1);
	auto m131 = make_matrix(3_C, 3_R_rt, data1);
	auto m132 = make_matrix(3_C, 3_R_rt, data1);
	auto m133 = make_matrix(3_C, 3_R_rt, data1);
	auto m134 = make_matrix(3_C, 3_R_rt, data1);
	auto m141 = make_matrix(3_C_rt, 3_R_rt, data1);
	auto m142 = make_matrix(3_C_rt, 3_R_rt, data1);
	auto m143 = make_matrix(3_C_rt, 3_R_rt, data1);
	auto m144 = make_matrix(3_C_rt, 3_R_rt, data1);
	auto m211 = make_matrix(3_C, 3_R, data2);
	auto m212 = make_matrix(3_C, 3_R, data2);
	auto m213 = make_matrix(3_C, 3_R, data2);
	auto m214 = make_matrix(3_C, 3_R, data2);
	auto m221 = make_matrix(3_C_rt, 3_R, data2);
	auto m222 = make_matrix(3_C_rt, 3_R, data2);
	auto m223 = make_matrix(3_C_rt, 3_R, data2);
	auto m224 = make_matrix(3_C_rt, 3_R, data2);
	auto m231 = make_matrix(3_C, 3_R_rt, data2);
	auto m232 = make_matrix(3_C, 3_R_rt, data2);
	auto m233 = make_matrix(3_C, 3_R_rt, data2);
	auto m234 = make_matrix(3_C, 3_R_rt, data2);
	auto m241 = make_matrix(3_C_rt, 3_R_rt, data2);
	auto m242 = make_matrix(3_C_rt, 3_R_rt, data2);
	auto m243 = make_matrix(3_C_rt, 3_R_rt, data2);
	auto m244 = make_matrix(3_C_rt, 3_R_rt, data2);

	swap_cols(m111, 1, m211, 2);
	swap_cols(m112, 1, m221, 2);
	swap_cols(m113, 1, m231, 2);
	swap_cols(m114, 1, m241, 2);
	swap_cols(m121, 1, m212, 2);
	swap_cols(m122, 1, m222, 2);
	swap_cols(m123, 1, m232, 2);
	swap_cols(m124, 1, m242, 2);
	swap_cols(m131, 1, m213, 2);
	swap_cols(m132, 1, m223, 2);
	swap_cols(m133, 1, m233, 2);
	swap_cols(m134, 1, m243, 2);
	swap_cols(m141, 1, m214, 2);
	swap_cols(m142, 1, m224, 2);
	swap_cols(m143, 1, m234, 2);
	swap_cols(m144, 1, m244, 2);

	auto check = [](auto const& m1, auto const& m2){
		return
			m1(0, 0) == 0 &&
			m1(1, 0) == 12 &&
			m1(2, 0) == 2 &&
			m1(0, 1) == 3 &&
			m1(1, 1) == 15 &&
			m1(2, 1) == 5 &&
			m1(0, 2) == 6 &&
			m1(1, 2) == 18 &&
			m1(2, 2) == 8 &&
			m2(0, 0) == 10 &&
			m2(1, 0) == 11 &&
			m2(2, 0) == 1 &&
			m2(0, 1) == 13 &&
			m2(1, 1) == 14 &&
			m2(2, 1) == 4 &&
			m2(0, 2) == 16 &&
			m2(1, 2) == 17 &&
			m2(2, 2) == 7;
	};

	BOOST_TEST(check(m111, m211));
	BOOST_TEST(check(m112, m221));
	BOOST_TEST(check(m113, m231));
	BOOST_TEST(check(m114, m241));
	BOOST_TEST(check(m121, m212));
	BOOST_TEST(check(m122, m222));
	BOOST_TEST(check(m123, m232));
	BOOST_TEST(check(m124, m242));
	BOOST_TEST(check(m131, m213));
	BOOST_TEST(check(m132, m223));
	BOOST_TEST(check(m133, m233));
	BOOST_TEST(check(m134, m243));
	BOOST_TEST(check(m141, m214));
	BOOST_TEST(check(m142, m224));
	BOOST_TEST(check(m143, m234));
	BOOST_TEST(check(m144, m244));
}


BOOST_AUTO_TEST_SUITE_END()
