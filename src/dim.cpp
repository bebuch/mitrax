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


namespace{


	template < typename T >
	auto rt_id(T&& v){
		return type_id_runtime(static_cast< T&& >(v));
	}

	template < typename T >
	auto const id = type_id< T >();


}


BOOST_AUTO_TEST_SUITE(test_suite_dim)


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

BOOST_AUTO_TEST_CASE(test_dim_t){
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


	BOOST_TEST(rt_id(d11) == (id< dim_t< 0, 0 > >));
	BOOST_TEST(rt_id(d12) == (id< dim_t< 0, 7 > >));
	BOOST_TEST(rt_id(d13) == (id< dim_t< 0, 0 > >));
	BOOST_TEST(rt_id(d14) == (id< dim_t< 0, 0 > >));
	BOOST_TEST(rt_id(d15) == (id< dim_t< 0, 7 > >));
	BOOST_TEST(rt_id(d16) == (id< dim_t< 0, 0 > >));
	BOOST_TEST(rt_id(d17) == (id< dim_t< 0, 0 > >));
	BOOST_TEST(rt_id(d18) == (id< dim_t< 0, 7 > >));

	BOOST_TEST(rt_id(d22) == (id< dim_t< 4, 7 > >));
	BOOST_TEST(rt_id(d23) == (id< dim_t< 4, 0 > >));
	BOOST_TEST(rt_id(d24) == (id< dim_t< 4, 0 > >));
	BOOST_TEST(rt_id(d25) == (id< dim_t< 4, 7 > >));
	BOOST_TEST(rt_id(d26) == (id< dim_t< 4, 0 > >));
	BOOST_TEST(rt_id(d27) == (id< dim_t< 4, 0 > >));
	BOOST_TEST(rt_id(d28) == (id< dim_t< 4, 7 > >));

	BOOST_TEST(rt_id(d33) == (id< dim_t< 0, 0 > >));
	BOOST_TEST(rt_id(d34) == (id< dim_t< 0, 0 > >));
	BOOST_TEST(rt_id(d35) == (id< dim_t< 0, 7 > >));
	BOOST_TEST(rt_id(d36) == (id< dim_t< 0, 0 > >));
	BOOST_TEST(rt_id(d37) == (id< dim_t< 0, 0 > >));
	BOOST_TEST(rt_id(d38) == (id< dim_t< 0, 7 > >));

	BOOST_TEST(rt_id(d44) == (id< dim_t< 0, 0 > >));
	BOOST_TEST(rt_id(d45) == (id< dim_t< 0, 7 > >));
	BOOST_TEST(rt_id(d46) == (id< dim_t< 0, 0 > >));
	BOOST_TEST(rt_id(d47) == (id< dim_t< 0, 0 > >));
	BOOST_TEST(rt_id(d48) == (id< dim_t< 0, 7 > >));

	BOOST_TEST(rt_id(d55) == (id< dim_t< 4, 7 > >));
	BOOST_TEST(rt_id(d56) == (id< dim_t< 4, 0 > >));
	BOOST_TEST(rt_id(d57) == (id< dim_t< 4, 0 > >));
	BOOST_TEST(rt_id(d58) == (id< dim_t< 4, 7 > >));

	BOOST_TEST(rt_id(d66) == (id< dim_t< 0, 0 > >));
	BOOST_TEST(rt_id(d67) == (id< dim_t< 0, 0 > >));
	BOOST_TEST(rt_id(d68) == (id< dim_t< 0, 7 > >));

	BOOST_TEST(rt_id(d77) == (id< dim_t< 0, 0 > >));
	BOOST_TEST(rt_id(d78) == (id< dim_t< 0, 7 > >));

	BOOST_TEST(rt_id(d88) == (id< dim_t< 4, 7 > >));
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

BOOST_AUTO_TEST_CASE(test_compare_dim_t){
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

	BOOST_TEST(rt_id(cct.get()) == (id< dim_t< 7, 7 > >));
	BOOST_TEST(rt_id(crt.get()) == (id< dim_t< 0, 0 > >));
	BOOST_TEST(rt_id(rrt.get()) == (id< dim_t< 0, 0 > >));

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


BOOST_AUTO_TEST_SUITE_END()
