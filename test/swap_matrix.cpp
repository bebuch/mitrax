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
	auto m1 = make_matrix(3_CS, 3_RS, data1);
	auto m2 = make_matrix(3_CD, 3_RS, data1);
	auto m3 = make_matrix(3_CS, 3_RD, data1);
	auto m4 = make_matrix(3_CD, 3_RD, data1);

	swap_rows(m1, 0_r, 1_r);
	swap_rows(m2, 0_r, 1_r);
	swap_rows(m3, 0_r, 1_r);
	swap_rows(m4, 0_r, 1_r);

	auto check = [](auto const& m){
		return
			m(0_c, 0_r) == 3 &&
			m(1_c, 0_r) == 4 &&
			m(2_c, 0_r) == 5 &&
			m(0_c, 1_r) == 0 &&
			m(1_c, 1_r) == 1 &&
			m(2_c, 1_r) == 2 &&
			m(0_c, 2_r) == 6 &&
			m(1_c, 2_r) == 7 &&
			m(2_c, 2_r) == 8;
	};

	BOOST_TEST(check(m1));
	BOOST_TEST(check(m2));
	BOOST_TEST(check(m3));
	BOOST_TEST(check(m4));
}

BOOST_AUTO_TEST_CASE(test_swap_rows_m_0_m_2){
	auto m1 = make_matrix(3_CS, 3_RS, data1);
	auto m2 = make_matrix(3_CD, 3_RS, data1);
	auto m3 = make_matrix(3_CS, 3_RD, data1);
	auto m4 = make_matrix(3_CD, 3_RD, data1);

	swap_rows(m1, 0_r, 2_r);
	swap_rows(m2, 0_r, 2_r);
	swap_rows(m3, 0_r, 2_r);
	swap_rows(m4, 0_r, 2_r);

	auto check = [](auto const& m){
		return
			m(0_c, 0_r) == 6 &&
			m(1_c, 0_r) == 7 &&
			m(2_c, 0_r) == 8 &&
			m(0_c, 1_r) == 3 &&
			m(1_c, 1_r) == 4 &&
			m(2_c, 1_r) == 5 &&
			m(0_c, 2_r) == 0 &&
			m(1_c, 2_r) == 1 &&
			m(2_c, 2_r) == 2;

	};

	BOOST_TEST(check(m1));
	BOOST_TEST(check(m2));
	BOOST_TEST(check(m3));
	BOOST_TEST(check(m4));
}

BOOST_AUTO_TEST_CASE(test_swap_rows_m1_1_m2_2){
	auto m111 = make_matrix(3_CS, 3_RS, data1);
	auto m112 = make_matrix(3_CS, 3_RS, data1);
	auto m113 = make_matrix(3_CS, 3_RS, data1);
	auto m114 = make_matrix(3_CS, 3_RS, data1);
	auto m121 = make_matrix(3_CD, 3_RS, data1);
	auto m122 = make_matrix(3_CD, 3_RS, data1);
	auto m123 = make_matrix(3_CD, 3_RS, data1);
	auto m124 = make_matrix(3_CD, 3_RS, data1);
	auto m131 = make_matrix(3_CS, 3_RD, data1);
	auto m132 = make_matrix(3_CS, 3_RD, data1);
	auto m133 = make_matrix(3_CS, 3_RD, data1);
	auto m134 = make_matrix(3_CS, 3_RD, data1);
	auto m141 = make_matrix(3_CD, 3_RD, data1);
	auto m142 = make_matrix(3_CD, 3_RD, data1);
	auto m143 = make_matrix(3_CD, 3_RD, data1);
	auto m144 = make_matrix(3_CD, 3_RD, data1);
	auto m211 = make_matrix(3_CS, 3_RS, data2);
	auto m212 = make_matrix(3_CS, 3_RS, data2);
	auto m213 = make_matrix(3_CS, 3_RS, data2);
	auto m214 = make_matrix(3_CS, 3_RS, data2);
	auto m221 = make_matrix(3_CD, 3_RS, data2);
	auto m222 = make_matrix(3_CD, 3_RS, data2);
	auto m223 = make_matrix(3_CD, 3_RS, data2);
	auto m224 = make_matrix(3_CD, 3_RS, data2);
	auto m231 = make_matrix(3_CS, 3_RD, data2);
	auto m232 = make_matrix(3_CS, 3_RD, data2);
	auto m233 = make_matrix(3_CS, 3_RD, data2);
	auto m234 = make_matrix(3_CS, 3_RD, data2);
	auto m241 = make_matrix(3_CD, 3_RD, data2);
	auto m242 = make_matrix(3_CD, 3_RD, data2);
	auto m243 = make_matrix(3_CD, 3_RD, data2);
	auto m244 = make_matrix(3_CD, 3_RD, data2);

	swap_rows(m111, 1_r, m211, 2_r);
	swap_rows(m112, 1_r, m221, 2_r);
	swap_rows(m113, 1_r, m231, 2_r);
	swap_rows(m114, 1_r, m241, 2_r);
	swap_rows(m121, 1_r, m212, 2_r);
	swap_rows(m122, 1_r, m222, 2_r);
	swap_rows(m123, 1_r, m232, 2_r);
	swap_rows(m124, 1_r, m242, 2_r);
	swap_rows(m131, 1_r, m213, 2_r);
	swap_rows(m132, 1_r, m223, 2_r);
	swap_rows(m133, 1_r, m233, 2_r);
	swap_rows(m134, 1_r, m243, 2_r);
	swap_rows(m141, 1_r, m214, 2_r);
	swap_rows(m142, 1_r, m224, 2_r);
	swap_rows(m143, 1_r, m234, 2_r);
	swap_rows(m144, 1_r, m244, 2_r);

	auto check = [](auto const& m1, auto const& m2){
		return
			m1(0_c, 0_r) == 0 &&
			m1(1_c, 0_r) == 1 &&
			m1(2_c, 0_r) == 2 &&
			m1(0_c, 1_r) == 16 &&
			m1(1_c, 1_r) == 17 &&
			m1(2_c, 1_r) == 18 &&
			m1(0_c, 2_r) == 6 &&
			m1(1_c, 2_r) == 7 &&
			m1(2_c, 2_r) == 8 &&
			m2(0_c, 0_r) == 10 &&
			m2(1_c, 0_r) == 11 &&
			m2(2_c, 0_r) == 12 &&
			m2(0_c, 1_r) == 13 &&
			m2(1_c, 1_r) == 14 &&
			m2(2_c, 1_r) == 15 &&
			m2(0_c, 2_r) == 3 &&
			m2(1_c, 2_r) == 4 &&
			m2(2_c, 2_r) == 5;
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
	auto m1 = make_matrix(3_CS, 3_RS, data1);
	auto m2 = make_matrix(3_CD, 3_RS, data1);
	auto m3 = make_matrix(3_CS, 3_RD, data1);
	auto m4 = make_matrix(3_CD, 3_RD, data1);

	swap_cols(m1, 0_c, 1_c);
	swap_cols(m2, 0_c, 1_c);
	swap_cols(m3, 0_c, 1_c);
	swap_cols(m4, 0_c, 1_c);

	auto check = [](auto const& m){
		return
			m(0_c, 0_r) == 1 &&
			m(1_c, 0_r) == 0 &&
			m(2_c, 0_r) == 2 &&
			m(0_c, 1_r) == 4 &&
			m(1_c, 1_r) == 3 &&
			m(2_c, 1_r) == 5 &&
			m(0_c, 2_r) == 7 &&
			m(1_c, 2_r) == 6 &&
			m(2_c, 2_r) == 8;
	};

	BOOST_TEST(check(m1));
	BOOST_TEST(check(m2));
	BOOST_TEST(check(m3));
	BOOST_TEST(check(m4));
}

BOOST_AUTO_TEST_CASE(test_swap_cols_m_0_m_2){
	auto m1 = make_matrix(3_CS, 3_RS, data1);
	auto m2 = make_matrix(3_CD, 3_RS, data1);
	auto m3 = make_matrix(3_CS, 3_RD, data1);
	auto m4 = make_matrix(3_CD, 3_RD, data1);

	swap_cols(m1, 0_c, 2_c);
	swap_cols(m2, 0_c, 2_c);
	swap_cols(m3, 0_c, 2_c);
	swap_cols(m4, 0_c, 2_c);

	auto check = [](auto const& m){
		return
			m(0_c, 0_r) == 2 &&
			m(1_c, 0_r) == 1 &&
			m(2_c, 0_r) == 0 &&
			m(0_c, 1_r) == 5 &&
			m(1_c, 1_r) == 4 &&
			m(2_c, 1_r) == 3 &&
			m(0_c, 2_r) == 8 &&
			m(1_c, 2_r) == 7 &&
			m(2_c, 2_r) == 6;
	};

	BOOST_TEST(check(m1));
	BOOST_TEST(check(m2));
	BOOST_TEST(check(m3));
	BOOST_TEST(check(m4));
}

BOOST_AUTO_TEST_CASE(test_swap_cols_m1_1_m2_2){
	auto m111 = make_matrix(3_CS, 3_RS, data1);
	auto m112 = make_matrix(3_CS, 3_RS, data1);
	auto m113 = make_matrix(3_CS, 3_RS, data1);
	auto m114 = make_matrix(3_CS, 3_RS, data1);
	auto m121 = make_matrix(3_CD, 3_RS, data1);
	auto m122 = make_matrix(3_CD, 3_RS, data1);
	auto m123 = make_matrix(3_CD, 3_RS, data1);
	auto m124 = make_matrix(3_CD, 3_RS, data1);
	auto m131 = make_matrix(3_CS, 3_RD, data1);
	auto m132 = make_matrix(3_CS, 3_RD, data1);
	auto m133 = make_matrix(3_CS, 3_RD, data1);
	auto m134 = make_matrix(3_CS, 3_RD, data1);
	auto m141 = make_matrix(3_CD, 3_RD, data1);
	auto m142 = make_matrix(3_CD, 3_RD, data1);
	auto m143 = make_matrix(3_CD, 3_RD, data1);
	auto m144 = make_matrix(3_CD, 3_RD, data1);
	auto m211 = make_matrix(3_CS, 3_RS, data2);
	auto m212 = make_matrix(3_CS, 3_RS, data2);
	auto m213 = make_matrix(3_CS, 3_RS, data2);
	auto m214 = make_matrix(3_CS, 3_RS, data2);
	auto m221 = make_matrix(3_CD, 3_RS, data2);
	auto m222 = make_matrix(3_CD, 3_RS, data2);
	auto m223 = make_matrix(3_CD, 3_RS, data2);
	auto m224 = make_matrix(3_CD, 3_RS, data2);
	auto m231 = make_matrix(3_CS, 3_RD, data2);
	auto m232 = make_matrix(3_CS, 3_RD, data2);
	auto m233 = make_matrix(3_CS, 3_RD, data2);
	auto m234 = make_matrix(3_CS, 3_RD, data2);
	auto m241 = make_matrix(3_CD, 3_RD, data2);
	auto m242 = make_matrix(3_CD, 3_RD, data2);
	auto m243 = make_matrix(3_CD, 3_RD, data2);
	auto m244 = make_matrix(3_CD, 3_RD, data2);

	swap_cols(m111, 1_c, m211, 2_c);
	swap_cols(m112, 1_c, m221, 2_c);
	swap_cols(m113, 1_c, m231, 2_c);
	swap_cols(m114, 1_c, m241, 2_c);
	swap_cols(m121, 1_c, m212, 2_c);
	swap_cols(m122, 1_c, m222, 2_c);
	swap_cols(m123, 1_c, m232, 2_c);
	swap_cols(m124, 1_c, m242, 2_c);
	swap_cols(m131, 1_c, m213, 2_c);
	swap_cols(m132, 1_c, m223, 2_c);
	swap_cols(m133, 1_c, m233, 2_c);
	swap_cols(m134, 1_c, m243, 2_c);
	swap_cols(m141, 1_c, m214, 2_c);
	swap_cols(m142, 1_c, m224, 2_c);
	swap_cols(m143, 1_c, m234, 2_c);
	swap_cols(m144, 1_c, m244, 2_c);

	auto check = [](auto const& m1, auto const& m2){
		return
			m1(0_c, 0_r) == 0 &&
			m1(1_c, 0_r) == 12 &&
			m1(2_c, 0_r) == 2 &&
			m1(0_c, 1_r) == 3 &&
			m1(1_c, 1_r) == 15 &&
			m1(2_c, 1_r) == 5 &&
			m1(0_c, 2_r) == 6 &&
			m1(1_c, 2_r) == 18 &&
			m1(2_c, 2_r) == 8 &&
			m2(0_c, 0_r) == 10 &&
			m2(1_c, 0_r) == 11 &&
			m2(2_c, 0_r) == 1 &&
			m2(0_c, 1_r) == 13 &&
			m2(1_c, 1_r) == 14 &&
			m2(2_c, 1_r) == 4 &&
			m2(0_c, 2_r) == 16 &&
			m2(1_c, 2_r) == 17 &&
			m2(2_c, 2_r) == 7;
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
