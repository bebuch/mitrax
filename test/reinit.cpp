// -----------------------------------------------------------------------------
// Copyright (c) 2016 Benjamin Buch
//
// https://github.com/bebuch/mitrax
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt)
// -----------------------------------------------------------------------------
#define BOOST_TEST_MODULE mitrax reinit
#include <boost/test/unit_test.hpp>
#include <boost/mpl/list.hpp>

#include <mitrax/make_matrix.hpp>
#include <mitrax/reinit.hpp>

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


BOOST_AUTO_TEST_SUITE(suite_reinit)


using types = boost::mpl::list< int, double, std::complex< float > >;


BOOST_AUTO_TEST_CASE_TEMPLATE(test_std, T, types){
	constexpr T ref_0[3][3] = {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}};
	constexpr T ref_v[3][3] = {{7, 7, 7}, {7, 7, 7}, {7, 7, 7}};
	constexpr T ref_i[3][3] = {{0, 1, 2}, {3, 4, 5}, {6, 7, 8}};
	constexpr T ref_f[3][3] = {{0, 1, 2}, {10, 11, 12}, {20, 21, 22}};
	static constexpr T init_i[9] = {0, 1, 2, 3, 4, 5, 6, 7, 8};
	constexpr auto init_p = mitrax::begin(init_i);
	constexpr auto fn = fn_xy_t< T >();

	auto m1 = make_matrix_v< T >(3_CS, 3_RS);
	auto m2 = make_matrix_v< T >(3_CD, 3_RS);
	auto m3 = make_matrix_v< T >(3_CS, 3_RD);
	auto m4 = make_matrix_v< T >(3_CD, 3_RD);
	auto m5 = make_matrix_v(3_CS, 3_RS, T(), maker::heap);

	BOOST_TEST((check(m1, ref_0)));
	BOOST_TEST((check(m2, ref_0)));
	BOOST_TEST((check(m3, ref_0)));
	BOOST_TEST((check(m4, ref_0)));
	BOOST_TEST((check(m5, ref_0)));

	reinit_v(m1, T(7));
	reinit_v(m2, T(7));
	reinit_v(m3, T(7));
	reinit_v(m4, T(7));
	reinit_v(m5, T(7));

	BOOST_TEST((check(m1, ref_v)));
	BOOST_TEST((check(m2, ref_v)));
	BOOST_TEST((check(m3, ref_v)));
	BOOST_TEST((check(m4, ref_v)));
	BOOST_TEST((check(m5, ref_v)));

	reinit_fn(m1, fn);
	reinit_fn(m2, fn);
	reinit_fn(m3, fn);
	reinit_fn(m4, fn);
	reinit_fn(m5, fn);

	BOOST_TEST((check(m1, ref_f)));
	BOOST_TEST((check(m2, ref_f)));
	BOOST_TEST((check(m3, ref_f)));
	BOOST_TEST((check(m4, ref_f)));
	BOOST_TEST((check(m5, ref_f)));

	reinit_iter(m1, init_p);
	reinit_iter(m2, init_p);
	reinit_iter(m3, init_p);
	reinit_iter(m4, init_p);
	reinit_iter(m5, init_p);

	BOOST_TEST((check(m1, ref_i)));
	BOOST_TEST((check(m2, ref_i)));
	BOOST_TEST((check(m3, ref_i)));
	BOOST_TEST((check(m4, ref_i)));
	BOOST_TEST((check(m5, ref_i)));
}


BOOST_AUTO_TEST_CASE_TEMPLATE(test_ct, T, types){
	constexpr T ref_i[3][3] = {{0, 1, 2}, {3, 4, 5}, {6, 7, 8}};
	constexpr T ref_v[3][3] = {{7, 7, 7}, {7, 7, 7}, {7, 7, 7}};

	auto m1 = make_matrix_v< T >(3_CS, 3_RS);
	auto m2 = make_matrix_v(3_CS, 3_RS, T(), maker::heap);

	reinit(m1, {{0, 1, 2}, {3, 4, 5}, {6, 7, 8}});
	reinit(m2, {{0, 1, 2}, {3, 4, 5}, {6, 7, 8}});

	BOOST_TEST((check(m1, ref_i)));
	BOOST_TEST((check(m2, ref_i)));

	reinit_v(m1, T(7));
	reinit_v(m2, T(7));

	BOOST_TEST((check(m1, ref_v)));
	BOOST_TEST((check(m2, ref_v)));

	reinit(m1, ref_i);
	reinit(m2, ref_i);

	BOOST_TEST((check(m1, ref_i)));
	BOOST_TEST((check(m2, ref_i)));
}

BOOST_AUTO_TEST_CASE_TEMPLATE(test_vector, T, types){
	constexpr T ref_i[3] = {0, 1, 2};
	constexpr T ref_f_c[3][1] = {{0}, {11}, {22}};
	constexpr T ref_f_r[1][3] = {{0, 11, 22}};
	constexpr T ref_i_c[3][1] = {{0}, {1}, {2}};
	constexpr T ref_i_r[1][3] = {{0, 1, 2}};
	constexpr T ref_v_c[3][1] = {{7}, {7}, {7}};
	constexpr T ref_v_r[1][3] = {{7, 7, 7}};
	constexpr auto fn = fn_i_t< T >();

	auto mc1 = make_vector_v< T >(3_RS);
	auto mc2 = make_vector_v(3_RS, T(), maker::heap);
	auto mr1 = make_vector_v< T >(3_CS);
	auto mr2 = make_vector_v(3_CS, T(), maker::heap);

	reinit_vector_fn(mc1, fn);
	reinit_vector_fn(mc2, fn);
	reinit_vector_fn(mr1, fn);
	reinit_vector_fn(mr2, fn);

	BOOST_TEST((check(mc1, ref_f_c)));
	BOOST_TEST((check(mc2, ref_f_c)));
	BOOST_TEST((check(mr1, ref_f_r)));
	BOOST_TEST((check(mr2, ref_f_r)));

	reinit_v(mc1, T(7));
	reinit_v(mc2, T(7));
	reinit_v(mr1, T(7));
	reinit_v(mr2, T(7));

	BOOST_TEST((check(mc1, ref_v_c)));
	BOOST_TEST((check(mc2, ref_v_c)));
	BOOST_TEST((check(mr1, ref_v_r)));
	BOOST_TEST((check(mr2, ref_v_r)));

	reinit_vector(mc1, {0, 1, 2});
	reinit_vector(mc2, {0, 1, 2});
	reinit_vector(mr1, {0, 1, 2});
	reinit_vector(mr2, {0, 1, 2});

	BOOST_TEST((check(mc1, ref_i_c)));
	BOOST_TEST((check(mc2, ref_i_c)));
	BOOST_TEST((check(mr1, ref_i_r)));
	BOOST_TEST((check(mr2, ref_i_r)));

	reinit_v(mc1, T(7));
	reinit_v(mc2, T(7));
	reinit_v(mr1, T(7));
	reinit_v(mr2, T(7));

	BOOST_TEST((check(mc1, ref_v_c)));
	BOOST_TEST((check(mc2, ref_v_c)));
	BOOST_TEST((check(mr1, ref_v_r)));
	BOOST_TEST((check(mr2, ref_v_r)));

	reinit_vector(mc1, ref_i);
	reinit_vector(mc2, ref_i);
	reinit_vector(mr1, ref_i);
	reinit_vector(mr2, ref_i);

	BOOST_TEST((check(mc1, ref_i_c)));
	BOOST_TEST((check(mc2, ref_i_c)));
	BOOST_TEST((check(mr1, ref_i_r)));
	BOOST_TEST((check(mr2, ref_i_r)));
}


BOOST_AUTO_TEST_SUITE_END()
