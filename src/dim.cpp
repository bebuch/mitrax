//-----------------------------------------------------------------------------
// Copyright (c) 2015 Benjamin Buch
//
// https://github.com/bebuch/mitrax
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt)
//-----------------------------------------------------------------------------
#include <boost/test/unit_test.hpp>

#include <mitrax/dim.hpp>


using boost::typeindex::type_id;
using boost::typeindex::type_id_runtime;
using namespace mitrax;
using namespace mitrax::literals;


BOOST_AUTO_TEST_SUITE(test_suite_dim)


namespace{


	template < typename T >
	auto rt_id(T&& v){
		return type_id_runtime(static_cast< T&& >(v));
	}

	template < typename T >
	auto const id = type_id< T >();


}


BOOST_AUTO_TEST_CASE(test_col_t){
	constexpr auto ct = col_t< 7 >();
	constexpr auto rt = col_t< 0 >(7);

	BOOST_TEST(ct == size_t(7));
	BOOST_TEST(rt == size_t(7));

	BOOST_TEST(rt_id(ct) == (id< col_t< 7 > >));
	BOOST_TEST(rt_id(rt) == (id< col_t< 0 > >));

	BOOST_TEST(ct.init() == size_t(7));
	BOOST_TEST(rt.init() == size_t(7));

	BOOST_TEST(rt_id(ct.init()) == (id< col_init_t< true, 7 > >));
	BOOST_TEST(rt_id(rt.init()) == (id< col_init_t< false, 0 > >));

	BOOST_TEST(ct.as_row() == size_t(7));
	BOOST_TEST(rt.as_row() == size_t(7));

	BOOST_TEST(rt_id(ct.as_row()) == (id< row_t< 7 > >));
	BOOST_TEST(rt_id(rt.as_row()) == (id< row_t< 0 > >));
}

BOOST_AUTO_TEST_CASE(test_row_t){
	constexpr auto ct = row_t< 7 >();
	constexpr auto rt = row_t< 0 >(7);

	BOOST_TEST(ct == size_t(7));
	BOOST_TEST(rt == size_t(7));

	BOOST_TEST(rt_id(ct) == (id< row_t< 7 > >));
	BOOST_TEST(rt_id(rt) == (id< row_t< 0 > >));

	BOOST_TEST(ct.init() == size_t(7));
	BOOST_TEST(rt.init() == size_t(7));

	BOOST_TEST(rt_id(ct.init()) == (id< row_init_t< true, 7 > >));
	BOOST_TEST(rt_id(rt.init()) == (id< row_init_t< false, 0 > >));

	BOOST_TEST(ct.as_col() == size_t(7));
	BOOST_TEST(rt.as_col() == size_t(7));

	BOOST_TEST(rt_id(ct.as_col()) == (id< col_t< 7 > >));
	BOOST_TEST(rt_id(rt.as_col()) == (id< col_t< 0 > >));
}

BOOST_AUTO_TEST_CASE(test_dims_t){
	constexpr auto d11 = dims(4, 7);
	constexpr auto d12 = dims(4, 7_R);
	constexpr auto d13 = dims(4, 7_R_rt);
	constexpr auto d14 = dims(4, rows(7));
	constexpr auto d15 = dims(4, rows< 7 >());
	constexpr auto d16 = dims(4, rows_rt< 7 >());
	constexpr auto d17 = dims(4, row_t< 0 >(7));
	constexpr auto d18 = dims(4, row_t< 7 >());

	constexpr auto d22 = dims(4_C, 7_R);
	constexpr auto d23 = dims(4_C, 7_R_rt);
	constexpr auto d24 = dims(4_C, rows(7));
	constexpr auto d25 = dims(4_C, rows< 7 >());
	constexpr auto d26 = dims(4_C, rows_rt< 7 >());
	constexpr auto d27 = dims(4_C, row_t< 0 >(7));
	constexpr auto d28 = dims(4_C, row_t< 7 >());

	constexpr auto d33 = dims(4_C_rt, 7_R_rt);
	constexpr auto d34 = dims(4_C_rt, rows(7));
	constexpr auto d35 = dims(4_C_rt, rows< 7 >());
	constexpr auto d36 = dims(4_C_rt, rows_rt< 7 >());
	constexpr auto d37 = dims(4_C_rt, row_t< 0 >(7));
	constexpr auto d38 = dims(4_C_rt, row_t< 7 >());

	constexpr auto d44 = dims(cols(4), rows(7));
	constexpr auto d45 = dims(cols(4), rows< 7 >());
	constexpr auto d46 = dims(cols(4), rows_rt< 7 >());
	constexpr auto d47 = dims(cols(4), row_t< 0 >(7));
	constexpr auto d48 = dims(cols(4), row_t< 7 >());

	constexpr auto d55 = dims(cols< 4 >(), rows< 7 >());
	constexpr auto d56 = dims(cols< 4 >(), rows_rt< 7 >());
	constexpr auto d57 = dims(cols< 4 >(), row_t< 0 >(7));
	constexpr auto d58 = dims(cols< 4 >(), row_t< 7 >());

	constexpr auto d66 = dims(cols_rt< 4 >(), rows_rt< 7 >());
	constexpr auto d67 = dims(cols_rt< 4 >(), row_t< 0 >(7));
	constexpr auto d68 = dims(cols_rt< 4 >(), row_t< 7 >());

	constexpr auto d77 = dims(col_t< 0 >(4), row_t< 0 >(7));
	constexpr auto d78 = dims(col_t< 0 >(4), row_t< 7 >());

	constexpr auto d88 = dims(col_t< 4 >(), row_t< 7 >());


	BOOST_TEST(d11.cols() == size_t(4));
	BOOST_TEST(d12.cols() == size_t(4));
	BOOST_TEST(d13.cols() == size_t(4));
	BOOST_TEST(d14.cols() == size_t(4));
	BOOST_TEST(d15.cols() == size_t(4));
	BOOST_TEST(d16.cols() == size_t(4));
	BOOST_TEST(d17.cols() == size_t(4));
	BOOST_TEST(d18.cols() == size_t(4));

	BOOST_TEST(d22.cols() == size_t(4));
	BOOST_TEST(d23.cols() == size_t(4));
	BOOST_TEST(d24.cols() == size_t(4));
	BOOST_TEST(d25.cols() == size_t(4));
	BOOST_TEST(d26.cols() == size_t(4));
	BOOST_TEST(d27.cols() == size_t(4));
	BOOST_TEST(d28.cols() == size_t(4));

	BOOST_TEST(d33.cols() == size_t(4));
	BOOST_TEST(d34.cols() == size_t(4));
	BOOST_TEST(d35.cols() == size_t(4));
	BOOST_TEST(d36.cols() == size_t(4));
	BOOST_TEST(d37.cols() == size_t(4));
	BOOST_TEST(d38.cols() == size_t(4));

	BOOST_TEST(d44.cols() == size_t(4));
	BOOST_TEST(d45.cols() == size_t(4));
	BOOST_TEST(d46.cols() == size_t(4));
	BOOST_TEST(d47.cols() == size_t(4));
	BOOST_TEST(d48.cols() == size_t(4));

	BOOST_TEST(d55.cols() == size_t(4));
	BOOST_TEST(d56.cols() == size_t(4));
	BOOST_TEST(d57.cols() == size_t(4));
	BOOST_TEST(d58.cols() == size_t(4));

	BOOST_TEST(d66.cols() == size_t(4));
	BOOST_TEST(d67.cols() == size_t(4));
	BOOST_TEST(d68.cols() == size_t(4));

	BOOST_TEST(d77.cols() == size_t(4));
	BOOST_TEST(d78.cols() == size_t(4));

	BOOST_TEST(d88.cols() == size_t(4));


	BOOST_TEST(d11.rows() == size_t(7));
	BOOST_TEST(d12.rows() == size_t(7));
	BOOST_TEST(d13.rows() == size_t(7));
	BOOST_TEST(d14.rows() == size_t(7));
	BOOST_TEST(d15.rows() == size_t(7));
	BOOST_TEST(d16.rows() == size_t(7));
	BOOST_TEST(d17.rows() == size_t(7));
	BOOST_TEST(d18.rows() == size_t(7));

	BOOST_TEST(d22.rows() == size_t(7));
	BOOST_TEST(d23.rows() == size_t(7));
	BOOST_TEST(d24.rows() == size_t(7));
	BOOST_TEST(d25.rows() == size_t(7));
	BOOST_TEST(d26.rows() == size_t(7));
	BOOST_TEST(d27.rows() == size_t(7));
	BOOST_TEST(d28.rows() == size_t(7));

	BOOST_TEST(d33.rows() == size_t(7));
	BOOST_TEST(d34.rows() == size_t(7));
	BOOST_TEST(d35.rows() == size_t(7));
	BOOST_TEST(d36.rows() == size_t(7));
	BOOST_TEST(d37.rows() == size_t(7));
	BOOST_TEST(d38.rows() == size_t(7));

	BOOST_TEST(d44.rows() == size_t(7));
	BOOST_TEST(d45.rows() == size_t(7));
	BOOST_TEST(d46.rows() == size_t(7));
	BOOST_TEST(d47.rows() == size_t(7));
	BOOST_TEST(d48.rows() == size_t(7));

	BOOST_TEST(d55.rows() == size_t(7));
	BOOST_TEST(d56.rows() == size_t(7));
	BOOST_TEST(d57.rows() == size_t(7));
	BOOST_TEST(d58.rows() == size_t(7));

	BOOST_TEST(d66.rows() == size_t(7));
	BOOST_TEST(d67.rows() == size_t(7));
	BOOST_TEST(d68.rows() == size_t(7));

	BOOST_TEST(d77.rows() == size_t(7));
	BOOST_TEST(d78.rows() == size_t(7));

	BOOST_TEST(d88.rows() == size_t(7));


	BOOST_TEST(rt_id(d11) == (id< dims_t< 0, 0 > >));
	BOOST_TEST(rt_id(d12) == (id< dims_t< 0, 7 > >));
	BOOST_TEST(rt_id(d13) == (id< dims_t< 0, 0 > >));
	BOOST_TEST(rt_id(d14) == (id< dims_t< 0, 0 > >));
	BOOST_TEST(rt_id(d15) == (id< dims_t< 0, 7 > >));
	BOOST_TEST(rt_id(d16) == (id< dims_t< 0, 0 > >));
	BOOST_TEST(rt_id(d17) == (id< dims_t< 0, 0 > >));
	BOOST_TEST(rt_id(d18) == (id< dims_t< 0, 7 > >));

	BOOST_TEST(rt_id(d22) == (id< dims_t< 4, 7 > >));
	BOOST_TEST(rt_id(d23) == (id< dims_t< 4, 0 > >));
	BOOST_TEST(rt_id(d24) == (id< dims_t< 4, 0 > >));
	BOOST_TEST(rt_id(d25) == (id< dims_t< 4, 7 > >));
	BOOST_TEST(rt_id(d26) == (id< dims_t< 4, 0 > >));
	BOOST_TEST(rt_id(d27) == (id< dims_t< 4, 0 > >));
	BOOST_TEST(rt_id(d28) == (id< dims_t< 4, 7 > >));

	BOOST_TEST(rt_id(d33) == (id< dims_t< 0, 0 > >));
	BOOST_TEST(rt_id(d34) == (id< dims_t< 0, 0 > >));
	BOOST_TEST(rt_id(d35) == (id< dims_t< 0, 7 > >));
	BOOST_TEST(rt_id(d36) == (id< dims_t< 0, 0 > >));
	BOOST_TEST(rt_id(d37) == (id< dims_t< 0, 0 > >));
	BOOST_TEST(rt_id(d38) == (id< dims_t< 0, 7 > >));

	BOOST_TEST(rt_id(d44) == (id< dims_t< 0, 0 > >));
	BOOST_TEST(rt_id(d45) == (id< dims_t< 0, 7 > >));
	BOOST_TEST(rt_id(d46) == (id< dims_t< 0, 0 > >));
	BOOST_TEST(rt_id(d47) == (id< dims_t< 0, 0 > >));
	BOOST_TEST(rt_id(d48) == (id< dims_t< 0, 7 > >));

	BOOST_TEST(rt_id(d55) == (id< dims_t< 4, 7 > >));
	BOOST_TEST(rt_id(d56) == (id< dims_t< 4, 0 > >));
	BOOST_TEST(rt_id(d57) == (id< dims_t< 4, 0 > >));
	BOOST_TEST(rt_id(d58) == (id< dims_t< 4, 7 > >));

	BOOST_TEST(rt_id(d66) == (id< dims_t< 0, 0 > >));
	BOOST_TEST(rt_id(d67) == (id< dims_t< 0, 0 > >));
	BOOST_TEST(rt_id(d68) == (id< dims_t< 0, 7 > >));

	BOOST_TEST(rt_id(d77) == (id< dims_t< 0, 0 > >));
	BOOST_TEST(rt_id(d78) == (id< dims_t< 0, 7 > >));

	BOOST_TEST(rt_id(d88) == (id< dims_t< 4, 7 > >));
}

BOOST_AUTO_TEST_CASE(test_col_init_t){
	BOOST_TEST(rt_id(7_C) == (id< col_init_t< true, 7 > >));
	BOOST_TEST(rt_id(7_C_rt) == (id< col_init_t< false, 7 > >));

	constexpr auto cct = col_init_t< true, 7 >();
	constexpr auto crt = col_init_t< false, 7 >();
	constexpr auto rrt = col_init_t< false, 0 >(7);

	BOOST_TEST(cct == size_t(7));
	BOOST_TEST(crt == size_t(7));
	BOOST_TEST(rrt == size_t(7));

	BOOST_TEST(rt_id(cct) == (id< col_init_t< true, 7 > >));
	BOOST_TEST(rt_id(crt) == (id< col_init_t< false, 7 > >));
	BOOST_TEST(rt_id(rrt) == (id< col_init_t< false, 0 > >));

	BOOST_TEST(cct.get() == size_t(7));
	BOOST_TEST(crt.get() == size_t(7));
	BOOST_TEST(rrt.get() == size_t(7));

	BOOST_TEST(rt_id(cct.get()) == (id< col_t< 7 > >));
	BOOST_TEST(rt_id(crt.get()) == (id< col_t< 0 > >));
	BOOST_TEST(rt_id(rrt.get()) == (id< col_t< 0 > >));

	BOOST_TEST(cct.as_row() == size_t(7));
	BOOST_TEST(crt.as_row() == size_t(7));
	BOOST_TEST(rrt.as_row() == size_t(7));

	BOOST_TEST(rt_id(cct.as_row()) == (id< row_init_t< true, 7 > >));
	BOOST_TEST(rt_id(crt.as_row()) == (id< row_init_t< false, 7 > >));
	BOOST_TEST(rt_id(rrt.as_row()) == (id< row_init_t< false, 0 > >));

	BOOST_TEST(cct.as_dim() == size_t(7));
	BOOST_TEST(crt.as_dim() == size_t(7));
	BOOST_TEST(rrt.as_dim() == size_t(7));

	BOOST_TEST(rt_id(cct.as_dim()) == (id< dim_init_t< true, 7 > >));
	BOOST_TEST(rt_id(crt.as_dim()) == (id< dim_init_t< false, 7 > >));
	BOOST_TEST(rt_id(rrt.as_dim()) == (id< dim_init_t< false, 0 > >));
}

BOOST_AUTO_TEST_CASE(test_row_init_t){
	BOOST_TEST(rt_id(7_R) == (id< row_init_t< true, 7 > >));
	BOOST_TEST(rt_id(7_R_rt) == (id< row_init_t< false, 7 > >));

	constexpr auto cct = row_init_t< true, 7 >();
	constexpr auto crt = row_init_t< false, 7 >();
	constexpr auto rrt = row_init_t< false, 0 >(7);

	BOOST_TEST(cct == size_t(7));
	BOOST_TEST(crt == size_t(7));
	BOOST_TEST(rrt == size_t(7));

	BOOST_TEST(rt_id(cct) == (id< row_init_t< true, 7 > >));
	BOOST_TEST(rt_id(crt) == (id< row_init_t< false, 7 > >));
	BOOST_TEST(rt_id(rrt) == (id< row_init_t< false, 0 > >));

	BOOST_TEST(cct.get() == size_t(7));
	BOOST_TEST(crt.get() == size_t(7));
	BOOST_TEST(rrt.get() == size_t(7));

	BOOST_TEST(rt_id(cct.get()) == (id< row_t< 7 > >));
	BOOST_TEST(rt_id(crt.get()) == (id< row_t< 0 > >));
	BOOST_TEST(rt_id(rrt.get()) == (id< row_t< 0 > >));

	BOOST_TEST(cct.as_col() == size_t(7));
	BOOST_TEST(crt.as_col() == size_t(7));
	BOOST_TEST(rrt.as_col() == size_t(7));

	BOOST_TEST(rt_id(cct.as_col()) == (id< col_init_t< true, 7 > >));
	BOOST_TEST(rt_id(crt.as_col()) == (id< col_init_t< false, 7 > >));
	BOOST_TEST(rt_id(rrt.as_col()) == (id< col_init_t< false, 0 > >));

	BOOST_TEST(cct.as_dim() == size_t(7));
	BOOST_TEST(crt.as_dim() == size_t(7));
	BOOST_TEST(rrt.as_dim() == size_t(7));

	BOOST_TEST(rt_id(cct.as_dim()) == (id< dim_init_t< true, 7 > >));
	BOOST_TEST(rt_id(crt.as_dim()) == (id< dim_init_t< false, 7 > >));
	BOOST_TEST(rt_id(rrt.as_dim()) == (id< dim_init_t< false, 0 > >));
}

BOOST_AUTO_TEST_CASE(test_dim_init_t){
	BOOST_TEST(rt_id(7_D) == (id< dim_init_t< true, 7 > >));
	BOOST_TEST(rt_id(7_D_rt) == (id< dim_init_t< false, 7 > >));

	constexpr auto cct = dim_init_t< true, 7 >();
	constexpr auto crt = dim_init_t< false, 7 >();
	constexpr auto rrt = dim_init_t< false, 0 >(7);

	BOOST_TEST(cct == size_t(7));
	BOOST_TEST(crt == size_t(7));
	BOOST_TEST(rrt == size_t(7));

	BOOST_TEST(rt_id(cct) == (id< dim_init_t< true, 7 > >));
	BOOST_TEST(rt_id(crt) == (id< dim_init_t< false, 7 > >));
	BOOST_TEST(rt_id(rrt) == (id< dim_init_t< false, 0 > >));

	BOOST_TEST((cct.get() == dims(7_C, 7_R)));
	BOOST_TEST((crt.get() == dims(7_C_rt, 7_R_rt)));
	BOOST_TEST((rrt.get() == dims(7_C_rt, 7_R_rt)));

	BOOST_TEST(rt_id(cct.get()) == (id< dims_t< 7, 7 > >));
	BOOST_TEST(rt_id(crt.get()) == (id< dims_t< 0, 0 > >));
	BOOST_TEST(rt_id(rrt.get()) == (id< dims_t< 0, 0 > >));

	BOOST_TEST(cct.as_col() == size_t(7));
	BOOST_TEST(crt.as_col() == size_t(7));
	BOOST_TEST(rrt.as_col() == size_t(7));

	BOOST_TEST(rt_id(cct.as_col()) == (id< col_init_t< true, 7 > >));
	BOOST_TEST(rt_id(crt.as_col()) == (id< col_init_t< false, 7 > >));
	BOOST_TEST(rt_id(rrt.as_col()) == (id< col_init_t< false, 0 > >));

	BOOST_TEST(cct.as_row() == size_t(7));
	BOOST_TEST(crt.as_row() == size_t(7));
	BOOST_TEST(rrt.as_row() == size_t(7));

	BOOST_TEST(rt_id(cct.as_row()) == (id< row_init_t< true, 7 > >));
	BOOST_TEST(rt_id(crt.as_row()) == (id< row_init_t< false, 7 > >));
	BOOST_TEST(rt_id(rrt.as_row()) == (id< row_init_t< false, 0 > >));
}

BOOST_AUTO_TEST_CASE(test_compare_col_t){
	constexpr col_t< 7 > c1{};
	constexpr col_t< 4 > c2{};
	constexpr col_t< 0 > c3{7};
	constexpr col_t< 0 > c4{4};

	BOOST_TEST((c1 == c1));
	BOOST_TEST((c1 != c2));
	BOOST_TEST((c1 == c3));
	BOOST_TEST((c1 != c4));
	BOOST_TEST((c2 != c1));
	BOOST_TEST((c2 == c2));
	BOOST_TEST((c2 != c3));
	BOOST_TEST((c2 == c4));
	BOOST_TEST((c3 == c1));
	BOOST_TEST((c3 != c2));
	BOOST_TEST((c3 == c3));
	BOOST_TEST((c3 != c4));
	BOOST_TEST((c4 != c1));
	BOOST_TEST((c4 == c2));
	BOOST_TEST((c4 != c3));
	BOOST_TEST((c4 == c4));

	BOOST_TEST(!(c1 != c1));
	BOOST_TEST(!(c1 == c2));
	BOOST_TEST(!(c1 != c3));
	BOOST_TEST(!(c1 == c4));
	BOOST_TEST(!(c2 == c1));
	BOOST_TEST(!(c2 != c2));
	BOOST_TEST(!(c2 == c3));
	BOOST_TEST(!(c2 != c4));
	BOOST_TEST(!(c3 != c1));
	BOOST_TEST(!(c3 == c2));
	BOOST_TEST(!(c3 != c3));
	BOOST_TEST(!(c3 == c4));
	BOOST_TEST(!(c4 == c1));
	BOOST_TEST(!(c4 != c2));
	BOOST_TEST(!(c4 == c3));
	BOOST_TEST(!(c4 != c4));
}

BOOST_AUTO_TEST_CASE(test_compare_row_t){
	constexpr row_t< 7 > r1{};
	constexpr row_t< 4 > r2{};
	constexpr row_t< 0 > r3{7};
	constexpr row_t< 0 > r4{4};

	BOOST_TEST((r1 == r1));
	BOOST_TEST((r1 != r2));
	BOOST_TEST((r1 == r3));
	BOOST_TEST((r1 != r4));
	BOOST_TEST((r2 != r1));
	BOOST_TEST((r2 == r2));
	BOOST_TEST((r2 != r3));
	BOOST_TEST((r2 == r4));
	BOOST_TEST((r3 == r1));
	BOOST_TEST((r3 != r2));
	BOOST_TEST((r3 == r3));
	BOOST_TEST((r3 != r4));
	BOOST_TEST((r4 != r1));
	BOOST_TEST((r4 == r2));
	BOOST_TEST((r4 != r3));
	BOOST_TEST((r4 == r4));

	BOOST_TEST(!(r1 != r1));
	BOOST_TEST(!(r1 == r2));
	BOOST_TEST(!(r1 != r3));
	BOOST_TEST(!(r1 == r4));
	BOOST_TEST(!(r2 == r1));
	BOOST_TEST(!(r2 != r2));
	BOOST_TEST(!(r2 == r3));
	BOOST_TEST(!(r2 != r4));
	BOOST_TEST(!(r3 != r1));
	BOOST_TEST(!(r3 == r2));
	BOOST_TEST(!(r3 != r3));
	BOOST_TEST(!(r3 == r4));
	BOOST_TEST(!(r4 == r1));
	BOOST_TEST(!(r4 != r2));
	BOOST_TEST(!(r4 == r3));
	BOOST_TEST(!(r4 != r4));
}

BOOST_AUTO_TEST_CASE(test_compare_dims_t){
	constexpr auto d1 = dims(7_C, 7_R);
	constexpr auto d2 = dims(7_C_rt, 7_R);
	constexpr auto d3 = dims(7_C, 7_R_rt);
	constexpr auto d4 = dims(7_C_rt, 7_R_rt);

	constexpr auto d5 = dims(4_C, 4_R);
	constexpr auto d6 = dims(4_C_rt, 4_R);
	constexpr auto d7 = dims(4_C, 4_R_rt);
	constexpr auto d8 = dims(4_C_rt, 4_R_rt);


	BOOST_TEST((d1 == d1));
	BOOST_TEST((d1 == d2));
	BOOST_TEST((d1 == d3));
	BOOST_TEST((d1 == d4));
// 	BOOST_TEST((d1 != d5));
// 	BOOST_TEST((d1 != d6));
// 	BOOST_TEST((d1 != d7));
	BOOST_TEST((d1 != d8));

	BOOST_TEST((d2 == d1));
	BOOST_TEST((d2 == d2));
	BOOST_TEST((d2 == d3));
	BOOST_TEST((d2 == d4));
// 	BOOST_TEST((d2 != d5));
// 	BOOST_TEST((d2 != d6));
	BOOST_TEST((d2 != d7));
	BOOST_TEST((d2 != d8));

	BOOST_TEST((d3 == d1));
	BOOST_TEST((d3 == d2));
	BOOST_TEST((d3 == d3));
	BOOST_TEST((d3 == d4));
// 	BOOST_TEST((d3 != d5));
	BOOST_TEST((d3 != d6));
// 	BOOST_TEST((d3 != d7));
	BOOST_TEST((d3 != d8));

	BOOST_TEST((d4 == d1));
	BOOST_TEST((d4 == d2));
	BOOST_TEST((d4 == d3));
	BOOST_TEST((d4 == d4));
	BOOST_TEST((d4 != d5));
	BOOST_TEST((d4 != d6));
	BOOST_TEST((d4 != d7));
	BOOST_TEST((d4 != d8));

// 	BOOST_TEST((d5 != d1));
// 	BOOST_TEST((d5 != d2));
// 	BOOST_TEST((d5 != d3));
	BOOST_TEST((d5 != d4));
	BOOST_TEST((d5 == d5));
	BOOST_TEST((d5 == d6));
	BOOST_TEST((d5 == d7));
	BOOST_TEST((d5 == d8));

// 	BOOST_TEST((d6 != d1));
// 	BOOST_TEST((d6 != d2));
	BOOST_TEST((d6 != d3));
	BOOST_TEST((d6 != d4));
	BOOST_TEST((d6 == d5));
	BOOST_TEST((d6 == d6));
	BOOST_TEST((d6 == d7));
	BOOST_TEST((d6 == d8));

// 	BOOST_TEST((d7 != d1));
	BOOST_TEST((d7 != d2));
// 	BOOST_TEST((d7 != d3));
	BOOST_TEST((d7 != d4));
	BOOST_TEST((d7 == d5));
	BOOST_TEST((d7 == d6));
	BOOST_TEST((d7 == d7));
	BOOST_TEST((d7 == d8));

	BOOST_TEST((d8 != d1));
	BOOST_TEST((d8 != d2));
	BOOST_TEST((d8 != d3));
	BOOST_TEST((d8 != d4));
	BOOST_TEST((d8 == d5));
	BOOST_TEST((d8 == d6));
	BOOST_TEST((d8 == d7));
	BOOST_TEST((d8 == d8));


	BOOST_TEST(!(d1 != d1));
	BOOST_TEST(!(d1 != d2));
	BOOST_TEST(!(d1 != d3));
	BOOST_TEST(!(d1 != d4));
// 	BOOST_TEST(!(d1 == d5));
// 	BOOST_TEST(!(d1 == d6));
// 	BOOST_TEST(!(d1 == d7));
	BOOST_TEST(!(d1 == d8));

	BOOST_TEST(!(d2 != d1));
	BOOST_TEST(!(d2 != d2));
	BOOST_TEST(!(d2 != d3));
	BOOST_TEST(!(d2 != d4));
// 	BOOST_TEST(!(d2 == d5));
// 	BOOST_TEST(!(d2 == d6));
	BOOST_TEST(!(d2 == d7));
	BOOST_TEST(!(d2 == d8));

	BOOST_TEST(!(d3 != d1));
	BOOST_TEST(!(d3 != d2));
	BOOST_TEST(!(d3 != d3));
	BOOST_TEST(!(d3 != d4));
// 	BOOST_TEST(!(d3 == d5));
	BOOST_TEST(!(d3 == d6));
// 	BOOST_TEST(!(d3 == d7));
	BOOST_TEST(!(d3 == d8));

	BOOST_TEST(!(d4 != d1));
	BOOST_TEST(!(d4 != d2));
	BOOST_TEST(!(d4 != d3));
	BOOST_TEST(!(d4 != d4));
	BOOST_TEST(!(d4 == d5));
	BOOST_TEST(!(d4 == d6));
	BOOST_TEST(!(d4 == d7));
	BOOST_TEST(!(d4 == d8));

// 	BOOST_TEST(!(d5 == d1));
// 	BOOST_TEST(!(d5 == d2));
// 	BOOST_TEST(!(d5 == d3));
	BOOST_TEST(!(d5 == d4));
	BOOST_TEST(!(d5 != d5));
	BOOST_TEST(!(d5 != d6));
	BOOST_TEST(!(d5 != d7));
	BOOST_TEST(!(d5 != d8));

// 	BOOST_TEST(!(d6 == d1));
// 	BOOST_TEST(!(d6 == d2));
	BOOST_TEST(!(d6 == d3));
	BOOST_TEST(!(d6 == d4));
	BOOST_TEST(!(d6 != d5));
	BOOST_TEST(!(d6 != d6));
	BOOST_TEST(!(d6 != d7));
	BOOST_TEST(!(d6 != d8));

// 	BOOST_TEST(!(d7 == d1));
	BOOST_TEST(!(d7 == d2));
// 	BOOST_TEST(!(d7 == d3));
	BOOST_TEST(!(d7 == d4));
	BOOST_TEST(!(d7 != d5));
	BOOST_TEST(!(d7 != d6));
	BOOST_TEST(!(d7 != d7));
	BOOST_TEST(!(d7 != d8));

	BOOST_TEST(!(d8 == d1));
	BOOST_TEST(!(d8 == d2));
	BOOST_TEST(!(d8 == d3));
	BOOST_TEST(!(d8 == d4));
	BOOST_TEST(!(d8 != d5));
	BOOST_TEST(!(d8 != d6));
	BOOST_TEST(!(d8 != d7));
	BOOST_TEST(!(d8 != d8));
}

BOOST_AUTO_TEST_CASE(test_col_t_operation){
	constexpr auto ct1 = col_t< 9 >();
	constexpr auto ct2 = col_t< 4 >();
	constexpr auto rt1 = col_t< 0 >(9);
	constexpr auto rt2 = col_t< 0 >(4);
// 	constexpr auto ct2 = col_init_t< true, 4 >();
// 	constexpr auto ct2 = col_init_t< false, 4 >();
// 	constexpr auto ct2 = col_init_t< false, 0 >(4);

	BOOST_TEST((ct1 + ct2 == 13));
	BOOST_TEST((ct1 + rt2 == 13));
	BOOST_TEST((rt1 + ct2 == 13));
	BOOST_TEST((rt1 + rt2 == 13));
	BOOST_TEST((ct1 + size_t(4) == 13));
	BOOST_TEST((ct1 + size_t(4) == 13));
	BOOST_TEST((rt1 + size_t(4) == 13));
	BOOST_TEST((rt1 + size_t(4) == 13));
	BOOST_TEST((size_t(9) + ct2 == 13));
	BOOST_TEST((size_t(9) + rt2 == 13));
	BOOST_TEST((size_t(9) + ct2 == 13));
	BOOST_TEST((size_t(9) + rt2 == 13));

	BOOST_TEST((ct1 - ct2 == 5));
	BOOST_TEST((ct1 - rt2 == 5));
	BOOST_TEST((rt1 - ct2 == 5));
	BOOST_TEST((rt1 - rt2 == 5));
	BOOST_TEST((ct1 - size_t(4) == 5));
	BOOST_TEST((ct1 - size_t(4) == 5));
	BOOST_TEST((rt1 - size_t(4) == 5));
	BOOST_TEST((rt1 - size_t(4) == 5));
	BOOST_TEST((size_t(9) - ct2 == 5));
	BOOST_TEST((size_t(9) - rt2 == 5));
	BOOST_TEST((size_t(9) - ct2 == 5));
	BOOST_TEST((size_t(9) - rt2 == 5));

	BOOST_TEST((ct1 * ct2 == 36));
	BOOST_TEST((ct1 * rt2 == 36));
	BOOST_TEST((rt1 * ct2 == 36));
	BOOST_TEST((rt1 * rt2 == 36));
	BOOST_TEST((ct1 * size_t(4) == 36));
	BOOST_TEST((ct1 * size_t(4) == 36));
	BOOST_TEST((rt1 * size_t(4) == 36));
	BOOST_TEST((rt1 * size_t(4) == 36));
	BOOST_TEST((size_t(9) * ct2 == 36));
	BOOST_TEST((size_t(9) * rt2 == 36));
	BOOST_TEST((size_t(9) * ct2 == 36));
	BOOST_TEST((size_t(9) * rt2 == 36));

	BOOST_TEST((ct1 / ct2 == 2));
	BOOST_TEST((ct1 / rt2 == 2));
	BOOST_TEST((rt1 / ct2 == 2));
	BOOST_TEST((rt1 / rt2 == 2));
	BOOST_TEST((ct1 / size_t(4) == 2));
	BOOST_TEST((ct1 / size_t(4) == 2));
	BOOST_TEST((rt1 / size_t(4) == 2));
	BOOST_TEST((rt1 / size_t(4) == 2));
	BOOST_TEST((size_t(9) / ct2 == 2));
	BOOST_TEST((size_t(9) / rt2 == 2));
	BOOST_TEST((size_t(9) / ct2 == 2));
	BOOST_TEST((size_t(9) / rt2 == 2));

	BOOST_TEST((ct1 % ct2 == 1));
	BOOST_TEST((ct1 % rt2 == 1));
	BOOST_TEST((rt1 % ct2 == 1));
	BOOST_TEST((rt1 % rt2 == 1));
	BOOST_TEST((ct1 % size_t(4) == 1));
	BOOST_TEST((ct1 % size_t(4) == 1));
	BOOST_TEST((rt1 % size_t(4) == 1));
	BOOST_TEST((rt1 % size_t(4) == 1));
	BOOST_TEST((size_t(9) % ct2 == 1));
	BOOST_TEST((size_t(9) % rt2 == 1));
	BOOST_TEST((size_t(9) % ct2 == 1));
	BOOST_TEST((size_t(9) % rt2 == 1));
}

BOOST_AUTO_TEST_CASE(test_row_t_operation){
	constexpr auto ct1 = row_t< 9 >();
	constexpr auto ct2 = row_t< 4 >();
	constexpr auto rt1 = row_t< 0 >(9);
	constexpr auto rt2 = row_t< 0 >(4);

	BOOST_TEST((ct1 + ct2 == 13));
	BOOST_TEST((ct1 + rt2 == 13));
	BOOST_TEST((rt1 + ct2 == 13));
	BOOST_TEST((rt1 + rt2 == 13));
	BOOST_TEST((ct1 + size_t(4) == 13));
	BOOST_TEST((ct1 + size_t(4) == 13));
	BOOST_TEST((rt1 + size_t(4) == 13));
	BOOST_TEST((rt1 + size_t(4) == 13));
	BOOST_TEST((size_t(9) + ct2 == 13));
	BOOST_TEST((size_t(9) + rt2 == 13));
	BOOST_TEST((size_t(9) + ct2 == 13));
	BOOST_TEST((size_t(9) + rt2 == 13));

	BOOST_TEST((ct1 - ct2 == 5));
	BOOST_TEST((ct1 - rt2 == 5));
	BOOST_TEST((rt1 - ct2 == 5));
	BOOST_TEST((rt1 - rt2 == 5));
	BOOST_TEST((ct1 - size_t(4) == 5));
	BOOST_TEST((ct1 - size_t(4) == 5));
	BOOST_TEST((rt1 - size_t(4) == 5));
	BOOST_TEST((rt1 - size_t(4) == 5));
	BOOST_TEST((size_t(9) - ct2 == 5));
	BOOST_TEST((size_t(9) - rt2 == 5));
	BOOST_TEST((size_t(9) - ct2 == 5));
	BOOST_TEST((size_t(9) - rt2 == 5));

	BOOST_TEST((ct1 * ct2 == 36));
	BOOST_TEST((ct1 * rt2 == 36));
	BOOST_TEST((rt1 * ct2 == 36));
	BOOST_TEST((rt1 * rt2 == 36));
	BOOST_TEST((ct1 * size_t(4) == 36));
	BOOST_TEST((ct1 * size_t(4) == 36));
	BOOST_TEST((rt1 * size_t(4) == 36));
	BOOST_TEST((rt1 * size_t(4) == 36));
	BOOST_TEST((size_t(9) * ct2 == 36));
	BOOST_TEST((size_t(9) * rt2 == 36));
	BOOST_TEST((size_t(9) * ct2 == 36));
	BOOST_TEST((size_t(9) * rt2 == 36));

	BOOST_TEST((ct1 / ct2 == 2));
	BOOST_TEST((ct1 / rt2 == 2));
	BOOST_TEST((rt1 / ct2 == 2));
	BOOST_TEST((rt1 / rt2 == 2));
	BOOST_TEST((ct1 / size_t(4) == 2));
	BOOST_TEST((ct1 / size_t(4) == 2));
	BOOST_TEST((rt1 / size_t(4) == 2));
	BOOST_TEST((rt1 / size_t(4) == 2));
	BOOST_TEST((size_t(9) / ct2 == 2));
	BOOST_TEST((size_t(9) / rt2 == 2));
	BOOST_TEST((size_t(9) / ct2 == 2));
	BOOST_TEST((size_t(9) / rt2 == 2));

	BOOST_TEST((ct1 % ct2 == 1));
	BOOST_TEST((ct1 % rt2 == 1));
	BOOST_TEST((rt1 % ct2 == 1));
	BOOST_TEST((rt1 % rt2 == 1));
	BOOST_TEST((ct1 % size_t(4) == 1));
	BOOST_TEST((ct1 % size_t(4) == 1));
	BOOST_TEST((rt1 % size_t(4) == 1));
	BOOST_TEST((rt1 % size_t(4) == 1));
	BOOST_TEST((size_t(9) % ct2 == 1));
	BOOST_TEST((size_t(9) % rt2 == 1));
	BOOST_TEST((size_t(9) % ct2 == 1));
	BOOST_TEST((size_t(9) % rt2 == 1));
}

BOOST_AUTO_TEST_CASE(
	test_dims_t_operation,
	*boost::unit_test::depends_on("test_suite_dim/test_compare_dims_t")
){
	constexpr auto d11 = dims(9_C, 9_R);
	constexpr auto d12 = dims(9_C_rt, 9_R);
	constexpr auto d13 = dims(9_C, 9_R_rt);
	constexpr auto d14 = dims(9_C_rt, 9_R_rt);

	constexpr auto d21 = dims(4_C, 4_R);
	constexpr auto d22 = dims(4_C_rt, 4_R);
	constexpr auto d23 = dims(4_C, 4_R_rt);
	constexpr auto d24 = dims(4_C_rt, 4_R_rt);

	BOOST_TEST((d11 + d21 == dims(13_C, 13_R)));
	BOOST_TEST((d11 + d22 == dims(13_C, 13_R)));
	BOOST_TEST((d11 + d23 == dims(13_C, 13_R)));
	BOOST_TEST((d11 + d24 == dims(13_C, 13_R)));
	BOOST_TEST((d12 + d21 == dims(13_C, 13_R)));
	BOOST_TEST((d12 + d22 == dims(13_C, 13_R)));
	BOOST_TEST((d12 + d23 == dims(13_C, 13_R)));
	BOOST_TEST((d12 + d24 == dims(13_C, 13_R)));
	BOOST_TEST((d13 + d21 == dims(13_C, 13_R)));
	BOOST_TEST((d13 + d22 == dims(13_C, 13_R)));
	BOOST_TEST((d13 + d23 == dims(13_C, 13_R)));
	BOOST_TEST((d13 + d24 == dims(13_C, 13_R)));
	BOOST_TEST((d14 + d21 == dims(13_C, 13_R)));
	BOOST_TEST((d14 + d22 == dims(13_C, 13_R)));
	BOOST_TEST((d14 + d23 == dims(13_C, 13_R)));
	BOOST_TEST((d14 + d24 == dims(13_C, 13_R)));

	BOOST_TEST(rt_id(d11 + d21) == (id< dims_t< 13, 13 > >));
	BOOST_TEST(rt_id(d11 + d22) == (id< dims_t<  0, 13 > >));
	BOOST_TEST(rt_id(d11 + d23) == (id< dims_t< 13,  0 > >));
	BOOST_TEST(rt_id(d11 + d24) == (id< dims_t<  0,  0 > >));
	BOOST_TEST(rt_id(d12 + d21) == (id< dims_t<  0, 13 > >));
	BOOST_TEST(rt_id(d12 + d22) == (id< dims_t<  0, 13 > >));
	BOOST_TEST(rt_id(d12 + d23) == (id< dims_t<  0,  0 > >));
	BOOST_TEST(rt_id(d12 + d24) == (id< dims_t<  0,  0 > >));
	BOOST_TEST(rt_id(d13 + d21) == (id< dims_t< 13,  0 > >));
	BOOST_TEST(rt_id(d13 + d22) == (id< dims_t<  0,  0 > >));
	BOOST_TEST(rt_id(d13 + d23) == (id< dims_t< 13,  0 > >));
	BOOST_TEST(rt_id(d13 + d24) == (id< dims_t<  0,  0 > >));
	BOOST_TEST(rt_id(d14 + d21) == (id< dims_t<  0,  0 > >));
	BOOST_TEST(rt_id(d14 + d22) == (id< dims_t<  0,  0 > >));
	BOOST_TEST(rt_id(d14 + d23) == (id< dims_t<  0,  0 > >));
	BOOST_TEST(rt_id(d14 + d24) == (id< dims_t<  0,  0 > >));

	BOOST_TEST((d11 - d21 == dims(5_C, 5_R)));
	BOOST_TEST((d11 - d22 == dims(5_C, 5_R)));
	BOOST_TEST((d11 - d23 == dims(5_C, 5_R)));
	BOOST_TEST((d11 - d24 == dims(5_C, 5_R)));
	BOOST_TEST((d12 - d21 == dims(5_C, 5_R)));
	BOOST_TEST((d12 - d22 == dims(5_C, 5_R)));
	BOOST_TEST((d12 - d23 == dims(5_C, 5_R)));
	BOOST_TEST((d12 - d24 == dims(5_C, 5_R)));
	BOOST_TEST((d13 - d21 == dims(5_C, 5_R)));
	BOOST_TEST((d13 - d22 == dims(5_C, 5_R)));
	BOOST_TEST((d13 - d23 == dims(5_C, 5_R)));
	BOOST_TEST((d13 - d24 == dims(5_C, 5_R)));
	BOOST_TEST((d14 - d21 == dims(5_C, 5_R)));
	BOOST_TEST((d14 - d22 == dims(5_C, 5_R)));
	BOOST_TEST((d14 - d23 == dims(5_C, 5_R)));
	BOOST_TEST((d14 - d24 == dims(5_C, 5_R)));

	BOOST_TEST(rt_id(d11 - d21) == (id< dims_t< 5, 5 > >));
	BOOST_TEST(rt_id(d11 - d22) == (id< dims_t< 0, 5 > >));
	BOOST_TEST(rt_id(d11 - d23) == (id< dims_t< 5, 0 > >));
	BOOST_TEST(rt_id(d11 - d24) == (id< dims_t< 0, 0 > >));
	BOOST_TEST(rt_id(d12 - d21) == (id< dims_t< 0, 5 > >));
	BOOST_TEST(rt_id(d12 - d22) == (id< dims_t< 0, 5 > >));
	BOOST_TEST(rt_id(d12 - d23) == (id< dims_t< 0, 0 > >));
	BOOST_TEST(rt_id(d12 - d24) == (id< dims_t< 0, 0 > >));
	BOOST_TEST(rt_id(d13 - d21) == (id< dims_t< 5, 0 > >));
	BOOST_TEST(rt_id(d13 - d22) == (id< dims_t< 0, 0 > >));
	BOOST_TEST(rt_id(d13 - d23) == (id< dims_t< 5, 0 > >));
	BOOST_TEST(rt_id(d13 - d24) == (id< dims_t< 0, 0 > >));
	BOOST_TEST(rt_id(d14 - d21) == (id< dims_t< 0, 0 > >));
	BOOST_TEST(rt_id(d14 - d22) == (id< dims_t< 0, 0 > >));
	BOOST_TEST(rt_id(d14 - d23) == (id< dims_t< 0, 0 > >));
	BOOST_TEST(rt_id(d14 - d24) == (id< dims_t< 0, 0 > >));

	BOOST_TEST((d11 * d21 == dims(36_C, 36_R)));
	BOOST_TEST((d11 * d22 == dims(36_C, 36_R)));
	BOOST_TEST((d11 * d23 == dims(36_C, 36_R)));
	BOOST_TEST((d11 * d24 == dims(36_C, 36_R)));
	BOOST_TEST((d12 * d21 == dims(36_C, 36_R)));
	BOOST_TEST((d12 * d22 == dims(36_C, 36_R)));
	BOOST_TEST((d12 * d23 == dims(36_C, 36_R)));
	BOOST_TEST((d12 * d24 == dims(36_C, 36_R)));
	BOOST_TEST((d13 * d21 == dims(36_C, 36_R)));
	BOOST_TEST((d13 * d22 == dims(36_C, 36_R)));
	BOOST_TEST((d13 * d23 == dims(36_C, 36_R)));
	BOOST_TEST((d13 * d24 == dims(36_C, 36_R)));
	BOOST_TEST((d14 * d21 == dims(36_C, 36_R)));
	BOOST_TEST((d14 * d22 == dims(36_C, 36_R)));
	BOOST_TEST((d14 * d23 == dims(36_C, 36_R)));
	BOOST_TEST((d14 * d24 == dims(36_C, 36_R)));

	BOOST_TEST(rt_id(d11 * d21) == (id< dims_t< 36, 36 > >));
	BOOST_TEST(rt_id(d11 * d22) == (id< dims_t<  0, 36 > >));
	BOOST_TEST(rt_id(d11 * d23) == (id< dims_t< 36,  0 > >));
	BOOST_TEST(rt_id(d11 * d24) == (id< dims_t<  0,  0 > >));
	BOOST_TEST(rt_id(d12 * d21) == (id< dims_t<  0, 36 > >));
	BOOST_TEST(rt_id(d12 * d22) == (id< dims_t<  0, 36 > >));
	BOOST_TEST(rt_id(d12 * d23) == (id< dims_t<  0,  0 > >));
	BOOST_TEST(rt_id(d12 * d24) == (id< dims_t<  0,  0 > >));
	BOOST_TEST(rt_id(d13 * d21) == (id< dims_t< 36,  0 > >));
	BOOST_TEST(rt_id(d13 * d22) == (id< dims_t<  0,  0 > >));
	BOOST_TEST(rt_id(d13 * d23) == (id< dims_t< 36,  0 > >));
	BOOST_TEST(rt_id(d13 * d24) == (id< dims_t<  0,  0 > >));
	BOOST_TEST(rt_id(d14 * d21) == (id< dims_t<  0,  0 > >));
	BOOST_TEST(rt_id(d14 * d22) == (id< dims_t<  0,  0 > >));
	BOOST_TEST(rt_id(d14 * d23) == (id< dims_t<  0,  0 > >));
	BOOST_TEST(rt_id(d14 * d24) == (id< dims_t<  0,  0 > >));

	BOOST_TEST((d11 / d21 == dims(2_C, 2_R)));
	BOOST_TEST((d11 / d22 == dims(2_C, 2_R)));
	BOOST_TEST((d11 / d23 == dims(2_C, 2_R)));
	BOOST_TEST((d11 / d24 == dims(2_C, 2_R)));
	BOOST_TEST((d12 / d21 == dims(2_C, 2_R)));
	BOOST_TEST((d12 / d22 == dims(2_C, 2_R)));
	BOOST_TEST((d12 / d23 == dims(2_C, 2_R)));
	BOOST_TEST((d12 / d24 == dims(2_C, 2_R)));
	BOOST_TEST((d13 / d21 == dims(2_C, 2_R)));
	BOOST_TEST((d13 / d22 == dims(2_C, 2_R)));
	BOOST_TEST((d13 / d23 == dims(2_C, 2_R)));
	BOOST_TEST((d13 / d24 == dims(2_C, 2_R)));
	BOOST_TEST((d14 / d21 == dims(2_C, 2_R)));
	BOOST_TEST((d14 / d22 == dims(2_C, 2_R)));
	BOOST_TEST((d14 / d23 == dims(2_C, 2_R)));
	BOOST_TEST((d14 / d24 == dims(2_C, 2_R)));

	BOOST_TEST(rt_id(d11 / d21) == (id< dims_t< 2, 2 > >));
	BOOST_TEST(rt_id(d11 / d22) == (id< dims_t< 0, 2 > >));
	BOOST_TEST(rt_id(d11 / d23) == (id< dims_t< 2, 0 > >));
	BOOST_TEST(rt_id(d11 / d24) == (id< dims_t< 0, 0 > >));
	BOOST_TEST(rt_id(d12 / d21) == (id< dims_t< 0, 2 > >));
	BOOST_TEST(rt_id(d12 / d22) == (id< dims_t< 0, 2 > >));
	BOOST_TEST(rt_id(d12 / d23) == (id< dims_t< 0, 0 > >));
	BOOST_TEST(rt_id(d12 / d24) == (id< dims_t< 0, 0 > >));
	BOOST_TEST(rt_id(d13 / d21) == (id< dims_t< 2, 0 > >));
	BOOST_TEST(rt_id(d13 / d22) == (id< dims_t< 0, 0 > >));
	BOOST_TEST(rt_id(d13 / d23) == (id< dims_t< 2, 0 > >));
	BOOST_TEST(rt_id(d13 / d24) == (id< dims_t< 0, 0 > >));
	BOOST_TEST(rt_id(d14 / d21) == (id< dims_t< 0, 0 > >));
	BOOST_TEST(rt_id(d14 / d22) == (id< dims_t< 0, 0 > >));
	BOOST_TEST(rt_id(d14 / d23) == (id< dims_t< 0, 0 > >));
	BOOST_TEST(rt_id(d14 / d24) == (id< dims_t< 0, 0 > >));

	BOOST_TEST((d11 % d21 == dims(1_C, 1_R)));
	BOOST_TEST((d11 % d22 == dims(1_C, 1_R)));
	BOOST_TEST((d11 % d23 == dims(1_C, 1_R)));
	BOOST_TEST((d11 % d24 == dims(1_C, 1_R)));
	BOOST_TEST((d12 % d21 == dims(1_C, 1_R)));
	BOOST_TEST((d12 % d22 == dims(1_C, 1_R)));
	BOOST_TEST((d12 % d23 == dims(1_C, 1_R)));
	BOOST_TEST((d12 % d24 == dims(1_C, 1_R)));
	BOOST_TEST((d13 % d21 == dims(1_C, 1_R)));
	BOOST_TEST((d13 % d22 == dims(1_C, 1_R)));
	BOOST_TEST((d13 % d23 == dims(1_C, 1_R)));
	BOOST_TEST((d13 % d24 == dims(1_C, 1_R)));
	BOOST_TEST((d14 % d21 == dims(1_C, 1_R)));
	BOOST_TEST((d14 % d22 == dims(1_C, 1_R)));
	BOOST_TEST((d14 % d23 == dims(1_C, 1_R)));
	BOOST_TEST((d14 % d24 == dims(1_C, 1_R)));

	BOOST_TEST(rt_id(d11 % d21) == (id< dims_t< 1, 1 > >));
	BOOST_TEST(rt_id(d11 % d22) == (id< dims_t< 0, 1 > >));
	BOOST_TEST(rt_id(d11 % d23) == (id< dims_t< 1, 0 > >));
	BOOST_TEST(rt_id(d11 % d24) == (id< dims_t< 0, 0 > >));
	BOOST_TEST(rt_id(d12 % d21) == (id< dims_t< 0, 1 > >));
	BOOST_TEST(rt_id(d12 % d22) == (id< dims_t< 0, 1 > >));
	BOOST_TEST(rt_id(d12 % d23) == (id< dims_t< 0, 0 > >));
	BOOST_TEST(rt_id(d12 % d24) == (id< dims_t< 0, 0 > >));
	BOOST_TEST(rt_id(d13 % d21) == (id< dims_t< 1, 0 > >));
	BOOST_TEST(rt_id(d13 % d22) == (id< dims_t< 0, 0 > >));
	BOOST_TEST(rt_id(d13 % d23) == (id< dims_t< 1, 0 > >));
	BOOST_TEST(rt_id(d13 % d24) == (id< dims_t< 0, 0 > >));
	BOOST_TEST(rt_id(d14 % d21) == (id< dims_t< 0, 0 > >));
	BOOST_TEST(rt_id(d14 % d22) == (id< dims_t< 0, 0 > >));
	BOOST_TEST(rt_id(d14 % d23) == (id< dims_t< 0, 0 > >));
	BOOST_TEST(rt_id(d14 % d24) == (id< dims_t< 0, 0 > >));

	BOOST_TEST((d11 * 4 == dims(36_C, 36_R)));
	BOOST_TEST((d11 * 4 == dims(36_C, 36_R)));
	BOOST_TEST((d11 * 4 == dims(36_C, 36_R)));
	BOOST_TEST((d11 * 4 == dims(36_C, 36_R)));

	BOOST_TEST(rt_id(d11 * 4) == (id< dims_t< 0, 0 > >));
	BOOST_TEST(rt_id(d12 * 4) == (id< dims_t< 0, 0 > >));
	BOOST_TEST(rt_id(d13 * 4) == (id< dims_t< 0, 0 > >));
	BOOST_TEST(rt_id(d14 * 4) == (id< dims_t< 0, 0 > >));

	BOOST_TEST((d11 / 4 == dims(2_C, 2_R)));
	BOOST_TEST((d11 / 4 == dims(2_C, 2_R)));
	BOOST_TEST((d11 / 4 == dims(2_C, 2_R)));
	BOOST_TEST((d11 / 4 == dims(2_C, 2_R)));

	BOOST_TEST(rt_id(d11 / 4) == (id< dims_t< 0, 0 > >));
	BOOST_TEST(rt_id(d12 / 4) == (id< dims_t< 0, 0 > >));
	BOOST_TEST(rt_id(d13 / 4) == (id< dims_t< 0, 0 > >));
	BOOST_TEST(rt_id(d14 / 4) == (id< dims_t< 0, 0 > >));

	BOOST_TEST((d11 % 4 == dims(1_C, 1_R)));
	BOOST_TEST((d11 % 4 == dims(1_C, 1_R)));
	BOOST_TEST((d11 % 4 == dims(1_C, 1_R)));
	BOOST_TEST((d11 % 4 == dims(1_C, 1_R)));

	BOOST_TEST(rt_id(d11 % 4) == (id< dims_t< 0, 0 > >));
	BOOST_TEST(rt_id(d12 % 4) == (id< dims_t< 0, 0 > >));
	BOOST_TEST(rt_id(d13 % 4) == (id< dims_t< 0, 0 > >));
	BOOST_TEST(rt_id(d14 % 4) == (id< dims_t< 0, 0 > >));
}


BOOST_AUTO_TEST_CASE(test_get_cols_init){
	constexpr auto d1 = 7_C;
	constexpr auto d2 = 7_C_rt;
	constexpr auto d3 = cols(7);

	constexpr auto res01 = get(d1);
	constexpr auto res02 = get(d2);
	constexpr auto res03 = get(d3);
	constexpr auto res04 = get(d1, d1);
	constexpr auto res05 = get(d2, d2);
	constexpr auto res06 = get(d3, d3);
	constexpr auto res07 = get(d1, d2);
	constexpr auto res08 = get(d1, d3);
	constexpr auto res09 = get(d2, d1);
	constexpr auto res10 = get(d2, d3);
	constexpr auto res11 = get(d3, d1);
	constexpr auto res12 = get(d3, d2);
	constexpr auto res13 = get(d1, d1, d1);
	constexpr auto res14 = get(d2, d2, d2);
	constexpr auto res15 = get(d3, d3, d3);
	constexpr auto res16 = get(d1, d2, d1);
	constexpr auto res17 = get(d1, d2, d2);
	constexpr auto res18 = get(d1, d2, d3);
	constexpr auto res19 = get(d1, d3, d1);
	constexpr auto res20 = get(d1, d3, d2);
	constexpr auto res21 = get(d1, d3, d3);
	constexpr auto res22 = get(d2, d1, d1);
	constexpr auto res23 = get(d2, d1, d2);
	constexpr auto res24 = get(d2, d1, d3);
	constexpr auto res25 = get(d2, d3, d1);
	constexpr auto res26 = get(d2, d3, d2);
	constexpr auto res27 = get(d2, d3, d3);
	constexpr auto res28 = get(d3, d1, d1);
	constexpr auto res29 = get(d3, d1, d2);
	constexpr auto res30 = get(d3, d1, d3);
	constexpr auto res31 = get(d3, d2, d1);
	constexpr auto res32 = get(d3, d2, d2);
	constexpr auto res33 = get(d3, d2, d3);

	BOOST_TEST(res01 == size_t(7));
	BOOST_TEST(res02 == size_t(7));
	BOOST_TEST(res03 == size_t(7));
	BOOST_TEST(res04 == size_t(7));
	BOOST_TEST(res05 == size_t(7));
	BOOST_TEST(res06 == size_t(7));
	BOOST_TEST(res07 == size_t(7));
	BOOST_TEST(res08 == size_t(7));
	BOOST_TEST(res09 == size_t(7));
	BOOST_TEST(res10 == size_t(7));
	BOOST_TEST(res11 == size_t(7));
	BOOST_TEST(res12 == size_t(7));
	BOOST_TEST(res13 == size_t(7));
	BOOST_TEST(res14 == size_t(7));
	BOOST_TEST(res15 == size_t(7));
	BOOST_TEST(res16 == size_t(7));
	BOOST_TEST(res17 == size_t(7));
	BOOST_TEST(res18 == size_t(7));
	BOOST_TEST(res19 == size_t(7));
	BOOST_TEST(res20 == size_t(7));
	BOOST_TEST(res21 == size_t(7));
	BOOST_TEST(res22 == size_t(7));
	BOOST_TEST(res23 == size_t(7));
	BOOST_TEST(res24 == size_t(7));
	BOOST_TEST(res25 == size_t(7));
	BOOST_TEST(res26 == size_t(7));
	BOOST_TEST(res27 == size_t(7));
	BOOST_TEST(res28 == size_t(7));
	BOOST_TEST(res29 == size_t(7));
	BOOST_TEST(res30 == size_t(7));
	BOOST_TEST(res31 == size_t(7));
	BOOST_TEST(res32 == size_t(7));
	BOOST_TEST(res33 == size_t(7));

	BOOST_TEST(rt_id(res01) == (id< col_init_t< true, 7 > >));
	BOOST_TEST(rt_id(res02) == (id< col_init_t< false, 7 > >));
	BOOST_TEST(rt_id(res03) == (id< col_init_t< false, 0 > >));
	BOOST_TEST(rt_id(res04) == (id< col_init_t< true, 7 > >));
	BOOST_TEST(rt_id(res05) == (id< col_init_t< false, 7 > >));
	BOOST_TEST(rt_id(res06) == (id< col_init_t< false, 0 > >));
	BOOST_TEST(rt_id(res07) == (id< col_init_t< true, 7 > >));
	BOOST_TEST(rt_id(res08) == (id< col_init_t< true, 7 > >));
	BOOST_TEST(rt_id(res09) == (id< col_init_t< true, 7 > >));
	BOOST_TEST(rt_id(res10) == (id< col_init_t< false, 7 > >));
	BOOST_TEST(rt_id(res11) == (id< col_init_t< true, 7 > >));
	BOOST_TEST(rt_id(res12) == (id< col_init_t< false, 7 > >));
	BOOST_TEST(rt_id(res13) == (id< col_init_t< true, 7 > >));
	BOOST_TEST(rt_id(res14) == (id< col_init_t< false, 7 > >));
	BOOST_TEST(rt_id(res15) == (id< col_init_t< false, 0 > >));
	BOOST_TEST(rt_id(res16) == (id< col_init_t< true, 7 > >));
	BOOST_TEST(rt_id(res17) == (id< col_init_t< true, 7 > >));
	BOOST_TEST(rt_id(res18) == (id< col_init_t< true, 7 > >));
	BOOST_TEST(rt_id(res19) == (id< col_init_t< true, 7 > >));
	BOOST_TEST(rt_id(res20) == (id< col_init_t< true, 7 > >));
	BOOST_TEST(rt_id(res21) == (id< col_init_t< true, 7 > >));
	BOOST_TEST(rt_id(res22) == (id< col_init_t< true, 7 > >));
	BOOST_TEST(rt_id(res23) == (id< col_init_t< true, 7 > >));
	BOOST_TEST(rt_id(res24) == (id< col_init_t< true, 7 > >));
	BOOST_TEST(rt_id(res25) == (id< col_init_t< true, 7 > >));
	BOOST_TEST(rt_id(res26) == (id< col_init_t< false, 7 > >));
	BOOST_TEST(rt_id(res27) == (id< col_init_t< false, 7 > >));
	BOOST_TEST(rt_id(res28) == (id< col_init_t< true, 7 > >));
	BOOST_TEST(rt_id(res29) == (id< col_init_t< true, 7 > >));
	BOOST_TEST(rt_id(res30) == (id< col_init_t< true, 7 > >));
	BOOST_TEST(rt_id(res31) == (id< col_init_t< true, 7 > >));
	BOOST_TEST(rt_id(res32) == (id< col_init_t< false, 7 > >));
	BOOST_TEST(rt_id(res33) == (id< col_init_t< false, 7 > >));
}


BOOST_AUTO_TEST_CASE(test_get_rows_init){
	constexpr auto d1 = 7_R;
	constexpr auto d2 = 7_R_rt;
	constexpr auto d3 = rows(7);

	constexpr auto res01 = get(d1);
	constexpr auto res02 = get(d2);
	constexpr auto res03 = get(d3);
	constexpr auto res04 = get(d1, d1);
	constexpr auto res05 = get(d2, d2);
	constexpr auto res06 = get(d3, d3);
	constexpr auto res07 = get(d1, d2);
	constexpr auto res08 = get(d1, d3);
	constexpr auto res09 = get(d2, d1);
	constexpr auto res10 = get(d2, d3);
	constexpr auto res11 = get(d3, d1);
	constexpr auto res12 = get(d3, d2);
	constexpr auto res13 = get(d1, d1, d1);
	constexpr auto res14 = get(d2, d2, d2);
	constexpr auto res15 = get(d3, d3, d3);
	constexpr auto res16 = get(d1, d2, d1);
	constexpr auto res17 = get(d1, d2, d2);
	constexpr auto res18 = get(d1, d2, d3);
	constexpr auto res19 = get(d1, d3, d1);
	constexpr auto res20 = get(d1, d3, d2);
	constexpr auto res21 = get(d1, d3, d3);
	constexpr auto res22 = get(d2, d1, d1);
	constexpr auto res23 = get(d2, d1, d2);
	constexpr auto res24 = get(d2, d1, d3);
	constexpr auto res25 = get(d2, d3, d1);
	constexpr auto res26 = get(d2, d3, d2);
	constexpr auto res27 = get(d2, d3, d3);
	constexpr auto res28 = get(d3, d1, d1);
	constexpr auto res29 = get(d3, d1, d2);
	constexpr auto res30 = get(d3, d1, d3);
	constexpr auto res31 = get(d3, d2, d1);
	constexpr auto res32 = get(d3, d2, d2);
	constexpr auto res33 = get(d3, d2, d3);

	BOOST_TEST(res01 == size_t(7));
	BOOST_TEST(res02 == size_t(7));
	BOOST_TEST(res03 == size_t(7));
	BOOST_TEST(res04 == size_t(7));
	BOOST_TEST(res05 == size_t(7));
	BOOST_TEST(res06 == size_t(7));
	BOOST_TEST(res07 == size_t(7));
	BOOST_TEST(res08 == size_t(7));
	BOOST_TEST(res09 == size_t(7));
	BOOST_TEST(res10 == size_t(7));
	BOOST_TEST(res11 == size_t(7));
	BOOST_TEST(res12 == size_t(7));
	BOOST_TEST(res13 == size_t(7));
	BOOST_TEST(res14 == size_t(7));
	BOOST_TEST(res15 == size_t(7));
	BOOST_TEST(res16 == size_t(7));
	BOOST_TEST(res17 == size_t(7));
	BOOST_TEST(res18 == size_t(7));
	BOOST_TEST(res19 == size_t(7));
	BOOST_TEST(res20 == size_t(7));
	BOOST_TEST(res21 == size_t(7));
	BOOST_TEST(res22 == size_t(7));
	BOOST_TEST(res23 == size_t(7));
	BOOST_TEST(res24 == size_t(7));
	BOOST_TEST(res25 == size_t(7));
	BOOST_TEST(res26 == size_t(7));
	BOOST_TEST(res27 == size_t(7));
	BOOST_TEST(res28 == size_t(7));
	BOOST_TEST(res29 == size_t(7));
	BOOST_TEST(res30 == size_t(7));
	BOOST_TEST(res31 == size_t(7));
	BOOST_TEST(res32 == size_t(7));
	BOOST_TEST(res33 == size_t(7));

	BOOST_TEST(rt_id(res01) == (id< row_init_t< true, 7 > >));
	BOOST_TEST(rt_id(res02) == (id< row_init_t< false, 7 > >));
	BOOST_TEST(rt_id(res03) == (id< row_init_t< false, 0 > >));
	BOOST_TEST(rt_id(res04) == (id< row_init_t< true, 7 > >));
	BOOST_TEST(rt_id(res05) == (id< row_init_t< false, 7 > >));
	BOOST_TEST(rt_id(res06) == (id< row_init_t< false, 0 > >));
	BOOST_TEST(rt_id(res07) == (id< row_init_t< true, 7 > >));
	BOOST_TEST(rt_id(res08) == (id< row_init_t< true, 7 > >));
	BOOST_TEST(rt_id(res09) == (id< row_init_t< true, 7 > >));
	BOOST_TEST(rt_id(res10) == (id< row_init_t< false, 7 > >));
	BOOST_TEST(rt_id(res11) == (id< row_init_t< true, 7 > >));
	BOOST_TEST(rt_id(res12) == (id< row_init_t< false, 7 > >));
	BOOST_TEST(rt_id(res13) == (id< row_init_t< true, 7 > >));
	BOOST_TEST(rt_id(res14) == (id< row_init_t< false, 7 > >));
	BOOST_TEST(rt_id(res15) == (id< row_init_t< false, 0 > >));
	BOOST_TEST(rt_id(res16) == (id< row_init_t< true, 7 > >));
	BOOST_TEST(rt_id(res17) == (id< row_init_t< true, 7 > >));
	BOOST_TEST(rt_id(res18) == (id< row_init_t< true, 7 > >));
	BOOST_TEST(rt_id(res19) == (id< row_init_t< true, 7 > >));
	BOOST_TEST(rt_id(res20) == (id< row_init_t< true, 7 > >));
	BOOST_TEST(rt_id(res21) == (id< row_init_t< true, 7 > >));
	BOOST_TEST(rt_id(res22) == (id< row_init_t< true, 7 > >));
	BOOST_TEST(rt_id(res23) == (id< row_init_t< true, 7 > >));
	BOOST_TEST(rt_id(res24) == (id< row_init_t< true, 7 > >));
	BOOST_TEST(rt_id(res25) == (id< row_init_t< true, 7 > >));
	BOOST_TEST(rt_id(res26) == (id< row_init_t< false, 7 > >));
	BOOST_TEST(rt_id(res27) == (id< row_init_t< false, 7 > >));
	BOOST_TEST(rt_id(res28) == (id< row_init_t< true, 7 > >));
	BOOST_TEST(rt_id(res29) == (id< row_init_t< true, 7 > >));
	BOOST_TEST(rt_id(res30) == (id< row_init_t< true, 7 > >));
	BOOST_TEST(rt_id(res31) == (id< row_init_t< true, 7 > >));
	BOOST_TEST(rt_id(res32) == (id< row_init_t< false, 7 > >));
	BOOST_TEST(rt_id(res33) == (id< row_init_t< false, 7 > >));
}


BOOST_AUTO_TEST_CASE(test_get_dims_init){
	constexpr auto d1 = 7_D;
	constexpr auto d2 = 7_D_rt;
	constexpr auto d3 = dims(7);

	constexpr auto res01 = get(d1);
	constexpr auto res02 = get(d2);
	constexpr auto res03 = get(d3);
	constexpr auto res04 = get(d1, d1);
	constexpr auto res05 = get(d2, d2);
	constexpr auto res06 = get(d3, d3);
	constexpr auto res07 = get(d1, d2);
	constexpr auto res08 = get(d1, d3);
	constexpr auto res09 = get(d2, d1);
	constexpr auto res10 = get(d2, d3);
	constexpr auto res11 = get(d3, d1);
	constexpr auto res12 = get(d3, d2);
	constexpr auto res13 = get(d1, d1, d1);
	constexpr auto res14 = get(d2, d2, d2);
	constexpr auto res15 = get(d3, d3, d3);
	constexpr auto res16 = get(d1, d2, d1);
	constexpr auto res17 = get(d1, d2, d2);
	constexpr auto res18 = get(d1, d2, d3);
	constexpr auto res19 = get(d1, d3, d1);
	constexpr auto res20 = get(d1, d3, d2);
	constexpr auto res21 = get(d1, d3, d3);
	constexpr auto res22 = get(d2, d1, d1);
	constexpr auto res23 = get(d2, d1, d2);
	constexpr auto res24 = get(d2, d1, d3);
	constexpr auto res25 = get(d2, d3, d1);
	constexpr auto res26 = get(d2, d3, d2);
	constexpr auto res27 = get(d2, d3, d3);
	constexpr auto res28 = get(d3, d1, d1);
	constexpr auto res29 = get(d3, d1, d2);
	constexpr auto res30 = get(d3, d1, d3);
	constexpr auto res31 = get(d3, d2, d1);
	constexpr auto res32 = get(d3, d2, d2);
	constexpr auto res33 = get(d3, d2, d3);

	BOOST_TEST(res01 == size_t(7));
	BOOST_TEST(res02 == size_t(7));
	BOOST_TEST(res03 == size_t(7));
	BOOST_TEST(res04 == size_t(7));
	BOOST_TEST(res05 == size_t(7));
	BOOST_TEST(res06 == size_t(7));
	BOOST_TEST(res07 == size_t(7));
	BOOST_TEST(res08 == size_t(7));
	BOOST_TEST(res09 == size_t(7));
	BOOST_TEST(res10 == size_t(7));
	BOOST_TEST(res11 == size_t(7));
	BOOST_TEST(res12 == size_t(7));
	BOOST_TEST(res13 == size_t(7));
	BOOST_TEST(res14 == size_t(7));
	BOOST_TEST(res15 == size_t(7));
	BOOST_TEST(res16 == size_t(7));
	BOOST_TEST(res17 == size_t(7));
	BOOST_TEST(res18 == size_t(7));
	BOOST_TEST(res19 == size_t(7));
	BOOST_TEST(res20 == size_t(7));
	BOOST_TEST(res21 == size_t(7));
	BOOST_TEST(res22 == size_t(7));
	BOOST_TEST(res23 == size_t(7));
	BOOST_TEST(res24 == size_t(7));
	BOOST_TEST(res25 == size_t(7));
	BOOST_TEST(res26 == size_t(7));
	BOOST_TEST(res27 == size_t(7));
	BOOST_TEST(res28 == size_t(7));
	BOOST_TEST(res29 == size_t(7));
	BOOST_TEST(res30 == size_t(7));
	BOOST_TEST(res31 == size_t(7));
	BOOST_TEST(res32 == size_t(7));
	BOOST_TEST(res33 == size_t(7));

	BOOST_TEST(rt_id(res01) == (id< dim_init_t< true, 7 > >));
	BOOST_TEST(rt_id(res02) == (id< dim_init_t< false, 7 > >));
	BOOST_TEST(rt_id(res03) == (id< dim_init_t< false, 0 > >));
	BOOST_TEST(rt_id(res04) == (id< dim_init_t< true, 7 > >));
	BOOST_TEST(rt_id(res05) == (id< dim_init_t< false, 7 > >));
	BOOST_TEST(rt_id(res06) == (id< dim_init_t< false, 0 > >));
	BOOST_TEST(rt_id(res07) == (id< dim_init_t< true, 7 > >));
	BOOST_TEST(rt_id(res08) == (id< dim_init_t< true, 7 > >));
	BOOST_TEST(rt_id(res09) == (id< dim_init_t< true, 7 > >));
	BOOST_TEST(rt_id(res10) == (id< dim_init_t< false, 7 > >));
	BOOST_TEST(rt_id(res11) == (id< dim_init_t< true, 7 > >));
	BOOST_TEST(rt_id(res12) == (id< dim_init_t< false, 7 > >));
	BOOST_TEST(rt_id(res13) == (id< dim_init_t< true, 7 > >));
	BOOST_TEST(rt_id(res14) == (id< dim_init_t< false, 7 > >));
	BOOST_TEST(rt_id(res15) == (id< dim_init_t< false, 0 > >));
	BOOST_TEST(rt_id(res16) == (id< dim_init_t< true, 7 > >));
	BOOST_TEST(rt_id(res17) == (id< dim_init_t< true, 7 > >));
	BOOST_TEST(rt_id(res18) == (id< dim_init_t< true, 7 > >));
	BOOST_TEST(rt_id(res19) == (id< dim_init_t< true, 7 > >));
	BOOST_TEST(rt_id(res20) == (id< dim_init_t< true, 7 > >));
	BOOST_TEST(rt_id(res21) == (id< dim_init_t< true, 7 > >));
	BOOST_TEST(rt_id(res22) == (id< dim_init_t< true, 7 > >));
	BOOST_TEST(rt_id(res23) == (id< dim_init_t< true, 7 > >));
	BOOST_TEST(rt_id(res24) == (id< dim_init_t< true, 7 > >));
	BOOST_TEST(rt_id(res25) == (id< dim_init_t< true, 7 > >));
	BOOST_TEST(rt_id(res26) == (id< dim_init_t< false, 7 > >));
	BOOST_TEST(rt_id(res27) == (id< dim_init_t< false, 7 > >));
	BOOST_TEST(rt_id(res28) == (id< dim_init_t< true, 7 > >));
	BOOST_TEST(rt_id(res29) == (id< dim_init_t< true, 7 > >));
	BOOST_TEST(rt_id(res30) == (id< dim_init_t< true, 7 > >));
	BOOST_TEST(rt_id(res31) == (id< dim_init_t< true, 7 > >));
	BOOST_TEST(rt_id(res32) == (id< dim_init_t< false, 7 > >));
	BOOST_TEST(rt_id(res33) == (id< dim_init_t< false, 7 > >));
}


BOOST_AUTO_TEST_CASE(test_get_cols){
	constexpr auto c1 = cols< 7 >();
	constexpr auto c2 = cols(7);

	constexpr auto ct01 = get(c1);
	constexpr auto ct02 = get(c1, c1);
	constexpr auto ct03 = get(c1, c1, c1);
	constexpr auto ct04 = get(c2, c1);
	constexpr auto ct05 = get(c2, c1, c1);
	constexpr auto ct06 = get(c1, c2, c1);
	constexpr auto ct07 = get(c1, c1, c2);
	constexpr auto ct08 = get(c2, c2, c1);
	constexpr auto ct09 = get(c2, c1, c2);
	constexpr auto ct10 = get(c1, c2, c2);
	constexpr auto ct11 = get(c1, c2);
	constexpr auto rt01 = get(c2, c2, c2);
	constexpr auto rt02 = get(c2, c2);
	constexpr auto rt03 = get(c2);

	BOOST_TEST(ct01 == size_t(7));
	BOOST_TEST(ct02 == size_t(7));
	BOOST_TEST(ct03 == size_t(7));
	BOOST_TEST(ct04 == size_t(7));
	BOOST_TEST(ct05 == size_t(7));
	BOOST_TEST(ct06 == size_t(7));
	BOOST_TEST(ct07 == size_t(7));
	BOOST_TEST(ct08 == size_t(7));
	BOOST_TEST(ct09 == size_t(7));
	BOOST_TEST(ct10 == size_t(7));
	BOOST_TEST(ct11 == size_t(7));
	BOOST_TEST(rt01 == size_t(7));
	BOOST_TEST(rt02 == size_t(7));
	BOOST_TEST(rt03 == size_t(7));

	BOOST_TEST(rt_id(ct01) == (id< col_init_t< true, 7 > >));
	BOOST_TEST(rt_id(ct02) == (id< col_init_t< true, 7 > >));
	BOOST_TEST(rt_id(ct03) == (id< col_init_t< true, 7 > >));
	BOOST_TEST(rt_id(ct04) == (id< col_init_t< true, 7 > >));
	BOOST_TEST(rt_id(ct05) == (id< col_init_t< true, 7 > >));
	BOOST_TEST(rt_id(ct06) == (id< col_init_t< true, 7 > >));
	BOOST_TEST(rt_id(ct07) == (id< col_init_t< true, 7 > >));
	BOOST_TEST(rt_id(ct08) == (id< col_init_t< true, 7 > >));
	BOOST_TEST(rt_id(ct09) == (id< col_init_t< true, 7 > >));
	BOOST_TEST(rt_id(ct10) == (id< col_init_t< true, 7 > >));
	BOOST_TEST(rt_id(ct11) == (id< col_init_t< true, 7 > >));
	BOOST_TEST(rt_id(rt01) == (id< col_init_t< false, 0 > >));
	BOOST_TEST(rt_id(rt02) == (id< col_init_t< false, 0 > >));
	BOOST_TEST(rt_id(rt03) == (id< col_init_t< false, 0 > >));
}


BOOST_AUTO_TEST_CASE(test_get_rows){
	constexpr auto r1 = rows< 7 >();
	constexpr auto r2 = rows(7);

	constexpr auto ct01 = get(r1);
	constexpr auto ct02 = get(r1, r1);
	constexpr auto ct03 = get(r1, r1, r1);
	constexpr auto ct04 = get(r2, r1);
	constexpr auto ct05 = get(r2, r1, r1);
	constexpr auto ct06 = get(r1, r2, r1);
	constexpr auto ct07 = get(r1, r1, r2);
	constexpr auto ct08 = get(r2, r2, r1);
	constexpr auto ct09 = get(r2, r1, r2);
	constexpr auto ct10 = get(r1, r2, r2);
	constexpr auto ct11 = get(r1, r2);
	constexpr auto rt01 = get(r2, r2, r2);
	constexpr auto rt02 = get(r2, r2);
	constexpr auto rt03 = get(r2);

	BOOST_TEST(ct01 == size_t(7));
	BOOST_TEST(ct02 == size_t(7));
	BOOST_TEST(ct03 == size_t(7));
	BOOST_TEST(ct04 == size_t(7));
	BOOST_TEST(ct05 == size_t(7));
	BOOST_TEST(ct06 == size_t(7));
	BOOST_TEST(ct07 == size_t(7));
	BOOST_TEST(ct08 == size_t(7));
	BOOST_TEST(ct09 == size_t(7));
	BOOST_TEST(ct10 == size_t(7));
	BOOST_TEST(ct11 == size_t(7));
	BOOST_TEST(rt01 == size_t(7));
	BOOST_TEST(rt02 == size_t(7));
	BOOST_TEST(rt03 == size_t(7));

	BOOST_TEST(rt_id(ct01) == (id< row_init_t< true, 7 > >));
	BOOST_TEST(rt_id(ct02) == (id< row_init_t< true, 7 > >));
	BOOST_TEST(rt_id(ct03) == (id< row_init_t< true, 7 > >));
	BOOST_TEST(rt_id(ct04) == (id< row_init_t< true, 7 > >));
	BOOST_TEST(rt_id(ct05) == (id< row_init_t< true, 7 > >));
	BOOST_TEST(rt_id(ct06) == (id< row_init_t< true, 7 > >));
	BOOST_TEST(rt_id(ct07) == (id< row_init_t< true, 7 > >));
	BOOST_TEST(rt_id(ct08) == (id< row_init_t< true, 7 > >));
	BOOST_TEST(rt_id(ct09) == (id< row_init_t< true, 7 > >));
	BOOST_TEST(rt_id(ct10) == (id< row_init_t< true, 7 > >));
	BOOST_TEST(rt_id(ct11) == (id< row_init_t< true, 7 > >));
	BOOST_TEST(rt_id(rt01) == (id< row_init_t< false, 0 > >));
	BOOST_TEST(rt_id(rt02) == (id< row_init_t< false, 0 > >));
	BOOST_TEST(rt_id(rt03) == (id< row_init_t< false, 0 > >));
}


BOOST_AUTO_TEST_CASE(test_get_dims){
	constexpr auto d1 = dims(7_C, 7_R);
	constexpr auto d2 = dims(7_C, 7_R_rt);
	constexpr auto d3 = dims(7_C_rt, 7_R);
	constexpr auto d4 = dims(7_C_rt, 7_R_rt);

	constexpr auto res01 = get(d1);
	constexpr auto res02 = get(d2);
	constexpr auto res03 = get(d3);
	constexpr auto res04 = get(d4);
	constexpr auto res05 = get(d1, d1);
	constexpr auto res06 = get(d1, d2);
	constexpr auto res07 = get(d1, d3);
	constexpr auto res08 = get(d1, d4);
	constexpr auto res09 = get(d2, d1);
	constexpr auto res10 = get(d2, d2);
	constexpr auto res11 = get(d2, d3);
	constexpr auto res12 = get(d2, d4);
	constexpr auto res13 = get(d3, d1);
	constexpr auto res14 = get(d3, d2);
	constexpr auto res15 = get(d3, d3);
	constexpr auto res16 = get(d3, d4);
	constexpr auto res17 = get(d4, d1);
	constexpr auto res18 = get(d4, d2);
	constexpr auto res19 = get(d4, d3);
	constexpr auto res20 = get(d4, d4);
	constexpr auto res21 = get(d1, d1, d1);
	constexpr auto res22 = get(d1, d1, d2);
	constexpr auto res23 = get(d1, d1, d3);
	constexpr auto res24 = get(d1, d1, d4);
	constexpr auto res25 = get(d1, d2, d1);
	constexpr auto res26 = get(d1, d2, d2);
	constexpr auto res27 = get(d1, d2, d3);
	constexpr auto res28 = get(d1, d2, d4);
	constexpr auto res29 = get(d1, d3, d1);
	constexpr auto res30 = get(d1, d3, d2);
	constexpr auto res31 = get(d1, d3, d3);
	constexpr auto res32 = get(d1, d3, d4);
	constexpr auto res33 = get(d1, d4, d1);
	constexpr auto res34 = get(d1, d4, d2);
	constexpr auto res35 = get(d1, d4, d3);
	constexpr auto res36 = get(d1, d4, d4);
	constexpr auto res37 = get(d2, d1, d1);
	constexpr auto res38 = get(d2, d1, d2);
	constexpr auto res39 = get(d2, d1, d3);
	constexpr auto res40 = get(d2, d1, d4);
	constexpr auto res41 = get(d2, d2, d1);
	constexpr auto res42 = get(d2, d2, d2);
	constexpr auto res43 = get(d2, d2, d3);
	constexpr auto res44 = get(d2, d2, d4);
	constexpr auto res45 = get(d2, d3, d1);
	constexpr auto res46 = get(d2, d3, d2);
	constexpr auto res47 = get(d2, d3, d3);
	constexpr auto res48 = get(d2, d3, d4);
	constexpr auto res49 = get(d2, d4, d1);
	constexpr auto res50 = get(d2, d4, d2);
	constexpr auto res51 = get(d2, d4, d3);
	constexpr auto res52 = get(d2, d4, d4);
	constexpr auto res53 = get(d3, d1, d1);
	constexpr auto res54 = get(d3, d1, d2);
	constexpr auto res55 = get(d3, d1, d3);
	constexpr auto res56 = get(d3, d1, d4);
	constexpr auto res57 = get(d3, d2, d1);
	constexpr auto res58 = get(d3, d2, d2);
	constexpr auto res59 = get(d3, d2, d3);
	constexpr auto res60 = get(d3, d2, d4);
	constexpr auto res61 = get(d3, d3, d1);
	constexpr auto res62 = get(d3, d3, d2);
	constexpr auto res63 = get(d3, d3, d3);
	constexpr auto res64 = get(d3, d3, d4);
	constexpr auto res65 = get(d3, d4, d1);
	constexpr auto res66 = get(d3, d4, d2);
	constexpr auto res67 = get(d3, d4, d3);
	constexpr auto res68 = get(d3, d4, d4);
	constexpr auto res69 = get(d4, d1, d1);
	constexpr auto res70 = get(d4, d1, d2);
	constexpr auto res71 = get(d4, d1, d3);
	constexpr auto res72 = get(d4, d1, d4);
	constexpr auto res73 = get(d4, d2, d1);
	constexpr auto res74 = get(d4, d2, d2);
	constexpr auto res75 = get(d4, d2, d3);
	constexpr auto res76 = get(d4, d2, d4);
	constexpr auto res77 = get(d4, d3, d1);
	constexpr auto res78 = get(d4, d3, d2);
	constexpr auto res79 = get(d4, d3, d3);
	constexpr auto res80 = get(d4, d3, d4);
	constexpr auto res81 = get(d4, d4, d1);
	constexpr auto res82 = get(d4, d4, d2);
	constexpr auto res83 = get(d4, d4, d3);
	constexpr auto res84 = get(d4, d4, d4);

	BOOST_TEST((res01 == dims(7, 7)));
	BOOST_TEST((res02 == dims(7, 7)));
	BOOST_TEST((res03 == dims(7, 7)));
	BOOST_TEST((res04 == dims(7, 7)));
	BOOST_TEST((res05 == dims(7, 7)));
	BOOST_TEST((res06 == dims(7, 7)));
	BOOST_TEST((res07 == dims(7, 7)));
	BOOST_TEST((res08 == dims(7, 7)));
	BOOST_TEST((res09 == dims(7, 7)));
	BOOST_TEST((res10 == dims(7, 7)));
	BOOST_TEST((res11 == dims(7, 7)));
	BOOST_TEST((res12 == dims(7, 7)));
	BOOST_TEST((res13 == dims(7, 7)));
	BOOST_TEST((res14 == dims(7, 7)));
	BOOST_TEST((res15 == dims(7, 7)));
	BOOST_TEST((res16 == dims(7, 7)));
	BOOST_TEST((res17 == dims(7, 7)));
	BOOST_TEST((res18 == dims(7, 7)));
	BOOST_TEST((res19 == dims(7, 7)));
	BOOST_TEST((res20 == dims(7, 7)));
	BOOST_TEST((res21 == dims(7, 7)));
	BOOST_TEST((res22 == dims(7, 7)));
	BOOST_TEST((res23 == dims(7, 7)));
	BOOST_TEST((res24 == dims(7, 7)));
	BOOST_TEST((res25 == dims(7, 7)));
	BOOST_TEST((res26 == dims(7, 7)));
	BOOST_TEST((res27 == dims(7, 7)));
	BOOST_TEST((res28 == dims(7, 7)));
	BOOST_TEST((res29 == dims(7, 7)));
	BOOST_TEST((res30 == dims(7, 7)));
	BOOST_TEST((res31 == dims(7, 7)));
	BOOST_TEST((res32 == dims(7, 7)));
	BOOST_TEST((res33 == dims(7, 7)));
	BOOST_TEST((res34 == dims(7, 7)));
	BOOST_TEST((res35 == dims(7, 7)));
	BOOST_TEST((res36 == dims(7, 7)));
	BOOST_TEST((res37 == dims(7, 7)));
	BOOST_TEST((res38 == dims(7, 7)));
	BOOST_TEST((res39 == dims(7, 7)));
	BOOST_TEST((res40 == dims(7, 7)));
	BOOST_TEST((res41 == dims(7, 7)));
	BOOST_TEST((res42 == dims(7, 7)));
	BOOST_TEST((res43 == dims(7, 7)));
	BOOST_TEST((res44 == dims(7, 7)));
	BOOST_TEST((res45 == dims(7, 7)));
	BOOST_TEST((res46 == dims(7, 7)));
	BOOST_TEST((res47 == dims(7, 7)));
	BOOST_TEST((res48 == dims(7, 7)));
	BOOST_TEST((res49 == dims(7, 7)));
	BOOST_TEST((res50 == dims(7, 7)));
	BOOST_TEST((res51 == dims(7, 7)));
	BOOST_TEST((res52 == dims(7, 7)));
	BOOST_TEST((res53 == dims(7, 7)));
	BOOST_TEST((res54 == dims(7, 7)));
	BOOST_TEST((res55 == dims(7, 7)));
	BOOST_TEST((res56 == dims(7, 7)));
	BOOST_TEST((res57 == dims(7, 7)));
	BOOST_TEST((res58 == dims(7, 7)));
	BOOST_TEST((res59 == dims(7, 7)));
	BOOST_TEST((res60 == dims(7, 7)));
	BOOST_TEST((res61 == dims(7, 7)));
	BOOST_TEST((res62 == dims(7, 7)));
	BOOST_TEST((res63 == dims(7, 7)));
	BOOST_TEST((res64 == dims(7, 7)));
	BOOST_TEST((res65 == dims(7, 7)));
	BOOST_TEST((res66 == dims(7, 7)));
	BOOST_TEST((res67 == dims(7, 7)));
	BOOST_TEST((res68 == dims(7, 7)));
	BOOST_TEST((res69 == dims(7, 7)));
	BOOST_TEST((res70 == dims(7, 7)));
	BOOST_TEST((res71 == dims(7, 7)));
	BOOST_TEST((res72 == dims(7, 7)));
	BOOST_TEST((res73 == dims(7, 7)));
	BOOST_TEST((res74 == dims(7, 7)));
	BOOST_TEST((res75 == dims(7, 7)));
	BOOST_TEST((res76 == dims(7, 7)));
	BOOST_TEST((res77 == dims(7, 7)));
	BOOST_TEST((res78 == dims(7, 7)));
	BOOST_TEST((res79 == dims(7, 7)));
	BOOST_TEST((res80 == dims(7, 7)));
	BOOST_TEST((res81 == dims(7, 7)));
	BOOST_TEST((res82 == dims(7, 7)));
	BOOST_TEST((res83 == dims(7, 7)));
	BOOST_TEST((res84 == dims(7, 7)));

	BOOST_TEST(rt_id(res01) == (id< dims_t< 7, 7 > >));
	BOOST_TEST(rt_id(res02) == (id< dims_t< 7, 0 > >));
	BOOST_TEST(rt_id(res03) == (id< dims_t< 0, 7 > >));
	BOOST_TEST(rt_id(res04) == (id< dims_t< 0, 0 > >));
	BOOST_TEST(rt_id(res05) == (id< dims_t< 7, 7 > >));
	BOOST_TEST(rt_id(res06) == (id< dims_t< 7, 7 > >));
	BOOST_TEST(rt_id(res07) == (id< dims_t< 7, 7 > >));
	BOOST_TEST(rt_id(res08) == (id< dims_t< 7, 7 > >));
	BOOST_TEST(rt_id(res09) == (id< dims_t< 7, 7 > >));
	BOOST_TEST(rt_id(res10) == (id< dims_t< 7, 0 > >));
	BOOST_TEST(rt_id(res11) == (id< dims_t< 7, 7 > >));
	BOOST_TEST(rt_id(res12) == (id< dims_t< 7, 0 > >));
	BOOST_TEST(rt_id(res13) == (id< dims_t< 7, 7 > >));
	BOOST_TEST(rt_id(res14) == (id< dims_t< 7, 7 > >));
	BOOST_TEST(rt_id(res15) == (id< dims_t< 0, 7 > >));
	BOOST_TEST(rt_id(res16) == (id< dims_t< 0, 7 > >));
	BOOST_TEST(rt_id(res17) == (id< dims_t< 7, 7 > >));
	BOOST_TEST(rt_id(res18) == (id< dims_t< 7, 0 > >));
	BOOST_TEST(rt_id(res19) == (id< dims_t< 0, 7 > >));
	BOOST_TEST(rt_id(res20) == (id< dims_t< 0, 0 > >));
	BOOST_TEST(rt_id(res21) == (id< dims_t< 7, 7 > >));
	BOOST_TEST(rt_id(res22) == (id< dims_t< 7, 7 > >));
	BOOST_TEST(rt_id(res23) == (id< dims_t< 7, 7 > >));
	BOOST_TEST(rt_id(res24) == (id< dims_t< 7, 7 > >));
	BOOST_TEST(rt_id(res25) == (id< dims_t< 7, 7 > >));
	BOOST_TEST(rt_id(res26) == (id< dims_t< 7, 7 > >));
	BOOST_TEST(rt_id(res27) == (id< dims_t< 7, 7 > >));
	BOOST_TEST(rt_id(res28) == (id< dims_t< 7, 7 > >));
	BOOST_TEST(rt_id(res29) == (id< dims_t< 7, 7 > >));
	BOOST_TEST(rt_id(res30) == (id< dims_t< 7, 7 > >));
	BOOST_TEST(rt_id(res31) == (id< dims_t< 7, 7 > >));
	BOOST_TEST(rt_id(res32) == (id< dims_t< 7, 7 > >));
	BOOST_TEST(rt_id(res33) == (id< dims_t< 7, 7 > >));
	BOOST_TEST(rt_id(res34) == (id< dims_t< 7, 7 > >));
	BOOST_TEST(rt_id(res35) == (id< dims_t< 7, 7 > >));
	BOOST_TEST(rt_id(res36) == (id< dims_t< 7, 7 > >));
	BOOST_TEST(rt_id(res37) == (id< dims_t< 7, 7 > >));
	BOOST_TEST(rt_id(res38) == (id< dims_t< 7, 7 > >));
	BOOST_TEST(rt_id(res39) == (id< dims_t< 7, 7 > >));
	BOOST_TEST(rt_id(res40) == (id< dims_t< 7, 7 > >));
	BOOST_TEST(rt_id(res41) == (id< dims_t< 7, 7 > >));
	BOOST_TEST(rt_id(res42) == (id< dims_t< 7, 0 > >));
	BOOST_TEST(rt_id(res43) == (id< dims_t< 7, 7 > >));
	BOOST_TEST(rt_id(res44) == (id< dims_t< 7, 0 > >));
	BOOST_TEST(rt_id(res45) == (id< dims_t< 7, 7 > >));
	BOOST_TEST(rt_id(res46) == (id< dims_t< 7, 7 > >));
	BOOST_TEST(rt_id(res47) == (id< dims_t< 7, 7 > >));
	BOOST_TEST(rt_id(res48) == (id< dims_t< 7, 7 > >));
	BOOST_TEST(rt_id(res49) == (id< dims_t< 7, 7 > >));
	BOOST_TEST(rt_id(res50) == (id< dims_t< 7, 0 > >));
	BOOST_TEST(rt_id(res51) == (id< dims_t< 7, 7 > >));
	BOOST_TEST(rt_id(res52) == (id< dims_t< 7, 0 > >));
	BOOST_TEST(rt_id(res53) == (id< dims_t< 7, 7 > >));
	BOOST_TEST(rt_id(res54) == (id< dims_t< 7, 7 > >));
	BOOST_TEST(rt_id(res55) == (id< dims_t< 7, 7 > >));
	BOOST_TEST(rt_id(res56) == (id< dims_t< 7, 7 > >));
	BOOST_TEST(rt_id(res57) == (id< dims_t< 7, 7 > >));
	BOOST_TEST(rt_id(res58) == (id< dims_t< 7, 7 > >));
	BOOST_TEST(rt_id(res59) == (id< dims_t< 7, 7 > >));
	BOOST_TEST(rt_id(res60) == (id< dims_t< 7, 7 > >));
	BOOST_TEST(rt_id(res61) == (id< dims_t< 7, 7 > >));
	BOOST_TEST(rt_id(res62) == (id< dims_t< 7, 7 > >));
	BOOST_TEST(rt_id(res63) == (id< dims_t< 0, 7 > >));
	BOOST_TEST(rt_id(res64) == (id< dims_t< 0, 7 > >));
	BOOST_TEST(rt_id(res65) == (id< dims_t< 7, 7 > >));
	BOOST_TEST(rt_id(res66) == (id< dims_t< 7, 7 > >));
	BOOST_TEST(rt_id(res67) == (id< dims_t< 0, 7 > >));
	BOOST_TEST(rt_id(res68) == (id< dims_t< 0, 7 > >));
	BOOST_TEST(rt_id(res69) == (id< dims_t< 7, 7 > >));
	BOOST_TEST(rt_id(res70) == (id< dims_t< 7, 7 > >));
	BOOST_TEST(rt_id(res71) == (id< dims_t< 7, 7 > >));
	BOOST_TEST(rt_id(res72) == (id< dims_t< 7, 7 > >));
	BOOST_TEST(rt_id(res73) == (id< dims_t< 7, 7 > >));
	BOOST_TEST(rt_id(res74) == (id< dims_t< 7, 0 > >));
	BOOST_TEST(rt_id(res75) == (id< dims_t< 7, 7 > >));
	BOOST_TEST(rt_id(res76) == (id< dims_t< 7, 0 > >));
	BOOST_TEST(rt_id(res77) == (id< dims_t< 7, 7 > >));
	BOOST_TEST(rt_id(res78) == (id< dims_t< 7, 7 > >));
	BOOST_TEST(rt_id(res79) == (id< dims_t< 0, 7 > >));
	BOOST_TEST(rt_id(res80) == (id< dims_t< 0, 7 > >));
	BOOST_TEST(rt_id(res81) == (id< dims_t< 7, 7 > >));
	BOOST_TEST(rt_id(res82) == (id< dims_t< 7, 0 > >));
	BOOST_TEST(rt_id(res83) == (id< dims_t< 0, 7 > >));
	BOOST_TEST(rt_id(res84) == (id< dims_t< 0, 0 > >));
}


BOOST_AUTO_TEST_SUITE_END()
