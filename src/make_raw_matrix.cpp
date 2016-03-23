//-----------------------------------------------------------------------------
// Copyright (c) 2015-2016 Benjamin Buch
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
	constexpr bool check_3x3_func(matrix< M, C, R > const& m){
		return
			m.cols() == 3 &&
			m.rows() == 3 &&
			m(0, 0) == 0 &&
			m(1, 0) == 1 &&
			m(2, 0) == 2 &&
			m(0, 1) == 10 &&
			m(1, 1) == 11 &&
			m(2, 1) == 12 &&
			m(0, 2) == 20 &&
			m(1, 2) == 21 &&
			m(2, 2) == 22;
	}

	template < typename M, size_t C, size_t R >
	constexpr bool check_diag3_7(matrix< M, C, R > const& m){
		return
			m.cols() == 3 &&
			m.rows() == 3 &&
			m(0, 0) == 7 &&
			m(1, 0) == 0 &&
			m(2, 0) == 0 &&
			m(0, 1) == 0 &&
			m(1, 1) == 7 &&
			m(2, 1) == 0 &&
			m(0, 2) == 0 &&
			m(1, 2) == 0 &&
			m(2, 2) == 7;
	}

	template < typename M, size_t C, size_t R >
	constexpr bool check_identity3x3(matrix< M, C, R > const& m){
		return
			m.cols() == 3 &&
			m.rows() == 3 &&
			m(0, 0) == 1 &&
			m(1, 0) == 0 &&
			m(2, 0) == 0 &&
			m(0, 1) == 0 &&
			m(1, 1) == 1 &&
			m(2, 1) == 0 &&
			m(0, 2) == 0 &&
			m(1, 2) == 0 &&
			m(2, 2) == 1;
	}

	template < typename M, size_t C, size_t R >
	constexpr bool check_diag3_ref(matrix< M, C, R > const& m){
		return
			m.cols() == 3 &&
			m.rows() == 3 &&
			m(0, 0) == 0 &&
			m(1, 0) == 0 &&
			m(2, 0) == 0 &&
			m(0, 1) == 0 &&
			m(1, 1) == 1 &&
			m(2, 1) == 0 &&
			m(0, 2) == 0 &&
			m(1, 2) == 0 &&
			m(2, 2) == 2;
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
	constexpr bool check_2x3_func(matrix< M, C, R > const& m){
		return
			m.cols() == 2 &&
			m.rows() == 3 &&
			m(0, 0) == 0 &&
			m(1, 0) == 1 &&
			m(0, 1) == 10 &&
			m(1, 1) == 11 &&
			m(0, 2) == 20 &&
			m(1, 2) == 21;
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
	constexpr bool check_3x2_func(matrix< M, C, R > const& m){
		return
			m.cols() == 3 &&
			m.rows() == 2 &&
			m(0, 0) == 0 &&
			m(1, 0) == 1 &&
			m(2, 0) == 2 &&
			m(0, 1) == 10 &&
			m(1, 1) == 11 &&
			m(2, 1) == 12;
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
	constexpr bool check_1x3_func(matrix< M, C, R > const& m){
		return
			m.cols() == 1 &&
			m.rows() == 3 &&
			m(0, 0) == 0 &&
			m(0, 1) == 10 &&
			m(0, 2) == 20 &&
			m[0] == 0 &&
			m[1] == 10 &&
			m[2] == 20;
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
	constexpr bool check_3x1_func(matrix< M, C, R > const& m){
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


	struct f_cr{
		constexpr int operator()(size_t x, size_t y)const noexcept{
			return x + y * 10;
		}
	};

	struct f_c{
		constexpr int operator()(size_t i)const noexcept{
			return i * 10;
		}
	};

	struct f_r{
		constexpr int operator()(size_t i)const noexcept{
			return i;
		}
	};


}


BOOST_AUTO_TEST_CASE(test_raw_matrix_types){
	BOOST_TEST((
		id< raw_matrix< int, 3, 4 > > ==
		id< matrix< detail::raw_matrix_impl< int, 3, 4 >, 3, 4 > >
	));

	BOOST_TEST((
		id< raw_bitmap< int > > ==
		id< bitmap< detail::raw_matrix_impl< int, 0, 0 > > >
	));

	BOOST_TEST((
		id< raw_col_vector< int, 4 > > ==
		id< col_vector< detail::raw_matrix_impl< int, 1, 4 >, 4 > >
	));

	BOOST_TEST((
		id< raw_col_vector< int, 4 > > ==
		id< matrix< detail::raw_matrix_impl< int, 1, 4 >, 1, 4 > >
	));

	BOOST_TEST((
		id< raw_row_vector< int, 4 > > ==
		id< row_vector< detail::raw_matrix_impl< int, 4, 1 >, 4 > >
	));

	BOOST_TEST((
		id< raw_row_vector< int, 4 > > ==
		id< matrix< detail::raw_matrix_impl< int, 4, 1 >, 4, 1 > >
	));

	BOOST_TEST((
		id< raw_square_matrix< int, 4 > > ==
		id< square_matrix< detail::raw_matrix_impl< int, 4, 4 >, 4 > >
	));

	BOOST_TEST((
		id< raw_square_matrix< int, 4 > > ==
		id< matrix< detail::raw_matrix_impl< int, 4, 4 >, 4, 4 > >
	));
}


BOOST_AUTO_TEST_CASE(test_raw_matrix_3x3){
	constexpr auto m01 = make_matrix_by_default< int >(3_C, 3_R);
	auto m02 = make_matrix_by_default< int >(3_C_rt, 3_R);
	auto m03 = make_matrix_by_default< int >(3_C, 3_R_rt);
	auto m04 = make_matrix_by_default< int >(3_C_rt, 3_R_rt);
	constexpr auto m05 = make_matrix_by_default< int >(dims(3_C, 3_R));
	auto m06 = make_matrix_by_default< int >(dims(3_C_rt, 3_R));
	auto m07 = make_matrix_by_default< int >(dims(3_C, 3_R_rt));
	auto m08 = make_matrix_by_default< int >(dims(3_C_rt, 3_R_rt));
	constexpr auto m09 = make_square_matrix_by_default< int >(3_D);
	auto m10 = make_square_matrix_by_default< int >(3_D_rt);
	constexpr auto m11 = make_matrix_by_default< int >(dims(3_D));
	auto m12 = make_matrix_by_default< int >(dims(3_D_rt));

	constexpr auto m13 = make_matrix_by_default(3_C, 3_R, 7);
	auto m14 = make_matrix_by_default(3_C_rt, 3_R, 7);
	auto m15 = make_matrix_by_default(3_C, 3_R_rt, 7);
	auto m16 = make_matrix_by_default(3_C_rt, 3_R_rt, 7);
	constexpr auto m17 = make_matrix_by_default(dims(3_C, 3_R), 7);
	auto m18 = make_matrix_by_default(dims(3_C_rt, 3_R), 7);
	auto m19 = make_matrix_by_default(dims(3_C, 3_R_rt), 7);
	auto m20 = make_matrix_by_default(dims(3_C_rt, 3_R_rt), 7);
	constexpr auto m21 = make_square_matrix_by_default(3_D, 7);
	auto m22 = make_square_matrix_by_default(3_D_rt, 7);
	constexpr auto m23 = make_matrix_by_default(dims(3_D), 7);
	auto m24 = make_matrix_by_default(dims(3_D_rt), 7);

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

	constexpr auto m37 = make_matrix_by_function(3_C, 3_R, f_cr());
	auto m38 = make_matrix_by_function(3_C_rt, 3_R, f_cr());
	auto m39 = make_matrix_by_function(3_C, 3_R_rt, f_cr());
	auto m40 = make_matrix_by_function(3_C_rt, 3_R_rt, f_cr());
	constexpr auto m41 = make_matrix_by_function(dims(3_C, 3_R), f_cr());
	auto m42 = make_matrix_by_function(dims(3_C_rt, 3_R), f_cr());
	auto m43 = make_matrix_by_function(dims(3_C, 3_R_rt), f_cr());
	auto m44 = make_matrix_by_function(dims(3_C_rt, 3_R_rt), f_cr());
	constexpr auto m45 = make_square_matrix_by_function(3_D, f_cr());
	auto m46 = make_square_matrix_by_function(3_D_rt, f_cr());
	constexpr auto m47 = make_matrix_by_function(dims(3_D), f_cr());
	auto m48 = make_matrix_by_function(dims(3_D_rt), f_cr());


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

	BOOST_TEST((rt_id(m37) == id< raw_matrix< int, 3, 3 > >));
	BOOST_TEST((rt_id(m38) == id< raw_matrix< int, 0, 3 > >));
	BOOST_TEST((rt_id(m39) == id< raw_matrix< int, 3, 0 > >));
	BOOST_TEST((rt_id(m40) == id< raw_matrix< int, 0, 0 > >));
	BOOST_TEST((rt_id(m41) == id< raw_matrix< int, 3, 3 > >));
	BOOST_TEST((rt_id(m42) == id< raw_matrix< int, 0, 3 > >));
	BOOST_TEST((rt_id(m43) == id< raw_matrix< int, 3, 0 > >));
	BOOST_TEST((rt_id(m44) == id< raw_matrix< int, 0, 0 > >));
	BOOST_TEST((rt_id(m45) == id< raw_matrix< int, 3, 3 > >));
	BOOST_TEST((rt_id(m46) == id< raw_matrix< int, 0, 0 > >));
	BOOST_TEST((rt_id(m47) == id< raw_matrix< int, 3, 3 > >));
	BOOST_TEST((rt_id(m48) == id< raw_matrix< int, 0, 0 > >));


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

	BOOST_TEST(check_3x3_func(m37));
	BOOST_TEST(check_3x3_func(m38));
	BOOST_TEST(check_3x3_func(m39));
	BOOST_TEST(check_3x3_func(m40));
	BOOST_TEST(check_3x3_func(m41));
	BOOST_TEST(check_3x3_func(m42));
	BOOST_TEST(check_3x3_func(m43));
	BOOST_TEST(check_3x3_func(m44));
	BOOST_TEST(check_3x3_func(m45));
	BOOST_TEST(check_3x3_func(m46));
	BOOST_TEST(check_3x3_func(m47));
	BOOST_TEST(check_3x3_func(m48));
}

BOOST_AUTO_TEST_CASE(test_raw_matrix_2x3){
	constexpr auto m01 = make_matrix_by_default< int >(2_C, 3_R);
	auto m02 = make_matrix_by_default< int >(2_C_rt, 3_R);
	auto m03 = make_matrix_by_default< int >(2_C, 3_R_rt);
	auto m04 = make_matrix_by_default< int >(2_C_rt, 3_R_rt);
	constexpr auto m05 = make_matrix_by_default< int >(dims(2_C, 3_R));
	auto m06 = make_matrix_by_default< int >(dims(2_C_rt, 3_R));
	auto m07 = make_matrix_by_default< int >(dims(2_C, 3_R_rt));
	auto m08 = make_matrix_by_default< int >(dims(2_C_rt, 3_R_rt));

	constexpr auto m09 = make_matrix_by_default(2_C, 3_R, 7);
	auto m10 = make_matrix_by_default(2_C_rt, 3_R, 7);
	auto m11 = make_matrix_by_default(2_C, 3_R_rt, 7);
	auto m12 = make_matrix_by_default(2_C_rt, 3_R_rt, 7);
	constexpr auto m13 = make_matrix_by_default(dims(2_C, 3_R), 7);
	auto m14 = make_matrix_by_default(dims(2_C_rt, 3_R), 7);
	auto m15 = make_matrix_by_default(dims(2_C, 3_R_rt), 7);
	auto m16 = make_matrix_by_default(dims(2_C_rt, 3_R_rt), 7);

	constexpr auto m17 =
		make_matrix< int >(2_C, 3_R, {{0, 1}, {2, 3}, {4, 5}});
	auto m18 = make_matrix< int >(2_C_rt, 3_R, {{0, 1}, {2, 3}, {4, 5}});
	auto m19 = make_matrix< int >(2_C, 3_R_rt, {{0, 1}, {2, 3}, {4, 5}});
	auto m20 = make_matrix< int >(2_C_rt, 3_R_rt, {{0, 1}, {2, 3}, {4, 5}});
	constexpr auto m21 = make_matrix(2_C, 3_R, ref_2x3);
	auto m22 = make_matrix(2_C_rt, 3_R, ref_2x3);
	auto m23 = make_matrix(2_C, 3_R_rt, ref_2x3);
	auto m24 = make_matrix(2_C_rt, 3_R_rt, ref_2x3);

	constexpr auto m25 = make_matrix_by_function(2_C, 3_R, f_cr());
	auto m26 = make_matrix_by_function(2_C_rt, 3_R, f_cr());
	auto m27 = make_matrix_by_function(2_C, 3_R_rt, f_cr());
	auto m28 = make_matrix_by_function(2_C_rt, 3_R_rt, f_cr());
	constexpr auto m29 = make_matrix_by_function(dims(2_C, 3_R), f_cr());
	auto m30 = make_matrix_by_function(dims(2_C_rt, 3_R), f_cr());
	auto m31 = make_matrix_by_function(dims(2_C, 3_R_rt), f_cr());
	auto m32 = make_matrix_by_function(dims(2_C_rt, 3_R_rt), f_cr());


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

	BOOST_TEST((rt_id(m25) == id< raw_matrix< int, 2, 3 > >));
	BOOST_TEST((rt_id(m26) == id< raw_matrix< int, 0, 3 > >));
	BOOST_TEST((rt_id(m27) == id< raw_matrix< int, 2, 0 > >));
	BOOST_TEST((rt_id(m28) == id< raw_matrix< int, 0, 0 > >));
	BOOST_TEST((rt_id(m29) == id< raw_matrix< int, 2, 3 > >));
	BOOST_TEST((rt_id(m30) == id< raw_matrix< int, 0, 3 > >));
	BOOST_TEST((rt_id(m31) == id< raw_matrix< int, 2, 0 > >));
	BOOST_TEST((rt_id(m32) == id< raw_matrix< int, 0, 0 > >));


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

	BOOST_TEST(check_2x3_func(m25));
	BOOST_TEST(check_2x3_func(m26));
	BOOST_TEST(check_2x3_func(m27));
	BOOST_TEST(check_2x3_func(m28));
	BOOST_TEST(check_2x3_func(m29));
	BOOST_TEST(check_2x3_func(m30));
	BOOST_TEST(check_2x3_func(m31));
	BOOST_TEST(check_2x3_func(m32));
}

BOOST_AUTO_TEST_CASE(test_raw_matrix_3x2){
	constexpr auto m01 = make_matrix_by_default< int >(3_C, 2_R);
	auto m02 = make_matrix_by_default< int >(3_C_rt, 2_R);
	auto m03 = make_matrix_by_default< int >(3_C, 2_R_rt);
	auto m04 = make_matrix_by_default< int >(3_C_rt, 2_R_rt);
	constexpr auto m05 = make_matrix_by_default< int >(dims(3_C, 2_R));
	auto m06 = make_matrix_by_default< int >(dims(3_C_rt, 2_R));
	auto m07 = make_matrix_by_default< int >(dims(3_C, 2_R_rt));
	auto m08 = make_matrix_by_default< int >(dims(3_C_rt, 2_R_rt));

	constexpr auto m09 = make_matrix_by_default(3_C, 2_R, 7);
	auto m10 = make_matrix_by_default(3_C_rt, 2_R, 7);
	auto m11 = make_matrix_by_default(3_C, 2_R_rt, 7);
	auto m12 = make_matrix_by_default(3_C_rt, 2_R_rt, 7);
	constexpr auto m13 = make_matrix_by_default(dims(3_C, 2_R), 7);
	auto m14 = make_matrix_by_default(dims(3_C_rt, 2_R), 7);
	auto m15 = make_matrix_by_default(dims(3_C, 2_R_rt), 7);
	auto m16 = make_matrix_by_default(dims(3_C_rt, 2_R_rt), 7);

	constexpr auto m17 = make_matrix< int >(3_C, 2_R, {{0, 1, 2}, {3, 4, 5}});
	auto m18 = make_matrix< int >(3_C_rt, 2_R, {{0, 1, 2}, {3, 4, 5}});
	auto m19 = make_matrix< int >(3_C, 2_R_rt, {{0, 1, 2}, {3, 4, 5}});
	auto m20 = make_matrix< int >(3_C_rt, 2_R_rt, {{0, 1, 2}, {3, 4, 5}});
	constexpr auto m21 = make_matrix(3_C, 2_R, ref_3x2);
	auto m22 = make_matrix(3_C_rt, 2_R, ref_3x2);
	auto m23 = make_matrix(3_C, 2_R_rt, ref_3x2);
	auto m24 = make_matrix(3_C_rt, 2_R_rt, ref_3x2);

	constexpr auto m25 = make_matrix_by_function(3_C, 2_R, f_cr());
	auto m26 = make_matrix_by_function(3_C_rt, 2_R, f_cr());
	auto m27 = make_matrix_by_function(3_C, 2_R_rt, f_cr());
	auto m28 = make_matrix_by_function(3_C_rt, 2_R_rt, f_cr());
	constexpr auto m29 = make_matrix_by_function(dims(3_C, 2_R), f_cr());
	auto m30 = make_matrix_by_function(dims(3_C_rt, 2_R), f_cr());
	auto m31 = make_matrix_by_function(dims(3_C, 2_R_rt), f_cr());
	auto m32 = make_matrix_by_function(dims(3_C_rt, 2_R_rt), f_cr());


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

	BOOST_TEST((rt_id(m25) == id< raw_matrix< int, 3, 2 > >));
	BOOST_TEST((rt_id(m26) == id< raw_matrix< int, 0, 2 > >));
	BOOST_TEST((rt_id(m27) == id< raw_matrix< int, 3, 0 > >));
	BOOST_TEST((rt_id(m28) == id< raw_matrix< int, 0, 0 > >));
	BOOST_TEST((rt_id(m29) == id< raw_matrix< int, 3, 2 > >));
	BOOST_TEST((rt_id(m30) == id< raw_matrix< int, 0, 2 > >));
	BOOST_TEST((rt_id(m31) == id< raw_matrix< int, 3, 0 > >));
	BOOST_TEST((rt_id(m32) == id< raw_matrix< int, 0, 0 > >));


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

	BOOST_TEST(check_3x2_func(m25));
	BOOST_TEST(check_3x2_func(m26));
	BOOST_TEST(check_3x2_func(m27));
	BOOST_TEST(check_3x2_func(m28));
	BOOST_TEST(check_3x2_func(m29));
	BOOST_TEST(check_3x2_func(m30));
	BOOST_TEST(check_3x2_func(m31));
	BOOST_TEST(check_3x2_func(m32));
}

BOOST_AUTO_TEST_CASE(test_raw_matrix_1x3){
	constexpr auto m01 = make_matrix_by_default< int >(1_C, 3_R);
	auto m02 = make_col_vector_by_default< int >(3_R);
	auto m03 = make_matrix_by_default< int >(1_C, 3_R_rt);
	auto m04 = make_col_vector_by_default< int >(3_R_rt);
	constexpr auto m05 = make_matrix_by_default< int >(dims(1_C, 3_R));
	auto m06 = make_matrix_by_default< int >(dims(1_C, 3_R_rt));

	constexpr auto m07 = make_matrix_by_default(1_C, 3_R, 7);
	auto m08 = make_col_vector_by_default(3_R, 7);
	auto m09 = make_matrix_by_default(1_C, 3_R_rt, 7);
	auto m10 = make_col_vector_by_default(3_R_rt, 7);
	constexpr auto m11 = make_matrix_by_default(dims(1_C, 3_R), 7);
	auto m12 = make_matrix_by_default(dims(1_C, 3_R_rt), 7);

	constexpr auto m13 = make_matrix< int >(1_C, 3_R, {{0}, {1}, {2}});
	auto m14 = make_col_vector< int >(3_R, {0, 1, 2});
	auto m15 = make_matrix< int >(1_C, 3_R_rt, {{0}, {1}, {2}});
	auto m16 = make_col_vector< int >(3_R_rt, {0, 1, 2});
	constexpr auto m17 = make_matrix(1_C, 3_R, ref_1x3);
	auto m18 = make_col_vector(3_R, ref_3);
	auto m19 = make_matrix(1_C, 3_R_rt, ref_1x3);
	auto m20 = make_col_vector(3_R_rt, ref_3);

	constexpr auto m21 = make_matrix_by_function(1_C, 3_R, f_cr());
	auto m22 = make_col_vector_by_function(3_R, f_c());
	auto m23 = make_matrix_by_function(1_C, 3_R_rt, f_cr());
	auto m24 = make_col_vector_by_function(3_R_rt, f_c());
	constexpr auto m25 = make_matrix_by_function(dims(1_C, 3_R), f_cr());
	auto m26 = make_matrix_by_function(dims(1_C, 3_R_rt), f_cr());


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

	BOOST_TEST((rt_id(m21) == id< raw_matrix< int, 1, 3 > >));
	BOOST_TEST((rt_id(m22) == id< raw_matrix< int, 1, 3 > >));
	BOOST_TEST((rt_id(m23) == id< raw_matrix< int, 1, 0 > >));
	BOOST_TEST((rt_id(m24) == id< raw_matrix< int, 1, 0 > >));
	BOOST_TEST((rt_id(m25) == id< raw_matrix< int, 1, 3 > >));
	BOOST_TEST((rt_id(m26) == id< raw_matrix< int, 1, 0 > >));


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

	BOOST_TEST(check_1x3_func(m21));
	BOOST_TEST(check_1x3_func(m22));
	BOOST_TEST(check_1x3_func(m23));
	BOOST_TEST(check_1x3_func(m24));
	BOOST_TEST(check_1x3_func(m25));
	BOOST_TEST(check_1x3_func(m26));
}

BOOST_AUTO_TEST_CASE(test_raw_matrix_3x1){
	constexpr auto m01 = make_matrix_by_default< int >(3_C, 1_R);
	auto m02 = make_row_vector_by_default< int >(3_C);
	auto m03 = make_matrix_by_default< int >(3_C_rt, 1_R);
	auto m04 = make_row_vector_by_default< int >(3_C_rt);
	constexpr auto m05 = make_matrix_by_default< int >(dims(3_C, 1_R));
	auto m06 = make_matrix_by_default< int >(dims(3_C_rt, 1_R));

	constexpr auto m07 = make_matrix_by_default(3_C, 1_R, 7);
	auto m08 = make_row_vector_by_default(3_C, 7);
	auto m09 = make_matrix_by_default(3_C_rt, 1_R, 7);
	auto m10 = make_row_vector_by_default(3_C_rt, 7);
	constexpr auto m11 = make_matrix_by_default(dims(3_C, 1_R), 7);
	auto m12 = make_matrix_by_default(dims(3_C_rt, 1_R), 7);

	constexpr auto m13 = make_matrix< int >(3_C, 1_R, {{0, 1, 2}});
	auto m14 = make_row_vector< int >(3_C, {0, 1, 2});
	auto m15 = make_matrix< int >(3_C_rt, 1_R, {{0, 1, 2}});
	auto m16 = make_row_vector< int >(3_C_rt, {0, 1, 2});
	constexpr auto m17 = make_matrix(3_C, 1_R, ref_3x1);
	auto m18 = make_row_vector(3_C, ref_3);
	auto m19 = make_matrix(3_C_rt, 1_R, ref_3x1);
	auto m20 = make_row_vector(3_C_rt, ref_3);

	constexpr auto m21 = make_matrix_by_function(3_C, 1_R, f_cr());
	auto m22 = make_row_vector_by_function(3_C, f_r());
	auto m23 = make_matrix_by_function(3_C_rt, 1_R, f_cr());
	auto m24 = make_row_vector_by_function(3_C_rt, f_r());
	constexpr auto m25 = make_matrix_by_function(dims(3_C, 1_R), f_cr());
	auto m26 = make_matrix_by_function(dims(3_C_rt, 1_R), f_cr());


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

	BOOST_TEST((rt_id(m21) == id< raw_matrix< int, 3, 1 > >));
	BOOST_TEST((rt_id(m22) == id< raw_matrix< int, 3, 1 > >));
	BOOST_TEST((rt_id(m23) == id< raw_matrix< int, 0, 1 > >));
	BOOST_TEST((rt_id(m24) == id< raw_matrix< int, 0, 1 > >));
	BOOST_TEST((rt_id(m25) == id< raw_matrix< int, 3, 1 > >));
	BOOST_TEST((rt_id(m26) == id< raw_matrix< int, 0, 1 > >));


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

	BOOST_TEST(check_3x1_func(m21));
	BOOST_TEST(check_3x1_func(m22));
	BOOST_TEST(check_3x1_func(m23));
	BOOST_TEST(check_3x1_func(m24));
	BOOST_TEST(check_3x1_func(m25));
	BOOST_TEST(check_3x1_func(m26));
}

BOOST_AUTO_TEST_CASE(test_raw_matrix_1x1){
	constexpr auto m01 = make_matrix_by_default< int >(1_C, 1_R);
	auto m02 = make_row_vector_by_default< int >(1_C);
	auto m03 = make_col_vector_by_default< int >(1_R);
	constexpr auto m04 = make_matrix_by_default< int >(dims(1_C, 1_R));
	constexpr auto m05 = make_square_matrix_by_default< int >(1_D);

	constexpr auto m06 = make_matrix_by_default(1_C, 1_R, 7);
	auto m07 = make_row_vector_by_default(1_C, 7);
	auto m08 = make_col_vector_by_default(1_R, 7);
	constexpr auto m09 = make_matrix_by_default(dims(1_C, 1_R), 7);
	constexpr auto m10 = make_square_matrix_by_default(1_D, 7);

	constexpr auto m11 = make_matrix< int >(1_C, 1_R, {{0}});
	auto m12 = make_row_vector< int >(1_C, {0});
	auto m13 = make_col_vector< int >(1_R, {0});
	constexpr auto m14 = make_square_matrix< int >(1_D, {{0}});
	constexpr auto m15 = make_matrix(1_C, 1_R, ref_1x1);
	auto m16 = make_row_vector(1_C, ref_1);
	auto m17 = make_col_vector(1_R, ref_1);
	constexpr auto m18 = make_square_matrix(1_D, ref_1x1);

	constexpr auto m19 = make_matrix_by_function(1_C, 1_R, f_cr());
	auto m20 = make_row_vector_by_function(1_C, f_r());
	auto m21 = make_col_vector_by_function(1_R, f_c());
	constexpr auto m22 = make_matrix_by_function(dims(1_C, 1_R), f_cr());
	constexpr auto m23 = make_square_matrix_by_function(1_D, f_cr());


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

	BOOST_TEST((rt_id(m19) == id< raw_matrix< int, 1, 1 > >));
	BOOST_TEST((rt_id(m20) == id< raw_matrix< int, 1, 1 > >));
	BOOST_TEST((rt_id(m21) == id< raw_matrix< int, 1, 1 > >));
	BOOST_TEST((rt_id(m22) == id< raw_matrix< int, 1, 1 > >));
	BOOST_TEST((rt_id(m23) == id< raw_matrix< int, 1, 1 > >));


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

	BOOST_TEST(check_1x1_0(m19));
	BOOST_TEST(check_1x1_0(m20));
	BOOST_TEST(check_1x1_0(m21));
	BOOST_TEST(check_1x1_0(m22));
	BOOST_TEST(check_1x1_0(m23));
}

BOOST_AUTO_TEST_CASE(test_raw_bitmap){
	auto m01 = make_bitmap_by_default< int >(2, 3);
	auto m02 = make_bitmap_by_default< int >(3, 2);
	auto m03 = make_bitmap_by_default< int >(dims(2, 3));
	auto m04 = make_bitmap_by_default< int >(dims(3, 2));

	auto m05 = make_bitmap_by_default(2, 3, 7);
	auto m06 = make_bitmap_by_default(3, 2, 7);
	auto m07 = make_bitmap_by_default(dims(2, 3), 7);
	auto m08 = make_bitmap_by_default(dims(3, 2), 7);

	auto m09 = make_bitmap_by_function(2, 3, f_cr());
	auto m10 = make_bitmap_by_function(3, 2, f_cr());
	auto m11 = make_bitmap_by_function(dims(2, 3), f_cr());
	auto m12 = make_bitmap_by_function(dims(3, 2), f_cr());

	BOOST_TEST((rt_id(m01) == id< raw_matrix< int, 0, 0 > >));
	BOOST_TEST((rt_id(m02) == id< raw_matrix< int, 0, 0 > >));
	BOOST_TEST((rt_id(m03) == id< raw_matrix< int, 0, 0 > >));
	BOOST_TEST((rt_id(m04) == id< raw_matrix< int, 0, 0 > >));

	BOOST_TEST((rt_id(m05) == id< raw_matrix< int, 0, 0 > >));
	BOOST_TEST((rt_id(m06) == id< raw_matrix< int, 0, 0 > >));
	BOOST_TEST((rt_id(m07) == id< raw_matrix< int, 0, 0 > >));
	BOOST_TEST((rt_id(m08) == id< raw_matrix< int, 0, 0 > >));

	BOOST_TEST((rt_id(m09) == id< raw_matrix< int, 0, 0 > >));
	BOOST_TEST((rt_id(m10) == id< raw_matrix< int, 0, 0 > >));
	BOOST_TEST((rt_id(m11) == id< raw_matrix< int, 0, 0 > >));
	BOOST_TEST((rt_id(m12) == id< raw_matrix< int, 0, 0 > >));

	BOOST_TEST(check_2x3_0(m01));
	BOOST_TEST(check_3x2_0(m02));
	BOOST_TEST(check_2x3_0(m03));
	BOOST_TEST(check_3x2_0(m04));

	BOOST_TEST(check_2x3_7(m05));
	BOOST_TEST(check_3x2_7(m06));
	BOOST_TEST(check_2x3_7(m07));
	BOOST_TEST(check_3x2_7(m08));

	BOOST_TEST(check_2x3_func(m09));
	BOOST_TEST(check_3x2_func(m10));
	BOOST_TEST(check_2x3_func(m11));
	BOOST_TEST(check_3x2_func(m12));
}


BOOST_AUTO_TEST_CASE(test_diag_matrix){
	constexpr auto m01 = make_diag_matrix_by_default< int >(3_D);
	auto m02 = make_diag_matrix_by_default< int >(3_D_rt);

	constexpr auto m03 = make_diag_matrix_by_default(3_D, 7);
	auto m04 = make_diag_matrix_by_default(3_D_rt, 7);

	constexpr auto m05 = make_diag_matrix< int >(3_D, {0, 1, 2});
	auto m06 = make_diag_matrix< int >(3_D_rt, {0, 1, 2});
	constexpr auto m07 = make_diag_matrix(3_D, ref_3);
	auto m08 = make_diag_matrix(3_D_rt, ref_3);

	constexpr auto m09 = make_diag_matrix_by_function(3_D, f_r());
	auto m10 = make_diag_matrix_by_function(3_D_rt, f_r());


	BOOST_TEST((rt_id(m01) == id< raw_matrix< int, 3, 3 > >));
	BOOST_TEST((rt_id(m02) == id< raw_matrix< int, 0, 0 > >));
	BOOST_TEST((rt_id(m03) == id< raw_matrix< int, 3, 3 > >));
	BOOST_TEST((rt_id(m04) == id< raw_matrix< int, 0, 0 > >));
	BOOST_TEST((rt_id(m05) == id< raw_matrix< int, 3, 3 > >));
	BOOST_TEST((rt_id(m06) == id< raw_matrix< int, 0, 0 > >));
	BOOST_TEST((rt_id(m07) == id< raw_matrix< int, 3, 3 > >));
	BOOST_TEST((rt_id(m08) == id< raw_matrix< int, 0, 0 > >));
	BOOST_TEST((rt_id(m09) == id< raw_matrix< int, 3, 3 > >));
	BOOST_TEST((rt_id(m10) == id< raw_matrix< int, 0, 0 > >));


	BOOST_TEST(check_3x3_0(m01));
	BOOST_TEST(check_3x3_0(m02));
	BOOST_TEST(check_diag3_7(m03));
	BOOST_TEST(check_diag3_7(m04));
	BOOST_TEST(check_diag3_ref(m05));
	BOOST_TEST(check_diag3_ref(m06));
	BOOST_TEST(check_diag3_ref(m07));
	BOOST_TEST(check_diag3_ref(m08));
	BOOST_TEST(check_diag3_ref(m09));
	BOOST_TEST(check_diag3_ref(m10));
}


BOOST_AUTO_TEST_CASE(test_identity_matrix){
	constexpr auto m01 = make_identity_matrix< int >(3_D);
	auto m02 = make_identity_matrix< int >(3_D_rt);


	BOOST_TEST((rt_id(m01) == id< raw_matrix< int, 3, 3 > >));
	BOOST_TEST((rt_id(m02) == id< raw_matrix< int, 0, 0 > >));


	BOOST_TEST(check_identity3x3(m01));
	BOOST_TEST(check_identity3x3(m02));
}


BOOST_AUTO_TEST_CASE(test_copy_constructor){
	constexpr auto m01 = make_matrix(3_C, 3_R, ref_3x3);
	auto m02 = make_matrix(3_C_rt, 3_R_rt, ref_3x3);

	constexpr auto m03 = m01;
	auto m04 = m02;

	BOOST_TEST((rt_id(m03) == id< raw_matrix< int, 3, 3 > >));
	BOOST_TEST((rt_id(m04) == id< raw_matrix< int, 0, 0 > >));


	BOOST_TEST(check_3x3_ref(m03));
	BOOST_TEST(check_3x3_ref(m04));
}


BOOST_AUTO_TEST_CASE(test_move_constructor){
	constexpr auto m01 = make_matrix(3_C, 3_R, ref_3x3);
	auto m02 = make_matrix(3_C_rt, 3_R_rt, ref_3x3);

	constexpr auto m03 = std::move(m01);
	auto m04 = std::move(m02);

	BOOST_TEST((rt_id(m03) == id< raw_matrix< int, 3, 3 > >));
	BOOST_TEST((rt_id(m04) == id< raw_matrix< int, 0, 0 > >));


	BOOST_TEST(check_3x3_ref(m03));
	BOOST_TEST(check_3x3_ref(m04));
}


BOOST_AUTO_TEST_CASE(test_copy_assignment){
	constexpr auto m01 = make_matrix(3_C, 3_R, ref_3x3);
	auto m02 = make_matrix(3_C_rt, 3_R_rt, ref_3x3);

	auto m03 = make_matrix_by_default(3_C, 3_R, 0);
	auto m04 = make_matrix_by_default(0_C_rt, 0_R_rt, 0);


	m03 = m01;
	m04 = m02;


	BOOST_TEST((rt_id(m03) == id< raw_matrix< int, 3, 3 > >));
	BOOST_TEST((rt_id(m04) == id< raw_matrix< int, 0, 0 > >));


	BOOST_TEST(check_3x3_ref(m03));
	BOOST_TEST(check_3x3_ref(m04));
}


BOOST_AUTO_TEST_CASE(test_move_assignment){
	constexpr auto m01 = make_matrix(3_C, 3_R, ref_3x3);
	auto m02 = make_matrix(3_C_rt, 3_R_rt, ref_3x3);

	auto m03 = make_matrix_by_default(3_C, 3_R, 0);
	auto m04 = make_matrix_by_default(0_C_rt, 0_R_rt, 0);


	m03 = std::move(m01);
	m04 = std::move(m02);


	BOOST_TEST((rt_id(m03) == id< raw_matrix< int, 3, 3 > >));
	BOOST_TEST((rt_id(m04) == id< raw_matrix< int, 0, 0 > >));


	BOOST_TEST(check_3x3_ref(m03));
	BOOST_TEST(check_3x3_ref(m04));
}


BOOST_AUTO_TEST_SUITE_END()
