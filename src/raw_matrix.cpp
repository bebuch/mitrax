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
#include <mitrax/compare.hpp>


using boost::typeindex::type_id;
using boost::typeindex::type_id_runtime;
using namespace mitrax;


BOOST_AUTO_TEST_CASE(test_raw_square_matrix){
	constexpr auto m1 = to_matrix< int, 3, 3 >({
		{0, 1, 2},
		{3, 4, 5},
		{6, 7, 8}
	});

	constexpr auto m2 = to_square_matrix< int, 3 >({
		{0, 1, 2},
		{3, 4, 5},
		{6, 7, 8}
	});

	BOOST_TEST(type_id_runtime(m1) == type_id_runtime(m2));

	auto type1 = type_id< raw_matrix< int, 3, 3 > >();
	BOOST_TEST(type_id_runtime(m1) == type1);

	auto type2 = type_id< matrix< raw_matrix_impl< int, 3, 3 >, 3, 3 > >();
	BOOST_TEST(type_id_runtime(m1) == type2);

	constexpr auto eq = m1 == m2;
	BOOST_TEST(eq);

	constexpr auto neq = m1 != m2;
	BOOST_TEST(!neq);

	BOOST_TEST(m1(0, 0) == 0);
	BOOST_TEST(m1(1, 0) == 1);
	BOOST_TEST(m1(2, 0) == 2);
	BOOST_TEST(m1(0, 1) == 3);
	BOOST_TEST(m1(1, 1) == 4);
	BOOST_TEST(m1(2, 1) == 5);
	BOOST_TEST(m1(0, 2) == 6);
	BOOST_TEST(m1(1, 2) == 7);
	BOOST_TEST(m1(2, 2) == 8);
}


BOOST_AUTO_TEST_CASE(test_raw_col_vector){
	constexpr auto m = to_matrix< int, 3, 1 >({ {0, 1, 2} });

	constexpr auto v = to_col_vector< int, 3 >({0, 1, 2});

	BOOST_TEST(type_id_runtime(m) == type_id_runtime(v));

	auto type1 = type_id< raw_matrix< int, 3, 1 > >();
	BOOST_TEST(type_id_runtime(m) == type1);

	auto type2 = type_id< raw_col_vector< int, 3 > >();
	BOOST_TEST(type_id_runtime(m) == type2);

	constexpr auto eq = m == v;
	BOOST_TEST(eq);

	constexpr auto neq = m != v;
	BOOST_TEST(!neq);

	BOOST_TEST(m(0, 0) == 0);
	BOOST_TEST(m(1, 0) == 1);
	BOOST_TEST(m(2, 0) == 2);

	BOOST_TEST(m[0] == 0);
	BOOST_TEST(m[1] == 1);
	BOOST_TEST(m[2] == 2);
}


BOOST_AUTO_TEST_CASE(test_raw_row_vector){
	constexpr auto m = to_matrix< int, 1, 3 >({ {0}, {1}, {2} });

	constexpr auto v = to_row_vector< int, 3 >({0, 1, 2});

	BOOST_TEST(type_id_runtime(m) == type_id_runtime(v));

	auto type1 = type_id< raw_matrix< int, 1, 3 > >();
	BOOST_TEST(type_id_runtime(m) == type1);

	auto type2 = type_id< raw_row_vector< int, 3 > >();
	BOOST_TEST(type_id_runtime(m) == type2);

	constexpr auto eq = m == v;
	BOOST_TEST(eq);

	constexpr auto neq = m != v;
	BOOST_TEST(!neq);

	BOOST_TEST(m(0, 0) == 0);
	BOOST_TEST(m(0, 1) == 1);
	BOOST_TEST(m(0, 2) == 2);

	BOOST_TEST(m[0] == 0);
	BOOST_TEST(m[1] == 1);
	BOOST_TEST(m[2] == 2);
}


BOOST_AUTO_TEST_CASE(test_one_element_matrix){
	constexpr auto m1 = to_matrix< int, 1, 1 >({ {0} });
	constexpr auto m2 = to_square_matrix< int, 1 >({ {0} });

	constexpr auto cv = to_col_vector< int, 1 >({0});
	constexpr auto rv = to_row_vector< int, 1 >({0});

	int value1 = m1; (void)value1;
	int value2 = m2; (void)value2;
	int value3 = cv; (void)value3;
	int value4 = rv; (void)value4;

	BOOST_TEST(type_id_runtime(m1) == type_id_runtime(m1));

	BOOST_TEST(type_id_runtime(m1) == type_id_runtime(cv));

	BOOST_TEST(type_id_runtime(m1) == type_id_runtime(rv));

	auto type1 = type_id< raw_matrix< int, 1, 1 > >();
	BOOST_TEST(type_id_runtime(m1) == type1);

	auto type2 = type_id< raw_row_vector< int, 1 > >();
	BOOST_TEST(type_id_runtime(m1) == type2);

	auto type3 = type_id< raw_col_vector< int, 1 > >();
	BOOST_TEST(type_id_runtime(m1) == type3);

	auto type4 = type_id< raw_square_matrix< int, 1 > >();
	BOOST_TEST(type_id_runtime(m1) == type4);


	constexpr auto eq1 = m1 == m2;
	BOOST_TEST(eq1);

	constexpr auto eq2 = m1 == cv;
	BOOST_TEST(eq2);

	constexpr auto eq3 = m1 == rv;
	BOOST_TEST(eq3);

	constexpr auto neq1 = m1 != m2;
	BOOST_TEST(!neq1);

	constexpr auto neq2 = m1 != cv;
	BOOST_TEST(!neq2);

	constexpr auto neq3 = m1 != rv;
	BOOST_TEST(!neq3);


	BOOST_TEST(m1(0, 0) == 0);

	BOOST_TEST(m1[0] == 0);
}


// 	auto ms0x3 = with_dynamic_cols(m3x3);
// 	std::cout << type_id_runtime(ms0x3).pretty_name() << std::endl;
// 
// 	auto ms3x0 = with_dynamic_rows(m3x3);
// 	std::cout << type_id_runtime(ms3x0).pretty_name() << std::endl;
// 
// 	auto ms0x0 = with_dynamic_dims(m3x3);
// 	std::cout << type_id_runtime(ms0x0).pretty_name() << std::endl;
