// -----------------------------------------------------------------------------
// Copyright (c) 2015-2016 Benjamin Buch
//
// https://github.com/bebuch/mitrax
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt)
// -----------------------------------------------------------------------------
#define BOOST_TEST_MODULE mitrax make_matrix_eigen
#include <boost/test/unit_test.hpp>
#include <boost/mpl/list.hpp>

#include <mitrax/make_matrix.hpp>
#include <mitrax/matrix/eigen.hpp>

#include <complex>
#include <iostream>


using namespace mitrax;
using namespace mitrax::literals;


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
	res &= m.cols() == cols< col_t(RefC) >();
	res &= m.rows() == rows< row_t(RefR) >();

	for(size_t y = 0; y < RefR; ++y){
		for(size_t x = 0; x < RefC; ++x){
			res &= m(x, y) == ref[y][x];
		}
	}

	if constexpr(Matrix::ct_cols == 1_C || Matrix::ct_rows == 1_R){
		auto vec_ref =
			reinterpret_cast< value_type const(&)[RefC * RefR] >(ref);

		for(size_t i = 0; i < RefC * RefR; ++i){
			res &= m[i] == vec_ref[i];
		}
	}

	if constexpr(Matrix::ct_cols == 1_C && Matrix::ct_rows == 1_R){
		res &= static_cast< value_type >(m) == ref[0][0];
	}

	return res;
}

template < typename M, col_t C, row_t R, size_t RefC, size_t RefR >
constexpr bool check(
	matrix< M, C, R > const& m,
	value_type_t< M > const(&ref)[RefR][RefC]
){
	return check_fn(m, ref);
}

template < typename M, col_t C, row_t R, size_t RefC, size_t RefR >
constexpr bool check(
	matrix< M, C, R >& m,
	value_type_t< M > const(&ref)[RefR][RefC]
){
	auto const& m_const = m;
	return check_fn(m, ref) && check(m_const, ref);
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


BOOST_AUTO_TEST_SUITE(suite_make_matrix)


using types = boost::mpl::list< int, double, std::complex< float > >;


BOOST_AUTO_TEST_CASE_TEMPLATE(test_eigen_matrix_types, T, types){
	BOOST_TEST((
		id< eigen_matrix< T, 3_C, 4_R > > ==
		id< matrix< detail::eigen_matrix_impl< T, 3_C, 4_R >, 3_C, 4_R > >
	));

	BOOST_TEST((
		id< eigen_col_vector< T, 4_R > > ==
		id< col_vector< detail::eigen_matrix_impl< T, 1_C, 4_R >, 4_R > >
	));

	BOOST_TEST((
		id< eigen_col_vector< T, 4_R > > ==
		id< matrix< detail::eigen_matrix_impl< T, 1_C, 4_R >, 1_C, 4_R > >
	));

	BOOST_TEST((
		id< eigen_row_vector< T, 4_C > > ==
		id< row_vector< detail::eigen_matrix_impl< T, 4_C, 1_R >, 4_C > >
	));

	BOOST_TEST((
		id< eigen_row_vector< T, 4_C > > ==
		id< matrix< detail::eigen_matrix_impl< T, 4_C, 1_R >, 4_C, 1_R > >
	));

	BOOST_TEST((
		id< eigen_square_matrix< T, 4_D > > ==
		id< square_matrix< detail::eigen_matrix_impl< T, 4_C, 4_R >, 4_D > >
	));

	BOOST_TEST((
		id< eigen_square_matrix< T, 4_D > > ==
		id< matrix< detail::eigen_matrix_impl< T, 4_C, 4_R >, 4_C, 4_R > >
	));
}


BOOST_AUTO_TEST_CASE_TEMPLATE(test_eigen_matrix_3x3, T, types){
	constexpr T ref_0[3][3] = {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}};
	constexpr T ref_v[3][3] = {{7, 7, 7}, {7, 7, 7}, {7, 7, 7}};
	constexpr T ref_i[3][3] = {{0, 1, 2}, {3, 4, 5}, {6, 7, 8}};
	static constexpr T init_i[9] = {0, 1, 2, 3, 4, 5, 6, 7, 8};
	constexpr auto init_p = mitrax::begin(init_i);
	constexpr T ref_f[3][3] = {{0, 1, 2}, {10, 11, 12}, {20, 21, 22}};
	constexpr auto fn = fn_xy_t< T >();

	auto m01 = make_matrix_v< T >(3_CS, 3_RS, T(), maker::eigen);
	auto m02 = make_matrix_v< T >(3_CD, 3_RS, T(), maker::eigen);
	auto m03 = make_matrix_v< T >(3_CS, 3_RD, T(), maker::eigen);
	auto m04 = make_matrix_v< T >(3_CD, 3_RD, T(), maker::eigen);
	auto m05 = make_matrix_v< T >(dim_pair(3_CS, 3_RS), T(), maker::eigen);
	auto m06 = make_matrix_v< T >(dim_pair(3_CD, 3_RS), T(), maker::eigen);
	auto m07 = make_matrix_v< T >(dim_pair(3_CS, 3_RD), T(), maker::eigen);
	auto m08 = make_matrix_v< T >(dim_pair(3_CD, 3_RD), T(), maker::eigen);
	auto m09 = make_matrix_v< T >(3_DS, T(), maker::eigen);
	auto m10 = make_matrix_v< T >(3_DD, T(), maker::eigen);
	auto m11 = make_matrix_v< T >(dim_pair(3_DS), T(), maker::eigen);
	auto m12 = make_matrix_v< T >(dim_pair(3_DD), T(), maker::eigen);

	auto m13 = make_matrix_v(3_CS, 3_RS, T(7), maker::eigen);
	auto m14 = make_matrix_v(3_CD, 3_RS, T(7), maker::eigen);
	auto m15 = make_matrix_v(3_CS, 3_RD, T(7), maker::eigen);
	auto m16 = make_matrix_v(3_CD, 3_RD, T(7), maker::eigen);
	auto m17 = make_matrix_v(dim_pair(3_CS, 3_RS), T(7), maker::eigen);
	auto m18 = make_matrix_v(dim_pair(3_CD, 3_RS), T(7), maker::eigen);
	auto m19 = make_matrix_v(dim_pair(3_CS, 3_RD), T(7), maker::eigen);
	auto m20 = make_matrix_v(dim_pair(3_CD, 3_RD), T(7), maker::eigen);
	auto m21 = make_matrix_v(3_DS, T(7), maker::eigen);
	auto m22 = make_matrix_v(3_DD, T(7), maker::eigen);
	auto m23 = make_matrix_v(dim_pair(3_DS), T(7), maker::eigen);
	auto m24 = make_matrix_v(dim_pair(3_DD), T(7), maker::eigen);

	auto m25 = make_matrix< T >
		(3_CS, 3_RS, {{0, 1, 2}, {3, 4, 5}, {6, 7, 8}}, maker::eigen);
	auto m26 = make_matrix< T >
		(3_CD, 3_RS, {{0, 1, 2}, {3, 4, 5}, {6, 7, 8}}, maker::eigen);
	auto m27 = make_matrix< T >
		(3_CS, 3_RD, {{0, 1, 2}, {3, 4, 5}, {6, 7, 8}}, maker::eigen);
	auto m28 = make_matrix< T >
		(3_CD, 3_RD, {{0, 1, 2}, {3, 4, 5}, {6, 7, 8}}, maker::eigen);
	auto m29 = make_matrix(3_CS, 3_RS, ref_i, maker::eigen);
	auto m30 = make_matrix(3_CD, 3_RS, ref_i, maker::eigen);
	auto m31 = make_matrix(3_CS, 3_RD, ref_i, maker::eigen);
	auto m32 = make_matrix(3_CD, 3_RD, ref_i, maker::eigen);
	auto m33 = make_matrix< T >
		(3_DS, {{0, 1, 2}, {3, 4, 5}, {6, 7, 8}}, maker::eigen);
	auto m34 = make_matrix< T >
		(3_DD, {{0, 1, 2}, {3, 4, 5}, {6, 7, 8}}, maker::eigen);
	auto m35 = make_matrix(3_DS, ref_i, maker::eigen);
	auto m36 = make_matrix(3_DD, ref_i, maker::eigen);

	auto m37 = make_matrix_fn(3_CS, 3_RS, fn, maker::eigen);
	auto m38 = make_matrix_fn(3_CD, 3_RS, fn, maker::eigen);
	auto m39 = make_matrix_fn(3_CS, 3_RD, fn, maker::eigen);
	auto m40 = make_matrix_fn(3_CD, 3_RD, fn, maker::eigen);
	auto m41 = make_matrix_fn(dim_pair(3_CS, 3_RS), fn, maker::eigen);
	auto m42 = make_matrix_fn(dim_pair(3_CD, 3_RS), fn, maker::eigen);
	auto m43 = make_matrix_fn(dim_pair(3_CS, 3_RD), fn, maker::eigen);
	auto m44 = make_matrix_fn(dim_pair(3_CD, 3_RD), fn, maker::eigen);
	auto m45 = make_matrix_fn(3_DS, fn, maker::eigen);
	auto m46 = make_matrix_fn(3_DD, fn, maker::eigen);
	auto m47 = make_matrix_fn(dim_pair(3_DS), fn, maker::eigen);
	auto m48 = make_matrix_fn(dim_pair(3_DD), fn, maker::eigen);

	auto m49 = make_matrix_i(3_CS, 3_RS, init_p, maker::eigen);
	auto m50 = make_matrix_i(3_CD, 3_RS, init_p, maker::eigen);
	auto m51 = make_matrix_i(3_CS, 3_RD, init_p, maker::eigen);
	auto m52 = make_matrix_i(3_CD, 3_RD, init_p, maker::eigen);
	auto m53 = make_matrix_i(dim_pair(3_CS, 3_RS), init_p, maker::eigen);
	auto m54 = make_matrix_i(dim_pair(3_CD, 3_RS), init_p, maker::eigen);
	auto m55 = make_matrix_i(dim_pair(3_CS, 3_RD), init_p, maker::eigen);
	auto m56 = make_matrix_i(dim_pair(3_CD, 3_RD), init_p, maker::eigen);
	auto m57 = make_matrix_i(3_DS, init_p, maker::eigen);
	auto m58 = make_matrix_i(3_DD, init_p, maker::eigen);
	auto m59 = make_matrix_i(dim_pair(3_DS), init_p, maker::eigen);
	auto m60 = make_matrix_i(dim_pair(3_DD), init_p, maker::eigen);


	BOOST_TEST((rt_id(m01) == id< eigen_matrix< T, 3_C, 3_R > >));
	BOOST_TEST((rt_id(m02) == id< eigen_matrix< T, 0_C, 3_R > >));
	BOOST_TEST((rt_id(m03) == id< eigen_matrix< T, 3_C, 0_R > >));
	BOOST_TEST((rt_id(m04) == id< eigen_matrix< T, 0_C, 0_R > >));
	BOOST_TEST((rt_id(m05) == id< eigen_matrix< T, 3_C, 3_R > >));
	BOOST_TEST((rt_id(m06) == id< eigen_matrix< T, 0_C, 3_R > >));
	BOOST_TEST((rt_id(m07) == id< eigen_matrix< T, 3_C, 0_R > >));
	BOOST_TEST((rt_id(m08) == id< eigen_matrix< T, 0_C, 0_R > >));
	BOOST_TEST((rt_id(m09) == id< eigen_matrix< T, 3_C, 3_R > >));
	BOOST_TEST((rt_id(m10) == id< eigen_matrix< T, 0_C, 0_R > >));
	BOOST_TEST((rt_id(m11) == id< eigen_matrix< T, 3_C, 3_R > >));
	BOOST_TEST((rt_id(m12) == id< eigen_matrix< T, 0_C, 0_R > >));

	BOOST_TEST((rt_id(m13) == id< eigen_matrix< T, 3_C, 3_R > >));
	BOOST_TEST((rt_id(m14) == id< eigen_matrix< T, 0_C, 3_R > >));
	BOOST_TEST((rt_id(m15) == id< eigen_matrix< T, 3_C, 0_R > >));
	BOOST_TEST((rt_id(m16) == id< eigen_matrix< T, 0_C, 0_R > >));
	BOOST_TEST((rt_id(m17) == id< eigen_matrix< T, 3_C, 3_R > >));
	BOOST_TEST((rt_id(m18) == id< eigen_matrix< T, 0_C, 3_R > >));
	BOOST_TEST((rt_id(m19) == id< eigen_matrix< T, 3_C, 0_R > >));
	BOOST_TEST((rt_id(m20) == id< eigen_matrix< T, 0_C, 0_R > >));
	BOOST_TEST((rt_id(m21) == id< eigen_matrix< T, 3_C, 3_R > >));
	BOOST_TEST((rt_id(m22) == id< eigen_matrix< T, 0_C, 0_R > >));
	BOOST_TEST((rt_id(m23) == id< eigen_matrix< T, 3_C, 3_R > >));
	BOOST_TEST((rt_id(m24) == id< eigen_matrix< T, 0_C, 0_R > >));

	BOOST_TEST((rt_id(m25) == id< eigen_matrix< T, 3_C, 3_R > >));
	BOOST_TEST((rt_id(m26) == id< eigen_matrix< T, 0_C, 3_R > >));
	BOOST_TEST((rt_id(m27) == id< eigen_matrix< T, 3_C, 0_R > >));
	BOOST_TEST((rt_id(m28) == id< eigen_matrix< T, 0_C, 0_R > >));
	BOOST_TEST((rt_id(m29) == id< eigen_matrix< T, 3_C, 3_R > >));
	BOOST_TEST((rt_id(m30) == id< eigen_matrix< T, 0_C, 3_R > >));
	BOOST_TEST((rt_id(m31) == id< eigen_matrix< T, 3_C, 0_R > >));
	BOOST_TEST((rt_id(m32) == id< eigen_matrix< T, 0_C, 0_R > >));
	BOOST_TEST((rt_id(m33) == id< eigen_matrix< T, 3_C, 3_R > >));
	BOOST_TEST((rt_id(m34) == id< eigen_matrix< T, 0_C, 0_R > >));
	BOOST_TEST((rt_id(m35) == id< eigen_matrix< T, 3_C, 3_R > >));
	BOOST_TEST((rt_id(m36) == id< eigen_matrix< T, 0_C, 0_R > >));

	BOOST_TEST((rt_id(m37) == id< eigen_matrix< T, 3_C, 3_R > >));
	BOOST_TEST((rt_id(m38) == id< eigen_matrix< T, 0_C, 3_R > >));
	BOOST_TEST((rt_id(m39) == id< eigen_matrix< T, 3_C, 0_R > >));
	BOOST_TEST((rt_id(m40) == id< eigen_matrix< T, 0_C, 0_R > >));
	BOOST_TEST((rt_id(m41) == id< eigen_matrix< T, 3_C, 3_R > >));
	BOOST_TEST((rt_id(m42) == id< eigen_matrix< T, 0_C, 3_R > >));
	BOOST_TEST((rt_id(m43) == id< eigen_matrix< T, 3_C, 0_R > >));
	BOOST_TEST((rt_id(m44) == id< eigen_matrix< T, 0_C, 0_R > >));
	BOOST_TEST((rt_id(m45) == id< eigen_matrix< T, 3_C, 3_R > >));
	BOOST_TEST((rt_id(m46) == id< eigen_matrix< T, 0_C, 0_R > >));
	BOOST_TEST((rt_id(m47) == id< eigen_matrix< T, 3_C, 3_R > >));
	BOOST_TEST((rt_id(m48) == id< eigen_matrix< T, 0_C, 0_R > >));

	BOOST_TEST((rt_id(m49) == id< eigen_matrix< T, 3_C, 3_R > >));
	BOOST_TEST((rt_id(m50) == id< eigen_matrix< T, 0_C, 3_R > >));
	BOOST_TEST((rt_id(m51) == id< eigen_matrix< T, 3_C, 0_R > >));
	BOOST_TEST((rt_id(m52) == id< eigen_matrix< T, 0_C, 0_R > >));
	BOOST_TEST((rt_id(m53) == id< eigen_matrix< T, 3_C, 3_R > >));
	BOOST_TEST((rt_id(m54) == id< eigen_matrix< T, 0_C, 3_R > >));
	BOOST_TEST((rt_id(m55) == id< eigen_matrix< T, 3_C, 0_R > >));
	BOOST_TEST((rt_id(m56) == id< eigen_matrix< T, 0_C, 0_R > >));
	BOOST_TEST((rt_id(m57) == id< eigen_matrix< T, 3_C, 3_R > >));
	BOOST_TEST((rt_id(m58) == id< eigen_matrix< T, 0_C, 0_R > >));
	BOOST_TEST((rt_id(m59) == id< eigen_matrix< T, 3_C, 3_R > >));
	BOOST_TEST((rt_id(m60) == id< eigen_matrix< T, 0_C, 0_R > >));


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

	BOOST_TEST((check(m49, ref_i)));
	BOOST_TEST((check(m50, ref_i)));
	BOOST_TEST((check(m51, ref_i)));
	BOOST_TEST((check(m52, ref_i)));
	BOOST_TEST((check(m53, ref_i)));
	BOOST_TEST((check(m54, ref_i)));
	BOOST_TEST((check(m55, ref_i)));
	BOOST_TEST((check(m56, ref_i)));
	BOOST_TEST((check(m57, ref_i)));
	BOOST_TEST((check(m58, ref_i)));
	BOOST_TEST((check(m59, ref_i)));
	BOOST_TEST((check(m60, ref_i)));
}


BOOST_AUTO_TEST_CASE_TEMPLATE(test_eigen_matrix_2x3, T, types){
	constexpr T ref_0[3][2] = {{0, 0}, {0, 0}, {0, 0}};
	constexpr T ref_v[3][2] = {{7, 7}, {7, 7}, {7, 7}};
	constexpr T ref_i[3][2] = {{0, 1}, {2, 3}, {4, 5}};
	static constexpr T init_i[6] = {0, 1, 2, 3, 4, 5};
	constexpr auto init_p = mitrax::begin(init_i);
	constexpr T ref_f[3][2] = {{0, 1}, {10, 11}, {20, 21}};
	constexpr auto fn = fn_xy_t< T >();

	auto m01 = make_matrix_v< T >(2_CS, 3_RS, T(), maker::eigen);
	auto m02 = make_matrix_v< T >(2_CD, 3_RS, T(), maker::eigen);
	auto m03 = make_matrix_v< T >(2_CS, 3_RD, T(), maker::eigen);
	auto m04 = make_matrix_v< T >(2_CD, 3_RD, T(), maker::eigen);
	auto m05 = make_matrix_v< T >(dim_pair(2_CS, 3_RS), T(), maker::eigen);
	auto m06 = make_matrix_v< T >(dim_pair(2_CD, 3_RS), T(), maker::eigen);
	auto m07 = make_matrix_v< T >(dim_pair(2_CS, 3_RD), T(), maker::eigen);
	auto m08 = make_matrix_v< T >(dim_pair(2_CD, 3_RD), T(), maker::eigen);

	auto m09 = make_matrix_v(2_CS, 3_RS, T(7), maker::eigen);
	auto m10 = make_matrix_v(2_CD, 3_RS, T(7), maker::eigen);
	auto m11 = make_matrix_v(2_CS, 3_RD, T(7), maker::eigen);
	auto m12 = make_matrix_v(2_CD, 3_RD, T(7), maker::eigen);
	auto m13 = make_matrix_v(dim_pair(2_CS, 3_RS), T(7), maker::eigen);
	auto m14 = make_matrix_v(dim_pair(2_CD, 3_RS), T(7), maker::eigen);
	auto m15 = make_matrix_v(dim_pair(2_CS, 3_RD), T(7), maker::eigen);
	auto m16 = make_matrix_v(dim_pair(2_CD, 3_RD), T(7), maker::eigen);

	auto m17 = make_matrix< T >(2_CS, 3_RS, {{0, 1}, {2, 3}, {4, 5}},
		maker::eigen);
	auto m18 = make_matrix< T >(2_CD, 3_RS, {{0, 1}, {2, 3}, {4, 5}},
		maker::eigen);
	auto m19 = make_matrix< T >(2_CS, 3_RD, {{0, 1}, {2, 3}, {4, 5}},
		maker::eigen);
	auto m20 = make_matrix< T >(2_CD, 3_RD, {{0, 1}, {2, 3}, {4, 5}},
		maker::eigen);
	auto m21 = make_matrix(2_CS, 3_RS, ref_i, maker::eigen);
	auto m22 = make_matrix(2_CD, 3_RS, ref_i, maker::eigen);
	auto m23 = make_matrix(2_CS, 3_RD, ref_i, maker::eigen);
	auto m24 = make_matrix(2_CD, 3_RD, ref_i, maker::eigen);

	auto m25 = make_matrix_fn(2_CS, 3_RS, fn, maker::eigen);
	auto m26 = make_matrix_fn(2_CD, 3_RS, fn, maker::eigen);
	auto m27 = make_matrix_fn(2_CS, 3_RD, fn, maker::eigen);
	auto m28 = make_matrix_fn(2_CD, 3_RD, fn, maker::eigen);
	auto m29 = make_matrix_fn(dim_pair(2_CS, 3_RS), fn, maker::eigen);
	auto m30 = make_matrix_fn(dim_pair(2_CD, 3_RS), fn, maker::eigen);
	auto m31 = make_matrix_fn(dim_pair(2_CS, 3_RD), fn, maker::eigen);
	auto m32 = make_matrix_fn(dim_pair(2_CD, 3_RD), fn, maker::eigen);

	auto m33 = make_matrix_i(2_CS, 3_RS, init_p, maker::eigen);
	auto m34 = make_matrix_i(2_CD, 3_RS, init_p, maker::eigen);
	auto m35 = make_matrix_i(2_CS, 3_RD, init_p, maker::eigen);
	auto m36 = make_matrix_i(2_CD, 3_RD, init_p, maker::eigen);
	auto m37 = make_matrix_i(dim_pair(2_CS, 3_RS), init_p, maker::eigen);
	auto m38 = make_matrix_i(dim_pair(2_CD, 3_RS), init_p, maker::eigen);
	auto m39 = make_matrix_i(dim_pair(2_CS, 3_RD), init_p, maker::eigen);
	auto m40 = make_matrix_i(dim_pair(2_CD, 3_RD), init_p, maker::eigen);


	BOOST_TEST((rt_id(m01) == id< eigen_matrix< T, 2_C, 3_R > >));
	BOOST_TEST((rt_id(m02) == id< eigen_matrix< T, 0_C, 3_R > >));
	BOOST_TEST((rt_id(m03) == id< eigen_matrix< T, 2_C, 0_R > >));
	BOOST_TEST((rt_id(m04) == id< eigen_matrix< T, 0_C, 0_R > >));
	BOOST_TEST((rt_id(m05) == id< eigen_matrix< T, 2_C, 3_R > >));
	BOOST_TEST((rt_id(m06) == id< eigen_matrix< T, 0_C, 3_R > >));
	BOOST_TEST((rt_id(m07) == id< eigen_matrix< T, 2_C, 0_R > >));
	BOOST_TEST((rt_id(m08) == id< eigen_matrix< T, 0_C, 0_R > >));

	BOOST_TEST((rt_id(m09) == id< eigen_matrix< T, 2_C, 3_R > >));
	BOOST_TEST((rt_id(m10) == id< eigen_matrix< T, 0_C, 3_R > >));
	BOOST_TEST((rt_id(m11) == id< eigen_matrix< T, 2_C, 0_R > >));
	BOOST_TEST((rt_id(m12) == id< eigen_matrix< T, 0_C, 0_R > >));
	BOOST_TEST((rt_id(m13) == id< eigen_matrix< T, 2_C, 3_R > >));
	BOOST_TEST((rt_id(m14) == id< eigen_matrix< T, 0_C, 3_R > >));
	BOOST_TEST((rt_id(m15) == id< eigen_matrix< T, 2_C, 0_R > >));
	BOOST_TEST((rt_id(m16) == id< eigen_matrix< T, 0_C, 0_R > >));

	BOOST_TEST((rt_id(m17) == id< eigen_matrix< T, 2_C, 3_R > >));
	BOOST_TEST((rt_id(m18) == id< eigen_matrix< T, 0_C, 3_R > >));
	BOOST_TEST((rt_id(m19) == id< eigen_matrix< T, 2_C, 0_R > >));
	BOOST_TEST((rt_id(m20) == id< eigen_matrix< T, 0_C, 0_R > >));
	BOOST_TEST((rt_id(m21) == id< eigen_matrix< T, 2_C, 3_R > >));
	BOOST_TEST((rt_id(m22) == id< eigen_matrix< T, 0_C, 3_R > >));
	BOOST_TEST((rt_id(m23) == id< eigen_matrix< T, 2_C, 0_R > >));
	BOOST_TEST((rt_id(m24) == id< eigen_matrix< T, 0_C, 0_R > >));

	BOOST_TEST((rt_id(m25) == id< eigen_matrix< T, 2_C, 3_R > >));
	BOOST_TEST((rt_id(m26) == id< eigen_matrix< T, 0_C, 3_R > >));
	BOOST_TEST((rt_id(m27) == id< eigen_matrix< T, 2_C, 0_R > >));
	BOOST_TEST((rt_id(m28) == id< eigen_matrix< T, 0_C, 0_R > >));
	BOOST_TEST((rt_id(m29) == id< eigen_matrix< T, 2_C, 3_R > >));
	BOOST_TEST((rt_id(m30) == id< eigen_matrix< T, 0_C, 3_R > >));
	BOOST_TEST((rt_id(m31) == id< eigen_matrix< T, 2_C, 0_R > >));
	BOOST_TEST((rt_id(m32) == id< eigen_matrix< T, 0_C, 0_R > >));

	BOOST_TEST((rt_id(m33) == id< eigen_matrix< T, 2_C, 3_R > >));
	BOOST_TEST((rt_id(m34) == id< eigen_matrix< T, 0_C, 3_R > >));
	BOOST_TEST((rt_id(m35) == id< eigen_matrix< T, 2_C, 0_R > >));
	BOOST_TEST((rt_id(m36) == id< eigen_matrix< T, 0_C, 0_R > >));
	BOOST_TEST((rt_id(m37) == id< eigen_matrix< T, 2_C, 3_R > >));
	BOOST_TEST((rt_id(m38) == id< eigen_matrix< T, 0_C, 3_R > >));
	BOOST_TEST((rt_id(m39) == id< eigen_matrix< T, 2_C, 0_R > >));
	BOOST_TEST((rt_id(m40) == id< eigen_matrix< T, 0_C, 0_R > >));


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

	BOOST_TEST(check(m33, ref_i));
	BOOST_TEST(check(m34, ref_i));
	BOOST_TEST(check(m35, ref_i));
	BOOST_TEST(check(m36, ref_i));
	BOOST_TEST(check(m37, ref_i));
	BOOST_TEST(check(m38, ref_i));
	BOOST_TEST(check(m39, ref_i));
	BOOST_TEST(check(m40, ref_i));
}

BOOST_AUTO_TEST_CASE_TEMPLATE(test_eigen_matrix_3x2, T, types){
	constexpr T ref_0[2][3] = {{0, 0, 0}, {0, 0, 0}};
	constexpr T ref_v[2][3] = {{7, 7, 7}, {7, 7, 7}};
	constexpr T ref_i[2][3] = {{0, 1, 2}, {3, 4, 5}};
	static constexpr T init_i[6] = {0, 1, 2, 3, 4, 5};
	constexpr auto init_p = mitrax::begin(init_i);
	constexpr T ref_f[2][3] = {{0, 1, 2}, {10, 11, 12}};
	constexpr auto fn = fn_xy_t< T >();

	auto m01 = make_matrix_v< T >(3_CS, 2_RS, T(), maker::eigen);
	auto m02 = make_matrix_v< T >(3_CD, 2_RS, T(), maker::eigen);
	auto m03 = make_matrix_v< T >(3_CS, 2_RD, T(), maker::eigen);
	auto m04 = make_matrix_v< T >(3_CD, 2_RD, T(), maker::eigen);
	auto m05 = make_matrix_v< T >(dim_pair(3_CS, 2_RS), T(), maker::eigen);
	auto m06 = make_matrix_v< T >(dim_pair(3_CD, 2_RS), T(), maker::eigen);
	auto m07 = make_matrix_v< T >(dim_pair(3_CS, 2_RD), T(), maker::eigen);
	auto m08 = make_matrix_v< T >(dim_pair(3_CD, 2_RD), T(), maker::eigen);

	auto m09 = make_matrix_v(3_CS, 2_RS, T(7), maker::eigen);
	auto m10 = make_matrix_v(3_CD, 2_RS, T(7), maker::eigen);
	auto m11 = make_matrix_v(3_CS, 2_RD, T(7), maker::eigen);
	auto m12 = make_matrix_v(3_CD, 2_RD, T(7), maker::eigen);
	auto m13 = make_matrix_v(dim_pair(3_CS, 2_RS), T(7), maker::eigen);
	auto m14 = make_matrix_v(dim_pair(3_CD, 2_RS), T(7), maker::eigen);
	auto m15 = make_matrix_v(dim_pair(3_CS, 2_RD), T(7), maker::eigen);
	auto m16 = make_matrix_v(dim_pair(3_CD, 2_RD), T(7), maker::eigen);

	auto m17 = make_matrix< T >
		(3_CS, 2_RS, {{0, 1, 2}, {3, 4, 5}}, maker::eigen);
	auto m18 = make_matrix< T >
		(3_CD, 2_RS, {{0, 1, 2}, {3, 4, 5}}, maker::eigen);
	auto m19 = make_matrix< T >
		(3_CS, 2_RD, {{0, 1, 2}, {3, 4, 5}}, maker::eigen);
	auto m20 = make_matrix< T >
		(3_CD, 2_RD, {{0, 1, 2}, {3, 4, 5}}, maker::eigen);
	auto m21 = make_matrix(3_CS, 2_RS, ref_i, maker::eigen);
	auto m22 = make_matrix(3_CD, 2_RS, ref_i, maker::eigen);
	auto m23 = make_matrix(3_CS, 2_RD, ref_i, maker::eigen);
	auto m24 = make_matrix(3_CD, 2_RD, ref_i, maker::eigen);

	auto m25 = make_matrix_fn(3_CS, 2_RS, fn, maker::eigen);
	auto m26 = make_matrix_fn(3_CD, 2_RS, fn, maker::eigen);
	auto m27 = make_matrix_fn(3_CS, 2_RD, fn, maker::eigen);
	auto m28 = make_matrix_fn(3_CD, 2_RD, fn, maker::eigen);
	auto m29 = make_matrix_fn(dim_pair(3_CS, 2_RS), fn, maker::eigen);
	auto m30 = make_matrix_fn(dim_pair(3_CD, 2_RS), fn, maker::eigen);
	auto m31 = make_matrix_fn(dim_pair(3_CS, 2_RD), fn, maker::eigen);
	auto m32 = make_matrix_fn(dim_pair(3_CD, 2_RD), fn, maker::eigen);

	auto m33 = make_matrix_i(3_CS, 2_RS, init_p, maker::eigen);
	auto m34 = make_matrix_i(3_CD, 2_RS, init_p, maker::eigen);
	auto m35 = make_matrix_i(3_CS, 2_RD, init_p, maker::eigen);
	auto m36 = make_matrix_i(3_CD, 2_RD, init_p, maker::eigen);
	auto m37 = make_matrix_i(dim_pair(3_CS, 2_RS), init_p, maker::eigen);
	auto m38 = make_matrix_i(dim_pair(3_CD, 2_RS), init_p, maker::eigen);
	auto m39 = make_matrix_i(dim_pair(3_CS, 2_RD), init_p, maker::eigen);
	auto m40 = make_matrix_i(dim_pair(3_CD, 2_RD), init_p, maker::eigen);


	BOOST_TEST((rt_id(m01) == id< eigen_matrix< T, 3_C, 2_R > >));
	BOOST_TEST((rt_id(m02) == id< eigen_matrix< T, 0_C, 2_R > >));
	BOOST_TEST((rt_id(m03) == id< eigen_matrix< T, 3_C, 0_R > >));
	BOOST_TEST((rt_id(m04) == id< eigen_matrix< T, 0_C, 0_R > >));
	BOOST_TEST((rt_id(m05) == id< eigen_matrix< T, 3_C, 2_R > >));
	BOOST_TEST((rt_id(m06) == id< eigen_matrix< T, 0_C, 2_R > >));
	BOOST_TEST((rt_id(m07) == id< eigen_matrix< T, 3_C, 0_R > >));
	BOOST_TEST((rt_id(m08) == id< eigen_matrix< T, 0_C, 0_R > >));

	BOOST_TEST((rt_id(m09) == id< eigen_matrix< T, 3_C, 2_R > >));
	BOOST_TEST((rt_id(m10) == id< eigen_matrix< T, 0_C, 2_R > >));
	BOOST_TEST((rt_id(m11) == id< eigen_matrix< T, 3_C, 0_R > >));
	BOOST_TEST((rt_id(m12) == id< eigen_matrix< T, 0_C, 0_R > >));
	BOOST_TEST((rt_id(m13) == id< eigen_matrix< T, 3_C, 2_R > >));
	BOOST_TEST((rt_id(m14) == id< eigen_matrix< T, 0_C, 2_R > >));
	BOOST_TEST((rt_id(m15) == id< eigen_matrix< T, 3_C, 0_R > >));
	BOOST_TEST((rt_id(m16) == id< eigen_matrix< T, 0_C, 0_R > >));

	BOOST_TEST((rt_id(m17) == id< eigen_matrix< T, 3_C, 2_R > >));
	BOOST_TEST((rt_id(m18) == id< eigen_matrix< T, 0_C, 2_R > >));
	BOOST_TEST((rt_id(m19) == id< eigen_matrix< T, 3_C, 0_R > >));
	BOOST_TEST((rt_id(m20) == id< eigen_matrix< T, 0_C, 0_R > >));
	BOOST_TEST((rt_id(m21) == id< eigen_matrix< T, 3_C, 2_R > >));
	BOOST_TEST((rt_id(m22) == id< eigen_matrix< T, 0_C, 2_R > >));
	BOOST_TEST((rt_id(m23) == id< eigen_matrix< T, 3_C, 0_R > >));
	BOOST_TEST((rt_id(m24) == id< eigen_matrix< T, 0_C, 0_R > >));

	BOOST_TEST((rt_id(m25) == id< eigen_matrix< T, 3_C, 2_R > >));
	BOOST_TEST((rt_id(m26) == id< eigen_matrix< T, 0_C, 2_R > >));
	BOOST_TEST((rt_id(m27) == id< eigen_matrix< T, 3_C, 0_R > >));
	BOOST_TEST((rt_id(m28) == id< eigen_matrix< T, 0_C, 0_R > >));
	BOOST_TEST((rt_id(m29) == id< eigen_matrix< T, 3_C, 2_R > >));
	BOOST_TEST((rt_id(m30) == id< eigen_matrix< T, 0_C, 2_R > >));
	BOOST_TEST((rt_id(m31) == id< eigen_matrix< T, 3_C, 0_R > >));
	BOOST_TEST((rt_id(m32) == id< eigen_matrix< T, 0_C, 0_R > >));

	BOOST_TEST((rt_id(m33) == id< eigen_matrix< T, 3_C, 2_R > >));
	BOOST_TEST((rt_id(m34) == id< eigen_matrix< T, 0_C, 2_R > >));
	BOOST_TEST((rt_id(m35) == id< eigen_matrix< T, 3_C, 0_R > >));
	BOOST_TEST((rt_id(m36) == id< eigen_matrix< T, 0_C, 0_R > >));
	BOOST_TEST((rt_id(m37) == id< eigen_matrix< T, 3_C, 2_R > >));
	BOOST_TEST((rt_id(m38) == id< eigen_matrix< T, 0_C, 2_R > >));
	BOOST_TEST((rt_id(m39) == id< eigen_matrix< T, 3_C, 0_R > >));
	BOOST_TEST((rt_id(m40) == id< eigen_matrix< T, 0_C, 0_R > >));


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

	BOOST_TEST(check(m33, ref_i));
	BOOST_TEST(check(m34, ref_i));
	BOOST_TEST(check(m35, ref_i));
	BOOST_TEST(check(m36, ref_i));
	BOOST_TEST(check(m37, ref_i));
	BOOST_TEST(check(m38, ref_i));
	BOOST_TEST(check(m39, ref_i));
	BOOST_TEST(check(m40, ref_i));
}

BOOST_AUTO_TEST_CASE_TEMPLATE(test_eigen_matrix_1x3, T, types){
	constexpr T ref_0[3][1] = {{0}, {0}, {0}};
	constexpr T ref_v[3][1] = {{7}, {7}, {7}};
	constexpr T ref_i[3][1] = {{0}, {1}, {2}};
	constexpr T ref_i_vec[3] = {0, 1, 2};
	static constexpr T init_i[3] = {0, 1, 2};
	constexpr auto init_p = mitrax::begin(init_i);
	constexpr T ref_f[3][1] = {{0}, {10}, {20}};
	constexpr auto fn_xy = fn_xy_t< T >();
	constexpr auto fn_i = fn_x_t< T >();

	auto m01 = make_matrix_v< T >(1_CS, 3_RS, T(), maker::eigen);
	auto m02 = make_vector_v< T >(3_RS, T(), maker::eigen);
	auto m03 = make_matrix_v< T >(1_CS, 3_RD, T(), maker::eigen);
	auto m04 = make_vector_v< T >(3_RD, T(), maker::eigen);
	auto m05 = make_matrix_v< T >(dim_pair(1_CS, 3_RS), T(), maker::eigen);
	auto m06 = make_matrix_v< T >(dim_pair(1_CS, 3_RD), T(), maker::eigen);

	auto m07 = make_matrix_v(1_CS, 3_RS, T(7), maker::eigen);
	auto m08 = make_vector_v(3_RS, T(7), maker::eigen);
	auto m09 = make_matrix_v(1_CS, 3_RD, T(7), maker::eigen);
	auto m10 = make_vector_v(3_RD, T(7), maker::eigen);
	auto m11 = make_matrix_v(dim_pair(1_CS, 3_RS), T(7), maker::eigen);
	auto m12 = make_matrix_v(dim_pair(1_CS, 3_RD), T(7), maker::eigen);

	auto m13 = make_matrix< T >(1_CS, 3_RS, {{0}, {1}, {2}}, maker::eigen);
	auto m14 = make_vector< T >(3_RS, {0, 1, 2}, maker::eigen);
	auto m15 = make_matrix< T >(1_CS, 3_RD, {{0}, {1}, {2}}, maker::eigen);
	auto m16 = make_vector< T >(3_RD, {0, 1, 2}, maker::eigen);
	auto m17 = make_matrix(1_CS, 3_RS, ref_i, maker::eigen);
	auto m18 = make_vector(3_RS, ref_i_vec, maker::eigen);
	auto m19 = make_matrix(1_CS, 3_RD, ref_i, maker::eigen);
	auto m20 = make_vector(3_RD, ref_i_vec, maker::eigen);

	auto m21 = make_matrix_fn(1_CS, 3_RS, fn_xy, maker::eigen);
	auto m22 = make_vector_fn(3_RS, fn_i, maker::eigen);
	auto m23 = make_matrix_fn(1_CS, 3_RD, fn_xy, maker::eigen);
	auto m24 = make_vector_fn(3_RD, fn_i, maker::eigen);
	auto m25 = make_matrix_fn(dim_pair(1_CS, 3_RS), fn_xy, maker::eigen);
	auto m26 = make_matrix_fn(dim_pair(1_CS, 3_RD), fn_xy, maker::eigen);

	auto m27 = make_matrix_i(1_CS, 3_RS, init_p, maker::eigen);
	auto m28 = make_vector_i(3_RS, init_p, maker::eigen);
	auto m29 = make_matrix_i(1_CS, 3_RD, init_p, maker::eigen);
	auto m30 = make_vector_i(3_RD, init_p, maker::eigen);
	auto m31 = make_matrix_i(dim_pair(1_CS, 3_RS), init_p, maker::eigen);
	auto m32 = make_matrix_i(dim_pair(1_CS, 3_RD), init_p, maker::eigen);


	BOOST_TEST((rt_id(m01) == id< eigen_matrix< T, 1_C, 3_R > >));
	BOOST_TEST((rt_id(m02) == id< eigen_matrix< T, 1_C, 3_R > >));
	BOOST_TEST((rt_id(m03) == id< eigen_matrix< T, 1_C, 0_R > >));
	BOOST_TEST((rt_id(m04) == id< eigen_matrix< T, 1_C, 0_R > >));
	BOOST_TEST((rt_id(m05) == id< eigen_matrix< T, 1_C, 3_R > >));
	BOOST_TEST((rt_id(m06) == id< eigen_matrix< T, 1_C, 0_R > >));

	BOOST_TEST((rt_id(m07) == id< eigen_matrix< T, 1_C, 3_R > >));
	BOOST_TEST((rt_id(m08) == id< eigen_matrix< T, 1_C, 3_R > >));
	BOOST_TEST((rt_id(m09) == id< eigen_matrix< T, 1_C, 0_R > >));
	BOOST_TEST((rt_id(m10) == id< eigen_matrix< T, 1_C, 0_R > >));
	BOOST_TEST((rt_id(m11) == id< eigen_matrix< T, 1_C, 3_R > >));
	BOOST_TEST((rt_id(m12) == id< eigen_matrix< T, 1_C, 0_R > >));

	BOOST_TEST((rt_id(m13) == id< eigen_matrix< T, 1_C, 3_R > >));
	BOOST_TEST((rt_id(m14) == id< eigen_matrix< T, 1_C, 3_R > >));
	BOOST_TEST((rt_id(m15) == id< eigen_matrix< T, 1_C, 0_R > >));
	BOOST_TEST((rt_id(m16) == id< eigen_matrix< T, 1_C, 0_R > >));
	BOOST_TEST((rt_id(m17) == id< eigen_matrix< T, 1_C, 3_R > >));
	BOOST_TEST((rt_id(m18) == id< eigen_matrix< T, 1_C, 3_R > >));
	BOOST_TEST((rt_id(m19) == id< eigen_matrix< T, 1_C, 0_R > >));
	BOOST_TEST((rt_id(m20) == id< eigen_matrix< T, 1_C, 0_R > >));

	BOOST_TEST((rt_id(m21) == id< eigen_matrix< T, 1_C, 3_R > >));
	BOOST_TEST((rt_id(m22) == id< eigen_matrix< T, 1_C, 3_R > >));
	BOOST_TEST((rt_id(m23) == id< eigen_matrix< T, 1_C, 0_R > >));
	BOOST_TEST((rt_id(m24) == id< eigen_matrix< T, 1_C, 0_R > >));
	BOOST_TEST((rt_id(m25) == id< eigen_matrix< T, 1_C, 3_R > >));
	BOOST_TEST((rt_id(m26) == id< eigen_matrix< T, 1_C, 0_R > >));

	BOOST_TEST((rt_id(m27) == id< eigen_matrix< T, 1_C, 3_R > >));
	BOOST_TEST((rt_id(m28) == id< eigen_matrix< T, 1_C, 3_R > >));
	BOOST_TEST((rt_id(m29) == id< eigen_matrix< T, 1_C, 0_R > >));
	BOOST_TEST((rt_id(m30) == id< eigen_matrix< T, 1_C, 0_R > >));
	BOOST_TEST((rt_id(m31) == id< eigen_matrix< T, 1_C, 3_R > >));
	BOOST_TEST((rt_id(m32) == id< eigen_matrix< T, 1_C, 0_R > >));


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

	BOOST_TEST(check(m27, ref_i));
	BOOST_TEST(check(m28, ref_i));
	BOOST_TEST(check(m29, ref_i));
	BOOST_TEST(check(m30, ref_i));
	BOOST_TEST(check(m31, ref_i));
	BOOST_TEST(check(m32, ref_i));
}

BOOST_AUTO_TEST_CASE_TEMPLATE(test_eigen_matrix_3x1, T, types){
	constexpr T ref_0[1][3] = {{0, 0, 0}};
	constexpr T ref_v[1][3] = {{7, 7, 7}};
	constexpr T ref_i[1][3] = {{0, 1, 2}};
	constexpr T ref_i_vec[3] = {0, 1, 2};
	static constexpr T init_i[3] = {0, 1, 2};
	constexpr auto init_p = mitrax::begin(init_i);
	constexpr T ref_f[1][3] = {{0, 1, 2}};
	constexpr auto fn_xy = fn_xy_t< T >();
	constexpr auto fn_i = fn_y_t< T >();

	auto m01 = make_matrix_v< T >(3_CS, 1_RS, T(), maker::eigen);
	auto m02 = make_vector_v< T >(3_CS, T(), maker::eigen);
	auto m03 = make_matrix_v< T >(3_CD, 1_RS, T(), maker::eigen);
	auto m04 = make_vector_v< T >(3_CD, T(), maker::eigen);
	auto m05 = make_matrix_v< T >(dim_pair(3_CS, 1_RS), T(), maker::eigen);
	auto m06 = make_matrix_v< T >(dim_pair(3_CD, 1_RS), T(), maker::eigen);

	auto m07 = make_matrix_v(3_CS, 1_RS, T(7), maker::eigen);
	auto m08 = make_vector_v(3_CS, T(7), maker::eigen);
	auto m09 = make_matrix_v(3_CD, 1_RS, T(7), maker::eigen);
	auto m10 = make_vector_v(3_CD, T(7), maker::eigen);
	auto m11 = make_matrix_v(dim_pair(3_CS, 1_RS), T(7), maker::eigen);
	auto m12 = make_matrix_v(dim_pair(3_CD, 1_RS), T(7), maker::eigen);

	auto m13 = make_matrix< T >(3_CS, 1_RS, {{0, 1, 2}}, maker::eigen);
	auto m14 = make_vector< T >(3_CS, {0, 1, 2}, maker::eigen);
	auto m15 = make_matrix< T >(3_CD, 1_RS, {{0, 1, 2}}, maker::eigen);
	auto m16 = make_vector< T >(3_CD, {0, 1, 2}, maker::eigen);
	auto m17 = make_matrix(3_CS, 1_RS, ref_i, maker::eigen);
	auto m18 = make_vector(3_CS, ref_i_vec, maker::eigen);
	auto m19 = make_matrix(3_CD, 1_RS, ref_i, maker::eigen);
	auto m20 = make_vector(3_CD, ref_i_vec, maker::eigen);

	auto m21 = make_matrix_fn(3_CS, 1_RS, fn_xy, maker::eigen);
	auto m22 = make_vector_fn(3_CS, fn_i, maker::eigen);
	auto m23 = make_matrix_fn(3_CD, 1_RS, fn_xy, maker::eigen);
	auto m24 = make_vector_fn(3_CD, fn_i, maker::eigen);
	auto m25 = make_matrix_fn(dim_pair(3_CS, 1_RS), fn_xy, maker::eigen);
	auto m26 = make_matrix_fn(dim_pair(3_CD, 1_RS), fn_xy, maker::eigen);

	auto m27 = make_matrix_i(3_CS, 1_RS, init_p, maker::eigen);
	auto m28 = make_vector_i(3_CS, init_p, maker::eigen);
	auto m29 = make_matrix_i(3_CD, 1_RS, init_p, maker::eigen);
	auto m30 = make_vector_i(3_CD, init_p, maker::eigen);
	auto m31 = make_matrix_i(dim_pair(3_CS, 1_RS), init_p, maker::eigen);
	auto m32 = make_matrix_i(dim_pair(3_CD, 1_RS), init_p, maker::eigen);


	BOOST_TEST((rt_id(m01) == id< eigen_matrix< T, 3_C, 1_R > >));
	BOOST_TEST((rt_id(m02) == id< eigen_matrix< T, 3_C, 1_R > >));
	BOOST_TEST((rt_id(m03) == id< eigen_matrix< T, 0_C, 1_R > >));
	BOOST_TEST((rt_id(m04) == id< eigen_matrix< T, 0_C, 1_R > >));
	BOOST_TEST((rt_id(m05) == id< eigen_matrix< T, 3_C, 1_R > >));
	BOOST_TEST((rt_id(m06) == id< eigen_matrix< T, 0_C, 1_R > >));

	BOOST_TEST((rt_id(m07) == id< eigen_matrix< T, 3_C, 1_R > >));
	BOOST_TEST((rt_id(m08) == id< eigen_matrix< T, 3_C, 1_R > >));
	BOOST_TEST((rt_id(m09) == id< eigen_matrix< T, 0_C, 1_R > >));
	BOOST_TEST((rt_id(m10) == id< eigen_matrix< T, 0_C, 1_R > >));
	BOOST_TEST((rt_id(m11) == id< eigen_matrix< T, 3_C, 1_R > >));
	BOOST_TEST((rt_id(m12) == id< eigen_matrix< T, 0_C, 1_R > >));

	BOOST_TEST((rt_id(m13) == id< eigen_matrix< T, 3_C, 1_R > >));
	BOOST_TEST((rt_id(m14) == id< eigen_matrix< T, 3_C, 1_R > >));
	BOOST_TEST((rt_id(m15) == id< eigen_matrix< T, 0_C, 1_R > >));
	BOOST_TEST((rt_id(m16) == id< eigen_matrix< T, 0_C, 1_R > >));
	BOOST_TEST((rt_id(m17) == id< eigen_matrix< T, 3_C, 1_R > >));
	BOOST_TEST((rt_id(m18) == id< eigen_matrix< T, 3_C, 1_R > >));
	BOOST_TEST((rt_id(m19) == id< eigen_matrix< T, 0_C, 1_R > >));
	BOOST_TEST((rt_id(m20) == id< eigen_matrix< T, 0_C, 1_R > >));

	BOOST_TEST((rt_id(m21) == id< eigen_matrix< T, 3_C, 1_R > >));
	BOOST_TEST((rt_id(m22) == id< eigen_matrix< T, 3_C, 1_R > >));
	BOOST_TEST((rt_id(m23) == id< eigen_matrix< T, 0_C, 1_R > >));
	BOOST_TEST((rt_id(m24) == id< eigen_matrix< T, 0_C, 1_R > >));
	BOOST_TEST((rt_id(m25) == id< eigen_matrix< T, 3_C, 1_R > >));
	BOOST_TEST((rt_id(m26) == id< eigen_matrix< T, 0_C, 1_R > >));

	BOOST_TEST((rt_id(m27) == id< eigen_matrix< T, 3_C, 1_R > >));
	BOOST_TEST((rt_id(m28) == id< eigen_matrix< T, 3_C, 1_R > >));
	BOOST_TEST((rt_id(m29) == id< eigen_matrix< T, 0_C, 1_R > >));
	BOOST_TEST((rt_id(m30) == id< eigen_matrix< T, 0_C, 1_R > >));
	BOOST_TEST((rt_id(m31) == id< eigen_matrix< T, 3_C, 1_R > >));
	BOOST_TEST((rt_id(m32) == id< eigen_matrix< T, 0_C, 1_R > >));


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

	BOOST_TEST(check(m27, ref_i));
	BOOST_TEST(check(m28, ref_i));
	BOOST_TEST(check(m29, ref_i));
	BOOST_TEST(check(m30, ref_i));
	BOOST_TEST(check(m31, ref_i));
	BOOST_TEST(check(m32, ref_i));
}

BOOST_AUTO_TEST_CASE_TEMPLATE(test_eigen_matrix_1x1, T, types){
	constexpr T ref_0[1][1] = {{0}};
	constexpr T ref_v[1][1] = {{7}};
	constexpr T ref_i[1][1] = {{0}};
	constexpr T ref_i_vec[1] = {0};
	static constexpr T init_i[1] = {0};
	constexpr auto init_p = mitrax::begin(init_i);
	constexpr T ref_f[1][1] = {{0}};
	constexpr auto fn_xy = fn_xy_t< T >();
	constexpr auto fn_x = fn_x_t< T >();
	constexpr auto fn_y = fn_y_t< T >();

	auto m01 = make_matrix_v< T >(1_CS, 1_RS, T(), maker::eigen);
	auto m02 = make_vector_v< T >(1_CS, T(), maker::eigen);
	auto m03 = make_vector_v< T >(1_RS, T(), maker::eigen);
	auto m04 = make_matrix_v< T >(dim_pair(1_CS, 1_RS), T(), maker::eigen);
	auto m05 = make_matrix_v< T >(1_DS, T(), maker::eigen);

	auto m06 = make_matrix_v(1_CS, 1_RS, T(7), maker::eigen);
	auto m07 = make_vector_v(1_CS, T(7), maker::eigen);
	auto m08 = make_vector_v(1_RS, T(7), maker::eigen);
	auto m09 = make_matrix_v(dim_pair(1_CS, 1_RS), T(7), maker::eigen);
	auto m10 = make_matrix_v(1_DS, T(7), maker::eigen);

	auto m11 = make_matrix< T >(1_CS, 1_RS, {{0}}, maker::eigen);
	auto m12 = make_vector< T >(1_CS, {0}, maker::eigen);
	auto m13 = make_vector< T >(1_RS, {0}, maker::eigen);
	auto m14 = make_matrix< T >(1_DS, {{0}}, maker::eigen);
	auto m15 = make_matrix(1_CS, 1_RS, ref_i, maker::eigen);
	auto m16 = make_vector(1_CS, ref_i_vec, maker::eigen);
	auto m17 = make_vector(1_RS, ref_i_vec, maker::eigen);
	auto m18 = make_matrix(1_DS, ref_i, maker::eigen);

	auto m19 = make_matrix_fn(1_CS, 1_RS, fn_xy, maker::eigen);
	auto m20 = make_vector_fn(1_CS, fn_x, maker::eigen);
	auto m21 = make_vector_fn(1_RS, fn_y, maker::eigen);
	auto m22 = make_matrix_fn(dim_pair(1_CS, 1_RS), fn_xy, maker::eigen);
	auto m23 = make_matrix_fn(1_DS, fn_xy, maker::eigen);

	auto m24 = make_matrix_i(1_CS, 1_RS, init_p, maker::eigen);
	auto m25 = make_vector_i(1_CS, init_p, maker::eigen);
	auto m26 = make_vector_i(1_RS, init_p, maker::eigen);
	auto m27 = make_matrix_i(dim_pair(1_CS, 1_RS), init_p, maker::eigen);
	auto m28 = make_matrix_i(1_DS, init_p, maker::eigen);


	BOOST_TEST((rt_id(m01) == id< eigen_matrix< T, 1_C, 1_R > >));
	BOOST_TEST((rt_id(m02) == id< eigen_matrix< T, 1_C, 1_R > >));
	BOOST_TEST((rt_id(m03) == id< eigen_matrix< T, 1_C, 1_R > >));
	BOOST_TEST((rt_id(m04) == id< eigen_matrix< T, 1_C, 1_R > >));
	BOOST_TEST((rt_id(m05) == id< eigen_matrix< T, 1_C, 1_R > >));

	BOOST_TEST((rt_id(m06) == id< eigen_matrix< T, 1_C, 1_R > >));
	BOOST_TEST((rt_id(m07) == id< eigen_matrix< T, 1_C, 1_R > >));
	BOOST_TEST((rt_id(m08) == id< eigen_matrix< T, 1_C, 1_R > >));
	BOOST_TEST((rt_id(m09) == id< eigen_matrix< T, 1_C, 1_R > >));
	BOOST_TEST((rt_id(m10) == id< eigen_matrix< T, 1_C, 1_R > >));

	BOOST_TEST((rt_id(m11) == id< eigen_matrix< T, 1_C, 1_R > >));
	BOOST_TEST((rt_id(m12) == id< eigen_matrix< T, 1_C, 1_R > >));
	BOOST_TEST((rt_id(m13) == id< eigen_matrix< T, 1_C, 1_R > >));
	BOOST_TEST((rt_id(m14) == id< eigen_matrix< T, 1_C, 1_R > >));
	BOOST_TEST((rt_id(m15) == id< eigen_matrix< T, 1_C, 1_R > >));
	BOOST_TEST((rt_id(m16) == id< eigen_matrix< T, 1_C, 1_R > >));
	BOOST_TEST((rt_id(m17) == id< eigen_matrix< T, 1_C, 1_R > >));
	BOOST_TEST((rt_id(m18) == id< eigen_matrix< T, 1_C, 1_R > >));

	BOOST_TEST((rt_id(m19) == id< eigen_matrix< T, 1_C, 1_R > >));
	BOOST_TEST((rt_id(m20) == id< eigen_matrix< T, 1_C, 1_R > >));
	BOOST_TEST((rt_id(m21) == id< eigen_matrix< T, 1_C, 1_R > >));
	BOOST_TEST((rt_id(m22) == id< eigen_matrix< T, 1_C, 1_R > >));
	BOOST_TEST((rt_id(m23) == id< eigen_matrix< T, 1_C, 1_R > >));

	BOOST_TEST((rt_id(m24) == id< eigen_matrix< T, 1_C, 1_R > >));
	BOOST_TEST((rt_id(m25) == id< eigen_matrix< T, 1_C, 1_R > >));
	BOOST_TEST((rt_id(m26) == id< eigen_matrix< T, 1_C, 1_R > >));
	BOOST_TEST((rt_id(m27) == id< eigen_matrix< T, 1_C, 1_R > >));
	BOOST_TEST((rt_id(m28) == id< eigen_matrix< T, 1_C, 1_R > >));


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

	BOOST_TEST(check(m24, ref_i));
	BOOST_TEST(check(m25, ref_i));
	BOOST_TEST(check(m26, ref_i));
	BOOST_TEST(check(m27, ref_i));
	BOOST_TEST(check(m28, ref_i));
}


BOOST_AUTO_TEST_CASE_TEMPLATE(test_diag_heap_matrix, T, types){
	constexpr T ref_0[3][3] = {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}};
	constexpr T ref_v[3][3] = {{7, 0, 0}, {0, 7, 0}, {0, 0, 7}};
	constexpr T ref_i[3][3] = {{0, 0, 0}, {0, 1, 0}, {0, 0, 2}};
	constexpr T ref_i_vec[3] = {0, 1, 2};
	static constexpr T init_i[3] = {0, 1, 2};
	constexpr auto init_p = mitrax::begin(init_i);
	constexpr T ref_f[3][3] = {{0, 0, 0}, {0, 11, 0}, {0, 0, 22}};
	constexpr auto fn = fn_i_t< T >();

	auto m01 = make_diag_matrix_v< T >(3_DS, T(), maker::eigen);
	auto m02 = make_diag_matrix_v< T >(3_DD, T(), maker::eigen);

	auto m03 = make_diag_matrix_v(3_DS, T(7), maker::eigen);
	auto m04 = make_diag_matrix_v(3_DD, T(7), maker::eigen);

	auto m05 = make_diag_matrix< T >(3_DS, {0, 1, 2}, maker::eigen);
	auto m06 = make_diag_matrix< T >(3_DD, {0, 1, 2}, maker::eigen);
	auto m07 = make_diag_matrix(3_DS, ref_i_vec, maker::eigen);
	auto m08 = make_diag_matrix(3_DD, ref_i_vec, maker::eigen);

	auto m09 = make_diag_matrix_fn(3_DS, fn, maker::eigen);
	auto m10 = make_diag_matrix_fn(3_DD, fn, maker::eigen);

	auto m11 = make_diag_matrix_i(3_DS, init_p, maker::eigen);
	auto m12 = make_diag_matrix_i(3_DD, init_p, maker::eigen);


	BOOST_TEST((rt_id(m01) == id< eigen_matrix< T, 3_C, 3_R > >));
	BOOST_TEST((rt_id(m02) == id< eigen_matrix< T, 0_C, 0_R > >));
	BOOST_TEST((rt_id(m03) == id< eigen_matrix< T, 3_C, 3_R > >));
	BOOST_TEST((rt_id(m04) == id< eigen_matrix< T, 0_C, 0_R > >));
	BOOST_TEST((rt_id(m05) == id< eigen_matrix< T, 3_C, 3_R > >));
	BOOST_TEST((rt_id(m06) == id< eigen_matrix< T, 0_C, 0_R > >));
	BOOST_TEST((rt_id(m07) == id< eigen_matrix< T, 3_C, 3_R > >));
	BOOST_TEST((rt_id(m08) == id< eigen_matrix< T, 0_C, 0_R > >));
	BOOST_TEST((rt_id(m09) == id< eigen_matrix< T, 3_C, 3_R > >));
	BOOST_TEST((rt_id(m10) == id< eigen_matrix< T, 0_C, 0_R > >));
	BOOST_TEST((rt_id(m11) == id< eigen_matrix< T, 3_C, 3_R > >));
	BOOST_TEST((rt_id(m12) == id< eigen_matrix< T, 0_C, 0_R > >));


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
	BOOST_TEST(check(m11, ref_i));
	BOOST_TEST(check(m12, ref_i));
}


BOOST_AUTO_TEST_CASE_TEMPLATE(test_identity_heap_matrix, T, types){
	constexpr T ref_i[3][3] = {{1, 0, 0}, {0, 1, 0}, {0, 0, 1}};

	auto m01 = make_identity_matrix< T >(3_DS, maker::eigen);
	auto m02 = make_identity_matrix< T >(3_DD, maker::eigen);


	BOOST_TEST((rt_id(m01) == id< eigen_matrix< T, 3_C, 3_R > >));
	BOOST_TEST((rt_id(m02) == id< eigen_matrix< T, 0_C, 0_R > >));


	BOOST_TEST(check(m01, ref_i));
	BOOST_TEST(check(m02, ref_i));
}

BOOST_AUTO_TEST_CASE_TEMPLATE(test_default_constructor, T, types){
	eigen_matrix< T, 3_C, 3_R > m01;
	eigen_matrix< T, 3_C, 0_R > m02;
	eigen_matrix< T, 0_C, 3_R > m03;
	eigen_matrix< T, 0_C, 0_R > m04;

	BOOST_TEST((m01.dims() == dim_pair(3_CS, 3_RS)));
	BOOST_TEST((m02.dims() == dim_pair(3_CS, 0_RD)));
	BOOST_TEST((m03.dims() == dim_pair(0_CD, 3_RS)));
	BOOST_TEST((m04.dims() == dim_pair(0_CD, 0_RD)));
}



BOOST_AUTO_TEST_CASE_TEMPLATE(test_copy_constructor_heap, T, types){
	constexpr T ref_i[3][3] = {{0, 1, 2}, {3, 4, 5}, {6, 7, 8}};

	auto m01 = make_matrix(3_CS, 3_RS, ref_i, maker::eigen);
	auto m02 = make_matrix(3_CD, 3_RD, ref_i, maker::eigen);

	auto m03 = m01;
	auto m04 = m02;

	BOOST_TEST((rt_id(m03) == id< eigen_matrix< T, 3_C, 3_R > >));
	BOOST_TEST((rt_id(m04) == id< eigen_matrix< T, 0_C, 0_R > >));


	BOOST_TEST(check(m03, ref_i));
	BOOST_TEST(check(m04, ref_i));
}


BOOST_AUTO_TEST_CASE_TEMPLATE(test_move_constructor_heap, T, types){
	constexpr T ref_i[3][3] = {{0, 1, 2}, {3, 4, 5}, {6, 7, 8}};

	auto m01 = make_matrix(3_CS, 3_RS, ref_i, maker::eigen);
	auto m02 = make_matrix(3_CD, 3_RD, ref_i, maker::eigen);

	auto m03 = std::move(m01);
	auto m04 = std::move(m02);

	BOOST_TEST((rt_id(m03) == id< eigen_matrix< T, 3_C, 3_R > >));
	BOOST_TEST((rt_id(m04) == id< eigen_matrix< T, 0_C, 0_R > >));


	BOOST_TEST(check(m03, ref_i));
	BOOST_TEST(check(m04, ref_i));
}


BOOST_AUTO_TEST_CASE_TEMPLATE(test_copy_assignment_heap, T, types){
	constexpr T ref_i[3][3] = {{0, 1, 2}, {3, 4, 5}, {6, 7, 8}};

	auto m01 = make_matrix(3_CS, 3_RS, ref_i, maker::eigen);
	auto m02 = make_matrix(3_CD, 3_RD, ref_i, maker::eigen);

	auto m03 = make_matrix_v(3_CS, 3_RS, T(), maker::eigen);

	// also assign dimensions
	auto m04 = make_matrix_v(0_CD, 0_RD, T(), maker::eigen);


	m03 = m01;
	m04 = m02;


	BOOST_TEST((rt_id(m03) == id< eigen_matrix< T, 3_C, 3_R > >));
	BOOST_TEST((rt_id(m04) == id< eigen_matrix< T, 0_C, 0_R > >));


	BOOST_TEST(check(m03, ref_i));
	BOOST_TEST(check(m04, ref_i));
}


BOOST_AUTO_TEST_CASE_TEMPLATE(test_move_assignment_heap, T, types){
	constexpr T ref_i[3][3] = {{0, 1, 2}, {3, 4, 5}, {6, 7, 8}};

	auto m01 = make_matrix(3_CS, 3_RS, ref_i, maker::eigen);
	auto m02 = make_matrix(3_CD, 3_RD, ref_i, maker::eigen);

	auto m03 = make_matrix_v(3_CS, 3_RS, T(), maker::eigen);

	// also move dimensions
	auto m04 = make_matrix_v(0_CD, 0_RD, T(), maker::eigen);


	m03 = std::move(m01);
	m04 = std::move(m02);


	BOOST_TEST((rt_id(m03) == id< eigen_matrix< T, 3_C, 3_R > >));
	BOOST_TEST((rt_id(m04) == id< eigen_matrix< T, 0_C, 0_R > >));


	BOOST_TEST(check(m03, ref_i));
	BOOST_TEST(check(m04, ref_i));
}


BOOST_AUTO_TEST_SUITE_END()
