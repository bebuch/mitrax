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

BOOST_AUTO_TEST_CASE(test_col_init_t){
// 	// static target with runtime init
// 	constexpr auto tt0 = col_init_t< true, true, 0 >();


// 	// no static info!
// 	constexpr auto ft7 = col_init_t< false, true, 7 >();

// 	// static target with runtime init
// 	constexpr auto ft0 = col_init_t< false, true, 0 >(7);

// 	// runtime init must have compile time info 0
// 	constexpr auto ff7 = col_init_t< false, false, 7 >();

// 	constexpr auto tt7 = col_init_t< true, true, 7 >();
// 	constexpr auto tf0 = col_init_t< true, false, 0 >();
// 	constexpr auto tf7 = col_init_t< true, false, 7 >();
// 	constexpr auto ff0 = col_init_t< false, false, 0 >(7);
}


BOOST_AUTO_TEST_SUITE_END()
