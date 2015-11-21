//-----------------------------------------------------------------------------
// Copyright (c) 2015 Benjamin Buch
//
// https://github.com/bebuch/mitrax
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt)
//-----------------------------------------------------------------------------
#include <boost/test/unit_test.hpp>

#include <mitrax/make_matrix.hpp>


using namespace mitrax;
using namespace mitrax::literals;


BOOST_AUTO_TEST_SUITE(test_suite_make_raw_matrix)


namespace{


	template < typename T >
	auto rt_id(T&& v){
		return boost::typeindex::type_id_runtime(static_cast< T&& >(v));
	}

	template < typename T >
	auto const id = boost::typeindex::type_id< T >();


	constexpr int ref_3x3[3][3] = {{0, 1, 2}, {3, 4, 5}, {6, 7, 8}};
	constexpr int ref_2x3[3][2] = {{0, 1}, {2, 3}, {4, 5}};
	constexpr int ref_3x2[2][3] = {{0, 1, 2}, {3, 4, 5}};
	constexpr int ref_1x3[3][1] = {{0}, {1}, {2}};
	constexpr int ref_3x1[1][3] = {{0, 1, 2}};
	constexpr int ref_1x1[1][1] = {{0}};

	constexpr int ref_3[3] = {0, 1, 2};
	constexpr int ref_1[1] = {0};

	template < typename M, size_t C, size_t R >
	constexpr bool check_3x3_0(matrix< M, C, R > const& m){
		return
			m.cols() == 3 &&
			m.rows() == 3 &&
			m(0, 0) == 0 &&
			m(1, 0) == 0 &&
			m(2, 0) == 0 &&
			m(0, 1) == 0 &&
			m(1, 1) == 0 &&
			m(2, 1) == 0 &&
			m(0, 2) == 0 &&
			m(1, 2) == 0 &&
			m(2, 2) == 0;
	}

	template < typename M, size_t C, size_t R >
	constexpr bool check_3x3_7(matrix< M, C, R > const& m){
		return
			m.cols() == 3 &&
			m.rows() == 3 &&
			m(0, 0) == 7 &&
			m(1, 0) == 7 &&
			m(2, 0) == 7 &&
			m(0, 1) == 7 &&
			m(1, 1) == 7 &&
			m(2, 1) == 7 &&
			m(0, 2) == 7 &&
			m(1, 2) == 7 &&
			m(2, 2) == 7;
	}

	template < typename M, size_t C, size_t R >
	constexpr bool check_3x3_ref(matrix< M, C, R > const& m){
		return
			m.cols() == 3 &&
			m.rows() == 3 &&
			m(0, 0) == 0 &&
			m(1, 0) == 1 &&
			m(2, 0) == 2 &&
			m(0, 1) == 3 &&
			m(1, 1) == 4 &&
			m(2, 1) == 5 &&
			m(0, 2) == 6 &&
			m(1, 2) == 7 &&
			m(2, 2) == 8;
	}

	template < typename M, size_t C, size_t R >
	constexpr bool check_2x3_0(matrix< M, C, R > const& m){
		return
			m.cols() == 2 &&
			m.rows() == 3 &&
			m(0, 0) == 0 &&
			m(1, 0) == 0 &&
			m(0, 1) == 0 &&
			m(1, 1) == 0 &&
			m(0, 2) == 0 &&
			m(1, 2) == 0;
	}

	template < typename M, size_t C, size_t R >
	constexpr bool check_2x3_7(matrix< M, C, R > const& m){
		return
			m.cols() == 2 &&
			m.rows() == 3 &&
			m(0, 0) == 7 &&
			m(1, 0) == 7 &&
			m(0, 1) == 7 &&
			m(1, 1) == 7 &&
			m(0, 2) == 7 &&
			m(1, 2) == 7;
	}

	template < typename M, size_t C, size_t R >
	constexpr bool check_2x3_ref(matrix< M, C, R > const& m){
		return
			m.cols() == 2 &&
			m.rows() == 3 &&
			m(0, 0) == 0 &&
			m(1, 0) == 1 &&
			m(0, 1) == 2 &&
			m(1, 1) == 3 &&
			m(0, 2) == 4 &&
			m(1, 2) == 5;
	}

	template < typename M, size_t C, size_t R >
	constexpr bool check_3x2_0(matrix< M, C, R > const& m){
		return
			m.cols() == 3 &&
			m.rows() == 2 &&
			m(0, 0) == 0 &&
			m(1, 0) == 0 &&
			m(2, 0) == 0 &&
			m(0, 1) == 0 &&
			m(1, 1) == 0 &&
			m(2, 1) == 0;
	}

	template < typename M, size_t C, size_t R >
	constexpr bool check_3x2_7(matrix< M, C, R > const& m){
		return
			m.cols() == 3 &&
			m.rows() == 2 &&
			m(0, 0) == 7 &&
			m(1, 0) == 7 &&
			m(2, 0) == 7 &&
			m(0, 1) == 7 &&
			m(1, 1) == 7 &&
			m(2, 1) == 7;
	}

	template < typename M, size_t C, size_t R >
	constexpr bool check_3x2_ref(matrix< M, C, R > const& m){
		return
			m.cols() == 3 &&
			m.rows() == 2 &&
			m(0, 0) == 0 &&
			m(1, 0) == 1 &&
			m(2, 0) == 2 &&
			m(0, 1) == 3 &&
			m(1, 1) == 4 &&
			m(2, 1) == 5;
	}

	template < typename M, size_t C, size_t R >
	constexpr bool check_1x3_0(matrix< M, C, R > const& m){
		return
			m.cols() == 1 &&
			m.rows() == 3 &&
			m(0, 0) == 0 &&
			m(0, 1) == 0 &&
			m(0, 2) == 0 &&
			m[0] == 0 &&
			m[1] == 0 &&
			m[2] == 0;
	}

	template < typename M, size_t C, size_t R >
	constexpr bool check_1x3_7(matrix< M, C, R > const& m){
		return
			m.cols() == 1 &&
			m.rows() == 3 &&
			m(0, 0) == 7 &&
			m(0, 1) == 7 &&
			m(0, 2) == 7 &&
			m[0] == 7 &&
			m[1] == 7 &&
			m[2] == 7;
	}

	template < typename M, size_t C, size_t R >
	constexpr bool check_1x3_ref(matrix< M, C, R > const& m){
		return
			m.cols() == 1 &&
			m.rows() == 3 &&
			m(0, 0) == 0 &&
			m(0, 1) == 1 &&
			m(0, 2) == 2 &&
			m[0] == 0 &&
			m[1] == 1 &&
			m[2] == 2;
	}

	template < typename M, size_t C, size_t R >
	constexpr bool check_3x1_0(matrix< M, C, R > const& m){
		return
			m.cols() == 3 &&
			m.rows() == 1 &&
			m(0, 0) == 0 &&
			m(1, 0) == 0 &&
			m(2, 0) == 0 &&
			m[0] == 0 &&
			m[1] == 0 &&
			m[2] == 0;
	}

	template < typename M, size_t C, size_t R >
	constexpr bool check_3x1_7(matrix< M, C, R > const& m){
		return
			m.cols() == 3 &&
			m.rows() == 1 &&
			m(0, 0) == 7 &&
			m(1, 0) == 7 &&
			m(2, 0) == 7 &&
			m[0] == 7 &&
			m[1] == 7 &&
			m[2] == 7;
	}

	template < typename M, size_t C, size_t R >
	constexpr bool check_3x1_ref(matrix< M, C, R > const& m){
		return
			m.cols() == 3 &&
			m.rows() == 1 &&
			m(0, 0) == 0 &&
			m(1, 0) == 1 &&
			m(2, 0) == 2 &&
			m[0] == 0 &&
			m[1] == 1 &&
			m[2] == 2;
	}

	template < typename M, size_t C, size_t R >
	constexpr bool check_1x1_0(matrix< M, C, R > const& m){
		return
			m.cols() == 1 &&
			m.rows() == 1 &&
			m(0, 0) == 0 &&
			m[0] == 0 &&
			m == 0;
	}

	template < typename M, size_t C, size_t R >
	constexpr bool check_1x1_7(matrix< M, C, R > const& m){
		return
			m.cols() == 1 &&
			m.rows() == 1 &&
			m(0, 0) == 7 &&
			m[0] == 7 &&
			m == 7;
	}


}


BOOST_AUTO_TEST_CASE(test_raw_matrix_types){
	BOOST_TEST((
		id< raw_matrix< int, 3, 4 > > ==
		id< matrix< raw_matrix_impl< int, 3, 4 >, 3, 4 > >
	));

	BOOST_TEST((
		id< raw_bitmap< int > > ==
		id< bitmap< raw_matrix_impl< int, 0, 0 > > >
	));

	BOOST_TEST((
		id< raw_col_vector< int, 4 > > ==
		id< col_vector< raw_matrix_impl< int, 1, 4 >, 4 > >
	));

	BOOST_TEST((
		id< raw_col_vector< int, 4 > > ==
		id< matrix< raw_matrix_impl< int, 1, 4 >, 1, 4 > >
	));

	BOOST_TEST((
		id< raw_row_vector< int, 4 > > ==
		id< row_vector< raw_matrix_impl< int, 4, 1 >, 4 > >
	));

	BOOST_TEST((
		id< raw_row_vector< int, 4 > > ==
		id< matrix< raw_matrix_impl< int, 4, 1 >, 4, 1 > >
	));

	BOOST_TEST((
		id< raw_square_matrix< int, 4 > > ==
		id< square_matrix< raw_matrix_impl< int, 4, 4 >, 4 > >
	));

	BOOST_TEST((
		id< raw_square_matrix< int, 4 > > ==
		id< matrix< raw_matrix_impl< int, 4, 4 >, 4, 4 > >
	));
}


BOOST_AUTO_TEST_CASE(test_raw_matrix_3x3){
	constexpr auto m01 = make_matrix< int >(3_C, 3_R);
	auto m02 = make_matrix< int >(3_C_rt, 3_R);
	auto m03 = make_matrix< int >(3_C, 3_R_rt);
	auto m04 = make_matrix< int >(3_C_rt, 3_R_rt);
	constexpr auto m05 = make_matrix< int >(dims(3_C, 3_R));
	auto m06 = make_matrix< int >(dims(3_C_rt, 3_R));
	auto m07 = make_matrix< int >(dims(3_C, 3_R_rt));
	auto m08 = make_matrix< int >(dims(3_C_rt, 3_R_rt));
	constexpr auto m09 = make_square_matrix< int >(3_D);
	auto m10 = make_square_matrix< int >(3_D_rt);
	constexpr auto m11 = make_matrix< int >(dims(3_D));
	auto m12 = make_matrix< int >(dims(3_D_rt));

	constexpr auto m13 = make_matrix(3_C, 3_R, 7);
	auto m14 = make_matrix(3_C_rt, 3_R, 7);
	auto m15 = make_matrix(3_C, 3_R_rt, 7);
	auto m16 = make_matrix(3_C_rt, 3_R_rt, 7);
	constexpr auto m17 = make_matrix(dims(3_C, 3_R), 7);
	auto m18 = make_matrix(dims(3_C_rt, 3_R), 7);
	auto m19 = make_matrix(dims(3_C, 3_R_rt), 7);
	auto m20 = make_matrix(dims(3_C_rt, 3_R_rt), 7);
	constexpr auto m21 = make_square_matrix(3_D, 7);
	auto m22 = make_square_matrix(3_D_rt, 7);
	constexpr auto m23 = make_matrix(dims(3_D), 7);
	auto m24 = make_matrix(dims(3_D_rt), 7);

	constexpr auto m25 =
		make_matrix< int >(3_C, 3_R, {{0, 1, 2}, {3, 4, 5}, {6, 7, 8}});
	auto m26 =
		make_matrix< int >(3_C_rt, 3_R, {{0, 1, 2}, {3, 4, 5}, {6, 7, 8}});
	auto m27 =
		make_matrix< int >(3_C, 3_R_rt, {{0, 1, 2}, {3, 4, 5}, {6, 7, 8}});
	auto m28 =
		make_matrix< int >(3_C_rt, 3_R_rt, {{0, 1, 2}, {3, 4, 5}, {6, 7, 8}});
	constexpr auto m29 = make_matrix(3_C, 3_R, ref_3x3);
	auto m30 = make_matrix(3_C_rt, 3_R, ref_3x3);
	auto m31 = make_matrix(3_C, 3_R_rt, ref_3x3);
	auto m32 = make_matrix(3_C_rt, 3_R_rt, ref_3x3);
	constexpr auto m33 =
		make_square_matrix< int >(3_D, {{0, 1, 2}, {3, 4, 5}, {6, 7, 8}});
	auto m34 =
		make_square_matrix< int >(3_D_rt, {{0, 1, 2}, {3, 4, 5}, {6, 7, 8}});
	constexpr auto m35 = make_square_matrix(3_D, ref_3x3);
	auto m36 = make_square_matrix(3_D_rt, ref_3x3);


	BOOST_TEST((rt_id(m01) == id< raw_matrix< int, 3, 3 > >));
	BOOST_TEST((rt_id(m02) == id< raw_matrix< int, 0, 3 > >));
	BOOST_TEST((rt_id(m03) == id< raw_matrix< int, 3, 0 > >));
	BOOST_TEST((rt_id(m04) == id< raw_matrix< int, 0, 0 > >));
	BOOST_TEST((rt_id(m05) == id< raw_matrix< int, 3, 3 > >));
	BOOST_TEST((rt_id(m06) == id< raw_matrix< int, 0, 3 > >));
	BOOST_TEST((rt_id(m07) == id< raw_matrix< int, 3, 0 > >));
	BOOST_TEST((rt_id(m08) == id< raw_matrix< int, 0, 0 > >));
	BOOST_TEST((rt_id(m09) == id< raw_matrix< int, 3, 3 > >));
	BOOST_TEST((rt_id(m10) == id< raw_matrix< int, 0, 0 > >));
	BOOST_TEST((rt_id(m11) == id< raw_matrix< int, 3, 3 > >));
	BOOST_TEST((rt_id(m12) == id< raw_matrix< int, 0, 0 > >));

	BOOST_TEST((rt_id(m13) == id< raw_matrix< int, 3, 3 > >));
	BOOST_TEST((rt_id(m14) == id< raw_matrix< int, 0, 3 > >));
	BOOST_TEST((rt_id(m15) == id< raw_matrix< int, 3, 0 > >));
	BOOST_TEST((rt_id(m16) == id< raw_matrix< int, 0, 0 > >));
	BOOST_TEST((rt_id(m17) == id< raw_matrix< int, 3, 3 > >));
	BOOST_TEST((rt_id(m18) == id< raw_matrix< int, 0, 3 > >));
	BOOST_TEST((rt_id(m19) == id< raw_matrix< int, 3, 0 > >));
	BOOST_TEST((rt_id(m20) == id< raw_matrix< int, 0, 0 > >));
	BOOST_TEST((rt_id(m21) == id< raw_matrix< int, 3, 3 > >));
	BOOST_TEST((rt_id(m22) == id< raw_matrix< int, 0, 0 > >));
	BOOST_TEST((rt_id(m23) == id< raw_matrix< int, 3, 3 > >));
	BOOST_TEST((rt_id(m24) == id< raw_matrix< int, 0, 0 > >));

	BOOST_TEST((rt_id(m25) == id< raw_matrix< int, 3, 3 > >));
	BOOST_TEST((rt_id(m26) == id< raw_matrix< int, 0, 3 > >));
	BOOST_TEST((rt_id(m27) == id< raw_matrix< int, 3, 0 > >));
	BOOST_TEST((rt_id(m28) == id< raw_matrix< int, 0, 0 > >));
	BOOST_TEST((rt_id(m29) == id< raw_matrix< int, 3, 3 > >));
	BOOST_TEST((rt_id(m30) == id< raw_matrix< int, 0, 3 > >));
	BOOST_TEST((rt_id(m31) == id< raw_matrix< int, 3, 0 > >));
	BOOST_TEST((rt_id(m32) == id< raw_matrix< int, 0, 0 > >));
	BOOST_TEST((rt_id(m33) == id< raw_matrix< int, 3, 3 > >));
	BOOST_TEST((rt_id(m34) == id< raw_matrix< int, 0, 0 > >));
	BOOST_TEST((rt_id(m35) == id< raw_matrix< int, 3, 3 > >));
	BOOST_TEST((rt_id(m36) == id< raw_matrix< int, 0, 0 > >));


	BOOST_TEST(check_3x3_0(m01));
	BOOST_TEST(check_3x3_0(m02));
	BOOST_TEST(check_3x3_0(m03));
	BOOST_TEST(check_3x3_0(m04));
	BOOST_TEST(check_3x3_0(m05));
	BOOST_TEST(check_3x3_0(m06));
	BOOST_TEST(check_3x3_0(m07));
	BOOST_TEST(check_3x3_0(m08));
	BOOST_TEST(check_3x3_0(m09));
	BOOST_TEST(check_3x3_0(m10));
	BOOST_TEST(check_3x3_0(m11));
	BOOST_TEST(check_3x3_0(m12));

	BOOST_TEST(check_3x3_7(m13));
	BOOST_TEST(check_3x3_7(m14));
	BOOST_TEST(check_3x3_7(m15));
	BOOST_TEST(check_3x3_7(m16));
	BOOST_TEST(check_3x3_7(m17));
	BOOST_TEST(check_3x3_7(m18));
	BOOST_TEST(check_3x3_7(m19));
	BOOST_TEST(check_3x3_7(m20));
	BOOST_TEST(check_3x3_7(m21));
	BOOST_TEST(check_3x3_7(m22));
	BOOST_TEST(check_3x3_7(m23));
	BOOST_TEST(check_3x3_7(m24));

	BOOST_TEST(check_3x3_ref(m25));
	BOOST_TEST(check_3x3_ref(m26));
	BOOST_TEST(check_3x3_ref(m27));
	BOOST_TEST(check_3x3_ref(m28));
	BOOST_TEST(check_3x3_ref(m29));
	BOOST_TEST(check_3x3_ref(m30));
	BOOST_TEST(check_3x3_ref(m31));
	BOOST_TEST(check_3x3_ref(m32));
	BOOST_TEST(check_3x3_ref(m33));
	BOOST_TEST(check_3x3_ref(m34));
	BOOST_TEST(check_3x3_ref(m35));
	BOOST_TEST(check_3x3_ref(m36));
}

BOOST_AUTO_TEST_CASE(test_raw_matrix_2x3){
	constexpr auto m01 = make_matrix< int >(2_C, 3_R);
	auto m02 = make_matrix< int >(2_C_rt, 3_R);
	auto m03 = make_matrix< int >(2_C, 3_R_rt);
	auto m04 = make_matrix< int >(2_C_rt, 3_R_rt);
	constexpr auto m05 = make_matrix< int >(dims(2_C, 3_R));
	auto m06 = make_matrix< int >(dims(2_C_rt, 3_R));
	auto m07 = make_matrix< int >(dims(2_C, 3_R_rt));
	auto m08 = make_matrix< int >(dims(2_C_rt, 3_R_rt));

	constexpr auto m09 = make_matrix(2_C, 3_R, 7);
	auto m10 = make_matrix(2_C_rt, 3_R, 7);
	auto m11 = make_matrix(2_C, 3_R_rt, 7);
	auto m12 = make_matrix(2_C_rt, 3_R_rt, 7);
	constexpr auto m13 = make_matrix(dims(2_C, 3_R), 7);
	auto m14 = make_matrix(dims(2_C_rt, 3_R), 7);
	auto m15 = make_matrix(dims(2_C, 3_R_rt), 7);
	auto m16 = make_matrix(dims(2_C_rt, 3_R_rt), 7);

	constexpr auto m17 =
		make_matrix< int >(2_C, 3_R, {{0, 1}, {2, 3}, {4, 5}});
	auto m18 = make_matrix< int >(2_C_rt, 3_R, {{0, 1}, {2, 3}, {4, 5}});
	auto m19 = make_matrix< int >(2_C, 3_R_rt, {{0, 1}, {2, 3}, {4, 5}});
	auto m20 = make_matrix< int >(2_C_rt, 3_R_rt, {{0, 1}, {2, 3}, {4, 5}});
	constexpr auto m21 = make_matrix(2_C, 3_R, ref_2x3);
	auto m22 = make_matrix(2_C_rt, 3_R, ref_2x3);
	auto m23 = make_matrix(2_C, 3_R_rt, ref_2x3);
	auto m24 = make_matrix(2_C_rt, 3_R_rt, ref_2x3);


	BOOST_TEST((rt_id(m01) == id< raw_matrix< int, 2, 3 > >));
	BOOST_TEST((rt_id(m02) == id< raw_matrix< int, 0, 3 > >));
	BOOST_TEST((rt_id(m03) == id< raw_matrix< int, 2, 0 > >));
	BOOST_TEST((rt_id(m04) == id< raw_matrix< int, 0, 0 > >));
	BOOST_TEST((rt_id(m05) == id< raw_matrix< int, 2, 3 > >));
	BOOST_TEST((rt_id(m06) == id< raw_matrix< int, 0, 3 > >));
	BOOST_TEST((rt_id(m07) == id< raw_matrix< int, 2, 0 > >));
	BOOST_TEST((rt_id(m08) == id< raw_matrix< int, 0, 0 > >));

	BOOST_TEST((rt_id(m09) == id< raw_matrix< int, 2, 3 > >));
	BOOST_TEST((rt_id(m10) == id< raw_matrix< int, 0, 3 > >));
	BOOST_TEST((rt_id(m11) == id< raw_matrix< int, 2, 0 > >));
	BOOST_TEST((rt_id(m12) == id< raw_matrix< int, 0, 0 > >));
	BOOST_TEST((rt_id(m13) == id< raw_matrix< int, 2, 3 > >));
	BOOST_TEST((rt_id(m14) == id< raw_matrix< int, 0, 3 > >));
	BOOST_TEST((rt_id(m15) == id< raw_matrix< int, 2, 0 > >));
	BOOST_TEST((rt_id(m16) == id< raw_matrix< int, 0, 0 > >));

	BOOST_TEST((rt_id(m17) == id< raw_matrix< int, 2, 3 > >));
	BOOST_TEST((rt_id(m18) == id< raw_matrix< int, 0, 3 > >));
	BOOST_TEST((rt_id(m19) == id< raw_matrix< int, 2, 0 > >));
	BOOST_TEST((rt_id(m20) == id< raw_matrix< int, 0, 0 > >));
	BOOST_TEST((rt_id(m21) == id< raw_matrix< int, 2, 3 > >));
	BOOST_TEST((rt_id(m22) == id< raw_matrix< int, 0, 3 > >));
	BOOST_TEST((rt_id(m23) == id< raw_matrix< int, 2, 0 > >));
	BOOST_TEST((rt_id(m24) == id< raw_matrix< int, 0, 0 > >));


	BOOST_TEST(check_2x3_0(m01));
	BOOST_TEST(check_2x3_0(m02));
	BOOST_TEST(check_2x3_0(m03));
	BOOST_TEST(check_2x3_0(m04));
	BOOST_TEST(check_2x3_0(m05));
	BOOST_TEST(check_2x3_0(m06));
	BOOST_TEST(check_2x3_0(m07));
	BOOST_TEST(check_2x3_0(m08));

	BOOST_TEST(check_2x3_7(m09));
	BOOST_TEST(check_2x3_7(m10));
	BOOST_TEST(check_2x3_7(m11));
	BOOST_TEST(check_2x3_7(m12));
	BOOST_TEST(check_2x3_7(m13));
	BOOST_TEST(check_2x3_7(m14));
	BOOST_TEST(check_2x3_7(m15));
	BOOST_TEST(check_2x3_7(m16));

	BOOST_TEST(check_2x3_ref(m17));
	BOOST_TEST(check_2x3_ref(m18));
	BOOST_TEST(check_2x3_ref(m19));
	BOOST_TEST(check_2x3_ref(m20));
	BOOST_TEST(check_2x3_ref(m21));
	BOOST_TEST(check_2x3_ref(m22));
	BOOST_TEST(check_2x3_ref(m23));
	BOOST_TEST(check_2x3_ref(m24));
}

BOOST_AUTO_TEST_CASE(test_raw_matrix_3x2){
	constexpr auto m01 = make_matrix< int >(3_C, 2_R);
	auto m02 = make_matrix< int >(3_C_rt, 2_R);
	auto m03 = make_matrix< int >(3_C, 2_R_rt);
	auto m04 = make_matrix< int >(3_C_rt, 2_R_rt);
	constexpr auto m05 = make_matrix< int >(dims(3_C, 2_R));
	auto m06 = make_matrix< int >(dims(3_C_rt, 2_R));
	auto m07 = make_matrix< int >(dims(3_C, 2_R_rt));
	auto m08 = make_matrix< int >(dims(3_C_rt, 2_R_rt));

	constexpr auto m09 = make_matrix(3_C, 2_R, 7);
	auto m10 = make_matrix(3_C_rt, 2_R, 7);
	auto m11 = make_matrix(3_C, 2_R_rt, 7);
	auto m12 = make_matrix(3_C_rt, 2_R_rt, 7);
	constexpr auto m13 = make_matrix(dims(3_C, 2_R), 7);
	auto m14 = make_matrix(dims(3_C_rt, 2_R), 7);
	auto m15 = make_matrix(dims(3_C, 2_R_rt), 7);
	auto m16 = make_matrix(dims(3_C_rt, 2_R_rt), 7);

	constexpr auto m17 = make_matrix< int >(3_C, 2_R, {{0, 1, 2}, {3, 4, 5}});
	auto m18 = make_matrix< int >(3_C_rt, 2_R, {{0, 1, 2}, {3, 4, 5}});
	auto m19 = make_matrix< int >(3_C, 2_R_rt, {{0, 1, 2}, {3, 4, 5}});
	auto m20 = make_matrix< int >(3_C_rt, 2_R_rt, {{0, 1, 2}, {3, 4, 5}});
	constexpr auto m21 = make_matrix(3_C, 2_R, ref_3x2);
	auto m22 = make_matrix(3_C_rt, 2_R, ref_3x2);
	auto m23 = make_matrix(3_C, 2_R_rt, ref_3x2);
	auto m24 = make_matrix(3_C_rt, 2_R_rt, ref_3x2);


	BOOST_TEST((rt_id(m01) == id< raw_matrix< int, 3, 2 > >));
	BOOST_TEST((rt_id(m02) == id< raw_matrix< int, 0, 2 > >));
	BOOST_TEST((rt_id(m03) == id< raw_matrix< int, 3, 0 > >));
	BOOST_TEST((rt_id(m04) == id< raw_matrix< int, 0, 0 > >));
	BOOST_TEST((rt_id(m05) == id< raw_matrix< int, 3, 2 > >));
	BOOST_TEST((rt_id(m06) == id< raw_matrix< int, 0, 2 > >));
	BOOST_TEST((rt_id(m07) == id< raw_matrix< int, 3, 0 > >));
	BOOST_TEST((rt_id(m08) == id< raw_matrix< int, 0, 0 > >));

	BOOST_TEST((rt_id(m09) == id< raw_matrix< int, 3, 2 > >));
	BOOST_TEST((rt_id(m10) == id< raw_matrix< int, 0, 2 > >));
	BOOST_TEST((rt_id(m11) == id< raw_matrix< int, 3, 0 > >));
	BOOST_TEST((rt_id(m12) == id< raw_matrix< int, 0, 0 > >));
	BOOST_TEST((rt_id(m13) == id< raw_matrix< int, 3, 2 > >));
	BOOST_TEST((rt_id(m14) == id< raw_matrix< int, 0, 2 > >));
	BOOST_TEST((rt_id(m15) == id< raw_matrix< int, 3, 0 > >));
	BOOST_TEST((rt_id(m16) == id< raw_matrix< int, 0, 0 > >));

	BOOST_TEST((rt_id(m17) == id< raw_matrix< int, 3, 2 > >));
	BOOST_TEST((rt_id(m18) == id< raw_matrix< int, 0, 2 > >));
	BOOST_TEST((rt_id(m19) == id< raw_matrix< int, 3, 0 > >));
	BOOST_TEST((rt_id(m20) == id< raw_matrix< int, 0, 0 > >));
	BOOST_TEST((rt_id(m21) == id< raw_matrix< int, 3, 2 > >));
	BOOST_TEST((rt_id(m22) == id< raw_matrix< int, 0, 2 > >));
	BOOST_TEST((rt_id(m23) == id< raw_matrix< int, 3, 0 > >));
	BOOST_TEST((rt_id(m24) == id< raw_matrix< int, 0, 0 > >));


	BOOST_TEST(check_3x2_0(m01));
	BOOST_TEST(check_3x2_0(m02));
	BOOST_TEST(check_3x2_0(m03));
	BOOST_TEST(check_3x2_0(m04));
	BOOST_TEST(check_3x2_0(m05));
	BOOST_TEST(check_3x2_0(m06));
	BOOST_TEST(check_3x2_0(m07));
	BOOST_TEST(check_3x2_0(m08));

	BOOST_TEST(check_3x2_7(m09));
	BOOST_TEST(check_3x2_7(m10));
	BOOST_TEST(check_3x2_7(m11));
	BOOST_TEST(check_3x2_7(m12));
	BOOST_TEST(check_3x2_7(m13));
	BOOST_TEST(check_3x2_7(m14));
	BOOST_TEST(check_3x2_7(m15));
	BOOST_TEST(check_3x2_7(m16));

	BOOST_TEST(check_3x2_ref(m17));
	BOOST_TEST(check_3x2_ref(m18));
	BOOST_TEST(check_3x2_ref(m19));
	BOOST_TEST(check_3x2_ref(m20));
	BOOST_TEST(check_3x2_ref(m21));
	BOOST_TEST(check_3x2_ref(m22));
	BOOST_TEST(check_3x2_ref(m23));
	BOOST_TEST(check_3x2_ref(m24));
}

BOOST_AUTO_TEST_CASE(test_raw_matrix_1x3){
	constexpr auto m01 = make_matrix< int >(1_C, 3_R);
	auto m02 = make_col_vector< int >(3_R);
	auto m03 = make_matrix< int >(1_C, 3_R_rt);
	auto m04 = make_col_vector< int >(3_R_rt);
	constexpr auto m05 = make_matrix< int >(dims(1_C, 3_R));
	auto m06 = make_matrix< int >(dims(1_C, 3_R_rt));

	constexpr auto m07 = make_matrix(1_C, 3_R, 7);
	auto m08 = make_col_vector(3_R, 7);
	auto m09 = make_matrix(1_C, 3_R_rt, 7);
	auto m10 = make_col_vector(3_R_rt, 7);
	constexpr auto m11 = make_matrix(dims(1_C, 3_R), 7);
	auto m12 = make_matrix(dims(1_C, 3_R_rt), 7);

	constexpr auto m13 = make_matrix< int >(1_C, 3_R, {{0}, {1}, {2}});
	auto m14 = make_col_vector< int >(3_R, {0, 1, 2});
	auto m15 = make_matrix< int >(1_C, 3_R_rt, {{0}, {1}, {2}});
	auto m16 = make_col_vector< int >(3_R_rt, {0, 1, 2});
	constexpr auto m17 = make_matrix(1_C, 3_R, ref_1x3);
	auto m18 = make_col_vector(3_R, ref_3);
	auto m19 = make_matrix(1_C, 3_R_rt, ref_1x3);
	auto m20 = make_col_vector(3_R_rt, ref_3);


	BOOST_TEST((rt_id(m01) == id< raw_matrix< int, 1, 3 > >));
	BOOST_TEST((rt_id(m02) == id< raw_matrix< int, 1, 3 > >));
	BOOST_TEST((rt_id(m03) == id< raw_matrix< int, 1, 0 > >));
	BOOST_TEST((rt_id(m04) == id< raw_matrix< int, 1, 0 > >));
	BOOST_TEST((rt_id(m05) == id< raw_matrix< int, 1, 3 > >));
	BOOST_TEST((rt_id(m06) == id< raw_matrix< int, 1, 0 > >));

	BOOST_TEST((rt_id(m07) == id< raw_matrix< int, 1, 3 > >));
	BOOST_TEST((rt_id(m08) == id< raw_matrix< int, 1, 3 > >));
	BOOST_TEST((rt_id(m09) == id< raw_matrix< int, 1, 0 > >));
	BOOST_TEST((rt_id(m10) == id< raw_matrix< int, 1, 0 > >));
	BOOST_TEST((rt_id(m11) == id< raw_matrix< int, 1, 3 > >));
	BOOST_TEST((rt_id(m12) == id< raw_matrix< int, 1, 0 > >));

	BOOST_TEST((rt_id(m13) == id< raw_matrix< int, 1, 3 > >));
	BOOST_TEST((rt_id(m14) == id< raw_matrix< int, 1, 3 > >));
	BOOST_TEST((rt_id(m15) == id< raw_matrix< int, 1, 0 > >));
	BOOST_TEST((rt_id(m16) == id< raw_matrix< int, 1, 0 > >));
	BOOST_TEST((rt_id(m17) == id< raw_matrix< int, 1, 3 > >));
	BOOST_TEST((rt_id(m18) == id< raw_matrix< int, 1, 3 > >));
	BOOST_TEST((rt_id(m19) == id< raw_matrix< int, 1, 0 > >));
	BOOST_TEST((rt_id(m20) == id< raw_matrix< int, 1, 0 > >));


	BOOST_TEST(check_1x3_0(m01));
	BOOST_TEST(check_1x3_0(m02));
	BOOST_TEST(check_1x3_0(m03));
	BOOST_TEST(check_1x3_0(m04));
	BOOST_TEST(check_1x3_0(m05));
	BOOST_TEST(check_1x3_0(m06));

	BOOST_TEST(check_1x3_7(m07));
	BOOST_TEST(check_1x3_7(m08));
	BOOST_TEST(check_1x3_7(m09));
	BOOST_TEST(check_1x3_7(m10));
	BOOST_TEST(check_1x3_7(m11));
	BOOST_TEST(check_1x3_7(m12));

	BOOST_TEST(check_1x3_ref(m13));
	BOOST_TEST(check_1x3_ref(m14));
	BOOST_TEST(check_1x3_ref(m15));
	BOOST_TEST(check_1x3_ref(m16));
	BOOST_TEST(check_1x3_ref(m17));
	BOOST_TEST(check_1x3_ref(m18));
	BOOST_TEST(check_1x3_ref(m19));
	BOOST_TEST(check_1x3_ref(m20));
}

BOOST_AUTO_TEST_CASE(test_raw_matrix_3x1){
	constexpr auto m01 = make_matrix< int >(3_C, 1_R);
	auto m02 = make_row_vector< int >(3_C);
	auto m03 = make_matrix< int >(3_C_rt, 1_R);
	auto m04 = make_row_vector< int >(3_C_rt);
	constexpr auto m05 = make_matrix< int >(dims(3_C, 1_R));
	auto m06 = make_matrix< int >(dims(3_C_rt, 1_R));

	constexpr auto m07 = make_matrix(3_C, 1_R, 7);
	auto m08 = make_row_vector(3_C, 7);
	auto m09 = make_matrix(3_C_rt, 1_R, 7);
	auto m10 = make_row_vector(3_C_rt, 7);
	constexpr auto m11 = make_matrix(dims(3_C, 1_R), 7);
	auto m12 = make_matrix(dims(3_C_rt, 1_R), 7);

	constexpr auto m13 = make_matrix< int >(3_C, 1_R, {{0, 1, 2}});
	auto m14 = make_row_vector< int >(3_C, {0, 1, 2});
	auto m15 = make_matrix< int >(3_C_rt, 1_R, {{0, 1, 2}});
	auto m16 = make_row_vector< int >(3_C_rt, {0, 1, 2});
	constexpr auto m17 = make_matrix(3_C, 1_R, ref_3x1);
	auto m18 = make_row_vector(3_C, ref_3);
	auto m19 = make_matrix(3_C_rt, 1_R, ref_3x1);
	auto m20 = make_row_vector(3_C_rt, ref_3);


	BOOST_TEST((rt_id(m01) == id< raw_matrix< int, 3, 1 > >));
	BOOST_TEST((rt_id(m02) == id< raw_matrix< int, 3, 1 > >));
	BOOST_TEST((rt_id(m03) == id< raw_matrix< int, 0, 1 > >));
	BOOST_TEST((rt_id(m04) == id< raw_matrix< int, 0, 1 > >));
	BOOST_TEST((rt_id(m05) == id< raw_matrix< int, 3, 1 > >));
	BOOST_TEST((rt_id(m06) == id< raw_matrix< int, 0, 1 > >));

	BOOST_TEST((rt_id(m07) == id< raw_matrix< int, 3, 1 > >));
	BOOST_TEST((rt_id(m08) == id< raw_matrix< int, 3, 1 > >));
	BOOST_TEST((rt_id(m09) == id< raw_matrix< int, 0, 1 > >));
	BOOST_TEST((rt_id(m10) == id< raw_matrix< int, 0, 1 > >));
	BOOST_TEST((rt_id(m11) == id< raw_matrix< int, 3, 1 > >));
	BOOST_TEST((rt_id(m12) == id< raw_matrix< int, 0, 1 > >));

	BOOST_TEST((rt_id(m13) == id< raw_matrix< int, 3, 1 > >));
	BOOST_TEST((rt_id(m14) == id< raw_matrix< int, 3, 1 > >));
	BOOST_TEST((rt_id(m15) == id< raw_matrix< int, 0, 1 > >));
	BOOST_TEST((rt_id(m16) == id< raw_matrix< int, 0, 1 > >));
	BOOST_TEST((rt_id(m17) == id< raw_matrix< int, 3, 1 > >));
	BOOST_TEST((rt_id(m18) == id< raw_matrix< int, 3, 1 > >));
	BOOST_TEST((rt_id(m19) == id< raw_matrix< int, 0, 1 > >));
	BOOST_TEST((rt_id(m20) == id< raw_matrix< int, 0, 1 > >));


	BOOST_TEST(check_3x1_0(m01));
	BOOST_TEST(check_3x1_0(m02));
	BOOST_TEST(check_3x1_0(m03));
	BOOST_TEST(check_3x1_0(m04));
	BOOST_TEST(check_3x1_0(m05));
	BOOST_TEST(check_3x1_0(m06));

	BOOST_TEST(check_3x1_7(m07));
	BOOST_TEST(check_3x1_7(m08));
	BOOST_TEST(check_3x1_7(m09));
	BOOST_TEST(check_3x1_7(m10));
	BOOST_TEST(check_3x1_7(m11));
	BOOST_TEST(check_3x1_7(m12));

	BOOST_TEST(check_3x1_ref(m13));
	BOOST_TEST(check_3x1_ref(m14));
	BOOST_TEST(check_3x1_ref(m15));
	BOOST_TEST(check_3x1_ref(m16));
	BOOST_TEST(check_3x1_ref(m17));
	BOOST_TEST(check_3x1_ref(m18));
	BOOST_TEST(check_3x1_ref(m19));
	BOOST_TEST(check_3x1_ref(m20));
}

BOOST_AUTO_TEST_CASE(test_raw_matrix_1x1){
	constexpr auto m01 = make_matrix< int >(1_C, 1_R);
	auto m02 = make_row_vector< int >(1_C);
	auto m03 = make_col_vector< int >(1_R);
	constexpr auto m04 = make_matrix< int >(dims(1_C, 1_R));
	constexpr auto m05 = make_square_matrix< int >(1_D);

	constexpr auto m06 = make_matrix(1_C, 1_R, 7);
	auto m07 = make_row_vector(1_C, 7);
	auto m08 = make_col_vector(1_R, 7);
	constexpr auto m09 = make_matrix(dims(1_C, 1_R), 7);
	constexpr auto m10 = make_square_matrix(1_D, 7);

	constexpr auto m11 = make_matrix< int >(1_C, 1_R, {{0}});
	auto m12 = make_row_vector< int >(1_C, {0});
	auto m13 = make_col_vector< int >(1_R, {0});
	constexpr auto m14 = make_square_matrix< int >(1_D, {{0}});
	constexpr auto m15 = make_matrix(1_C, 1_R, ref_1x1);
	auto m16 = make_row_vector(1_C, ref_1);
	auto m17 = make_col_vector(1_R, ref_1);
	constexpr auto m18 = make_square_matrix(1_D, ref_1x1);


	BOOST_TEST((rt_id(m01) == id< raw_matrix< int, 1, 1 > >));
	BOOST_TEST((rt_id(m02) == id< raw_matrix< int, 1, 1 > >));
	BOOST_TEST((rt_id(m03) == id< raw_matrix< int, 1, 1 > >));
	BOOST_TEST((rt_id(m04) == id< raw_matrix< int, 1, 1 > >));
	BOOST_TEST((rt_id(m05) == id< raw_matrix< int, 1, 1 > >));

	BOOST_TEST((rt_id(m06) == id< raw_matrix< int, 1, 1 > >));
	BOOST_TEST((rt_id(m07) == id< raw_matrix< int, 1, 1 > >));
	BOOST_TEST((rt_id(m08) == id< raw_matrix< int, 1, 1 > >));
	BOOST_TEST((rt_id(m09) == id< raw_matrix< int, 1, 1 > >));
	BOOST_TEST((rt_id(m10) == id< raw_matrix< int, 1, 1 > >));

	BOOST_TEST((rt_id(m11) == id< raw_matrix< int, 1, 1 > >));
	BOOST_TEST((rt_id(m12) == id< raw_matrix< int, 1, 1 > >));
	BOOST_TEST((rt_id(m13) == id< raw_matrix< int, 1, 1 > >));
	BOOST_TEST((rt_id(m14) == id< raw_matrix< int, 1, 1 > >));
	BOOST_TEST((rt_id(m15) == id< raw_matrix< int, 1, 1 > >));
	BOOST_TEST((rt_id(m16) == id< raw_matrix< int, 1, 1 > >));
	BOOST_TEST((rt_id(m17) == id< raw_matrix< int, 1, 1 > >));
	BOOST_TEST((rt_id(m18) == id< raw_matrix< int, 1, 1 > >));


	BOOST_TEST(check_1x1_0(m01));
	BOOST_TEST(check_1x1_0(m02));
	BOOST_TEST(check_1x1_0(m03));
	BOOST_TEST(check_1x1_0(m04));
	BOOST_TEST(check_1x1_0(m05));

	BOOST_TEST(check_1x1_7(m06));
	BOOST_TEST(check_1x1_7(m07));
	BOOST_TEST(check_1x1_7(m08));
	BOOST_TEST(check_1x1_7(m09));
	BOOST_TEST(check_1x1_7(m10));

	BOOST_TEST(check_1x1_0(m11));
	BOOST_TEST(check_1x1_0(m12));
	BOOST_TEST(check_1x1_0(m13));
	BOOST_TEST(check_1x1_0(m14));
	BOOST_TEST(check_1x1_0(m15));
	BOOST_TEST(check_1x1_0(m16));
	BOOST_TEST(check_1x1_0(m17));
	BOOST_TEST(check_1x1_0(m18));
}

BOOST_AUTO_TEST_CASE(test_raw_bitmap){
	auto m1 = make_bitmap< int >(2, 3);
	auto m2 = make_bitmap< int >(3, 2);
	auto m3 = make_bitmap< int >(dims(2, 3));
	auto m4 = make_bitmap< int >(dims(3, 2));
	auto m5 = make_bitmap(2, 3, 7);
	auto m6 = make_bitmap(3, 2, 7);
	auto m7 = make_bitmap(dims(2, 3), 7);
	auto m8 = make_bitmap(dims(3, 2), 7);

	BOOST_TEST((rt_id(m1) == id< raw_matrix< int, 0, 0 > >));
	BOOST_TEST((rt_id(m2) == id< raw_matrix< int, 0, 0 > >));
	BOOST_TEST((rt_id(m3) == id< raw_matrix< int, 0, 0 > >));
	BOOST_TEST((rt_id(m4) == id< raw_matrix< int, 0, 0 > >));
	BOOST_TEST((rt_id(m5) == id< raw_matrix< int, 0, 0 > >));
	BOOST_TEST((rt_id(m6) == id< raw_matrix< int, 0, 0 > >));
	BOOST_TEST((rt_id(m7) == id< raw_matrix< int, 0, 0 > >));
	BOOST_TEST((rt_id(m8) == id< raw_matrix< int, 0, 0 > >));

	BOOST_TEST(check_2x3_0(m1));
	BOOST_TEST(check_3x2_0(m2));
	BOOST_TEST(check_2x3_0(m3));
	BOOST_TEST(check_3x2_0(m4));
	BOOST_TEST(check_2x3_7(m5));
	BOOST_TEST(check_3x2_7(m6));
	BOOST_TEST(check_2x3_7(m7));
	BOOST_TEST(check_3x2_7(m8));
}


BOOST_AUTO_TEST_SUITE_END()
