//-----------------------------------------------------------------------------
// Copyright (c) 2015-2016 Benjamin Buch
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


#define CP(expr) [&]{ constexpr auto tmp = expr; return tmp; }()


namespace{


	template < typename T >
	auto rt_id(T&& v){
		return type_id_runtime(static_cast< T&& >(v));
	}

	template < typename T >
	auto const id = type_id< T >();


}


BOOST_AUTO_TEST_CASE(test_col_t){
	BOOST_TEST((rt_id(7_C) == (id< col_t< true, 7 > >)));
	BOOST_TEST((rt_id(7_C_rt) == (id< col_t< false, 7 > >)));

	constexpr auto cct = col_t< true, 7 >();
	constexpr auto crt = col_t< false, 7 >();
	constexpr auto rrt = col_t< false, 0 >(7);

	BOOST_TEST((cct == 7));
	BOOST_TEST((crt == 7));
	BOOST_TEST((rrt == 7));

	BOOST_TEST((rt_id(cct) == (id< col_t< true, 7 > >)));
	BOOST_TEST((rt_id(crt) == (id< col_t< false, 7 > >)));
	BOOST_TEST((rt_id(rrt) == (id< col_t< false, 0 > >)));

	BOOST_TEST((CP(cct.as_row()) == 7));
	BOOST_TEST((CP(crt.as_row()) == 7));
	BOOST_TEST((CP(rrt.as_row()) == 7));

	BOOST_TEST((rt_id(cct.as_row()) == (id< row_t< true, 7 > >)));
	BOOST_TEST((rt_id(crt.as_row()) == (id< row_t< false, 7 > >)));
	BOOST_TEST((rt_id(rrt.as_row()) == (id< row_t< false, 0 > >)));

	BOOST_TEST((CP(cct.as_dim()) == 7));
	BOOST_TEST((CP(crt.as_dim()) == 7));
	BOOST_TEST((CP(rrt.as_dim()) == 7));

	BOOST_TEST((rt_id(cct.as_dim()) == (id< dim_t< true, 7 > >)));
	BOOST_TEST((rt_id(crt.as_dim()) == (id< dim_t< false, 7 > >)));
	BOOST_TEST((rt_id(rrt.as_dim()) == (id< dim_t< false, 0 > >)));
}

BOOST_AUTO_TEST_CASE(test_row_t){
	BOOST_TEST((rt_id(7_R) == (id< row_t< true, 7 > >)));
	BOOST_TEST((rt_id(7_R_rt) == (id< row_t< false, 7 > >)));

	constexpr auto cct = row_t< true, 7 >();
	constexpr auto crt = row_t< false, 7 >();
	constexpr auto rrt = row_t< false, 0 >(7);

	BOOST_TEST((cct == 7));
	BOOST_TEST((crt == 7));
	BOOST_TEST((rrt == 7));

	BOOST_TEST((rt_id(cct) == (id< row_t< true, 7 > >)));
	BOOST_TEST((rt_id(crt) == (id< row_t< false, 7 > >)));
	BOOST_TEST((rt_id(rrt) == (id< row_t< false, 0 > >)));

	BOOST_TEST((CP(cct.as_col()) == 7));
	BOOST_TEST((CP(crt.as_col()) == 7));
	BOOST_TEST((CP(rrt.as_col()) == 7));

	BOOST_TEST((rt_id(cct.as_col()) == (id< col_t< true, 7 > >)));
	BOOST_TEST((rt_id(crt.as_col()) == (id< col_t< false, 7 > >)));
	BOOST_TEST((rt_id(rrt.as_col()) == (id< col_t< false, 0 > >)));

	BOOST_TEST((CP(cct.as_dim()) == 7));
	BOOST_TEST((CP(crt.as_dim()) == 7));
	BOOST_TEST((CP(rrt.as_dim()) == 7));

	BOOST_TEST((rt_id(cct.as_dim()) == (id< dim_t< true, 7 > >)));
	BOOST_TEST((rt_id(crt.as_dim()) == (id< dim_t< false, 7 > >)));
	BOOST_TEST((rt_id(rrt.as_dim()) == (id< dim_t< false, 0 > >)));
}

BOOST_AUTO_TEST_CASE(test_dim_t){
	BOOST_TEST((rt_id(7_D) == (id< dim_t< true, 7 > >)));
	BOOST_TEST((rt_id(7_D_rt) == (id< dim_t< false, 7 > >)));

	constexpr auto cct = dim_t< true, 7 >();
	constexpr auto crt = dim_t< false, 7 >();
	constexpr auto rrt = dim_t< false, 0 >(7);

	BOOST_TEST((cct == 7));
	BOOST_TEST((crt == 7));
	BOOST_TEST((rrt == 7));

	BOOST_TEST((rt_id(cct) == (id< dim_t< true, 7 > >)));
	BOOST_TEST((rt_id(crt) == (id< dim_t< false, 7 > >)));
	BOOST_TEST((rt_id(rrt) == (id< dim_t< false, 0 > >)));

	BOOST_TEST((CP(cct.as_col()) == 7));
	BOOST_TEST((CP(crt.as_col()) == 7));
	BOOST_TEST((CP(rrt.as_col()) == 7));

	BOOST_TEST((rt_id(cct.as_col()) == (id< col_t< true, 7 > >)));
	BOOST_TEST((rt_id(crt.as_col()) == (id< col_t< false, 7 > >)));
	BOOST_TEST((rt_id(rrt.as_col()) == (id< col_t< false, 0 > >)));

	BOOST_TEST((CP(cct.as_row()) == 7));
	BOOST_TEST((CP(crt.as_row()) == 7));
	BOOST_TEST((CP(rrt.as_row()) == 7));

	BOOST_TEST((rt_id(cct.as_row()) == (id< row_t< true, 7 > >)));
	BOOST_TEST((rt_id(crt.as_row()) == (id< row_t< false, 7 > >)));
	BOOST_TEST((rt_id(rrt.as_row()) == (id< row_t< false, 0 > >)));
}


BOOST_AUTO_TEST_CASE(test_dims_t){
	constexpr auto d11 = dims(4, 7);
	constexpr auto d12 = dims(4, 7_R);
	constexpr auto d13 = dims(4, 7_R_rt);
	constexpr auto d14 = dims(4, rows(7));
	constexpr auto d15 = dims(4, rows< 7 >());
	constexpr auto d16 = dims(4, rows_rt< 7 >());

	constexpr auto d22 = dims(4_C, 7_R);
	constexpr auto d23 = dims(4_C, 7_R_rt);
	constexpr auto d24 = dims(4_C, rows(7));
	constexpr auto d25 = dims(4_C, rows< 7 >());
	constexpr auto d26 = dims(4_C, rows_rt< 7 >());

	constexpr auto d33 = dims(4_C_rt, 7_R_rt);
	constexpr auto d34 = dims(4_C_rt, rows(7));
	constexpr auto d35 = dims(4_C_rt, rows< 7 >());
	constexpr auto d36 = dims(4_C_rt, rows_rt< 7 >());

	constexpr auto d44 = dims(cols(4), rows(7));
	constexpr auto d45 = dims(cols(4), rows< 7 >());
	constexpr auto d46 = dims(cols(4), rows_rt< 7 >());

	constexpr auto d55 = dims(cols< 4 >(), rows< 7 >());
	constexpr auto d56 = dims(cols< 4 >(), rows_rt< 7 >());

	constexpr auto d66 = dims(cols_rt< 4 >(), rows_rt< 7 >());


	BOOST_TEST((CP(d11.cols()) == 4));
	BOOST_TEST((CP(d12.cols()) == 4));
	BOOST_TEST((CP(d13.cols()) == 4));
	BOOST_TEST((CP(d14.cols()) == 4));
	BOOST_TEST((CP(d15.cols()) == 4));
	BOOST_TEST((CP(d16.cols()) == 4));

	BOOST_TEST((CP(d22.cols()) == 4));
	BOOST_TEST((CP(d23.cols()) == 4));
	BOOST_TEST((CP(d24.cols()) == 4));
	BOOST_TEST((CP(d25.cols()) == 4));
	BOOST_TEST((CP(d26.cols()) == 4));

	BOOST_TEST((CP(d33.cols()) == 4));
	BOOST_TEST((CP(d34.cols()) == 4));
	BOOST_TEST((CP(d35.cols()) == 4));
	BOOST_TEST((CP(d36.cols()) == 4));

	BOOST_TEST((CP(d44.cols()) == 4));
	BOOST_TEST((CP(d45.cols()) == 4));
	BOOST_TEST((CP(d46.cols()) == 4));

	BOOST_TEST((CP(d55.cols()) == 4));
	BOOST_TEST((CP(d56.cols()) == 4));

	BOOST_TEST((CP(d66.cols()) == 4));


	BOOST_TEST((CP(d11.rows()) == 7));
	BOOST_TEST((CP(d12.rows()) == 7));
	BOOST_TEST((CP(d13.rows()) == 7));
	BOOST_TEST((CP(d14.rows()) == 7));
	BOOST_TEST((CP(d15.rows()) == 7));
	BOOST_TEST((CP(d16.rows()) == 7));

	BOOST_TEST((CP(d22.rows()) == 7));
	BOOST_TEST((CP(d23.rows()) == 7));
	BOOST_TEST((CP(d24.rows()) == 7));
	BOOST_TEST((CP(d25.rows()) == 7));
	BOOST_TEST((CP(d26.rows()) == 7));

	BOOST_TEST((CP(d33.rows()) == 7));
	BOOST_TEST((CP(d34.rows()) == 7));
	BOOST_TEST((CP(d35.rows()) == 7));
	BOOST_TEST((CP(d36.rows()) == 7));

	BOOST_TEST((CP(d44.rows()) == 7));
	BOOST_TEST((CP(d45.rows()) == 7));
	BOOST_TEST((CP(d46.rows()) == 7));

	BOOST_TEST((CP(d55.rows()) == 7));
	BOOST_TEST((CP(d56.rows()) == 7));

	BOOST_TEST((CP(d66.rows()) == 7));


	BOOST_TEST((rt_id(d11) == (id< dims_t< 0, 0 > >)));
	BOOST_TEST((rt_id(d12) == (id< dims_t< 0, 7 > >)));
	BOOST_TEST((rt_id(d13) == (id< dims_t< 0, 0 > >)));
	BOOST_TEST((rt_id(d14) == (id< dims_t< 0, 0 > >)));
	BOOST_TEST((rt_id(d15) == (id< dims_t< 0, 7 > >)));
	BOOST_TEST((rt_id(d16) == (id< dims_t< 0, 0 > >)));

	BOOST_TEST((rt_id(d22) == (id< dims_t< 4, 7 > >)));
	BOOST_TEST((rt_id(d23) == (id< dims_t< 4, 0 > >)));
	BOOST_TEST((rt_id(d24) == (id< dims_t< 4, 0 > >)));
	BOOST_TEST((rt_id(d25) == (id< dims_t< 4, 7 > >)));
	BOOST_TEST((rt_id(d26) == (id< dims_t< 4, 0 > >)));

	BOOST_TEST((rt_id(d33) == (id< dims_t< 0, 0 > >)));
	BOOST_TEST((rt_id(d34) == (id< dims_t< 0, 0 > >)));
	BOOST_TEST((rt_id(d35) == (id< dims_t< 0, 7 > >)));
	BOOST_TEST((rt_id(d36) == (id< dims_t< 0, 0 > >)));

	BOOST_TEST((rt_id(d44) == (id< dims_t< 0, 0 > >)));
	BOOST_TEST((rt_id(d45) == (id< dims_t< 0, 7 > >)));
	BOOST_TEST((rt_id(d46) == (id< dims_t< 0, 0 > >)));

	BOOST_TEST((rt_id(d55) == (id< dims_t< 4, 7 > >)));
	BOOST_TEST((rt_id(d56) == (id< dims_t< 4, 0 > >)));

	BOOST_TEST((rt_id(d66) == (id< dims_t< 0, 0 > >)));
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


	BOOST_TEST((CP(d1 == d1)));
	BOOST_TEST((CP(d1 == d2)));
	BOOST_TEST((CP(d1 == d3)));
	BOOST_TEST((CP(d1 == d4)));
	BOOST_TEST((CP(d1 != d5)));
	BOOST_TEST((CP(d1 != d6)));
	BOOST_TEST((CP(d1 != d7)));
	BOOST_TEST((CP(d1 != d8)));

	BOOST_TEST((CP(d2 == d1)));
	BOOST_TEST((CP(d2 == d2)));
	BOOST_TEST((CP(d2 == d3)));
	BOOST_TEST((CP(d2 == d4)));
	BOOST_TEST((CP(d2 != d5)));
	BOOST_TEST((CP(d2 != d6)));
	BOOST_TEST((CP(d2 != d7)));
	BOOST_TEST((CP(d2 != d8)));

	BOOST_TEST((CP(d3 == d1)));
	BOOST_TEST((CP(d3 == d2)));
	BOOST_TEST((CP(d3 == d3)));
	BOOST_TEST((CP(d3 == d4)));
	BOOST_TEST((CP(d3 != d5)));
	BOOST_TEST((CP(d3 != d6)));
	BOOST_TEST((CP(d3 != d7)));
	BOOST_TEST((CP(d3 != d8)));

	BOOST_TEST((CP(d4 == d1)));
	BOOST_TEST((CP(d4 == d2)));
	BOOST_TEST((CP(d4 == d3)));
	BOOST_TEST((CP(d4 == d4)));
	BOOST_TEST((CP(d4 != d5)));
	BOOST_TEST((CP(d4 != d6)));
	BOOST_TEST((CP(d4 != d7)));
	BOOST_TEST((CP(d4 != d8)));

	BOOST_TEST((CP(d5 != d1)));
	BOOST_TEST((CP(d5 != d2)));
	BOOST_TEST((CP(d5 != d3)));
	BOOST_TEST((CP(d5 != d4)));
	BOOST_TEST((CP(d5 == d5)));
	BOOST_TEST((CP(d5 == d6)));
	BOOST_TEST((CP(d5 == d7)));
	BOOST_TEST((CP(d5 == d8)));

	BOOST_TEST((CP(d6 != d1)));
	BOOST_TEST((CP(d6 != d2)));
	BOOST_TEST((CP(d6 != d3)));
	BOOST_TEST((CP(d6 != d4)));
	BOOST_TEST((CP(d6 == d5)));
	BOOST_TEST((CP(d6 == d6)));
	BOOST_TEST((CP(d6 == d7)));
	BOOST_TEST((CP(d6 == d8)));

	BOOST_TEST((CP(d7 != d1)));
	BOOST_TEST((CP(d7 != d2)));
	BOOST_TEST((CP(d7 != d3)));
	BOOST_TEST((CP(d7 != d4)));
	BOOST_TEST((CP(d7 == d5)));
	BOOST_TEST((CP(d7 == d6)));
	BOOST_TEST((CP(d7 == d7)));
	BOOST_TEST((CP(d7 == d8)));

	BOOST_TEST((CP(d8 != d1)));
	BOOST_TEST((CP(d8 != d2)));
	BOOST_TEST((CP(d8 != d3)));
	BOOST_TEST((CP(d8 != d4)));
	BOOST_TEST((CP(d8 == d5)));
	BOOST_TEST((CP(d8 == d6)));
	BOOST_TEST((CP(d8 == d7)));
	BOOST_TEST((CP(d8 == d8)));


	BOOST_TEST((!CP(d1 != d1)));
	BOOST_TEST((!CP(d1 != d2)));
	BOOST_TEST((!CP(d1 != d3)));
	BOOST_TEST((!CP(d1 != d4)));
	BOOST_TEST((!CP(d1 == d5)));
	BOOST_TEST((!CP(d1 == d6)));
	BOOST_TEST((!CP(d1 == d7)));
	BOOST_TEST((!CP(d1 == d8)));

	BOOST_TEST((!CP(d2 != d1)));
	BOOST_TEST((!CP(d2 != d2)));
	BOOST_TEST((!CP(d2 != d3)));
	BOOST_TEST((!CP(d2 != d4)));
	BOOST_TEST((!CP(d2 == d5)));
	BOOST_TEST((!CP(d2 == d6)));
	BOOST_TEST((!CP(d2 == d7)));
	BOOST_TEST((!CP(d2 == d8)));

	BOOST_TEST((!CP(d3 != d1)));
	BOOST_TEST((!CP(d3 != d2)));
	BOOST_TEST((!CP(d3 != d3)));
	BOOST_TEST((!CP(d3 != d4)));
	BOOST_TEST((!CP(d3 == d5)));
	BOOST_TEST((!CP(d3 == d6)));
	BOOST_TEST((!CP(d3 == d7)));
	BOOST_TEST((!CP(d3 == d8)));

	BOOST_TEST((!CP(d4 != d1)));
	BOOST_TEST((!CP(d4 != d2)));
	BOOST_TEST((!CP(d4 != d3)));
	BOOST_TEST((!CP(d4 != d4)));
	BOOST_TEST((!CP(d4 == d5)));
	BOOST_TEST((!CP(d4 == d6)));
	BOOST_TEST((!CP(d4 == d7)));
	BOOST_TEST((!CP(d4 == d8)));

	BOOST_TEST((!CP(d5 == d1)));
	BOOST_TEST((!CP(d5 == d2)));
	BOOST_TEST((!CP(d5 == d3)));
	BOOST_TEST((!CP(d5 == d4)));
	BOOST_TEST((!CP(d5 != d5)));
	BOOST_TEST((!CP(d5 != d6)));
	BOOST_TEST((!CP(d5 != d7)));
	BOOST_TEST((!CP(d5 != d8)));

	BOOST_TEST((!CP(d6 == d1)));
	BOOST_TEST((!CP(d6 == d2)));
	BOOST_TEST((!CP(d6 == d3)));
	BOOST_TEST((!CP(d6 == d4)));
	BOOST_TEST((!CP(d6 != d5)));
	BOOST_TEST((!CP(d6 != d6)));
	BOOST_TEST((!CP(d6 != d7)));
	BOOST_TEST((!CP(d6 != d8)));

	BOOST_TEST((!CP(d7 == d1)));
	BOOST_TEST((!CP(d7 == d2)));
	BOOST_TEST((!CP(d7 == d3)));
	BOOST_TEST((!CP(d7 == d4)));
	BOOST_TEST((!CP(d7 != d5)));
	BOOST_TEST((!CP(d7 != d6)));
	BOOST_TEST((!CP(d7 != d7)));
	BOOST_TEST((!CP(d7 != d8)));

	BOOST_TEST((!CP(d8 == d1)));
	BOOST_TEST((!CP(d8 == d2)));
	BOOST_TEST((!CP(d8 == d3)));
	BOOST_TEST((!CP(d8 == d4)));
	BOOST_TEST((!CP(d8 != d5)));
	BOOST_TEST((!CP(d8 != d6)));
	BOOST_TEST((!CP(d8 != d7)));
	BOOST_TEST((!CP(d8 != d8)));
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

	BOOST_TEST((CP(d11 + d21 == dims(13_C, 13_R))));
	BOOST_TEST((CP(d11 + d22 == dims(13_C, 13_R))));
	BOOST_TEST((CP(d11 + d23 == dims(13_C, 13_R))));
	BOOST_TEST((CP(d11 + d24 == dims(13_C, 13_R))));
	BOOST_TEST((CP(d12 + d21 == dims(13_C, 13_R))));
	BOOST_TEST((CP(d12 + d22 == dims(13_C, 13_R))));
	BOOST_TEST((CP(d12 + d23 == dims(13_C, 13_R))));
	BOOST_TEST((CP(d12 + d24 == dims(13_C, 13_R))));
	BOOST_TEST((CP(d13 + d21 == dims(13_C, 13_R))));
	BOOST_TEST((CP(d13 + d22 == dims(13_C, 13_R))));
	BOOST_TEST((CP(d13 + d23 == dims(13_C, 13_R))));
	BOOST_TEST((CP(d13 + d24 == dims(13_C, 13_R))));
	BOOST_TEST((CP(d14 + d21 == dims(13_C, 13_R))));
	BOOST_TEST((CP(d14 + d22 == dims(13_C, 13_R))));
	BOOST_TEST((CP(d14 + d23 == dims(13_C, 13_R))));
	BOOST_TEST((CP(d14 + d24 == dims(13_C, 13_R))));

	BOOST_TEST((rt_id(d11 + d21) == (id< dims_t< 13, 13 > >)));
	BOOST_TEST((rt_id(d11 + d22) == (id< dims_t<  0, 13 > >)));
	BOOST_TEST((rt_id(d11 + d23) == (id< dims_t< 13,  0 > >)));
	BOOST_TEST((rt_id(d11 + d24) == (id< dims_t<  0,  0 > >)));
	BOOST_TEST((rt_id(d12 + d21) == (id< dims_t<  0, 13 > >)));
	BOOST_TEST((rt_id(d12 + d22) == (id< dims_t<  0, 13 > >)));
	BOOST_TEST((rt_id(d12 + d23) == (id< dims_t<  0,  0 > >)));
	BOOST_TEST((rt_id(d12 + d24) == (id< dims_t<  0,  0 > >)));
	BOOST_TEST((rt_id(d13 + d21) == (id< dims_t< 13,  0 > >)));
	BOOST_TEST((rt_id(d13 + d22) == (id< dims_t<  0,  0 > >)));
	BOOST_TEST((rt_id(d13 + d23) == (id< dims_t< 13,  0 > >)));
	BOOST_TEST((rt_id(d13 + d24) == (id< dims_t<  0,  0 > >)));
	BOOST_TEST((rt_id(d14 + d21) == (id< dims_t<  0,  0 > >)));
	BOOST_TEST((rt_id(d14 + d22) == (id< dims_t<  0,  0 > >)));
	BOOST_TEST((rt_id(d14 + d23) == (id< dims_t<  0,  0 > >)));
	BOOST_TEST((rt_id(d14 + d24) == (id< dims_t<  0,  0 > >)));

	BOOST_TEST((CP(d11 - d21 == dims(5_C, 5_R))));
	BOOST_TEST((CP(d11 - d22 == dims(5_C, 5_R))));
	BOOST_TEST((CP(d11 - d23 == dims(5_C, 5_R))));
	BOOST_TEST((CP(d11 - d24 == dims(5_C, 5_R))));
	BOOST_TEST((CP(d12 - d21 == dims(5_C, 5_R))));
	BOOST_TEST((CP(d12 - d22 == dims(5_C, 5_R))));
	BOOST_TEST((CP(d12 - d23 == dims(5_C, 5_R))));
	BOOST_TEST((CP(d12 - d24 == dims(5_C, 5_R))));
	BOOST_TEST((CP(d13 - d21 == dims(5_C, 5_R))));
	BOOST_TEST((CP(d13 - d22 == dims(5_C, 5_R))));
	BOOST_TEST((CP(d13 - d23 == dims(5_C, 5_R))));
	BOOST_TEST((CP(d13 - d24 == dims(5_C, 5_R))));
	BOOST_TEST((CP(d14 - d21 == dims(5_C, 5_R))));
	BOOST_TEST((CP(d14 - d22 == dims(5_C, 5_R))));
	BOOST_TEST((CP(d14 - d23 == dims(5_C, 5_R))));
	BOOST_TEST((CP(d14 - d24 == dims(5_C, 5_R))));

	BOOST_TEST((rt_id(d11 - d21) == (id< dims_t< 5, 5 > >)));
	BOOST_TEST((rt_id(d11 - d22) == (id< dims_t< 0, 5 > >)));
	BOOST_TEST((rt_id(d11 - d23) == (id< dims_t< 5, 0 > >)));
	BOOST_TEST((rt_id(d11 - d24) == (id< dims_t< 0, 0 > >)));
	BOOST_TEST((rt_id(d12 - d21) == (id< dims_t< 0, 5 > >)));
	BOOST_TEST((rt_id(d12 - d22) == (id< dims_t< 0, 5 > >)));
	BOOST_TEST((rt_id(d12 - d23) == (id< dims_t< 0, 0 > >)));
	BOOST_TEST((rt_id(d12 - d24) == (id< dims_t< 0, 0 > >)));
	BOOST_TEST((rt_id(d13 - d21) == (id< dims_t< 5, 0 > >)));
	BOOST_TEST((rt_id(d13 - d22) == (id< dims_t< 0, 0 > >)));
	BOOST_TEST((rt_id(d13 - d23) == (id< dims_t< 5, 0 > >)));
	BOOST_TEST((rt_id(d13 - d24) == (id< dims_t< 0, 0 > >)));
	BOOST_TEST((rt_id(d14 - d21) == (id< dims_t< 0, 0 > >)));
	BOOST_TEST((rt_id(d14 - d22) == (id< dims_t< 0, 0 > >)));
	BOOST_TEST((rt_id(d14 - d23) == (id< dims_t< 0, 0 > >)));
	BOOST_TEST((rt_id(d14 - d24) == (id< dims_t< 0, 0 > >)));

	BOOST_TEST((CP(d11 * d21 == dims(36_C, 36_R))));
	BOOST_TEST((CP(d11 * d22 == dims(36_C, 36_R))));
	BOOST_TEST((CP(d11 * d23 == dims(36_C, 36_R))));
	BOOST_TEST((CP(d11 * d24 == dims(36_C, 36_R))));
	BOOST_TEST((CP(d12 * d21 == dims(36_C, 36_R))));
	BOOST_TEST((CP(d12 * d22 == dims(36_C, 36_R))));
	BOOST_TEST((CP(d12 * d23 == dims(36_C, 36_R))));
	BOOST_TEST((CP(d12 * d24 == dims(36_C, 36_R))));
	BOOST_TEST((CP(d13 * d21 == dims(36_C, 36_R))));
	BOOST_TEST((CP(d13 * d22 == dims(36_C, 36_R))));
	BOOST_TEST((CP(d13 * d23 == dims(36_C, 36_R))));
	BOOST_TEST((CP(d13 * d24 == dims(36_C, 36_R))));
	BOOST_TEST((CP(d14 * d21 == dims(36_C, 36_R))));
	BOOST_TEST((CP(d14 * d22 == dims(36_C, 36_R))));
	BOOST_TEST((CP(d14 * d23 == dims(36_C, 36_R))));
	BOOST_TEST((CP(d14 * d24 == dims(36_C, 36_R))));

	BOOST_TEST((rt_id(d11 * d21) == (id< dims_t< 36, 36 > >)));
	BOOST_TEST((rt_id(d11 * d22) == (id< dims_t<  0, 36 > >)));
	BOOST_TEST((rt_id(d11 * d23) == (id< dims_t< 36,  0 > >)));
	BOOST_TEST((rt_id(d11 * d24) == (id< dims_t<  0,  0 > >)));
	BOOST_TEST((rt_id(d12 * d21) == (id< dims_t<  0, 36 > >)));
	BOOST_TEST((rt_id(d12 * d22) == (id< dims_t<  0, 36 > >)));
	BOOST_TEST((rt_id(d12 * d23) == (id< dims_t<  0,  0 > >)));
	BOOST_TEST((rt_id(d12 * d24) == (id< dims_t<  0,  0 > >)));
	BOOST_TEST((rt_id(d13 * d21) == (id< dims_t< 36,  0 > >)));
	BOOST_TEST((rt_id(d13 * d22) == (id< dims_t<  0,  0 > >)));
	BOOST_TEST((rt_id(d13 * d23) == (id< dims_t< 36,  0 > >)));
	BOOST_TEST((rt_id(d13 * d24) == (id< dims_t<  0,  0 > >)));
	BOOST_TEST((rt_id(d14 * d21) == (id< dims_t<  0,  0 > >)));
	BOOST_TEST((rt_id(d14 * d22) == (id< dims_t<  0,  0 > >)));
	BOOST_TEST((rt_id(d14 * d23) == (id< dims_t<  0,  0 > >)));
	BOOST_TEST((rt_id(d14 * d24) == (id< dims_t<  0,  0 > >)));

	BOOST_TEST((CP(d11 / d21 == dims(2_C, 2_R))));
	BOOST_TEST((CP(d11 / d22 == dims(2_C, 2_R))));
	BOOST_TEST((CP(d11 / d23 == dims(2_C, 2_R))));
	BOOST_TEST((CP(d11 / d24 == dims(2_C, 2_R))));
	BOOST_TEST((CP(d12 / d21 == dims(2_C, 2_R))));
	BOOST_TEST((CP(d12 / d22 == dims(2_C, 2_R))));
	BOOST_TEST((CP(d12 / d23 == dims(2_C, 2_R))));
	BOOST_TEST((CP(d12 / d24 == dims(2_C, 2_R))));
	BOOST_TEST((CP(d13 / d21 == dims(2_C, 2_R))));
	BOOST_TEST((CP(d13 / d22 == dims(2_C, 2_R))));
	BOOST_TEST((CP(d13 / d23 == dims(2_C, 2_R))));
	BOOST_TEST((CP(d13 / d24 == dims(2_C, 2_R))));
	BOOST_TEST((CP(d14 / d21 == dims(2_C, 2_R))));
	BOOST_TEST((CP(d14 / d22 == dims(2_C, 2_R))));
	BOOST_TEST((CP(d14 / d23 == dims(2_C, 2_R))));
	BOOST_TEST((CP(d14 / d24 == dims(2_C, 2_R))));

	BOOST_TEST((rt_id(d11 / d21) == (id< dims_t< 2, 2 > >)));
	BOOST_TEST((rt_id(d11 / d22) == (id< dims_t< 0, 2 > >)));
	BOOST_TEST((rt_id(d11 / d23) == (id< dims_t< 2, 0 > >)));
	BOOST_TEST((rt_id(d11 / d24) == (id< dims_t< 0, 0 > >)));
	BOOST_TEST((rt_id(d12 / d21) == (id< dims_t< 0, 2 > >)));
	BOOST_TEST((rt_id(d12 / d22) == (id< dims_t< 0, 2 > >)));
	BOOST_TEST((rt_id(d12 / d23) == (id< dims_t< 0, 0 > >)));
	BOOST_TEST((rt_id(d12 / d24) == (id< dims_t< 0, 0 > >)));
	BOOST_TEST((rt_id(d13 / d21) == (id< dims_t< 2, 0 > >)));
	BOOST_TEST((rt_id(d13 / d22) == (id< dims_t< 0, 0 > >)));
	BOOST_TEST((rt_id(d13 / d23) == (id< dims_t< 2, 0 > >)));
	BOOST_TEST((rt_id(d13 / d24) == (id< dims_t< 0, 0 > >)));
	BOOST_TEST((rt_id(d14 / d21) == (id< dims_t< 0, 0 > >)));
	BOOST_TEST((rt_id(d14 / d22) == (id< dims_t< 0, 0 > >)));
	BOOST_TEST((rt_id(d14 / d23) == (id< dims_t< 0, 0 > >)));
	BOOST_TEST((rt_id(d14 / d24) == (id< dims_t< 0, 0 > >)));

	BOOST_TEST((CP(d11 % d21 == dims(1_C, 1_R))));
	BOOST_TEST((CP(d11 % d22 == dims(1_C, 1_R))));
	BOOST_TEST((CP(d11 % d23 == dims(1_C, 1_R))));
	BOOST_TEST((CP(d11 % d24 == dims(1_C, 1_R))));
	BOOST_TEST((CP(d12 % d21 == dims(1_C, 1_R))));
	BOOST_TEST((CP(d12 % d22 == dims(1_C, 1_R))));
	BOOST_TEST((CP(d12 % d23 == dims(1_C, 1_R))));
	BOOST_TEST((CP(d12 % d24 == dims(1_C, 1_R))));
	BOOST_TEST((CP(d13 % d21 == dims(1_C, 1_R))));
	BOOST_TEST((CP(d13 % d22 == dims(1_C, 1_R))));
	BOOST_TEST((CP(d13 % d23 == dims(1_C, 1_R))));
	BOOST_TEST((CP(d13 % d24 == dims(1_C, 1_R))));
	BOOST_TEST((CP(d14 % d21 == dims(1_C, 1_R))));
	BOOST_TEST((CP(d14 % d22 == dims(1_C, 1_R))));
	BOOST_TEST((CP(d14 % d23 == dims(1_C, 1_R))));
	BOOST_TEST((CP(d14 % d24 == dims(1_C, 1_R))));

	BOOST_TEST((rt_id(d11 % d21) == (id< dims_t< 1, 1 > >)));
	BOOST_TEST((rt_id(d11 % d22) == (id< dims_t< 0, 1 > >)));
	BOOST_TEST((rt_id(d11 % d23) == (id< dims_t< 1, 0 > >)));
	BOOST_TEST((rt_id(d11 % d24) == (id< dims_t< 0, 0 > >)));
	BOOST_TEST((rt_id(d12 % d21) == (id< dims_t< 0, 1 > >)));
	BOOST_TEST((rt_id(d12 % d22) == (id< dims_t< 0, 1 > >)));
	BOOST_TEST((rt_id(d12 % d23) == (id< dims_t< 0, 0 > >)));
	BOOST_TEST((rt_id(d12 % d24) == (id< dims_t< 0, 0 > >)));
	BOOST_TEST((rt_id(d13 % d21) == (id< dims_t< 1, 0 > >)));
	BOOST_TEST((rt_id(d13 % d22) == (id< dims_t< 0, 0 > >)));
	BOOST_TEST((rt_id(d13 % d23) == (id< dims_t< 1, 0 > >)));
	BOOST_TEST((rt_id(d13 % d24) == (id< dims_t< 0, 0 > >)));
	BOOST_TEST((rt_id(d14 % d21) == (id< dims_t< 0, 0 > >)));
	BOOST_TEST((rt_id(d14 % d22) == (id< dims_t< 0, 0 > >)));
	BOOST_TEST((rt_id(d14 % d23) == (id< dims_t< 0, 0 > >)));
	BOOST_TEST((rt_id(d14 % d24) == (id< dims_t< 0, 0 > >)));

	BOOST_TEST((CP(d11 * 4 == dims(36_C, 36_R))));
	BOOST_TEST((CP(d12 * 4 == dims(36_C, 36_R))));
	BOOST_TEST((CP(d13 * 4 == dims(36_C, 36_R))));
	BOOST_TEST((CP(d14 * 4 == dims(36_C, 36_R))));

	BOOST_TEST((rt_id(d11 * 4) == (id< dims_t< 0, 0 > >)));
	BOOST_TEST((rt_id(d12 * 4) == (id< dims_t< 0, 0 > >)));
	BOOST_TEST((rt_id(d13 * 4) == (id< dims_t< 0, 0 > >)));
	BOOST_TEST((rt_id(d14 * 4) == (id< dims_t< 0, 0 > >)));

	BOOST_TEST((CP(d11 / 4 == dims(2_C, 2_R))));
	BOOST_TEST((CP(d12 / 4 == dims(2_C, 2_R))));
	BOOST_TEST((CP(d13 / 4 == dims(2_C, 2_R))));
	BOOST_TEST((CP(d14 / 4 == dims(2_C, 2_R))));

	BOOST_TEST((rt_id(d11 / 4) == (id< dims_t< 0, 0 > >)));
	BOOST_TEST((rt_id(d12 / 4) == (id< dims_t< 0, 0 > >)));
	BOOST_TEST((rt_id(d13 / 4) == (id< dims_t< 0, 0 > >)));
	BOOST_TEST((rt_id(d14 / 4) == (id< dims_t< 0, 0 > >)));

	BOOST_TEST((CP(d11 % 4 == dims(1_C, 1_R))));
	BOOST_TEST((CP(d12 % 4 == dims(1_C, 1_R))));
	BOOST_TEST((CP(d13 % 4 == dims(1_C, 1_R))));
	BOOST_TEST((CP(d14 % 4 == dims(1_C, 1_R))));

	BOOST_TEST((rt_id(d11 % 4) == (id< dims_t< 0, 0 > >)));
	BOOST_TEST((rt_id(d12 % 4) == (id< dims_t< 0, 0 > >)));
	BOOST_TEST((rt_id(d13 % 4) == (id< dims_t< 0, 0 > >)));
	BOOST_TEST((rt_id(d14 % 4) == (id< dims_t< 0, 0 > >)));
}


BOOST_AUTO_TEST_CASE(test_get_col_t){
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

	BOOST_TEST((res01 == 7));
	BOOST_TEST((res02 == 7));
	BOOST_TEST((res03 == 7));
	BOOST_TEST((res04 == 7));
	BOOST_TEST((res05 == 7));
	BOOST_TEST((res06 == 7));
	BOOST_TEST((res07 == 7));
	BOOST_TEST((res08 == 7));
	BOOST_TEST((res09 == 7));
	BOOST_TEST((res10 == 7));
	BOOST_TEST((res11 == 7));
	BOOST_TEST((res12 == 7));
	BOOST_TEST((res13 == 7));
	BOOST_TEST((res14 == 7));
	BOOST_TEST((res15 == 7));
	BOOST_TEST((res16 == 7));
	BOOST_TEST((res17 == 7));
	BOOST_TEST((res18 == 7));
	BOOST_TEST((res19 == 7));
	BOOST_TEST((res20 == 7));
	BOOST_TEST((res21 == 7));
	BOOST_TEST((res22 == 7));
	BOOST_TEST((res23 == 7));
	BOOST_TEST((res24 == 7));
	BOOST_TEST((res25 == 7));
	BOOST_TEST((res26 == 7));
	BOOST_TEST((res27 == 7));
	BOOST_TEST((res28 == 7));
	BOOST_TEST((res29 == 7));
	BOOST_TEST((res30 == 7));
	BOOST_TEST((res31 == 7));
	BOOST_TEST((res32 == 7));
	BOOST_TEST((res33 == 7));

	BOOST_TEST((rt_id(res01) == (id< col_t< true, 7 > >)));
	BOOST_TEST((rt_id(res02) == (id< col_t< false, 7 > >)));
	BOOST_TEST((rt_id(res03) == (id< col_t< false, 0 > >)));
	BOOST_TEST((rt_id(res04) == (id< col_t< true, 7 > >)));
	BOOST_TEST((rt_id(res05) == (id< col_t< false, 7 > >)));
	BOOST_TEST((rt_id(res06) == (id< col_t< false, 0 > >)));
	BOOST_TEST((rt_id(res07) == (id< col_t< true, 7 > >)));
	BOOST_TEST((rt_id(res08) == (id< col_t< true, 7 > >)));
	BOOST_TEST((rt_id(res09) == (id< col_t< true, 7 > >)));
	BOOST_TEST((rt_id(res10) == (id< col_t< false, 7 > >)));
	BOOST_TEST((rt_id(res11) == (id< col_t< true, 7 > >)));
	BOOST_TEST((rt_id(res12) == (id< col_t< false, 7 > >)));
	BOOST_TEST((rt_id(res13) == (id< col_t< true, 7 > >)));
	BOOST_TEST((rt_id(res14) == (id< col_t< false, 7 > >)));
	BOOST_TEST((rt_id(res15) == (id< col_t< false, 0 > >)));
	BOOST_TEST((rt_id(res16) == (id< col_t< true, 7 > >)));
	BOOST_TEST((rt_id(res17) == (id< col_t< true, 7 > >)));
	BOOST_TEST((rt_id(res18) == (id< col_t< true, 7 > >)));
	BOOST_TEST((rt_id(res19) == (id< col_t< true, 7 > >)));
	BOOST_TEST((rt_id(res20) == (id< col_t< true, 7 > >)));
	BOOST_TEST((rt_id(res21) == (id< col_t< true, 7 > >)));
	BOOST_TEST((rt_id(res22) == (id< col_t< true, 7 > >)));
	BOOST_TEST((rt_id(res23) == (id< col_t< true, 7 > >)));
	BOOST_TEST((rt_id(res24) == (id< col_t< true, 7 > >)));
	BOOST_TEST((rt_id(res25) == (id< col_t< true, 7 > >)));
	BOOST_TEST((rt_id(res26) == (id< col_t< false, 7 > >)));
	BOOST_TEST((rt_id(res27) == (id< col_t< false, 7 > >)));
	BOOST_TEST((rt_id(res28) == (id< col_t< true, 7 > >)));
	BOOST_TEST((rt_id(res29) == (id< col_t< true, 7 > >)));
	BOOST_TEST((rt_id(res30) == (id< col_t< true, 7 > >)));
	BOOST_TEST((rt_id(res31) == (id< col_t< true, 7 > >)));
	BOOST_TEST((rt_id(res32) == (id< col_t< false, 7 > >)));
	BOOST_TEST((rt_id(res33) == (id< col_t< false, 7 > >)));
}


BOOST_AUTO_TEST_CASE(test_get_row_t){
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

	BOOST_TEST((res01 == 7));
	BOOST_TEST((res02 == 7));
	BOOST_TEST((res03 == 7));
	BOOST_TEST((res04 == 7));
	BOOST_TEST((res05 == 7));
	BOOST_TEST((res06 == 7));
	BOOST_TEST((res07 == 7));
	BOOST_TEST((res08 == 7));
	BOOST_TEST((res09 == 7));
	BOOST_TEST((res10 == 7));
	BOOST_TEST((res11 == 7));
	BOOST_TEST((res12 == 7));
	BOOST_TEST((res13 == 7));
	BOOST_TEST((res14 == 7));
	BOOST_TEST((res15 == 7));
	BOOST_TEST((res16 == 7));
	BOOST_TEST((res17 == 7));
	BOOST_TEST((res18 == 7));
	BOOST_TEST((res19 == 7));
	BOOST_TEST((res20 == 7));
	BOOST_TEST((res21 == 7));
	BOOST_TEST((res22 == 7));
	BOOST_TEST((res23 == 7));
	BOOST_TEST((res24 == 7));
	BOOST_TEST((res25 == 7));
	BOOST_TEST((res26 == 7));
	BOOST_TEST((res27 == 7));
	BOOST_TEST((res28 == 7));
	BOOST_TEST((res29 == 7));
	BOOST_TEST((res30 == 7));
	BOOST_TEST((res31 == 7));
	BOOST_TEST((res32 == 7));
	BOOST_TEST((res33 == 7));

	BOOST_TEST((rt_id(res01) == (id< row_t< true, 7 > >)));
	BOOST_TEST((rt_id(res02) == (id< row_t< false, 7 > >)));
	BOOST_TEST((rt_id(res03) == (id< row_t< false, 0 > >)));
	BOOST_TEST((rt_id(res04) == (id< row_t< true, 7 > >)));
	BOOST_TEST((rt_id(res05) == (id< row_t< false, 7 > >)));
	BOOST_TEST((rt_id(res06) == (id< row_t< false, 0 > >)));
	BOOST_TEST((rt_id(res07) == (id< row_t< true, 7 > >)));
	BOOST_TEST((rt_id(res08) == (id< row_t< true, 7 > >)));
	BOOST_TEST((rt_id(res09) == (id< row_t< true, 7 > >)));
	BOOST_TEST((rt_id(res10) == (id< row_t< false, 7 > >)));
	BOOST_TEST((rt_id(res11) == (id< row_t< true, 7 > >)));
	BOOST_TEST((rt_id(res12) == (id< row_t< false, 7 > >)));
	BOOST_TEST((rt_id(res13) == (id< row_t< true, 7 > >)));
	BOOST_TEST((rt_id(res14) == (id< row_t< false, 7 > >)));
	BOOST_TEST((rt_id(res15) == (id< row_t< false, 0 > >)));
	BOOST_TEST((rt_id(res16) == (id< row_t< true, 7 > >)));
	BOOST_TEST((rt_id(res17) == (id< row_t< true, 7 > >)));
	BOOST_TEST((rt_id(res18) == (id< row_t< true, 7 > >)));
	BOOST_TEST((rt_id(res19) == (id< row_t< true, 7 > >)));
	BOOST_TEST((rt_id(res20) == (id< row_t< true, 7 > >)));
	BOOST_TEST((rt_id(res21) == (id< row_t< true, 7 > >)));
	BOOST_TEST((rt_id(res22) == (id< row_t< true, 7 > >)));
	BOOST_TEST((rt_id(res23) == (id< row_t< true, 7 > >)));
	BOOST_TEST((rt_id(res24) == (id< row_t< true, 7 > >)));
	BOOST_TEST((rt_id(res25) == (id< row_t< true, 7 > >)));
	BOOST_TEST((rt_id(res26) == (id< row_t< false, 7 > >)));
	BOOST_TEST((rt_id(res27) == (id< row_t< false, 7 > >)));
	BOOST_TEST((rt_id(res28) == (id< row_t< true, 7 > >)));
	BOOST_TEST((rt_id(res29) == (id< row_t< true, 7 > >)));
	BOOST_TEST((rt_id(res30) == (id< row_t< true, 7 > >)));
	BOOST_TEST((rt_id(res31) == (id< row_t< true, 7 > >)));
	BOOST_TEST((rt_id(res32) == (id< row_t< false, 7 > >)));
	BOOST_TEST((rt_id(res33) == (id< row_t< false, 7 > >)));
}


BOOST_AUTO_TEST_CASE(test_get_dim_t){
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

	BOOST_TEST((res01 == 7));
	BOOST_TEST((res02 == 7));
	BOOST_TEST((res03 == 7));
	BOOST_TEST((res04 == 7));
	BOOST_TEST((res05 == 7));
	BOOST_TEST((res06 == 7));
	BOOST_TEST((res07 == 7));
	BOOST_TEST((res08 == 7));
	BOOST_TEST((res09 == 7));
	BOOST_TEST((res10 == 7));
	BOOST_TEST((res11 == 7));
	BOOST_TEST((res12 == 7));
	BOOST_TEST((res13 == 7));
	BOOST_TEST((res14 == 7));
	BOOST_TEST((res15 == 7));
	BOOST_TEST((res16 == 7));
	BOOST_TEST((res17 == 7));
	BOOST_TEST((res18 == 7));
	BOOST_TEST((res19 == 7));
	BOOST_TEST((res20 == 7));
	BOOST_TEST((res21 == 7));
	BOOST_TEST((res22 == 7));
	BOOST_TEST((res23 == 7));
	BOOST_TEST((res24 == 7));
	BOOST_TEST((res25 == 7));
	BOOST_TEST((res26 == 7));
	BOOST_TEST((res27 == 7));
	BOOST_TEST((res28 == 7));
	BOOST_TEST((res29 == 7));
	BOOST_TEST((res30 == 7));
	BOOST_TEST((res31 == 7));
	BOOST_TEST((res32 == 7));
	BOOST_TEST((res33 == 7));

	BOOST_TEST((rt_id(res01) == (id< dim_t< true, 7 > >)));
	BOOST_TEST((rt_id(res02) == (id< dim_t< false, 7 > >)));
	BOOST_TEST((rt_id(res03) == (id< dim_t< false, 0 > >)));
	BOOST_TEST((rt_id(res04) == (id< dim_t< true, 7 > >)));
	BOOST_TEST((rt_id(res05) == (id< dim_t< false, 7 > >)));
	BOOST_TEST((rt_id(res06) == (id< dim_t< false, 0 > >)));
	BOOST_TEST((rt_id(res07) == (id< dim_t< true, 7 > >)));
	BOOST_TEST((rt_id(res08) == (id< dim_t< true, 7 > >)));
	BOOST_TEST((rt_id(res09) == (id< dim_t< true, 7 > >)));
	BOOST_TEST((rt_id(res10) == (id< dim_t< false, 7 > >)));
	BOOST_TEST((rt_id(res11) == (id< dim_t< true, 7 > >)));
	BOOST_TEST((rt_id(res12) == (id< dim_t< false, 7 > >)));
	BOOST_TEST((rt_id(res13) == (id< dim_t< true, 7 > >)));
	BOOST_TEST((rt_id(res14) == (id< dim_t< false, 7 > >)));
	BOOST_TEST((rt_id(res15) == (id< dim_t< false, 0 > >)));
	BOOST_TEST((rt_id(res16) == (id< dim_t< true, 7 > >)));
	BOOST_TEST((rt_id(res17) == (id< dim_t< true, 7 > >)));
	BOOST_TEST((rt_id(res18) == (id< dim_t< true, 7 > >)));
	BOOST_TEST((rt_id(res19) == (id< dim_t< true, 7 > >)));
	BOOST_TEST((rt_id(res20) == (id< dim_t< true, 7 > >)));
	BOOST_TEST((rt_id(res21) == (id< dim_t< true, 7 > >)));
	BOOST_TEST((rt_id(res22) == (id< dim_t< true, 7 > >)));
	BOOST_TEST((rt_id(res23) == (id< dim_t< true, 7 > >)));
	BOOST_TEST((rt_id(res24) == (id< dim_t< true, 7 > >)));
	BOOST_TEST((rt_id(res25) == (id< dim_t< true, 7 > >)));
	BOOST_TEST((rt_id(res26) == (id< dim_t< false, 7 > >)));
	BOOST_TEST((rt_id(res27) == (id< dim_t< false, 7 > >)));
	BOOST_TEST((rt_id(res28) == (id< dim_t< true, 7 > >)));
	BOOST_TEST((rt_id(res29) == (id< dim_t< true, 7 > >)));
	BOOST_TEST((rt_id(res30) == (id< dim_t< true, 7 > >)));
	BOOST_TEST((rt_id(res31) == (id< dim_t< true, 7 > >)));
	BOOST_TEST((rt_id(res32) == (id< dim_t< false, 7 > >)));
	BOOST_TEST((rt_id(res33) == (id< dim_t< false, 7 > >)));
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

	BOOST_TEST(((res01 == dims(7, 7))));
	BOOST_TEST(((res02 == dims(7, 7))));
	BOOST_TEST(((res03 == dims(7, 7))));
	BOOST_TEST(((res04 == dims(7, 7))));
	BOOST_TEST(((res05 == dims(7, 7))));
	BOOST_TEST(((res06 == dims(7, 7))));
	BOOST_TEST(((res07 == dims(7, 7))));
	BOOST_TEST(((res08 == dims(7, 7))));
	BOOST_TEST(((res09 == dims(7, 7))));
	BOOST_TEST(((res10 == dims(7, 7))));
	BOOST_TEST(((res11 == dims(7, 7))));
	BOOST_TEST(((res12 == dims(7, 7))));
	BOOST_TEST(((res13 == dims(7, 7))));
	BOOST_TEST(((res14 == dims(7, 7))));
	BOOST_TEST(((res15 == dims(7, 7))));
	BOOST_TEST(((res16 == dims(7, 7))));
	BOOST_TEST(((res17 == dims(7, 7))));
	BOOST_TEST(((res18 == dims(7, 7))));
	BOOST_TEST(((res19 == dims(7, 7))));
	BOOST_TEST(((res20 == dims(7, 7))));
	BOOST_TEST(((res21 == dims(7, 7))));
	BOOST_TEST(((res22 == dims(7, 7))));
	BOOST_TEST(((res23 == dims(7, 7))));
	BOOST_TEST(((res24 == dims(7, 7))));
	BOOST_TEST(((res25 == dims(7, 7))));
	BOOST_TEST(((res26 == dims(7, 7))));
	BOOST_TEST(((res27 == dims(7, 7))));
	BOOST_TEST(((res28 == dims(7, 7))));
	BOOST_TEST(((res29 == dims(7, 7))));
	BOOST_TEST(((res30 == dims(7, 7))));
	BOOST_TEST(((res31 == dims(7, 7))));
	BOOST_TEST(((res32 == dims(7, 7))));
	BOOST_TEST(((res33 == dims(7, 7))));
	BOOST_TEST(((res34 == dims(7, 7))));
	BOOST_TEST(((res35 == dims(7, 7))));
	BOOST_TEST(((res36 == dims(7, 7))));
	BOOST_TEST(((res37 == dims(7, 7))));
	BOOST_TEST(((res38 == dims(7, 7))));
	BOOST_TEST(((res39 == dims(7, 7))));
	BOOST_TEST(((res40 == dims(7, 7))));
	BOOST_TEST(((res41 == dims(7, 7))));
	BOOST_TEST(((res42 == dims(7, 7))));
	BOOST_TEST(((res43 == dims(7, 7))));
	BOOST_TEST(((res44 == dims(7, 7))));
	BOOST_TEST(((res45 == dims(7, 7))));
	BOOST_TEST(((res46 == dims(7, 7))));
	BOOST_TEST(((res47 == dims(7, 7))));
	BOOST_TEST(((res48 == dims(7, 7))));
	BOOST_TEST(((res49 == dims(7, 7))));
	BOOST_TEST(((res50 == dims(7, 7))));
	BOOST_TEST(((res51 == dims(7, 7))));
	BOOST_TEST(((res52 == dims(7, 7))));
	BOOST_TEST(((res53 == dims(7, 7))));
	BOOST_TEST(((res54 == dims(7, 7))));
	BOOST_TEST(((res55 == dims(7, 7))));
	BOOST_TEST(((res56 == dims(7, 7))));
	BOOST_TEST(((res57 == dims(7, 7))));
	BOOST_TEST(((res58 == dims(7, 7))));
	BOOST_TEST(((res59 == dims(7, 7))));
	BOOST_TEST(((res60 == dims(7, 7))));
	BOOST_TEST(((res61 == dims(7, 7))));
	BOOST_TEST(((res62 == dims(7, 7))));
	BOOST_TEST(((res63 == dims(7, 7))));
	BOOST_TEST(((res64 == dims(7, 7))));
	BOOST_TEST(((res65 == dims(7, 7))));
	BOOST_TEST(((res66 == dims(7, 7))));
	BOOST_TEST(((res67 == dims(7, 7))));
	BOOST_TEST(((res68 == dims(7, 7))));
	BOOST_TEST(((res69 == dims(7, 7))));
	BOOST_TEST(((res70 == dims(7, 7))));
	BOOST_TEST(((res71 == dims(7, 7))));
	BOOST_TEST(((res72 == dims(7, 7))));
	BOOST_TEST(((res73 == dims(7, 7))));
	BOOST_TEST(((res74 == dims(7, 7))));
	BOOST_TEST(((res75 == dims(7, 7))));
	BOOST_TEST(((res76 == dims(7, 7))));
	BOOST_TEST(((res77 == dims(7, 7))));
	BOOST_TEST(((res78 == dims(7, 7))));
	BOOST_TEST(((res79 == dims(7, 7))));
	BOOST_TEST(((res80 == dims(7, 7))));
	BOOST_TEST(((res81 == dims(7, 7))));
	BOOST_TEST(((res82 == dims(7, 7))));
	BOOST_TEST(((res83 == dims(7, 7))));
	BOOST_TEST(((res84 == dims(7, 7))));

	BOOST_TEST((rt_id(res01) == (id< dims_t< 7, 7 > >)));
	BOOST_TEST((rt_id(res02) == (id< dims_t< 7, 0 > >)));
	BOOST_TEST((rt_id(res03) == (id< dims_t< 0, 7 > >)));
	BOOST_TEST((rt_id(res04) == (id< dims_t< 0, 0 > >)));
	BOOST_TEST((rt_id(res05) == (id< dims_t< 7, 7 > >)));
	BOOST_TEST((rt_id(res06) == (id< dims_t< 7, 7 > >)));
	BOOST_TEST((rt_id(res07) == (id< dims_t< 7, 7 > >)));
	BOOST_TEST((rt_id(res08) == (id< dims_t< 7, 7 > >)));
	BOOST_TEST((rt_id(res09) == (id< dims_t< 7, 7 > >)));
	BOOST_TEST((rt_id(res10) == (id< dims_t< 7, 0 > >)));
	BOOST_TEST((rt_id(res11) == (id< dims_t< 7, 7 > >)));
	BOOST_TEST((rt_id(res12) == (id< dims_t< 7, 0 > >)));
	BOOST_TEST((rt_id(res13) == (id< dims_t< 7, 7 > >)));
	BOOST_TEST((rt_id(res14) == (id< dims_t< 7, 7 > >)));
	BOOST_TEST((rt_id(res15) == (id< dims_t< 0, 7 > >)));
	BOOST_TEST((rt_id(res16) == (id< dims_t< 0, 7 > >)));
	BOOST_TEST((rt_id(res17) == (id< dims_t< 7, 7 > >)));
	BOOST_TEST((rt_id(res18) == (id< dims_t< 7, 0 > >)));
	BOOST_TEST((rt_id(res19) == (id< dims_t< 0, 7 > >)));
	BOOST_TEST((rt_id(res20) == (id< dims_t< 0, 0 > >)));
	BOOST_TEST((rt_id(res21) == (id< dims_t< 7, 7 > >)));
	BOOST_TEST((rt_id(res22) == (id< dims_t< 7, 7 > >)));
	BOOST_TEST((rt_id(res23) == (id< dims_t< 7, 7 > >)));
	BOOST_TEST((rt_id(res24) == (id< dims_t< 7, 7 > >)));
	BOOST_TEST((rt_id(res25) == (id< dims_t< 7, 7 > >)));
	BOOST_TEST((rt_id(res26) == (id< dims_t< 7, 7 > >)));
	BOOST_TEST((rt_id(res27) == (id< dims_t< 7, 7 > >)));
	BOOST_TEST((rt_id(res28) == (id< dims_t< 7, 7 > >)));
	BOOST_TEST((rt_id(res29) == (id< dims_t< 7, 7 > >)));
	BOOST_TEST((rt_id(res30) == (id< dims_t< 7, 7 > >)));
	BOOST_TEST((rt_id(res31) == (id< dims_t< 7, 7 > >)));
	BOOST_TEST((rt_id(res32) == (id< dims_t< 7, 7 > >)));
	BOOST_TEST((rt_id(res33) == (id< dims_t< 7, 7 > >)));
	BOOST_TEST((rt_id(res34) == (id< dims_t< 7, 7 > >)));
	BOOST_TEST((rt_id(res35) == (id< dims_t< 7, 7 > >)));
	BOOST_TEST((rt_id(res36) == (id< dims_t< 7, 7 > >)));
	BOOST_TEST((rt_id(res37) == (id< dims_t< 7, 7 > >)));
	BOOST_TEST((rt_id(res38) == (id< dims_t< 7, 7 > >)));
	BOOST_TEST((rt_id(res39) == (id< dims_t< 7, 7 > >)));
	BOOST_TEST((rt_id(res40) == (id< dims_t< 7, 7 > >)));
	BOOST_TEST((rt_id(res41) == (id< dims_t< 7, 7 > >)));
	BOOST_TEST((rt_id(res42) == (id< dims_t< 7, 0 > >)));
	BOOST_TEST((rt_id(res43) == (id< dims_t< 7, 7 > >)));
	BOOST_TEST((rt_id(res44) == (id< dims_t< 7, 0 > >)));
	BOOST_TEST((rt_id(res45) == (id< dims_t< 7, 7 > >)));
	BOOST_TEST((rt_id(res46) == (id< dims_t< 7, 7 > >)));
	BOOST_TEST((rt_id(res47) == (id< dims_t< 7, 7 > >)));
	BOOST_TEST((rt_id(res48) == (id< dims_t< 7, 7 > >)));
	BOOST_TEST((rt_id(res49) == (id< dims_t< 7, 7 > >)));
	BOOST_TEST((rt_id(res50) == (id< dims_t< 7, 0 > >)));
	BOOST_TEST((rt_id(res51) == (id< dims_t< 7, 7 > >)));
	BOOST_TEST((rt_id(res52) == (id< dims_t< 7, 0 > >)));
	BOOST_TEST((rt_id(res53) == (id< dims_t< 7, 7 > >)));
	BOOST_TEST((rt_id(res54) == (id< dims_t< 7, 7 > >)));
	BOOST_TEST((rt_id(res55) == (id< dims_t< 7, 7 > >)));
	BOOST_TEST((rt_id(res56) == (id< dims_t< 7, 7 > >)));
	BOOST_TEST((rt_id(res57) == (id< dims_t< 7, 7 > >)));
	BOOST_TEST((rt_id(res58) == (id< dims_t< 7, 7 > >)));
	BOOST_TEST((rt_id(res59) == (id< dims_t< 7, 7 > >)));
	BOOST_TEST((rt_id(res60) == (id< dims_t< 7, 7 > >)));
	BOOST_TEST((rt_id(res61) == (id< dims_t< 7, 7 > >)));
	BOOST_TEST((rt_id(res62) == (id< dims_t< 7, 7 > >)));
	BOOST_TEST((rt_id(res63) == (id< dims_t< 0, 7 > >)));
	BOOST_TEST((rt_id(res64) == (id< dims_t< 0, 7 > >)));
	BOOST_TEST((rt_id(res65) == (id< dims_t< 7, 7 > >)));
	BOOST_TEST((rt_id(res66) == (id< dims_t< 7, 7 > >)));
	BOOST_TEST((rt_id(res67) == (id< dims_t< 0, 7 > >)));
	BOOST_TEST((rt_id(res68) == (id< dims_t< 0, 7 > >)));
	BOOST_TEST((rt_id(res69) == (id< dims_t< 7, 7 > >)));
	BOOST_TEST((rt_id(res70) == (id< dims_t< 7, 7 > >)));
	BOOST_TEST((rt_id(res71) == (id< dims_t< 7, 7 > >)));
	BOOST_TEST((rt_id(res72) == (id< dims_t< 7, 7 > >)));
	BOOST_TEST((rt_id(res73) == (id< dims_t< 7, 7 > >)));
	BOOST_TEST((rt_id(res74) == (id< dims_t< 7, 0 > >)));
	BOOST_TEST((rt_id(res75) == (id< dims_t< 7, 7 > >)));
	BOOST_TEST((rt_id(res76) == (id< dims_t< 7, 0 > >)));
	BOOST_TEST((rt_id(res77) == (id< dims_t< 7, 7 > >)));
	BOOST_TEST((rt_id(res78) == (id< dims_t< 7, 7 > >)));
	BOOST_TEST((rt_id(res79) == (id< dims_t< 0, 7 > >)));
	BOOST_TEST((rt_id(res80) == (id< dims_t< 0, 7 > >)));
	BOOST_TEST((rt_id(res81) == (id< dims_t< 7, 7 > >)));
	BOOST_TEST((rt_id(res82) == (id< dims_t< 7, 0 > >)));
	BOOST_TEST((rt_id(res83) == (id< dims_t< 0, 7 > >)));
	BOOST_TEST((rt_id(res84) == (id< dims_t< 0, 0 > >)));
}


BOOST_AUTO_TEST_SUITE_END()
