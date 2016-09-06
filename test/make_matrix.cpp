//-----------------------------------------------------------------------------
// Copyright (c) 2015-2016 Benjamin Buch
//
// https://github.com/bebuch/mitrax
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt)
//-----------------------------------------------------------------------------
#define BOOST_TEST_MODULE mitrax make_matrix
#include <boost/test/unit_test.hpp>

#include <mitrax/make_matrix.hpp>


using namespace mitrax;
using namespace mitrax::literals;


namespace{


	template < typename T >
	auto rt_id(T&& v){
		return boost::typeindex::type_id_runtime(static_cast< T&& >(v));
	}

	template < typename T >
	auto const id = boost::typeindex::type_id< T >();


	template < typename Matrix, size_t RefC, size_t RefR >
	constexpr bool check_fn(
		Matrix& m,
		value_type_t< Matrix > const(&ref)[RefR][RefC]
	){
		using value_type = value_type_t< Matrix >;

		bool res = true;
		res &= m.cols() == cols< RefC >();
		res &= m.rows() == rows< RefR >();

		for(size_t y = 0; y < RefR; ++y){
			for(size_t x = 0; x < RefC; ++x){
				res &= m(x, y) == ref[y][x];
			}
		}

		if constexpr(Matrix::ct_cols == 1 || Matrix::ct_rows == 1){
			auto vec_ref =
				reinterpret_cast< value_type const(&)[RefC * RefR] >(ref);

			for(size_t i = 0; i < RefC * RefR; ++i){
				res &= m[i] == vec_ref[i];
			}
		}

		if constexpr(Matrix::ct_cols == 1 && Matrix::ct_rows == 1){
			res &= static_cast< value_type >(m) == ref[0][0];
		}

		return res;
	}

	template < typename M, size_t C, size_t R, size_t RefC, size_t RefR >
	constexpr bool check(
		matrix< M, C, R >& m,
		value_type_t< M > const(&ref)[RefR][RefC]
	){
		auto const& m_const = m;
		return check_fn(m, ref) && check_fn(m_const, ref);
	}

	template < typename M, size_t C, size_t R, size_t RefC, size_t RefR >
	constexpr bool check(
		matrix< M, C, R > const& m,
		value_type_t< M > const(&ref)[RefR][RefC]
	){
		return check_fn(m, ref);
	}


	template < typename T >
	struct fn_xy_t{
		template < typename T1, typename T2 >
		constexpr T operator()(T1 x, T2 y)const noexcept{
			return x + y * 10;
		}
	};

	template < typename T >
	struct fn_x_t{
		template < typename T1 >
		constexpr T operator()(T1 i)const noexcept{
			return i * 10;
		}
	};

	template < typename T >
	struct fn_y_t{
		template < typename T1 >
		constexpr T operator()(T1 i)const noexcept{
			return i;
		}
	};

	template < typename T >
	struct fn_i_t{
		template < typename T1 >
		constexpr T operator()(T1 i)const noexcept{
			return i + i * 10;
		}
	};


}


BOOST_AUTO_TEST_SUITE(suite_make_matrix)


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
	constexpr int ref_0[3][3] = {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}};
	constexpr int ref_v[3][3] = {{7, 7, 7}, {7, 7, 7}, {7, 7, 7}};
	constexpr int ref_i[3][3] = {{0, 1, 2}, {3, 4, 5}, {6, 7, 8}};
	constexpr int ref_f[3][3] = {{0, 1, 2}, {10, 11, 12}, {20, 21, 22}};
	constexpr auto fn = fn_xy_t< int >();

	constexpr auto m01 = make_matrix_v< int >(3_C, 3_R);
	auto m02 = make_matrix_v< int >(3_C_rt, 3_R);
	auto m03 = make_matrix_v< int >(3_C, 3_R_rt);
	auto m04 = make_matrix_v< int >(3_C_rt, 3_R_rt);
	constexpr auto m05 = make_matrix_v< int >(dims(3_C, 3_R));
	auto m06 = make_matrix_v< int >(dims(3_C_rt, 3_R));
	auto m07 = make_matrix_v< int >(dims(3_C, 3_R_rt));
	auto m08 = make_matrix_v< int >(dims(3_C_rt, 3_R_rt));
	constexpr auto m09 = make_square_matrix_v< int >(3_D);
	auto m10 = make_square_matrix_v< int >(3_D_rt);
	constexpr auto m11 = make_matrix_v< int >(dims(3_D));
	auto m12 = make_matrix_v< int >(dims(3_D_rt));

	constexpr auto m13 = make_matrix_v(3_C, 3_R, 7);
	auto m14 = make_matrix_v(3_C_rt, 3_R, 7);
	auto m15 = make_matrix_v(3_C, 3_R_rt, 7);
	auto m16 = make_matrix_v(3_C_rt, 3_R_rt, 7);
	constexpr auto m17 = make_matrix_v(dims(3_C, 3_R), 7);
	auto m18 = make_matrix_v(dims(3_C_rt, 3_R), 7);
	auto m19 = make_matrix_v(dims(3_C, 3_R_rt), 7);
	auto m20 = make_matrix_v(dims(3_C_rt, 3_R_rt), 7);
	constexpr auto m21 = make_square_matrix_v(3_D, 7);
	auto m22 = make_square_matrix_v(3_D_rt, 7);
	constexpr auto m23 = make_matrix_v(dims(3_D), 7);
	auto m24 = make_matrix_v(dims(3_D_rt), 7);

	constexpr auto m25 =
		make_matrix< int >(3_C, 3_R, {{0, 1, 2}, {3, 4, 5}, {6, 7, 8}});
	auto m26 =
		make_matrix< int >(3_C_rt, 3_R, {{0, 1, 2}, {3, 4, 5}, {6, 7, 8}});
	auto m27 =
		make_matrix< int >(3_C, 3_R_rt, {{0, 1, 2}, {3, 4, 5}, {6, 7, 8}});
	auto m28 =
		make_matrix< int >(3_C_rt, 3_R_rt, {{0, 1, 2}, {3, 4, 5}, {6, 7, 8}});
	constexpr auto m29 = make_matrix(3_C, 3_R, ref_i);
	auto m30 = make_matrix(3_C_rt, 3_R, ref_i);
	auto m31 = make_matrix(3_C, 3_R_rt, ref_i);
	auto m32 = make_matrix(3_C_rt, 3_R_rt, ref_i);
	constexpr auto m33 =
		make_square_matrix< int >(3_D, {{0, 1, 2}, {3, 4, 5}, {6, 7, 8}});
	auto m34 =
		make_square_matrix< int >(3_D_rt, {{0, 1, 2}, {3, 4, 5}, {6, 7, 8}});
	constexpr auto m35 = make_square_matrix(3_D, ref_i);
	auto m36 = make_square_matrix(3_D_rt, ref_i);

	constexpr auto m37 = make_matrix_fn(3_C, 3_R, fn);
	auto m38 = make_matrix_fn(3_C_rt, 3_R, fn);
	auto m39 = make_matrix_fn(3_C, 3_R_rt, fn);
	auto m40 = make_matrix_fn(3_C_rt, 3_R_rt, fn);
	constexpr auto m41 = make_matrix_fn(dims(3_C, 3_R), fn);
	auto m42 = make_matrix_fn(dims(3_C_rt, 3_R), fn);
	auto m43 = make_matrix_fn(dims(3_C, 3_R_rt), fn);
	auto m44 = make_matrix_fn(dims(3_C_rt, 3_R_rt), fn);
	constexpr auto m45 = make_square_matrix_fn(3_D, fn);
	auto m46 = make_square_matrix_fn(3_D_rt, fn);
	constexpr auto m47 = make_matrix_fn(dims(3_D), fn);
	auto m48 = make_matrix_fn(dims(3_D_rt), fn);


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


	BOOST_TEST((check(m01, ref_0)));
	BOOST_TEST((check(m02, ref_0)));
	BOOST_TEST((check(m03, ref_0)));
	BOOST_TEST((check(m04, ref_0)));
	BOOST_TEST((check(m05, ref_0)));
	BOOST_TEST((check(m06, ref_0)));
	BOOST_TEST((check(m07, ref_0)));
	BOOST_TEST((check(m08, ref_0)));
	BOOST_TEST((check(m09, ref_0)));
	BOOST_TEST((check(m10, ref_0)));
	BOOST_TEST((check(m11, ref_0)));
	BOOST_TEST((check(m12, ref_0)));

	BOOST_TEST((check(m13, ref_v)));
	BOOST_TEST((check(m14, ref_v)));
	BOOST_TEST((check(m15, ref_v)));
	BOOST_TEST((check(m16, ref_v)));
	BOOST_TEST((check(m17, ref_v)));
	BOOST_TEST((check(m18, ref_v)));
	BOOST_TEST((check(m19, ref_v)));
	BOOST_TEST((check(m20, ref_v)));
	BOOST_TEST((check(m21, ref_v)));
	BOOST_TEST((check(m22, ref_v)));
	BOOST_TEST((check(m23, ref_v)));
	BOOST_TEST((check(m24, ref_v)));

	BOOST_TEST((check(m25, ref_i)));
	BOOST_TEST((check(m26, ref_i)));
	BOOST_TEST((check(m27, ref_i)));
	BOOST_TEST((check(m28, ref_i)));
	BOOST_TEST((check(m29, ref_i)));
	BOOST_TEST((check(m30, ref_i)));
	BOOST_TEST((check(m31, ref_i)));
	BOOST_TEST((check(m32, ref_i)));
	BOOST_TEST((check(m33, ref_i)));
	BOOST_TEST((check(m34, ref_i)));
	BOOST_TEST((check(m35, ref_i)));
	BOOST_TEST((check(m36, ref_i)));

	BOOST_TEST((check(m37, ref_f)));
	BOOST_TEST((check(m38, ref_f)));
	BOOST_TEST((check(m39, ref_f)));
	BOOST_TEST((check(m40, ref_f)));
	BOOST_TEST((check(m41, ref_f)));
	BOOST_TEST((check(m42, ref_f)));
	BOOST_TEST((check(m43, ref_f)));
	BOOST_TEST((check(m44, ref_f)));
	BOOST_TEST((check(m45, ref_f)));
	BOOST_TEST((check(m46, ref_f)));
	BOOST_TEST((check(m47, ref_f)));
	BOOST_TEST((check(m48, ref_f)));
}


BOOST_AUTO_TEST_CASE(test_raw_matrix_2x3){
	constexpr int ref_0[3][2] = {{0, 0}, {0, 0}, {0, 0}};
	constexpr int ref_v[3][2] = {{7, 7}, {7, 7}, {7, 7}};
	constexpr int ref_i[3][2] = {{0, 1}, {2, 3}, {4, 5}};
	constexpr int ref_f[3][2] = {{0, 1}, {10, 11}, {20, 21}};
	constexpr auto fn = fn_xy_t< int >();

	constexpr auto m01 = make_matrix_v< int >(2_C, 3_R);
	auto m02 = make_matrix_v< int >(2_C_rt, 3_R);
	auto m03 = make_matrix_v< int >(2_C, 3_R_rt);
	auto m04 = make_matrix_v< int >(2_C_rt, 3_R_rt);
	constexpr auto m05 = make_matrix_v< int >(dims(2_C, 3_R));
	auto m06 = make_matrix_v< int >(dims(2_C_rt, 3_R));
	auto m07 = make_matrix_v< int >(dims(2_C, 3_R_rt));
	auto m08 = make_matrix_v< int >(dims(2_C_rt, 3_R_rt));

	constexpr auto m09 = make_matrix_v(2_C, 3_R, 7);
	auto m10 = make_matrix_v(2_C_rt, 3_R, 7);
	auto m11 = make_matrix_v(2_C, 3_R_rt, 7);
	auto m12 = make_matrix_v(2_C_rt, 3_R_rt, 7);
	constexpr auto m13 = make_matrix_v(dims(2_C, 3_R), 7);
	auto m14 = make_matrix_v(dims(2_C_rt, 3_R), 7);
	auto m15 = make_matrix_v(dims(2_C, 3_R_rt), 7);
	auto m16 = make_matrix_v(dims(2_C_rt, 3_R_rt), 7);

	constexpr auto m17 =
		make_matrix< int >(2_C, 3_R, {{0, 1}, {2, 3}, {4, 5}});
	auto m18 = make_matrix< int >(2_C_rt, 3_R, {{0, 1}, {2, 3}, {4, 5}});
	auto m19 = make_matrix< int >(2_C, 3_R_rt, {{0, 1}, {2, 3}, {4, 5}});
	auto m20 = make_matrix< int >(2_C_rt, 3_R_rt, {{0, 1}, {2, 3}, {4, 5}});
	constexpr auto m21 = make_matrix(2_C, 3_R, ref_i);
	auto m22 = make_matrix(2_C_rt, 3_R, ref_i);
	auto m23 = make_matrix(2_C, 3_R_rt, ref_i);
	auto m24 = make_matrix(2_C_rt, 3_R_rt, ref_i);

	constexpr auto m25 = make_matrix_fn(2_C, 3_R, fn);
	auto m26 = make_matrix_fn(2_C_rt, 3_R, fn);
	auto m27 = make_matrix_fn(2_C, 3_R_rt, fn);
	auto m28 = make_matrix_fn(2_C_rt, 3_R_rt, fn);
	constexpr auto m29 = make_matrix_fn(dims(2_C, 3_R), fn);
	auto m30 = make_matrix_fn(dims(2_C_rt, 3_R), fn);
	auto m31 = make_matrix_fn(dims(2_C, 3_R_rt), fn);
	auto m32 = make_matrix_fn(dims(2_C_rt, 3_R_rt), fn);


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


	BOOST_TEST(check(m01, ref_0));
	BOOST_TEST(check(m02, ref_0));
	BOOST_TEST(check(m03, ref_0));
	BOOST_TEST(check(m04, ref_0));
	BOOST_TEST(check(m05, ref_0));
	BOOST_TEST(check(m06, ref_0));
	BOOST_TEST(check(m07, ref_0));
	BOOST_TEST(check(m08, ref_0));

	BOOST_TEST(check(m09, ref_v));
	BOOST_TEST(check(m10, ref_v));
	BOOST_TEST(check(m11, ref_v));
	BOOST_TEST(check(m12, ref_v));
	BOOST_TEST(check(m13, ref_v));
	BOOST_TEST(check(m14, ref_v));
	BOOST_TEST(check(m15, ref_v));
	BOOST_TEST(check(m16, ref_v));

	BOOST_TEST(check(m17, ref_i));
	BOOST_TEST(check(m18, ref_i));
	BOOST_TEST(check(m19, ref_i));
	BOOST_TEST(check(m20, ref_i));
	BOOST_TEST(check(m21, ref_i));
	BOOST_TEST(check(m22, ref_i));
	BOOST_TEST(check(m23, ref_i));
	BOOST_TEST(check(m24, ref_i));

	BOOST_TEST(check(m25, ref_f));
	BOOST_TEST(check(m26, ref_f));
	BOOST_TEST(check(m27, ref_f));
	BOOST_TEST(check(m28, ref_f));
	BOOST_TEST(check(m29, ref_f));
	BOOST_TEST(check(m30, ref_f));
	BOOST_TEST(check(m31, ref_f));
	BOOST_TEST(check(m32, ref_f));
}

BOOST_AUTO_TEST_CASE(test_raw_matrix_3x2){
	constexpr int ref_0[2][3] = {{0, 0, 0}, {0, 0, 0}};
	constexpr int ref_v[2][3] = {{7, 7, 7}, {7, 7, 7}};
	constexpr int ref_i[2][3] = {{0, 1, 2}, {3, 4, 5}};
	constexpr int ref_f[2][3] = {{0, 1, 2}, {10, 11, 12}};
	constexpr auto fn = fn_xy_t< int >();

	constexpr auto m01 = make_matrix_v< int >(3_C, 2_R);
	auto m02 = make_matrix_v< int >(3_C_rt, 2_R);
	auto m03 = make_matrix_v< int >(3_C, 2_R_rt);
	auto m04 = make_matrix_v< int >(3_C_rt, 2_R_rt);
	constexpr auto m05 = make_matrix_v< int >(dims(3_C, 2_R));
	auto m06 = make_matrix_v< int >(dims(3_C_rt, 2_R));
	auto m07 = make_matrix_v< int >(dims(3_C, 2_R_rt));
	auto m08 = make_matrix_v< int >(dims(3_C_rt, 2_R_rt));

	constexpr auto m09 = make_matrix_v(3_C, 2_R, 7);
	auto m10 = make_matrix_v(3_C_rt, 2_R, 7);
	auto m11 = make_matrix_v(3_C, 2_R_rt, 7);
	auto m12 = make_matrix_v(3_C_rt, 2_R_rt, 7);
	constexpr auto m13 = make_matrix_v(dims(3_C, 2_R), 7);
	auto m14 = make_matrix_v(dims(3_C_rt, 2_R), 7);
	auto m15 = make_matrix_v(dims(3_C, 2_R_rt), 7);
	auto m16 = make_matrix_v(dims(3_C_rt, 2_R_rt), 7);

	constexpr auto m17 = make_matrix< int >(3_C, 2_R, {{0, 1, 2}, {3, 4, 5}});
	auto m18 = make_matrix< int >(3_C_rt, 2_R, {{0, 1, 2}, {3, 4, 5}});
	auto m19 = make_matrix< int >(3_C, 2_R_rt, {{0, 1, 2}, {3, 4, 5}});
	auto m20 = make_matrix< int >(3_C_rt, 2_R_rt, {{0, 1, 2}, {3, 4, 5}});
	constexpr auto m21 = make_matrix(3_C, 2_R, ref_i);
	auto m22 = make_matrix(3_C_rt, 2_R, ref_i);
	auto m23 = make_matrix(3_C, 2_R_rt, ref_i);
	auto m24 = make_matrix(3_C_rt, 2_R_rt, ref_i);

	constexpr auto m25 = make_matrix_fn(3_C, 2_R, fn);
	auto m26 = make_matrix_fn(3_C_rt, 2_R, fn);
	auto m27 = make_matrix_fn(3_C, 2_R_rt, fn);
	auto m28 = make_matrix_fn(3_C_rt, 2_R_rt, fn);
	constexpr auto m29 = make_matrix_fn(dims(3_C, 2_R), fn);
	auto m30 = make_matrix_fn(dims(3_C_rt, 2_R), fn);
	auto m31 = make_matrix_fn(dims(3_C, 2_R_rt), fn);
	auto m32 = make_matrix_fn(dims(3_C_rt, 2_R_rt), fn);


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


	BOOST_TEST(check(m01, ref_0));
	BOOST_TEST(check(m02, ref_0));
	BOOST_TEST(check(m03, ref_0));
	BOOST_TEST(check(m04, ref_0));
	BOOST_TEST(check(m05, ref_0));
	BOOST_TEST(check(m06, ref_0));
	BOOST_TEST(check(m07, ref_0));
	BOOST_TEST(check(m08, ref_0));

	BOOST_TEST(check(m09, ref_v));
	BOOST_TEST(check(m10, ref_v));
	BOOST_TEST(check(m11, ref_v));
	BOOST_TEST(check(m12, ref_v));
	BOOST_TEST(check(m13, ref_v));
	BOOST_TEST(check(m14, ref_v));
	BOOST_TEST(check(m15, ref_v));
	BOOST_TEST(check(m16, ref_v));

	BOOST_TEST(check(m17, ref_i));
	BOOST_TEST(check(m18, ref_i));
	BOOST_TEST(check(m19, ref_i));
	BOOST_TEST(check(m20, ref_i));
	BOOST_TEST(check(m21, ref_i));
	BOOST_TEST(check(m22, ref_i));
	BOOST_TEST(check(m23, ref_i));
	BOOST_TEST(check(m24, ref_i));

	BOOST_TEST(check(m25, ref_f));
	BOOST_TEST(check(m26, ref_f));
	BOOST_TEST(check(m27, ref_f));
	BOOST_TEST(check(m28, ref_f));
	BOOST_TEST(check(m29, ref_f));
	BOOST_TEST(check(m30, ref_f));
	BOOST_TEST(check(m31, ref_f));
	BOOST_TEST(check(m32, ref_f));
}

BOOST_AUTO_TEST_CASE(test_raw_matrix_1x3){
	constexpr int ref_0[3][1] = {{0}, {0}, {0}};
	constexpr int ref_v[3][1] = {{7}, {7}, {7}};
	constexpr int ref_i[3][1] = {{0}, {1}, {2}};
	constexpr int ref_i_vec[3] = {0, 1, 2};
	constexpr int ref_f[3][1] = {{0}, {10}, {20}};
	constexpr auto fn_xy = fn_xy_t< int >();
	constexpr auto fn_i = fn_x_t< int >();

	constexpr auto m01 = make_matrix_v< int >(1_C, 3_R);
	auto m02 = make_col_vector_v< int >(3_R);
	auto m03 = make_matrix_v< int >(1_C, 3_R_rt);
	auto m04 = make_col_vector_v< int >(3_R_rt);
	constexpr auto m05 = make_matrix_v< int >(dims(1_C, 3_R));
	auto m06 = make_matrix_v< int >(dims(1_C, 3_R_rt));

	constexpr auto m07 = make_matrix_v(1_C, 3_R, 7);
	auto m08 = make_col_vector_v(3_R, 7);
	auto m09 = make_matrix_v(1_C, 3_R_rt, 7);
	auto m10 = make_col_vector_v(3_R_rt, 7);
	constexpr auto m11 = make_matrix_v(dims(1_C, 3_R), 7);
	auto m12 = make_matrix_v(dims(1_C, 3_R_rt), 7);

	constexpr auto m13 = make_matrix< int >(1_C, 3_R, {{0}, {1}, {2}});
	auto m14 = make_col_vector< int >(3_R, {0, 1, 2});
	auto m15 = make_matrix< int >(1_C, 3_R_rt, {{0}, {1}, {2}});
	auto m16 = make_col_vector< int >(3_R_rt, {0, 1, 2});
	constexpr auto m17 = make_matrix(1_C, 3_R, ref_i);
	auto m18 = make_col_vector(3_R, ref_i_vec);
	auto m19 = make_matrix(1_C, 3_R_rt, ref_i);
	auto m20 = make_col_vector(3_R_rt, ref_i_vec);

	constexpr auto m21 = make_matrix_fn(1_C, 3_R, fn_xy);
	auto m22 = make_col_vector_fn(3_R, fn_i);
	auto m23 = make_matrix_fn(1_C, 3_R_rt, fn_xy);
	auto m24 = make_col_vector_fn(3_R_rt, fn_i);
	constexpr auto m25 = make_matrix_fn(dims(1_C, 3_R), fn_xy);
	auto m26 = make_matrix_fn(dims(1_C, 3_R_rt), fn_xy);


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


	BOOST_TEST(check(m01, ref_0));
	BOOST_TEST(check(m02, ref_0));
	BOOST_TEST(check(m03, ref_0));
	BOOST_TEST(check(m04, ref_0));
	BOOST_TEST(check(m05, ref_0));
	BOOST_TEST(check(m06, ref_0));

	BOOST_TEST(check(m07, ref_v));
	BOOST_TEST(check(m08, ref_v));
	BOOST_TEST(check(m09, ref_v));
	BOOST_TEST(check(m10, ref_v));
	BOOST_TEST(check(m11, ref_v));
	BOOST_TEST(check(m12, ref_v));

	BOOST_TEST(check(m13, ref_i));
	BOOST_TEST(check(m14, ref_i));
	BOOST_TEST(check(m15, ref_i));
	BOOST_TEST(check(m16, ref_i));
	BOOST_TEST(check(m17, ref_i));
	BOOST_TEST(check(m18, ref_i));
	BOOST_TEST(check(m19, ref_i));
	BOOST_TEST(check(m20, ref_i));

	BOOST_TEST(check(m21, ref_f));
	BOOST_TEST(check(m22, ref_f));
	BOOST_TEST(check(m23, ref_f));
	BOOST_TEST(check(m24, ref_f));
	BOOST_TEST(check(m25, ref_f));
	BOOST_TEST(check(m26, ref_f));
}

BOOST_AUTO_TEST_CASE(test_raw_matrix_3x1){
	constexpr int ref_0[1][3] = {{0, 0, 0}};
	constexpr int ref_v[1][3] = {{7, 7, 7}};
	constexpr int ref_i[1][3] = {{0, 1, 2}};
	constexpr int ref_i_vec[3] = {0, 1, 2};
	constexpr int ref_f[1][3] = {{0, 1, 2}};
	constexpr auto fn_xy = fn_xy_t< int >();
	constexpr auto fn_i = fn_y_t< int >();

	constexpr auto m01 = make_matrix_v< int >(3_C, 1_R);
	auto m02 = make_row_vector_v< int >(3_C);
	auto m03 = make_matrix_v< int >(3_C_rt, 1_R);
	auto m04 = make_row_vector_v< int >(3_C_rt);
	constexpr auto m05 = make_matrix_v< int >(dims(3_C, 1_R));
	auto m06 = make_matrix_v< int >(dims(3_C_rt, 1_R));

	constexpr auto m07 = make_matrix_v(3_C, 1_R, 7);
	auto m08 = make_row_vector_v(3_C, 7);
	auto m09 = make_matrix_v(3_C_rt, 1_R, 7);
	auto m10 = make_row_vector_v(3_C_rt, 7);
	constexpr auto m11 = make_matrix_v(dims(3_C, 1_R), 7);
	auto m12 = make_matrix_v(dims(3_C_rt, 1_R), 7);

	constexpr auto m13 = make_matrix< int >(3_C, 1_R, {{0, 1, 2}});
	auto m14 = make_row_vector< int >(3_C, {0, 1, 2});
	auto m15 = make_matrix< int >(3_C_rt, 1_R, {{0, 1, 2}});
	auto m16 = make_row_vector< int >(3_C_rt, {0, 1, 2});
	constexpr auto m17 = make_matrix(3_C, 1_R, ref_i);
	auto m18 = make_row_vector(3_C, ref_i_vec);
	auto m19 = make_matrix(3_C_rt, 1_R, ref_i);
	auto m20 = make_row_vector(3_C_rt, ref_i_vec);

	constexpr auto m21 = make_matrix_fn(3_C, 1_R, fn_xy);
	auto m22 = make_row_vector_fn(3_C, fn_i);
	auto m23 = make_matrix_fn(3_C_rt, 1_R, fn_xy);
	auto m24 = make_row_vector_fn(3_C_rt, fn_i);
	constexpr auto m25 = make_matrix_fn(dims(3_C, 1_R), fn_xy);
	auto m26 = make_matrix_fn(dims(3_C_rt, 1_R), fn_xy);


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


	BOOST_TEST(check(m01, ref_0));
	BOOST_TEST(check(m02, ref_0));
	BOOST_TEST(check(m03, ref_0));
	BOOST_TEST(check(m04, ref_0));
	BOOST_TEST(check(m05, ref_0));
	BOOST_TEST(check(m06, ref_0));

	BOOST_TEST(check(m07, ref_v));
	BOOST_TEST(check(m08, ref_v));
	BOOST_TEST(check(m09, ref_v));
	BOOST_TEST(check(m10, ref_v));
	BOOST_TEST(check(m11, ref_v));
	BOOST_TEST(check(m12, ref_v));

	BOOST_TEST(check(m13, ref_i));
	BOOST_TEST(check(m14, ref_i));
	BOOST_TEST(check(m15, ref_i));
	BOOST_TEST(check(m16, ref_i));
	BOOST_TEST(check(m17, ref_i));
	BOOST_TEST(check(m18, ref_i));
	BOOST_TEST(check(m19, ref_i));
	BOOST_TEST(check(m20, ref_i));

	BOOST_TEST(check(m21, ref_f));
	BOOST_TEST(check(m22, ref_f));
	BOOST_TEST(check(m23, ref_f));
	BOOST_TEST(check(m24, ref_f));
	BOOST_TEST(check(m25, ref_f));
	BOOST_TEST(check(m26, ref_f));
}

BOOST_AUTO_TEST_CASE(test_raw_matrix_1x1){
	constexpr int ref_0[1][1] = {{0}};
	constexpr int ref_v[1][1] = {{7}};
	constexpr int ref_i[1][1] = {{0}};
	constexpr int ref_i_vec[1] = {0};
	constexpr int ref_f[1][1] = {{0}};
	constexpr auto fn_xy = fn_xy_t< int >();
	constexpr auto fn_x = fn_x_t< int >();
	constexpr auto fn_y = fn_y_t< int >();

	constexpr auto m01 = make_matrix_v< int >(1_C, 1_R);
	auto m02 = make_row_vector_v< int >(1_C);
	auto m03 = make_col_vector_v< int >(1_R);
	constexpr auto m04 = make_matrix_v< int >(dims(1_C, 1_R));
	constexpr auto m05 = make_square_matrix_v< int >(1_D);

	constexpr auto m06 = make_matrix_v(1_C, 1_R, 7);
	auto m07 = make_row_vector_v(1_C, 7);
	auto m08 = make_col_vector_v(1_R, 7);
	constexpr auto m09 = make_matrix_v(dims(1_C, 1_R), 7);
	constexpr auto m10 = make_square_matrix_v(1_D, 7);

	constexpr auto m11 = make_matrix< int >(1_C, 1_R, {{0}});
	auto m12 = make_row_vector< int >(1_C, {0});
	auto m13 = make_col_vector< int >(1_R, {0});
	constexpr auto m14 = make_square_matrix< int >(1_D, {{0}});
	constexpr auto m15 = make_matrix(1_C, 1_R, ref_i);
	auto m16 = make_row_vector(1_C, ref_i_vec);
	auto m17 = make_col_vector(1_R, ref_i_vec);
	constexpr auto m18 = make_square_matrix(1_D, ref_i);

	constexpr auto m19 = make_matrix_fn(1_C, 1_R, fn_xy);
	auto m20 = make_row_vector_fn(1_C, fn_x);
	auto m21 = make_col_vector_fn(1_R, fn_y);
	constexpr auto m22 = make_matrix_fn(dims(1_C, 1_R), fn_xy);
	constexpr auto m23 = make_square_matrix_fn(1_D, fn_xy);


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


	BOOST_TEST(check(m01, ref_0));
	BOOST_TEST(check(m02, ref_0));
	BOOST_TEST(check(m03, ref_0));
	BOOST_TEST(check(m04, ref_0));
	BOOST_TEST(check(m05, ref_0));

	BOOST_TEST(check(m06, ref_v));
	BOOST_TEST(check(m07, ref_v));
	BOOST_TEST(check(m08, ref_v));
	BOOST_TEST(check(m09, ref_v));
	BOOST_TEST(check(m10, ref_v));

	BOOST_TEST(check(m11, ref_i));
	BOOST_TEST(check(m12, ref_i));
	BOOST_TEST(check(m13, ref_i));
	BOOST_TEST(check(m14, ref_i));
	BOOST_TEST(check(m15, ref_i));
	BOOST_TEST(check(m16, ref_i));
	BOOST_TEST(check(m17, ref_i));
	BOOST_TEST(check(m18, ref_i));

	BOOST_TEST(check(m19, ref_f));
	BOOST_TEST(check(m20, ref_f));
	BOOST_TEST(check(m21, ref_f));
	BOOST_TEST(check(m22, ref_f));
	BOOST_TEST(check(m23, ref_f));
}

BOOST_AUTO_TEST_CASE(test_raw_bitmap){
	constexpr int ref_0_23[3][2] = {{0, 0}, {0, 0}, {0, 0}};
	constexpr int ref_v_23[3][2] = {{7, 7}, {7, 7}, {7, 7}};
	constexpr int ref_f_23[3][2] = {{0, 1}, {10, 11}, {20, 21}};
	constexpr int ref_0_32[2][3] = {{0, 0, 0}, {0, 0, 0}};
	constexpr int ref_v_32[2][3] = {{7, 7, 7}, {7, 7, 7}};
	constexpr int ref_f_32[2][3] = {{0, 1, 2}, {10, 11, 12}};
	constexpr auto fn = fn_xy_t< int >();

	auto m01 = make_bitmap_v< int >(2, 3);
	auto m02 = make_bitmap_v< int >(3, 2);
	auto m03 = make_bitmap_v< int >(dims(2, 3));
	auto m04 = make_bitmap_v< int >(dims(3, 2));

	auto m05 = make_bitmap_v(2, 3, 7);
	auto m06 = make_bitmap_v(3, 2, 7);
	auto m07 = make_bitmap_v(dims(2, 3), 7);
	auto m08 = make_bitmap_v(dims(3, 2), 7);

	auto m09 = make_bitmap_fn(2, 3, fn);
	auto m10 = make_bitmap_fn(3, 2, fn);
	auto m11 = make_bitmap_fn(dims(2, 3), fn);
	auto m12 = make_bitmap_fn(dims(3, 2), fn);

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

	BOOST_TEST(check(m01, ref_0_23));
	BOOST_TEST(check(m02, ref_0_32));
	BOOST_TEST(check(m03, ref_0_23));
	BOOST_TEST(check(m04, ref_0_32));

	BOOST_TEST(check(m05, ref_v_23));
	BOOST_TEST(check(m06, ref_v_32));
	BOOST_TEST(check(m07, ref_v_23));
	BOOST_TEST(check(m08, ref_v_32));

	BOOST_TEST(check(m09, ref_f_23));
	BOOST_TEST(check(m10, ref_f_32));
	BOOST_TEST(check(m11, ref_f_23));
	BOOST_TEST(check(m12, ref_f_32));
}


BOOST_AUTO_TEST_CASE(test_diag_matrix){
	constexpr int ref_0[3][3] = {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}};
	constexpr int ref_v[3][3] = {{7, 0, 0}, {0, 7, 0}, {0, 0, 7}};
	constexpr int ref_i[3][3] = {{0, 0, 0}, {0, 1, 0}, {0, 0, 2}};
	constexpr int ref_i_vec[3] = {0, 1, 2};
	constexpr int ref_f[3][3] = {{0, 0, 0}, {0, 11, 0}, {0, 0, 22}};
	constexpr auto fn = fn_i_t< int >();

	constexpr auto m01 = make_diag_matrix_v< int >(3_D);
	auto m02 = make_diag_matrix_v< int >(3_D_rt);

	constexpr auto m03 = make_diag_matrix_v(3_D, 7);
	auto m04 = make_diag_matrix_v(3_D_rt, 7);

	constexpr auto m05 = make_diag_matrix< int >(3_D, {0, 1, 2});
	auto m06 = make_diag_matrix< int >(3_D_rt, {0, 1, 2});
	constexpr auto m07 = make_diag_matrix(3_D, ref_i_vec);
	auto m08 = make_diag_matrix(3_D_rt, ref_i_vec);

	constexpr auto m09 = make_diag_matrix_fn(3_D, fn);
	auto m10 = make_diag_matrix_fn(3_D_rt, fn);


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


	BOOST_TEST(check(m01, ref_0));
	BOOST_TEST(check(m02, ref_0));
	BOOST_TEST(check(m03, ref_v));
	BOOST_TEST(check(m04, ref_v));
	BOOST_TEST(check(m05, ref_i));
	BOOST_TEST(check(m06, ref_i));
	BOOST_TEST(check(m07, ref_i));
	BOOST_TEST(check(m08, ref_i));
	BOOST_TEST(check(m09, ref_f));
	BOOST_TEST(check(m10, ref_f));
}


BOOST_AUTO_TEST_CASE(test_identity_matrix){
	constexpr int ref_i[3][3] = {{1, 0, 0}, {0, 1, 0}, {0, 0, 1}};

	constexpr auto m01 = make_identity_matrix< int >(3_D);
	auto m02 = make_identity_matrix< int >(3_D_rt);


	BOOST_TEST((rt_id(m01) == id< raw_matrix< int, 3, 3 > >));
	BOOST_TEST((rt_id(m02) == id< raw_matrix< int, 0, 0 > >));


	BOOST_TEST(check(m01, ref_i));
	BOOST_TEST(check(m02, ref_i));
}


BOOST_AUTO_TEST_CASE(test_copy_constructor){
	constexpr int ref_i[3][3] = {{0, 1, 2}, {3, 4, 5}, {6, 7, 8}};

	constexpr auto m01 = make_matrix(3_C, 3_R, ref_i);
	auto m02 = make_matrix(3_C_rt, 3_R_rt, ref_i);

	constexpr auto m03 = m01;
	auto m04 = m02;

	BOOST_TEST((rt_id(m03) == id< raw_matrix< int, 3, 3 > >));
	BOOST_TEST((rt_id(m04) == id< raw_matrix< int, 0, 0 > >));


	BOOST_TEST(check(m03, ref_i));
	BOOST_TEST(check(m04, ref_i));
}


BOOST_AUTO_TEST_CASE(test_move_constructor){
	constexpr int ref_i[3][3] = {{0, 1, 2}, {3, 4, 5}, {6, 7, 8}};

	constexpr auto m01 = make_matrix(3_C, 3_R, ref_i);
	auto m02 = make_matrix(3_C_rt, 3_R_rt, ref_i);

	constexpr auto m03 = std::move(m01);
	auto m04 = std::move(m02);

	BOOST_TEST((rt_id(m03) == id< raw_matrix< int, 3, 3 > >));
	BOOST_TEST((rt_id(m04) == id< raw_matrix< int, 0, 0 > >));


	BOOST_TEST(check(m03, ref_i));
	BOOST_TEST(check(m04, ref_i));
}


BOOST_AUTO_TEST_CASE(test_copy_assignment){
	constexpr int ref_i[3][3] = {{0, 1, 2}, {3, 4, 5}, {6, 7, 8}};

	constexpr auto m01 = make_matrix(3_C, 3_R, ref_i);
	auto m02 = make_matrix(3_C_rt, 3_R_rt, ref_i);

	auto m03 = make_matrix_v(3_C, 3_R, 0);
	auto m04 = make_matrix_v(3_C_rt, 3_R_rt, 0);


	m03 = m01;
	m04 = m02;


	BOOST_TEST((rt_id(m03) == id< raw_matrix< int, 3, 3 > >));
	BOOST_TEST((rt_id(m04) == id< raw_matrix< int, 0, 0 > >));


	BOOST_TEST(check(m03, ref_i));
	BOOST_TEST(check(m04, ref_i));
}


BOOST_AUTO_TEST_CASE(test_move_assignment){
	constexpr int ref_i[3][3] = {{0, 1, 2}, {3, 4, 5}, {6, 7, 8}};

	constexpr auto m01 = make_matrix(3_C, 3_R, ref_i);
	auto m02 = make_matrix(3_C_rt, 3_R_rt, ref_i);

	auto m03 = make_matrix_v(3_C, 3_R, 0);
	auto m04 = make_matrix_v(0_C_rt, 0_R_rt, 0);


	m03 = std::move(m01);
	m04 = std::move(m02);


	BOOST_TEST((rt_id(m03) == id< raw_matrix< int, 3, 3 > >));
	BOOST_TEST((rt_id(m04) == id< raw_matrix< int, 0, 0 > >));


	BOOST_TEST(check(m03, ref_i));
	BOOST_TEST(check(m04, ref_i));
}


BOOST_AUTO_TEST_SUITE_END()