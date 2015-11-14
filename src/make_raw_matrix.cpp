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


BOOST_AUTO_TEST_SUITE(make_raw_matrix)


BOOST_AUTO_TEST_CASE(test_raw_matrix_3x3){
	constexpr auto m1 = make_matrix< int >(3_C, 3_R, {
		{0, 1, 2},
		{3, 4, 5},
		{6, 7, 8}
	});

	constexpr auto m2 = make_square_matrix< int >(3_D, {
		{0, 1, 2},
		{3, 4, 5},
		{6, 7, 8}
	});


	BOOST_TEST(type_id_runtime(m1) == type_id_runtime(m2));


	auto type1 = type_id< raw_matrix< int, 3, 3 > >();
	BOOST_TEST(type_id_runtime(m1) == type1);

	auto type2 = type_id< matrix< raw_matrix_impl< int, 3, 3 >, 3, 3 > >();
	BOOST_TEST(type_id_runtime(m1) == type2);


	BOOST_TEST(m1.cols() == 3_C);
	BOOST_TEST(m1.rows() == 3_R);

	BOOST_TEST(m1(0, 0) == 0);
	BOOST_TEST(m1(1, 0) == 1);
	BOOST_TEST(m1(2, 0) == 2);
	BOOST_TEST(m1(0, 1) == 3);
	BOOST_TEST(m1(1, 1) == 4);
	BOOST_TEST(m1(2, 1) == 5);
	BOOST_TEST(m1(0, 2) == 6);
	BOOST_TEST(m1(1, 2) == 7);
	BOOST_TEST(m1(2, 2) == 8);


	BOOST_TEST(m2.cols() == 3_C);
	BOOST_TEST(m2.rows() == 3_R);

	BOOST_TEST(m2(0, 0) == 0);
	BOOST_TEST(m2(1, 0) == 1);
	BOOST_TEST(m2(2, 0) == 2);
	BOOST_TEST(m2(0, 1) == 3);
	BOOST_TEST(m2(1, 1) == 4);
	BOOST_TEST(m2(2, 1) == 5);
	BOOST_TEST(m2(0, 2) == 6);
	BOOST_TEST(m2(1, 2) == 7);
	BOOST_TEST(m2(2, 2) == 8);
}


BOOST_AUTO_TEST_CASE(test_raw_matrix_2x3){
	constexpr auto m = make_matrix< int >(2_C, 3_R, {
		{0, 1},
		{3, 4},
		{6, 7}
	});

	auto type1 = type_id< raw_matrix< int, 2, 3 > >();
	BOOST_TEST(type_id_runtime(m) == type1);

	auto type2 = type_id< matrix< raw_matrix_impl< int, 2, 3 >, 2, 3 > >();
	BOOST_TEST(type_id_runtime(m) == type2);


	BOOST_TEST(m.cols() == 2_C);
	BOOST_TEST(m.rows() == 3_R);

	BOOST_TEST(m(0, 0) == 0);
	BOOST_TEST(m(1, 0) == 1);
	BOOST_TEST(m(0, 1) == 3);
	BOOST_TEST(m(1, 1) == 4);
	BOOST_TEST(m(0, 2) == 6);
	BOOST_TEST(m(1, 2) == 7);
}


BOOST_AUTO_TEST_CASE(test_raw_matrix_3x2){
	constexpr auto m = make_matrix< int >(3_C, 2_R, {
		{0, 1, 2},
		{3, 4, 5}
	});

	auto type1 = type_id< raw_matrix< int, 3, 2 > >();
	BOOST_TEST(type_id_runtime(m) == type1);

	auto type2 = type_id< matrix< raw_matrix_impl< int, 3, 2 >, 3, 2 > >();
	BOOST_TEST(type_id_runtime(m) == type2);


	BOOST_TEST(m.cols() == 3_C);
	BOOST_TEST(m.rows() == 2_R);

	BOOST_TEST(m(0, 0) == 0);
	BOOST_TEST(m(1, 0) == 1);
	BOOST_TEST(m(2, 0) == 2);
	BOOST_TEST(m(0, 1) == 3);
	BOOST_TEST(m(1, 1) == 4);
	BOOST_TEST(m(2, 1) == 5);
}


BOOST_AUTO_TEST_CASE(test_raw_col_vector_3){
	constexpr auto m = make_matrix< int >(1_C, 3_R, {{0}, {1}, {2}});

	constexpr auto v = make_col_vector< int >(3_R, {0, 1, 2});


	BOOST_TEST(type_id_runtime(m) == type_id_runtime(v));


	auto type1 = type_id< raw_matrix< int, 1, 3 > >();
	BOOST_TEST(type_id_runtime(m) == type1);

	auto type2 = type_id< raw_col_vector< int, 3 > >();
	BOOST_TEST(type_id_runtime(m) == type2);


	BOOST_TEST(m.cols() == 1_C);
	BOOST_TEST(m.rows() == 3_R);

	BOOST_TEST(m(0, 0) == 0);
	BOOST_TEST(m(0, 1) == 1);
	BOOST_TEST(m(0, 2) == 2);

	BOOST_TEST(m[0] == 0);
	BOOST_TEST(m[1] == 1);
	BOOST_TEST(m[2] == 2);

	BOOST_TEST(v.cols() == 1_C);
	BOOST_TEST(v.rows() == 3_R);

	BOOST_TEST(v(0, 0) == 0);
	BOOST_TEST(v(0, 1) == 1);
	BOOST_TEST(v(0, 2) == 2);

	BOOST_TEST(v[0] == 0);
	BOOST_TEST(v[1] == 1);
	BOOST_TEST(v[2] == 2);
}


BOOST_AUTO_TEST_CASE(test_raw_row_vector_3){
	constexpr auto m = make_matrix< int >(3_C, 1_R, {{0, 1, 2}});

	constexpr auto v = make_row_vector< int >(3_C, {0, 1, 2});


	BOOST_TEST(type_id_runtime(m) == type_id_runtime(v));


	auto type1 = type_id< raw_matrix< int, 3, 1 > >();
	BOOST_TEST(type_id_runtime(m) == type1);

	auto type2 = type_id< raw_row_vector< int, 3 > >();
	BOOST_TEST(type_id_runtime(m) == type2);


	BOOST_TEST(m.cols() == 3_C);
	BOOST_TEST(m.rows() == 1_R);

	BOOST_TEST(m(0, 0) == 0);
	BOOST_TEST(m(1, 0) == 1);
	BOOST_TEST(m(2, 0) == 2);

	BOOST_TEST(m[0] == 0);
	BOOST_TEST(m[1] == 1);
	BOOST_TEST(m[2] == 2);

	BOOST_TEST(v.cols() == 3_C);
	BOOST_TEST(v.rows() == 1_R);

	BOOST_TEST(v(0, 0) == 0);
	BOOST_TEST(v(1, 0) == 1);
	BOOST_TEST(v(2, 0) == 2);

	BOOST_TEST(v[0] == 0);
	BOOST_TEST(v[1] == 1);
	BOOST_TEST(v[2] == 2);
}


BOOST_AUTO_TEST_CASE(test_raw_matrix_1x1){
	constexpr auto m1 = make_matrix< int >(1_C, 1_R, {{0}});
	constexpr auto m2 = make_square_matrix< int >(1_D, {{0}});

	constexpr auto cv = make_col_vector< int >(1_R, {0});
	constexpr auto rv = make_row_vector< int >(1_C, {0});


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


	BOOST_TEST(m1(0, 0) == 0);
	BOOST_TEST(m2(0, 0) == 0);
	BOOST_TEST(cv(0, 0) == 0);
	BOOST_TEST(rv(0, 0) == 0);

	BOOST_TEST(m1[0] == 0);
	BOOST_TEST(m2[0] == 0);
	BOOST_TEST(cv[0] == 0);
	BOOST_TEST(rv[0] == 0);
}


BOOST_AUTO_TEST_CASE(test_raw_matrix_3rtx3rt){
	auto const m1 = make_matrix< int >(3_C_rt, 3_R_rt, {
		{0, 1, 2},
		{3, 4, 5},
		{6, 7, 8}
	});

	auto const m2 = make_square_matrix< int >(3_D_rt, {
		{0, 1, 2},
		{3, 4, 5},
		{6, 7, 8}
	});


	BOOST_TEST(type_id_runtime(m1) == type_id_runtime(m2));


	auto type1 = type_id< raw_matrix< int, 0, 0 > >();
	BOOST_TEST(type_id_runtime(m1) == type1);

	auto type2 = type_id< matrix< raw_matrix_impl< int, 0, 0 >, 0, 0 > >();
	BOOST_TEST(type_id_runtime(m1) == type2);


	BOOST_TEST(m1.cols() == 3_C_rt);
	BOOST_TEST(m1.rows() == 3_R_rt);

	BOOST_TEST(m1(0, 0) == 0);
	BOOST_TEST(m1(1, 0) == 1);
	BOOST_TEST(m1(2, 0) == 2);
	BOOST_TEST(m1(0, 1) == 3);
	BOOST_TEST(m1(1, 1) == 4);
	BOOST_TEST(m1(2, 1) == 5);
	BOOST_TEST(m1(0, 2) == 6);
	BOOST_TEST(m1(1, 2) == 7);
	BOOST_TEST(m1(2, 2) == 8);


	BOOST_TEST(m2.cols() == 3_C_rt);
	BOOST_TEST(m2.rows() == 3_R_rt);

	BOOST_TEST(m2(0, 0) == 0);
	BOOST_TEST(m2(1, 0) == 1);
	BOOST_TEST(m2(2, 0) == 2);
	BOOST_TEST(m2(0, 1) == 3);
	BOOST_TEST(m2(1, 1) == 4);
	BOOST_TEST(m2(2, 1) == 5);
	BOOST_TEST(m2(0, 2) == 6);
	BOOST_TEST(m2(1, 2) == 7);
	BOOST_TEST(m2(2, 2) == 8);
}


BOOST_AUTO_TEST_CASE(test_raw_matrix_3rtx3){
	auto const m = make_matrix< int >(3_C_rt, 3_R, {
		{0, 1, 2},
		{3, 4, 5},
		{6, 7, 8}
	});


	auto type1 = type_id< raw_matrix< int, 0, 3 > >();
	BOOST_TEST(type_id_runtime(m) == type1);

	auto type2 = type_id< matrix< raw_matrix_impl< int, 0, 3 >, 0, 3 > >();
	BOOST_TEST(type_id_runtime(m) == type2);


	BOOST_TEST(m.cols() == 3_C_rt);
	BOOST_TEST(m.rows() == 3_R);

	BOOST_TEST(m(0, 0) == 0);
	BOOST_TEST(m(1, 0) == 1);
	BOOST_TEST(m(2, 0) == 2);
	BOOST_TEST(m(0, 1) == 3);
	BOOST_TEST(m(1, 1) == 4);
	BOOST_TEST(m(2, 1) == 5);
	BOOST_TEST(m(0, 2) == 6);
	BOOST_TEST(m(1, 2) == 7);
	BOOST_TEST(m(2, 2) == 8);
}


BOOST_AUTO_TEST_CASE(test_raw_matrix_3x3rt){
	auto const m = make_matrix< int >(3_C, 3_R_rt, {
		{0, 1, 2},
		{3, 4, 5},
		{6, 7, 8}
	});


	auto type1 = type_id< raw_matrix< int, 3, 0 > >();
	BOOST_TEST(type_id_runtime(m) == type1);

	auto type2 = type_id< matrix< raw_matrix_impl< int, 3, 0 >, 3, 0 > >();
	BOOST_TEST(type_id_runtime(m) == type2);


	BOOST_TEST(m.cols() == 3_C);
	BOOST_TEST(m.rows() == 3_R_rt);

	BOOST_TEST(m(0, 0) == 0);
	BOOST_TEST(m(1, 0) == 1);
	BOOST_TEST(m(2, 0) == 2);
	BOOST_TEST(m(0, 1) == 3);
	BOOST_TEST(m(1, 1) == 4);
	BOOST_TEST(m(2, 1) == 5);
	BOOST_TEST(m(0, 2) == 6);
	BOOST_TEST(m(1, 2) == 7);
	BOOST_TEST(m(2, 2) == 8);
}


BOOST_AUTO_TEST_CASE(test_raw_matrix_2rtx3){
	auto const m = make_matrix< int >(2_C_rt, 3_R, {
		{0, 1},
		{3, 4},
		{6, 7}
	});

	auto type1 = type_id< raw_matrix< int, 0, 3 > >();
	BOOST_TEST(type_id_runtime(m) == type1);

	auto type2 = type_id< matrix< raw_matrix_impl< int, 0, 3 >, 0, 3 > >();
	BOOST_TEST(type_id_runtime(m) == type2);


	BOOST_TEST(m.cols() == 2_C_rt);
	BOOST_TEST(m.rows() == 3_R);

	BOOST_TEST(m(0, 0) == 0);
	BOOST_TEST(m(1, 0) == 1);
	BOOST_TEST(m(0, 1) == 3);
	BOOST_TEST(m(1, 1) == 4);
	BOOST_TEST(m(0, 2) == 6);
	BOOST_TEST(m(1, 2) == 7);
}


BOOST_AUTO_TEST_CASE(test_raw_matrix_3x2rt){
	auto const m = make_matrix< int >(3_C, 2_R_rt, {
		{0, 1, 2},
		{3, 4, 5}
	});

	auto type1 = type_id< raw_matrix< int, 3, 0 > >();
	BOOST_TEST(type_id_runtime(m) == type1);

	auto type2 = type_id< matrix< raw_matrix_impl< int, 3, 0 >, 3, 0 > >();
	BOOST_TEST(type_id_runtime(m) == type2);


	BOOST_TEST(m.cols() == 3_C);
	BOOST_TEST(m.rows() == 2_R_rt);

	BOOST_TEST(m(0, 0) == 0);
	BOOST_TEST(m(1, 0) == 1);
	BOOST_TEST(m(2, 0) == 2);
	BOOST_TEST(m(0, 1) == 3);
	BOOST_TEST(m(1, 1) == 4);
	BOOST_TEST(m(2, 1) == 5);
}



BOOST_AUTO_TEST_CASE(test_raw_col_vector_3rt){
	auto const m = make_matrix< int >(1_C, 3_R_rt, {{0}, {1}, {2}});

	auto const v = make_col_vector< int >(3_R_rt, {0, 1, 2});


	BOOST_TEST(type_id_runtime(m) == type_id_runtime(v));


	auto type1 = type_id< raw_matrix< int, 1, 0 > >();
	BOOST_TEST(type_id_runtime(m) == type1);

	auto type2 = type_id< raw_col_vector< int, 0 > >();
	BOOST_TEST(type_id_runtime(m) == type2);


	BOOST_TEST(m.cols() == 1_C);
	BOOST_TEST(m.rows() == 3_R_rt);

	BOOST_TEST(m(0, 0) == 0);
	BOOST_TEST(m(0, 1) == 1);
	BOOST_TEST(m(0, 2) == 2);

	BOOST_TEST(m[0] == 0);
	BOOST_TEST(m[1] == 1);
	BOOST_TEST(m[2] == 2);

	BOOST_TEST(v.cols() == 1_C);
	BOOST_TEST(v.rows() == 3_R_rt);

	BOOST_TEST(v(0, 0) == 0);
	BOOST_TEST(v(0, 1) == 1);
	BOOST_TEST(v(0, 2) == 2);

	BOOST_TEST(v[0] == 0);
	BOOST_TEST(v[1] == 1);
	BOOST_TEST(v[2] == 2);
}


BOOST_AUTO_TEST_CASE(test_raw_row_vector_3rt){
	auto const m = make_matrix< int >(3_C_rt, 1_R, {{0, 1, 2}});

	auto const v = make_row_vector< int >(3_C_rt, {0, 1, 2});


	BOOST_TEST(type_id_runtime(m) == type_id_runtime(v));


	auto type1 = type_id< raw_matrix< int, 0, 1 > >();
	BOOST_TEST(type_id_runtime(m) == type1);

	auto type2 = type_id< raw_row_vector< int, 0 > >();
	BOOST_TEST(type_id_runtime(m) == type2);


	BOOST_TEST(m.cols() == 3_C_rt);
	BOOST_TEST(m.rows() == 1_R);

	BOOST_TEST(m(0, 0) == 0);
	BOOST_TEST(m(1, 0) == 1);
	BOOST_TEST(m(2, 0) == 2);

	BOOST_TEST(m[0] == 0);
	BOOST_TEST(m[1] == 1);
	BOOST_TEST(m[2] == 2);

	BOOST_TEST(v.cols() == 3_C_rt);
	BOOST_TEST(v.rows() == 1_R);

	BOOST_TEST(v(0, 0) == 0);
	BOOST_TEST(v(1, 0) == 1);
	BOOST_TEST(v(2, 0) == 2);

	BOOST_TEST(v[0] == 0);
	BOOST_TEST(v[1] == 1);
	BOOST_TEST(v[2] == 2);
}


BOOST_AUTO_TEST_CASE(test_raw_matrix_3x3_default){
	constexpr auto m1 = make_matrix< int >(3_C, 3_R);

	constexpr auto m2 = make_square_matrix< int >(3_D);


	BOOST_TEST(type_id_runtime(m1) == type_id_runtime(m2));


	auto type1 = type_id< raw_matrix< int, 3, 3 > >();
	BOOST_TEST(type_id_runtime(m1) == type1);

	auto type2 = type_id< matrix< raw_matrix_impl< int, 3, 3 >, 3, 3 > >();
	BOOST_TEST(type_id_runtime(m1) == type2);


	BOOST_TEST(m1.cols() == 3_C);
	BOOST_TEST(m1.rows() == 3_R);

	BOOST_TEST(m1(0, 0) == 0);
	BOOST_TEST(m1(1, 0) == 0);
	BOOST_TEST(m1(2, 0) == 0);
	BOOST_TEST(m1(0, 1) == 0);
	BOOST_TEST(m1(1, 1) == 0);
	BOOST_TEST(m1(2, 1) == 0);
	BOOST_TEST(m1(0, 2) == 0);
	BOOST_TEST(m1(1, 2) == 0);
	BOOST_TEST(m1(2, 2) == 0);


	BOOST_TEST(m2.cols() == 3_C);
	BOOST_TEST(m2.rows() == 3_R);

	BOOST_TEST(m2(0, 0) == 0);
	BOOST_TEST(m2(1, 0) == 0);
	BOOST_TEST(m2(2, 0) == 0);
	BOOST_TEST(m2(0, 1) == 0);
	BOOST_TEST(m2(1, 1) == 0);
	BOOST_TEST(m2(2, 1) == 0);
	BOOST_TEST(m2(0, 2) == 0);
	BOOST_TEST(m2(1, 2) == 0);
	BOOST_TEST(m2(2, 2) == 0);
}


BOOST_AUTO_TEST_CASE(test_raw_matrix_2x3_default){
	constexpr auto m = make_matrix< int >(2_C, 3_R);

	auto type1 = type_id< raw_matrix< int, 2, 3 > >();
	BOOST_TEST(type_id_runtime(m) == type1);

	auto type2 = type_id< matrix< raw_matrix_impl< int, 2, 3 >, 2, 3 > >();
	BOOST_TEST(type_id_runtime(m) == type2);


	BOOST_TEST(m.cols() == 2_C);
	BOOST_TEST(m.rows() == 3_R);

	BOOST_TEST(m(0, 0) == 0);
	BOOST_TEST(m(1, 0) == 0);
	BOOST_TEST(m(0, 1) == 0);
	BOOST_TEST(m(1, 1) == 0);
	BOOST_TEST(m(0, 2) == 0);
	BOOST_TEST(m(1, 2) == 0);
}


BOOST_AUTO_TEST_CASE(test_raw_matrix_3x2_default){
	constexpr auto m = make_matrix< int >(3_C, 2_R);

	auto type1 = type_id< raw_matrix< int, 3, 2 > >();
	BOOST_TEST(type_id_runtime(m) == type1);

	auto type2 = type_id< matrix< raw_matrix_impl< int, 3, 2 >, 3, 2 > >();
	BOOST_TEST(type_id_runtime(m) == type2);


	BOOST_TEST(m.cols() == 3_C);
	BOOST_TEST(m.rows() == 2_R);

	BOOST_TEST(m(0, 0) == 0);
	BOOST_TEST(m(1, 0) == 0);
	BOOST_TEST(m(2, 0) == 0);
	BOOST_TEST(m(0, 1) == 0);
	BOOST_TEST(m(1, 1) == 0);
	BOOST_TEST(m(2, 1) == 0);
}


BOOST_AUTO_TEST_CASE(test_raw_col_vector_3_default){
	constexpr auto m = make_matrix< int >(1_C, 3_R);

	constexpr auto v = make_col_vector< int >(3_R);


	BOOST_TEST(type_id_runtime(m) == type_id_runtime(v));


	auto type1 = type_id< raw_matrix< int, 1, 3 > >();
	BOOST_TEST(type_id_runtime(m) == type1);

	auto type2 = type_id< raw_col_vector< int, 3 > >();
	BOOST_TEST(type_id_runtime(m) == type2);


	BOOST_TEST(m.cols() == 1_C);
	BOOST_TEST(m.rows() == 3_R);

	BOOST_TEST(m(0, 0) == 0);
	BOOST_TEST(m(0, 1) == 0);
	BOOST_TEST(m(0, 2) == 0);

	BOOST_TEST(m[0] == 0);
	BOOST_TEST(m[1] == 0);
	BOOST_TEST(m[2] == 0);

	BOOST_TEST(v.cols() == 1_C);
	BOOST_TEST(v.rows() == 3_R);

	BOOST_TEST(v(0, 0) == 0);
	BOOST_TEST(v(0, 1) == 0);
	BOOST_TEST(v(0, 2) == 0);

	BOOST_TEST(v[0] == 0);
	BOOST_TEST(v[1] == 0);
	BOOST_TEST(v[2] == 0);
}


BOOST_AUTO_TEST_CASE(test_raw_row_vector_3_default){
	constexpr auto m = make_matrix< int >(3_C, 1_R);

	constexpr auto v = make_row_vector< int >(3_C);


	BOOST_TEST(type_id_runtime(m) == type_id_runtime(v));


	auto type1 = type_id< raw_matrix< int, 3, 1 > >();
	BOOST_TEST(type_id_runtime(m) == type1);

	auto type2 = type_id< raw_row_vector< int, 3 > >();
	BOOST_TEST(type_id_runtime(m) == type2);


	BOOST_TEST(m.cols() == 3_C);
	BOOST_TEST(m.rows() == 1_R);

	BOOST_TEST(m(0, 0) == 0);
	BOOST_TEST(m(1, 0) == 0);
	BOOST_TEST(m(2, 0) == 0);

	BOOST_TEST(m[0] == 0);
	BOOST_TEST(m[1] == 0);
	BOOST_TEST(m[2] == 0);

	BOOST_TEST(v.cols() == 3_C);
	BOOST_TEST(v.rows() == 1_R);

	BOOST_TEST(v(0, 0) == 0);
	BOOST_TEST(v(1, 0) == 0);
	BOOST_TEST(v(2, 0) == 0);

	BOOST_TEST(v[0] == 0);
	BOOST_TEST(v[1] == 0);
	BOOST_TEST(v[2] == 0);
}


BOOST_AUTO_TEST_CASE(test_raw_matrix_1x1_default){
	constexpr auto m1 = make_matrix< int >(1_C, 1_R);
	constexpr auto m2 = make_square_matrix< int >(1_D);

	constexpr auto cv = make_col_vector< int >(1_R);
	constexpr auto rv = make_row_vector< int >(1_C);


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


	BOOST_TEST(m1(0, 0) == 0);
	BOOST_TEST(m2(0, 0) == 0);
	BOOST_TEST(cv(0, 0) == 0);
	BOOST_TEST(rv(0, 0) == 0);

	BOOST_TEST(m1[0] == 0);
	BOOST_TEST(m2[0] == 0);
	BOOST_TEST(cv[0] == 0);
	BOOST_TEST(rv[0] == 0);
}


BOOST_AUTO_TEST_CASE(test_raw_matrix_3rtx3rt_default){
	auto const m1 = make_matrix< int >(3_C_rt, 3_R_rt);

	auto const m2 = make_square_matrix< int >(3_D_rt);


	BOOST_TEST(type_id_runtime(m1) == type_id_runtime(m2));


	auto type1 = type_id< raw_matrix< int, 0, 0 > >();
	BOOST_TEST(type_id_runtime(m1) == type1);

	auto type2 = type_id< matrix< raw_matrix_impl< int, 0, 0 >, 0, 0 > >();
	BOOST_TEST(type_id_runtime(m1) == type2);


	BOOST_TEST(m1.cols() == 3_C_rt);
	BOOST_TEST(m1.rows() == 3_R_rt);

	BOOST_TEST(m1(0, 0) == 0);
	BOOST_TEST(m1(1, 0) == 0);
	BOOST_TEST(m1(2, 0) == 0);
	BOOST_TEST(m1(0, 1) == 0);
	BOOST_TEST(m1(1, 1) == 0);
	BOOST_TEST(m1(2, 1) == 0);
	BOOST_TEST(m1(0, 2) == 0);
	BOOST_TEST(m1(1, 2) == 0);
	BOOST_TEST(m1(2, 2) == 0);


	BOOST_TEST(m2.cols() == 3_C_rt);
	BOOST_TEST(m2.rows() == 3_R_rt);

	BOOST_TEST(m2(0, 0) == 0);
	BOOST_TEST(m2(1, 0) == 0);
	BOOST_TEST(m2(2, 0) == 0);
	BOOST_TEST(m2(0, 1) == 0);
	BOOST_TEST(m2(1, 1) == 0);
	BOOST_TEST(m2(2, 1) == 0);
	BOOST_TEST(m2(0, 2) == 0);
	BOOST_TEST(m2(1, 2) == 0);
	BOOST_TEST(m2(2, 2) == 0);
}


BOOST_AUTO_TEST_CASE(test_raw_matrix_3rtx3_default){
	auto const m = make_matrix< int >(3_C_rt, 3_R);


	auto type1 = type_id< raw_matrix< int, 0, 3 > >();
	BOOST_TEST(type_id_runtime(m) == type1);

	auto type2 = type_id< matrix< raw_matrix_impl< int, 0, 3 >, 0, 3 > >();
	BOOST_TEST(type_id_runtime(m) == type2);


	BOOST_TEST(m.cols() == 3_C_rt);
	BOOST_TEST(m.rows() == 3_R);

	BOOST_TEST(m(0, 0) == 0);
	BOOST_TEST(m(1, 0) == 0);
	BOOST_TEST(m(2, 0) == 0);
	BOOST_TEST(m(0, 1) == 0);
	BOOST_TEST(m(1, 1) == 0);
	BOOST_TEST(m(2, 1) == 0);
	BOOST_TEST(m(0, 2) == 0);
	BOOST_TEST(m(1, 2) == 0);
	BOOST_TEST(m(2, 2) == 0);
}


BOOST_AUTO_TEST_CASE(test_raw_matrix_3x3rt_default){
	auto const m = make_matrix< int >(3_C, 3_R_rt);


	auto type1 = type_id< raw_matrix< int, 3, 0 > >();
	BOOST_TEST(type_id_runtime(m) == type1);

	auto type2 = type_id< matrix< raw_matrix_impl< int, 3, 0 >, 3, 0 > >();
	BOOST_TEST(type_id_runtime(m) == type2);


	BOOST_TEST(m.cols() == 3_C);
	BOOST_TEST(m.rows() == 3_R_rt);

	BOOST_TEST(m(0, 0) == 0);
	BOOST_TEST(m(1, 0) == 0);
	BOOST_TEST(m(2, 0) == 0);
	BOOST_TEST(m(0, 1) == 0);
	BOOST_TEST(m(1, 1) == 0);
	BOOST_TEST(m(2, 1) == 0);
	BOOST_TEST(m(0, 2) == 0);
	BOOST_TEST(m(1, 2) == 0);
	BOOST_TEST(m(2, 2) == 0);
}


BOOST_AUTO_TEST_CASE(test_raw_matrix_2rtx3_default){
	auto const m = make_matrix< int >(2_C_rt, 3_R);

	auto type1 = type_id< raw_matrix< int, 0, 3 > >();
	BOOST_TEST(type_id_runtime(m) == type1);

	auto type2 = type_id< matrix< raw_matrix_impl< int, 0, 3 >, 0, 3 > >();
	BOOST_TEST(type_id_runtime(m) == type2);


	BOOST_TEST(m.cols() == 2_C_rt);
	BOOST_TEST(m.rows() == 3_R);

	BOOST_TEST(m(0, 0) == 0);
	BOOST_TEST(m(1, 0) == 0);
	BOOST_TEST(m(0, 1) == 0);
	BOOST_TEST(m(1, 1) == 0);
	BOOST_TEST(m(0, 2) == 0);
	BOOST_TEST(m(1, 2) == 0);
}


BOOST_AUTO_TEST_CASE(test_raw_matrix_3x2rt_default){
	auto const m = make_matrix< int >(3_C, 2_R_rt);

	auto type1 = type_id< raw_matrix< int, 3, 0 > >();
	BOOST_TEST(type_id_runtime(m) == type1);

	auto type2 = type_id< matrix< raw_matrix_impl< int, 3, 0 >, 3, 0 > >();
	BOOST_TEST(type_id_runtime(m) == type2);


	BOOST_TEST(m.cols() == 3_C);
	BOOST_TEST(m.rows() == 2_R_rt);

	BOOST_TEST(m(0, 0) == 0);
	BOOST_TEST(m(1, 0) == 0);
	BOOST_TEST(m(2, 0) == 0);
	BOOST_TEST(m(0, 1) == 0);
	BOOST_TEST(m(1, 1) == 0);
	BOOST_TEST(m(2, 1) == 0);
}



BOOST_AUTO_TEST_CASE(test_raw_col_vector_3rt_default){
	auto const m = make_matrix< int >(1_C, 3_R_rt);

	auto const v = make_col_vector< int >(3_R_rt);


	BOOST_TEST(type_id_runtime(m) == type_id_runtime(v));


	auto type1 = type_id< raw_matrix< int, 1, 0 > >();
	BOOST_TEST(type_id_runtime(m) == type1);

	auto type2 = type_id< raw_col_vector< int, 0 > >();
	BOOST_TEST(type_id_runtime(m) == type2);


	BOOST_TEST(m.cols() == 1_C);
	BOOST_TEST(m.rows() == 3_R_rt);

	BOOST_TEST(m(0, 0) == 0);
	BOOST_TEST(m(0, 1) == 0);
	BOOST_TEST(m(0, 2) == 0);

	BOOST_TEST(m[0] == 0);
	BOOST_TEST(m[1] == 0);
	BOOST_TEST(m[2] == 0);

	BOOST_TEST(v.cols() == 1_C);
	BOOST_TEST(v.rows() == 3_R_rt);

	BOOST_TEST(v(0, 0) == 0);
	BOOST_TEST(v(0, 1) == 0);
	BOOST_TEST(v(0, 2) == 0);

	BOOST_TEST(v[0] == 0);
	BOOST_TEST(v[1] == 0);
	BOOST_TEST(v[2] == 0);
}


BOOST_AUTO_TEST_CASE(test_raw_row_vector_3rt_default){
	auto const m = make_matrix< int >(3_C_rt, 1_R);

	auto const v = make_row_vector< int >(3_C_rt);


	BOOST_TEST(type_id_runtime(m) == type_id_runtime(v));


	auto type1 = type_id< raw_matrix< int, 0, 1 > >();
	BOOST_TEST(type_id_runtime(m) == type1);

	auto type2 = type_id< raw_row_vector< int, 0 > >();
	BOOST_TEST(type_id_runtime(m) == type2);


	BOOST_TEST(m.cols() == 3_C_rt);
	BOOST_TEST(m.rows() == 1_R);

	BOOST_TEST(m(0, 0) == 0);
	BOOST_TEST(m(1, 0) == 0);
	BOOST_TEST(m(2, 0) == 0);

	BOOST_TEST(m[0] == 0);
	BOOST_TEST(m[1] == 0);
	BOOST_TEST(m[2] == 0);

	BOOST_TEST(v.cols() == 3_C_rt);
	BOOST_TEST(v.rows() == 1_R);

	BOOST_TEST(v(0, 0) == 0);
	BOOST_TEST(v(1, 0) == 0);
	BOOST_TEST(v(2, 0) == 0);

	BOOST_TEST(v[0] == 0);
	BOOST_TEST(v[1] == 0);
	BOOST_TEST(v[2] == 0);
}


BOOST_AUTO_TEST_CASE(test_raw_matrix_3x3_init7){
	constexpr auto m1 = make_matrix(3_C, 3_R, 7);

	constexpr auto m2 = make_square_matrix(3_D, 7);


	BOOST_TEST(type_id_runtime(m1) == type_id_runtime(m2));


	auto type1 = type_id< raw_matrix< int, 3, 3 > >();
	BOOST_TEST(type_id_runtime(m1) == type1);

	auto type2 = type_id< matrix< raw_matrix_impl< int, 3, 3 >, 3, 3 > >();
	BOOST_TEST(type_id_runtime(m1) == type2);


	BOOST_TEST(m1.cols() == 3_C);
	BOOST_TEST(m1.rows() == 3_R);

	BOOST_TEST(m1(0, 0) == 7);
	BOOST_TEST(m1(1, 0) == 7);
	BOOST_TEST(m1(2, 0) == 7);
	BOOST_TEST(m1(0, 1) == 7);
	BOOST_TEST(m1(1, 1) == 7);
	BOOST_TEST(m1(2, 1) == 7);
	BOOST_TEST(m1(0, 2) == 7);
	BOOST_TEST(m1(1, 2) == 7);
	BOOST_TEST(m1(2, 2) == 7);


	BOOST_TEST(m2.cols() == 3_C);
	BOOST_TEST(m2.rows() == 3_R);

	BOOST_TEST(m2(0, 0) == 7);
	BOOST_TEST(m2(1, 0) == 7);
	BOOST_TEST(m2(2, 0) == 7);
	BOOST_TEST(m2(0, 1) == 7);
	BOOST_TEST(m2(1, 1) == 7);
	BOOST_TEST(m2(2, 1) == 7);
	BOOST_TEST(m2(0, 2) == 7);
	BOOST_TEST(m2(1, 2) == 7);
	BOOST_TEST(m2(2, 2) == 7);
}


BOOST_AUTO_TEST_CASE(test_raw_matrix_2x3_init7){
	constexpr auto m = make_matrix(2_C, 3_R, 7);

	auto type1 = type_id< raw_matrix< int, 2, 3 > >();
	BOOST_TEST(type_id_runtime(m) == type1);

	auto type2 = type_id< matrix< raw_matrix_impl< int, 2, 3 >, 2, 3 > >();
	BOOST_TEST(type_id_runtime(m) == type2);


	BOOST_TEST(m.cols() == 2_C);
	BOOST_TEST(m.rows() == 3_R);

	BOOST_TEST(m(0, 0) == 7);
	BOOST_TEST(m(1, 0) == 7);
	BOOST_TEST(m(0, 1) == 7);
	BOOST_TEST(m(1, 1) == 7);
	BOOST_TEST(m(0, 2) == 7);
	BOOST_TEST(m(1, 2) == 7);
}


BOOST_AUTO_TEST_CASE(test_raw_matrix_3x2_init7){
	constexpr auto m = make_matrix(3_C, 2_R, 7);

	auto type1 = type_id< raw_matrix< int, 3, 2 > >();
	BOOST_TEST(type_id_runtime(m) == type1);

	auto type2 = type_id< matrix< raw_matrix_impl< int, 3, 2 >, 3, 2 > >();
	BOOST_TEST(type_id_runtime(m) == type2);


	BOOST_TEST(m.cols() == 3_C);
	BOOST_TEST(m.rows() == 2_R);

	BOOST_TEST(m(0, 0) == 7);
	BOOST_TEST(m(1, 0) == 7);
	BOOST_TEST(m(2, 0) == 7);
	BOOST_TEST(m(0, 1) == 7);
	BOOST_TEST(m(1, 1) == 7);
	BOOST_TEST(m(2, 1) == 7);
}


BOOST_AUTO_TEST_CASE(test_raw_col_vector_3_init7){
	constexpr auto m = make_matrix(1_C, 3_R, 7);

	constexpr auto v = make_col_vector< int >(3_R, 7);


	BOOST_TEST(type_id_runtime(m) == type_id_runtime(v));


	auto type1 = type_id< raw_matrix< int, 1, 3 > >();
	BOOST_TEST(type_id_runtime(m) == type1);

	auto type2 = type_id< raw_col_vector< int, 3 > >();
	BOOST_TEST(type_id_runtime(m) == type2);


	BOOST_TEST(m.cols() == 1_C);
	BOOST_TEST(m.rows() == 3_R);

	BOOST_TEST(m(0, 0) == 7);
	BOOST_TEST(m(0, 1) == 7);
	BOOST_TEST(m(0, 2) == 7);

	BOOST_TEST(m[0] == 7);
	BOOST_TEST(m[1] == 7);
	BOOST_TEST(m[2] == 7);

	BOOST_TEST(v.cols() == 1_C);
	BOOST_TEST(v.rows() == 3_R);

	BOOST_TEST(v(0, 0) == 7);
	BOOST_TEST(v(0, 1) == 7);
	BOOST_TEST(v(0, 2) == 7);

	BOOST_TEST(v[0] == 7);
	BOOST_TEST(v[1] == 7);
	BOOST_TEST(v[2] == 7);
}


BOOST_AUTO_TEST_CASE(test_raw_row_vector_3_init7){
	constexpr auto m = make_matrix(3_C, 1_R, 7);

	constexpr auto v = make_row_vector(3_C, 7);


	BOOST_TEST(type_id_runtime(m) == type_id_runtime(v));


	auto type1 = type_id< raw_matrix< int, 3, 1 > >();
	BOOST_TEST(type_id_runtime(m) == type1);

	auto type2 = type_id< raw_row_vector< int, 3 > >();
	BOOST_TEST(type_id_runtime(m) == type2);


	BOOST_TEST(m.cols() == 3_C);
	BOOST_TEST(m.rows() == 1_R);

	BOOST_TEST(m(0, 0) == 7);
	BOOST_TEST(m(1, 0) == 7);
	BOOST_TEST(m(2, 0) == 7);

	BOOST_TEST(m[0] == 7);
	BOOST_TEST(m[1] == 7);
	BOOST_TEST(m[2] == 7);

	BOOST_TEST(v.cols() == 3_C);
	BOOST_TEST(v.rows() == 1_R);

	BOOST_TEST(v(0, 0) == 7);
	BOOST_TEST(v(1, 0) == 7);
	BOOST_TEST(v(2, 0) == 7);

	BOOST_TEST(v[0] == 7);
	BOOST_TEST(v[1] == 7);
	BOOST_TEST(v[2] == 7);
}


BOOST_AUTO_TEST_CASE(test_raw_matrix_1x1_init7){
	constexpr auto m1 = make_matrix(1_C, 1_R, 7);
	constexpr auto m2 = make_square_matrix(1_D, 7);

	constexpr auto cv = make_col_vector(1_R, 7);
	constexpr auto rv = make_row_vector(1_C, 7);


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


	BOOST_TEST(m1(0, 0) == 7);
	BOOST_TEST(m2(0, 0) == 7);
	BOOST_TEST(cv(0, 0) == 7);
	BOOST_TEST(rv(0, 0) == 7);

	BOOST_TEST(m1[0] == 7);
	BOOST_TEST(m2[0] == 7);
	BOOST_TEST(cv[0] == 7);
	BOOST_TEST(rv[0] == 7);
}


BOOST_AUTO_TEST_CASE(test_raw_matrix_3rtx3rt_init7){
	auto const m1 = make_matrix(3_C_rt, 3_R_rt, 7);

	auto const m2 = make_square_matrix(3_D_rt, 7);


	BOOST_TEST(type_id_runtime(m1) == type_id_runtime(m2));


	auto type1 = type_id< raw_matrix< int, 0, 0 > >();
	BOOST_TEST(type_id_runtime(m1) == type1);

	auto type2 = type_id< matrix< raw_matrix_impl< int, 0, 0 >, 0, 0 > >();
	BOOST_TEST(type_id_runtime(m1) == type2);


	BOOST_TEST(m1.cols() == 3_C_rt);
	BOOST_TEST(m1.rows() == 3_R_rt);

	BOOST_TEST(m1(0, 0) == 7);
	BOOST_TEST(m1(1, 0) == 7);
	BOOST_TEST(m1(2, 0) == 7);
	BOOST_TEST(m1(0, 1) == 7);
	BOOST_TEST(m1(1, 1) == 7);
	BOOST_TEST(m1(2, 1) == 7);
	BOOST_TEST(m1(0, 2) == 7);
	BOOST_TEST(m1(1, 2) == 7);
	BOOST_TEST(m1(2, 2) == 7);


	BOOST_TEST(m2.cols() == 3_C_rt);
	BOOST_TEST(m2.rows() == 3_R_rt);

	BOOST_TEST(m2(0, 0) == 7);
	BOOST_TEST(m2(1, 0) == 7);
	BOOST_TEST(m2(2, 0) == 7);
	BOOST_TEST(m2(0, 1) == 7);
	BOOST_TEST(m2(1, 1) == 7);
	BOOST_TEST(m2(2, 1) == 7);
	BOOST_TEST(m2(0, 2) == 7);
	BOOST_TEST(m2(1, 2) == 7);
	BOOST_TEST(m2(2, 2) == 7);
}


BOOST_AUTO_TEST_CASE(test_raw_matrix_3rtx3_init7){
	auto const m = make_matrix(3_C_rt, 3_R, 7);


	auto type1 = type_id< raw_matrix< int, 0, 3 > >();
	BOOST_TEST(type_id_runtime(m) == type1);

	auto type2 = type_id< matrix< raw_matrix_impl< int, 0, 3 >, 0, 3 > >();
	BOOST_TEST(type_id_runtime(m) == type2);


	BOOST_TEST(m.cols() == 3_C_rt);
	BOOST_TEST(m.rows() == 3_R);

	BOOST_TEST(m(0, 0) == 7);
	BOOST_TEST(m(1, 0) == 7);
	BOOST_TEST(m(2, 0) == 7);
	BOOST_TEST(m(0, 1) == 7);
	BOOST_TEST(m(1, 1) == 7);
	BOOST_TEST(m(2, 1) == 7);
	BOOST_TEST(m(0, 2) == 7);
	BOOST_TEST(m(1, 2) == 7);
	BOOST_TEST(m(2, 2) == 7);
}


BOOST_AUTO_TEST_CASE(test_raw_matrix_3x3rt_init7){
	auto const m = make_matrix(3_C, 3_R_rt, 7);


	auto type1 = type_id< raw_matrix< int, 3, 0 > >();
	BOOST_TEST(type_id_runtime(m) == type1);

	auto type2 = type_id< matrix< raw_matrix_impl< int, 3, 0 >, 3, 0 > >();
	BOOST_TEST(type_id_runtime(m) == type2);


	BOOST_TEST(m.cols() == 3_C);
	BOOST_TEST(m.rows() == 3_R_rt);

	BOOST_TEST(m(0, 0) == 7);
	BOOST_TEST(m(1, 0) == 7);
	BOOST_TEST(m(2, 0) == 7);
	BOOST_TEST(m(0, 1) == 7);
	BOOST_TEST(m(1, 1) == 7);
	BOOST_TEST(m(2, 1) == 7);
	BOOST_TEST(m(0, 2) == 7);
	BOOST_TEST(m(1, 2) == 7);
	BOOST_TEST(m(2, 2) == 7);
}


BOOST_AUTO_TEST_CASE(test_raw_matrix_2rtx3_init7){
	auto const m = make_matrix(2_C_rt, 3_R, 7);

	auto type1 = type_id< raw_matrix< int, 0, 3 > >();
	BOOST_TEST(type_id_runtime(m) == type1);

	auto type2 = type_id< matrix< raw_matrix_impl< int, 0, 3 >, 0, 3 > >();
	BOOST_TEST(type_id_runtime(m) == type2);


	BOOST_TEST(m.cols() == 2_C_rt);
	BOOST_TEST(m.rows() == 3_R);

	BOOST_TEST(m(0, 0) == 7);
	BOOST_TEST(m(1, 0) == 7);
	BOOST_TEST(m(0, 1) == 7);
	BOOST_TEST(m(1, 1) == 7);
	BOOST_TEST(m(0, 2) == 7);
	BOOST_TEST(m(1, 2) == 7);
}


BOOST_AUTO_TEST_CASE(test_raw_matrix_3x2rt_init7){
	auto const m = make_matrix(3_C, 2_R_rt, 7);

	auto type1 = type_id< raw_matrix< int, 3, 0 > >();
	BOOST_TEST(type_id_runtime(m) == type1);

	auto type2 = type_id< matrix< raw_matrix_impl< int, 3, 0 >, 3, 0 > >();
	BOOST_TEST(type_id_runtime(m) == type2);


	BOOST_TEST(m.cols() == 3_C);
	BOOST_TEST(m.rows() == 2_R_rt);

	BOOST_TEST(m(0, 0) == 7);
	BOOST_TEST(m(1, 0) == 7);
	BOOST_TEST(m(2, 0) == 7);
	BOOST_TEST(m(0, 1) == 7);
	BOOST_TEST(m(1, 1) == 7);
	BOOST_TEST(m(2, 1) == 7);
}



BOOST_AUTO_TEST_CASE(test_raw_col_vector_3rt_init7){
	auto const m = make_matrix(1_C, 3_R_rt, 7);

	auto const v = make_col_vector(3_R_rt, 7);


	BOOST_TEST(type_id_runtime(m) == type_id_runtime(v));


	auto type1 = type_id< raw_matrix< int, 1, 0 > >();
	BOOST_TEST(type_id_runtime(m) == type1);

	auto type2 = type_id< raw_col_vector< int, 0 > >();
	BOOST_TEST(type_id_runtime(m) == type2);


	BOOST_TEST(m.cols() == 1_C);
	BOOST_TEST(m.rows() == 3_R_rt);

	BOOST_TEST(m(0, 0) == 7);
	BOOST_TEST(m(0, 1) == 7);
	BOOST_TEST(m(0, 2) == 7);

	BOOST_TEST(m[0] == 7);
	BOOST_TEST(m[1] == 7);
	BOOST_TEST(m[2] == 7);

	BOOST_TEST(v.cols() == 1_C);
	BOOST_TEST(v.rows() == 3_R_rt);

	BOOST_TEST(v(0, 0) == 7);
	BOOST_TEST(v(0, 1) == 7);
	BOOST_TEST(v(0, 2) == 7);

	BOOST_TEST(v[0] == 7);
	BOOST_TEST(v[1] == 7);
	BOOST_TEST(v[2] == 7);
}


BOOST_AUTO_TEST_CASE(test_raw_row_vector_3rt_init7){
	auto const m = make_matrix(3_C_rt, 1_R, 7);

	auto const v = make_row_vector(3_C_rt, 7);


	BOOST_TEST(type_id_runtime(m) == type_id_runtime(v));


	auto type1 = type_id< raw_matrix< int, 0, 1 > >();
	BOOST_TEST(type_id_runtime(m) == type1);

	auto type2 = type_id< raw_row_vector< int, 0 > >();
	BOOST_TEST(type_id_runtime(m) == type2);


	BOOST_TEST(m.cols() == 3_C_rt);
	BOOST_TEST(m.rows() == 1_R);

	BOOST_TEST(m(0, 0) == 7);
	BOOST_TEST(m(1, 0) == 7);
	BOOST_TEST(m(2, 0) == 7);

	BOOST_TEST(m[0] == 7);
	BOOST_TEST(m[1] == 7);
	BOOST_TEST(m[2] == 7);

	BOOST_TEST(v.cols() == 3_C_rt);
	BOOST_TEST(v.rows() == 1_R);

	BOOST_TEST(v(0, 0) == 7);
	BOOST_TEST(v(1, 0) == 7);
	BOOST_TEST(v(2, 0) == 7);

	BOOST_TEST(v[0] == 7);
	BOOST_TEST(v[1] == 7);
	BOOST_TEST(v[2] == 7);
}


BOOST_AUTO_TEST_SUITE_END()
