//-----------------------------------------------------------------------------
// Copyright (c) 2015 Benjamin Buch
//
// https://github.com/bebuch/mitrax
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt)
//-----------------------------------------------------------------------------
#include <boost/test/unit_test.hpp>

#include <mitrax/integer.hpp>


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


BOOST_AUTO_TEST_SUITE(integer)


BOOST_AUTO_TEST_CASE(test_col_t){
	constexpr auto ct = col_t< 7 >();
	constexpr auto rt = col_t< 0 >(7);

	BOOST_TEST(ct == size_t(7));
	BOOST_TEST(rt == size_t(7));

	BOOST_TEST(rt_id(ct) == (id< col_t< 7 > >));
	BOOST_TEST(rt_id(rt) == (id< col_t< 0 > >));

	BOOST_TEST(ct.init() == size_t(7));
	BOOST_TEST(rt.init() == size_t(7));

	BOOST_TEST(rt_id(ct.init()) == (id< col_init_t< true, true, 7 > >));
	BOOST_TEST(rt_id(rt.init()) == (id< col_init_t< false, false, 0 > >));

	BOOST_TEST(ct.as_row() == size_t(7));
	BOOST_TEST(rt.as_row() == size_t(7));

	BOOST_TEST(rt_id(ct.as_row()) == (id< row_t< 7 > >));
	BOOST_TEST(rt_id(rt.as_row()) == (id< row_t< 0 > >));

	BOOST_TEST(ct.as_dim() == size_t(7));
	BOOST_TEST(rt.as_dim() == size_t(7));

	BOOST_TEST(rt_id(ct.as_dim()) == (id< dim_t< 7 > >));
	BOOST_TEST(rt_id(rt.as_dim()) == (id< dim_t< 0 > >));
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

	BOOST_TEST(rt_id(ct.init()) == (id< row_init_t< true, true, 7 > >));
	BOOST_TEST(rt_id(rt.init()) == (id< row_init_t< false, false, 0 > >));

	BOOST_TEST(ct.as_col() == size_t(7));
	BOOST_TEST(rt.as_col() == size_t(7));

	BOOST_TEST(rt_id(ct.as_col()) == (id< col_t< 7 > >));
	BOOST_TEST(rt_id(rt.as_col()) == (id< col_t< 0 > >));

	BOOST_TEST(ct.as_dim() == size_t(7));
	BOOST_TEST(rt.as_dim() == size_t(7));

	BOOST_TEST(rt_id(ct.as_dim()) == (id< dim_t< 7 > >));
	BOOST_TEST(rt_id(rt.as_dim()) == (id< dim_t< 0 > >));
}

BOOST_AUTO_TEST_CASE(test_dim_t){
	constexpr auto ct = dim_t< 7 >();
	constexpr auto rt = dim_t< 0 >(7);

	BOOST_TEST(ct == size_t(7));
	BOOST_TEST(rt == size_t(7));

	BOOST_TEST(rt_id(ct) == (id< dim_t< 7 > >));
	BOOST_TEST(rt_id(rt) == (id< dim_t< 0 > >));

	BOOST_TEST(ct.init() == size_t(7));
	BOOST_TEST(rt.init() == size_t(7));

	BOOST_TEST(rt_id(ct.init()) == (id< dim_init_t< true, true, 7 > >));
	BOOST_TEST(rt_id(rt.init()) == (id< dim_init_t< false, false, 0 > >));

	BOOST_TEST(ct.as_col() == size_t(7));
	BOOST_TEST(rt.as_col() == size_t(7));

	BOOST_TEST(rt_id(ct.as_col()) == (id< col_t< 7 > >));
	BOOST_TEST(rt_id(rt.as_col()) == (id< col_t< 0 > >));

	BOOST_TEST(ct.as_row() == size_t(7));
	BOOST_TEST(rt.as_row() == size_t(7));

	BOOST_TEST(rt_id(ct.as_row()) == (id< row_t< 7 > >));
	BOOST_TEST(rt_id(rt.as_row()) == (id< row_t< 0 > >));
}


BOOST_AUTO_TEST_SUITE_END()
