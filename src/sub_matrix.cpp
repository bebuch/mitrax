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


using boost::typeindex::type_id;
using boost::typeindex::type_id_runtime;
using namespace mitrax;
using namespace mitrax::literals;


BOOST_AUTO_TEST_SUITE(test_suite_sub_matrix)


namespace{


	constexpr auto ref = make_square_matrix< int >(3_D, {
		{0, 1, 2},
		{3, 4, 5},
		{6, 7, 8}
	});


	template < typename M >
	constexpr bool check1(M const& m){
		return
			m.cols() == 2 &&
			m.rows() == 2 &&
			m(0, 0) == 0 &&
			m(1, 0) == 1 &&
			m(0, 1) == 3 &&
			m(1, 1) == 4;
	}

	template < typename M >
	constexpr bool check2(M const& m){
		return
			m.cols() == 2 &&
			m.rows() == 2 &&
			m(0, 0) == 1 &&
			m(1, 0) == 2 &&
			m(0, 1) == 4 &&
			m(1, 1) == 5;
	}

	template < typename M >
	constexpr bool check3(M const& m){
		return
			m.cols() == 2 &&
			m.rows() == 2 &&
			m(0, 0) == 3 &&
			m(1, 0) == 4 &&
			m(0, 1) == 6 &&
			m(1, 1) == 7;
	}

	template < typename M >
	constexpr bool check4(M const& m){
		return
			m.cols() == 2 &&
			m.rows() == 2 &&
			m(0, 0) == 4 &&
			m(1, 0) == 5 &&
			m(0, 1) == 7 &&
			m(1, 1) == 8;
	}


}


// TODO: add more unit tests
// TODO: check also for result types
// TODO: check move version and const/non-const versions
// TODO: use non square matrices


BOOST_AUTO_TEST_CASE(test_sub_matrix_2x2){
	constexpr auto m = ref;

	constexpr auto sub = m.sub_matrix(0, 0, 2_C, 2_R);
	auto type = type_id< raw_matrix< int, 2, 2 > >();
	BOOST_TEST(type_id_runtime(sub) == type);

	BOOST_TEST(check1(m.sub_matrix(0, 0, 2_C, 2_R)));
	BOOST_TEST(check2(m.sub_matrix(1, 0, 2_C, 2_R)));
	BOOST_TEST(check3(m.sub_matrix(0, 1, 2_C, 2_R)));
	BOOST_TEST(check4(m.sub_matrix(1, 1, 2_C, 2_R)));
}

BOOST_AUTO_TEST_CASE(test_sub_matrix_2rtx2){
	auto m = ref;

	auto sub = m.sub_matrix(0, 0, 2_C_rt, 2_R);
	auto type = type_id< raw_matrix< int, 0, 2 > >();
	BOOST_TEST(type_id_runtime(sub) == type);

	BOOST_TEST(check1(m.sub_matrix(0, 0, 2_C_rt, 2_R)));
	BOOST_TEST(check2(m.sub_matrix(1, 0, 2_C_rt, 2_R)));
	BOOST_TEST(check3(m.sub_matrix(0, 1, 2_C_rt, 2_R)));
	BOOST_TEST(check4(m.sub_matrix(1, 1, 2_C_rt, 2_R)));
}

BOOST_AUTO_TEST_CASE(test_sub_matrix_2x2rt){
	auto m = ref;

	auto sub = m.sub_matrix(0, 0, 2_C, 2_R_rt);
	auto type = type_id< raw_matrix< int, 2, 0 > >();
	BOOST_TEST(type_id_runtime(sub) == type);

	BOOST_TEST(check1(m.sub_matrix(0, 0, 2_C, 2_R_rt)));
	BOOST_TEST(check2(m.sub_matrix(1, 0, 2_C, 2_R_rt)));
	BOOST_TEST(check3(m.sub_matrix(0, 1, 2_C, 2_R_rt)));
	BOOST_TEST(check4(m.sub_matrix(1, 1, 2_C, 2_R_rt)));
}

BOOST_AUTO_TEST_CASE(test_sub_matrix_2rtx2rt){
	auto m = ref;

	auto sub = m.sub_matrix(0, 0, 2_C_rt, 2_R_rt);
	auto type = type_id< raw_matrix< int, 0, 0 > >();
	BOOST_TEST(type_id_runtime(sub) == type);

	BOOST_TEST(check1(m.sub_matrix(0, 0, 2_C_rt, 2_R_rt)));
	BOOST_TEST(check2(m.sub_matrix(1, 0, 2_C_rt, 2_R_rt)));
	BOOST_TEST(check3(m.sub_matrix(0, 1, 2_C_rt, 2_R_rt)));
	BOOST_TEST(check4(m.sub_matrix(1, 1, 2_C_rt, 2_R_rt)));
}


BOOST_AUTO_TEST_SUITE_END()
