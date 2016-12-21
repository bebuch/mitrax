//-----------------------------------------------------------------------------
// Copyright (c) 2015-2016 Benjamin Buch
//
// https://github.com/bebuch/mitrax
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt)
//-----------------------------------------------------------------------------
#define BOOST_TEST_MODULE mitrax operator
#include <boost/test/unit_test.hpp>

#include <mitrax/operator.hpp>
#include <mitrax/compare.hpp>


using boost::typeindex::type_id;
using boost::typeindex::type_id_runtime;
using namespace mitrax;
using namespace mitrax::literals;


template < typename T >
auto rt_id(T&& v){
	return type_id_runtime(static_cast< T&& >(v));
}

template < typename T >
auto const id = type_id< T >();


constexpr auto ref1 = make_matrix< int >(3_DS, {
	{0, 1, 2},
	{3, 4, 5},
	{6, 7, 8}
});

constexpr auto ref2 = make_matrix< int >(3_DS, {
	{0, 2, 4},
	{6, 8, 10},
	{12, 14, 16}
});

constexpr auto ref3 = make_matrix< int >(3_DS, {
	{0, 3, 6},
	{9, 12, 15},
	{18, 21, 24}
});

constexpr auto ref1_mod3 = make_matrix< int >(3_DS, {
	{0, 1, 2},
	{0, 1, 2},
	{0, 1, 2}
});

constexpr auto ref1_square = make_matrix< int >(3_DS, {
	{0, 1, 4},
	{9, 16, 25},
	{36, 49, 64}
});

constexpr auto ref1_element_plus1 = make_matrix< int >(3_DS, {
	{1, 2, 3},
	{4, 5, 6},
	{7, 8, 9}
});

constexpr auto ref1_element_minus1 = make_matrix< int >(3_DS, {
	{-1, 0, 1},
	{2, 3, 4},
	{5, 6, 7}
});

constexpr auto ref_all1 = make_matrix< int >(3_DS, {
	{1, 1, 1},
	{1, 1, 1},
	{1, 1, 1}
});

constexpr auto ref_all3 = make_matrix< int >(3_DS, {
	{3, 3, 3},
	{3, 3, 3},
	{3, 3, 3}
});

constexpr auto ref_all9 = make_matrix< int >(3_DS, {
	{9, 9, 9},
	{9, 9, 9},
	{9, 9, 9}
});

constexpr auto ref_mod = make_matrix< int >(3_DS, {
	{2, 3, 4},
	{5, 6, 7},
	{8, 9, 10}
});

constexpr auto ref_all9_mod_res = make_matrix< int >(3_DS, {
	{1, 0, 1},
	{4, 3, 2},
	{1, 0, 9}
});


// TODO: also check non compile time versions
// TODO: also check non square versions


BOOST_AUTO_TEST_SUITE(suite_operator)


BOOST_AUTO_TEST_CASE(test_element_plus_assign){
	auto m = ref1;

	element_plus_assign(m, 1);
	auto eq = m == ref1_element_plus1;
	BOOST_TEST(eq);
}

BOOST_AUTO_TEST_CASE(test_element_minus_assign){
	auto m = ref1;

	element_minus_assign(m, 1);
	auto eq = m == ref1_element_minus1;
	BOOST_TEST(eq);
}

BOOST_AUTO_TEST_CASE(test_multiplies_assign){
	auto m = ref1;

	m *= 3;
	auto eq = m == ref3;
	BOOST_TEST(eq);
}

BOOST_AUTO_TEST_CASE(test_divides_assign){
	auto m = ref3;

	m /= 3;
	auto eq = m == ref1;
	BOOST_TEST(eq);
}

BOOST_AUTO_TEST_CASE(test_modulus_assign){
	auto m = ref1;

	m %= 3;
	auto eq = m == ref1_mod3;
	BOOST_TEST(eq);
}


BOOST_AUTO_TEST_CASE(test_plus_assign){
	auto m = ref1;

	m += ref1;
	auto eq = m == ref2;
	BOOST_TEST(eq);
}

BOOST_AUTO_TEST_CASE(test_minus_assign){
	auto m = ref2;

	m -= ref1;
	auto eq = m == ref1;
	BOOST_TEST(eq);
}

BOOST_AUTO_TEST_CASE(test_element_multiplies_assign){
	auto m = ref1;

	element_multiplies_assign(m, ref1);
	auto eq = m == ref1_square;
	BOOST_TEST(eq);
}

BOOST_AUTO_TEST_CASE(test_element_divides_assign){
	auto m = ref1_element_plus1;

	element_divides_assign(m, ref1_element_plus1);
	auto eq = m == ref_all1;
	BOOST_TEST(eq);
}

BOOST_AUTO_TEST_CASE(test_element_modulus_assign){
	auto m = ref_all9;

	element_modulus_assign(m, ref_mod);
	auto eq = m == ref_all9_mod_res;
	BOOST_TEST(eq);
}


BOOST_AUTO_TEST_CASE(test_element_plus){
	auto m = ref1;

	auto res = element_plus(m, 1);
	auto eq = res == ref1_element_plus1;
	BOOST_TEST(eq);
}

BOOST_AUTO_TEST_CASE(test_element_minus){
	auto m = ref1;

	auto res = element_minus(m, 1);
	auto eq = res == ref1_element_minus1;
	BOOST_TEST(eq);
}

BOOST_AUTO_TEST_CASE(test_multiplies){
	auto m = ref1;

	auto res1 = m * 3;
	auto res2 = 3 * m;
	auto eq1 = res1 == ref3;
	auto eq2 = res2 == ref3;
	BOOST_TEST(eq1);
	BOOST_TEST(eq2);
}

BOOST_AUTO_TEST_CASE(test_divides){
	auto m = ref3;

	auto res = m / 3;
	auto eq = res == ref1;
	BOOST_TEST(eq);
}

BOOST_AUTO_TEST_CASE(test_modulus){
	auto m = ref1;

	auto res = m % 3;
	auto eq = res == ref1_mod3;
	BOOST_TEST(eq);
}


BOOST_AUTO_TEST_CASE(test_plus){
	auto m = ref1;

	auto res = m + ref1;
	auto eq = res == ref2;
	BOOST_TEST(eq);
}

BOOST_AUTO_TEST_CASE(test_minus){
	auto m = ref2;

	auto res = m - ref1;
	auto eq = res == ref1;
	BOOST_TEST(eq);
}

BOOST_AUTO_TEST_CASE(test_element_multiplies){
	auto m = ref1;

	auto res = element_multiplies(m, ref1);
	auto eq = res == ref1_square;
	BOOST_TEST(eq);
}

BOOST_AUTO_TEST_CASE(test_element_divides){
	auto m = ref1_element_plus1;

	auto res = element_divides(m, ref1_element_plus1);
	auto eq = res == ref_all1;
	BOOST_TEST(eq);
}

BOOST_AUTO_TEST_CASE(test_element_modulus){
	auto m = ref_all9;

	auto res = element_modulus(m, ref_mod);
	auto eq = res == ref_all9_mod_res;
	BOOST_TEST(eq);
}


BOOST_AUTO_TEST_CASE(test_matrix_multiplies){
	auto m = ref_all1 * ref_all1;

	auto eq = m == ref_all3;
	BOOST_TEST(eq);
}


BOOST_AUTO_TEST_CASE(test_transpose){
	constexpr auto m_cc = make_matrix< int >(2_CS, 3_RS, {
		{1, 2},
		{3, 4},
		{5, 6}
	});

	auto m_CD = make_matrix< int >(2_CS, 3_RD, {
		{1, 2},
		{3, 4},
		{5, 6}
	});

	auto m_dc = make_matrix< int >(2_CD, 3_RS, {
		{1, 2},
		{3, 4},
		{5, 6}
	});

	auto m_DD = make_matrix< int >(2_CD, 3_RD, {
		{1, 2},
		{3, 4},
		{5, 6}
	});

	/*constexpr*/ auto trans_cc = transpose(m_cc); //TODO:need constexpr lambda
	auto trans_CD = transpose(m_CD);
	auto trans_dc = transpose(m_dc);
	auto trans_DD = transpose(m_DD);

	auto check1 = [](auto const& m){
		return
			m.cols() == 3_CS &&
			m.rows() == 2_RS &&
			m(0_c, 0_r) == 1 &&
			m(1_c, 0_r) == 3 &&
			m(2_c, 0_r) == 5 &&
			m(0_c, 1_r) == 2 &&
			m(1_c, 1_r) == 4 &&
			m(2_c, 1_r) == 6;
	};

	auto check2 = [](auto const& m){
		return
			m.cols() == 2_CS &&
			m.rows() == 3_RS &&
			m(0_c, 0_r) == 1 &&
			m(1_c, 0_r) == 2 &&
			m(0_c, 1_r) == 3 &&
			m(1_c, 1_r) == 4 &&
			m(0_c, 2_r) == 5 &&
			m(1_c, 2_r) == 6;
	};

	BOOST_TEST(check1(trans_cc));
	BOOST_TEST(check1(trans_CD));
	BOOST_TEST(check1(trans_dc));
	BOOST_TEST(check1(trans_DD));

	BOOST_TEST((rt_id(trans_cc) == id< std_matrix< int, 3_C, 2_R > >));
	BOOST_TEST((rt_id(trans_CD) == id< std_matrix< int, 0_C, 2_R > >));
	BOOST_TEST((rt_id(trans_dc) == id< std_matrix< int, 3_C, 0_R > >));
	BOOST_TEST((rt_id(trans_DD) == id< std_matrix< int, 0_C, 0_R > >));

	BOOST_TEST(check2(transpose(trans_cc)));
	BOOST_TEST(check2(transpose(trans_CD)));
	BOOST_TEST(check2(transpose(trans_dc)));
	BOOST_TEST(check2(transpose(trans_DD)));
}

BOOST_AUTO_TEST_CASE(test_unary_plus){
	auto m = ref1_element_minus1;

	auto n = +m;

	BOOST_TEST((
			n.cols() == 3_CS &&
			n.rows() == 3_RS &&
			n(0_c, 0_r) == -1 &&
			n(1_c, 0_r) == 0 &&
			n(2_c, 0_r) == 1 &&
			n(0_c, 1_r) == 2 &&
			n(1_c, 1_r) == 3 &&
			n(2_c, 1_r) == 4 &&
			n(0_c, 2_r) == 5 &&
			n(1_c, 2_r) == 6 &&
			n(2_c, 2_r) == 7
	));
}

BOOST_AUTO_TEST_CASE(test_unary_minus){
	auto m = ref1_element_minus1;

	auto n = -m;

	BOOST_TEST((
			n.cols() == 3_CS &&
			n.rows() == 3_RS &&
			n(0_c, 0_r) == 1 &&
			n(1_c, 0_r) == 0 &&
			n(2_c, 0_r) == -1 &&
			n(0_c, 1_r) == -2 &&
			n(1_c, 1_r) == -3 &&
			n(2_c, 1_r) == -4 &&
			n(0_c, 2_r) == -5 &&
			n(1_c, 2_r) == -6 &&
			n(2_c, 2_r) == -7
	));
}

BOOST_AUTO_TEST_CASE(test_abs){
	auto m = ref1_element_minus1;

	auto n = abs(m);

	BOOST_TEST((
			n.cols() == 3_CS &&
			n.rows() == 3_RS &&
			n(0_c, 0_r) == 1 &&
			n(1_c, 0_r) == 0 &&
			n(2_c, 0_r) == 1 &&
			n(0_c, 1_r) == 2 &&
			n(1_c, 1_r) == 3 &&
			n(2_c, 1_r) == 4 &&
			n(0_c, 2_r) == 5 &&
			n(1_c, 2_r) == 6 &&
			n(2_c, 2_r) == 7
	));
}


BOOST_AUTO_TEST_SUITE_END()
