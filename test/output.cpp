//-----------------------------------------------------------------------------
// Copyright (c) 2015-2018 Benjamin Buch
//
// https://github.com/bebuch/mitrax
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt)
//-----------------------------------------------------------------------------
#define BOOST_TEST_MODULE mitrax output
#include <boost/test/unit_test.hpp>

#include <mitrax/matrix.hpp>
#include <mitrax/io.hpp>

#include <sstream>


using boost::typeindex::type_id;
using boost::typeindex::type_id_runtime;
using namespace mitrax;
using namespace mitrax::literals;


constexpr int m33[3][3] = {
	{1, 2, 3},
	{4, 5, 6},
	{7, 8, 9}
};

constexpr char const* m33_ref = "[3,3]((1,2,3),(4,5,6),(7,8,9))";

constexpr int m23[3][2] = {
	{1, 2},
	{4, 5},
	{7, 8}
};

constexpr char const* m23_ref = "[2,3]((1,2),(4,5),(7,8))";

constexpr int m32[2][3] = {
	{1, 2, 3},
	{4, 5, 6}
};

constexpr char const* m32_ref = "[3,2]((1,2,3),(4,5,6))";

template < typename T >
std::string out(T const& m){
	std::ostringstream os;
	os << m;
	return os.str();
}


BOOST_AUTO_TEST_SUITE(suite_output)


BOOST_AUTO_TEST_CASE(test_output_3x3){
	auto m1 = make_matrix(3_CS, 3_RS, m33);
	auto m2 = make_matrix(3_CD, 3_RS, m33);
	auto m3 = make_matrix(3_CS, 3_RD, m33);
	auto m4 = make_matrix(3_CD, 3_RD, m33);

	BOOST_TEST(out(m1) == m33_ref);
	BOOST_TEST(out(m2) == m33_ref);
	BOOST_TEST(out(m3) == m33_ref);
	BOOST_TEST(out(m4) == m33_ref);
}

BOOST_AUTO_TEST_CASE(test_output_2x3){
	auto m1 = make_matrix(2_CS, 3_RS, m23);
	auto m2 = make_matrix(2_CD, 3_RS, m23);
	auto m3 = make_matrix(2_CS, 3_RD, m23);
	auto m4 = make_matrix(2_CD, 3_RD, m23);

	BOOST_TEST(out(m1) == m23_ref);
	BOOST_TEST(out(m2) == m23_ref);
	BOOST_TEST(out(m3) == m23_ref);
	BOOST_TEST(out(m4) == m23_ref);
}

BOOST_AUTO_TEST_CASE(test_output_3x2){
	auto m1 = make_matrix(3_CS, 2_RS, m32);
	auto m2 = make_matrix(3_CD, 2_RS, m32);
	auto m3 = make_matrix(3_CS, 2_RD, m32);
	auto m4 = make_matrix(3_CD, 2_RD, m32);

	BOOST_TEST(out(m1) == m32_ref);
	BOOST_TEST(out(m2) == m32_ref);
	BOOST_TEST(out(m3) == m32_ref);
	BOOST_TEST(out(m4) == m32_ref);
}


BOOST_AUTO_TEST_SUITE_END()
