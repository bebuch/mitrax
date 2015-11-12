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


BOOST_AUTO_TEST_CASE(test_col_t){
	constexpr auto s = 14_C;
	BOOST_TEST(s.get() == size_t(14));

	auto type = type_id< col_t< 14 > >();
	BOOST_TEST(type == type_id_runtime(s.get()));
}

BOOST_AUTO_TEST_CASE(test_col_t0){
	constexpr auto s = 14_C_rt;
	BOOST_TEST(s.get() == size_t(14));

	auto type = type_id< col_t< 0 > >();
	BOOST_TEST(type == type_id_runtime(s.get()));
}

BOOST_AUTO_TEST_CASE(test_row_t){
	constexpr auto s = 14_R;
	BOOST_TEST(s.get() == size_t(14));

	auto type = type_id< row_t< 14 > >();
	BOOST_TEST(type == type_id_runtime(s.get()));
}

BOOST_AUTO_TEST_CASE(test_row_t0){
	constexpr auto s = 14_R_rt;
	BOOST_TEST(s.get() == size_t(14));

	auto type = type_id< row_t< 0 > >();
	BOOST_TEST(type == type_id_runtime(s.get()));
}

BOOST_AUTO_TEST_CASE(test_dim_t){
	constexpr auto s = 14_D;
	BOOST_TEST(s.get() == size_t(14));
	BOOST_TEST(s.get().col() == size_t(14));
	BOOST_TEST(s.col().get() == size_t(14));
	BOOST_TEST(s.get().row() == size_t(14));
	BOOST_TEST(s.row().get() == size_t(14));

	auto type = type_id< dim_t< 14 > >();
	BOOST_TEST(type == type_id_runtime(s.get()));
}

BOOST_AUTO_TEST_CASE(test_dim_t0){
	constexpr auto s = 14_D_rt;
	BOOST_TEST(s.get() == size_t(14));
	BOOST_TEST(s.get().col() == size_t(14));
	BOOST_TEST(s.col().get() == size_t(14));
	BOOST_TEST(s.get().row() == size_t(14));
	BOOST_TEST(s.row().get() == size_t(14));

	auto type1 = type_id< dim_t< 0 > >();
	BOOST_TEST(type1 == type_id_runtime(s.get()));

	auto type2 = type_id< col_t< 0 > >();
	BOOST_TEST(type2 == type_id_runtime(s.get().col()));

	auto type3 = type_id< row_t< 0 > >();
	BOOST_TEST(type3 == type_id_runtime(s.get().row()));
}

BOOST_AUTO_TEST_CASE(test_int_to_size_t){
	BOOST_TEST(col_t< 14 >() == size_t(14));
	BOOST_TEST(col_t< 0 >(14) == size_t(14));
	BOOST_TEST((col_init< true, 14 >()) == size_t(14));
	BOOST_TEST((col_init< false, 14 >()) == size_t(14));
	BOOST_TEST((col_init< true, 14 >()).get() == size_t(14));
	BOOST_TEST((col_init< false, 14 >()).get() == size_t(14));

	BOOST_TEST(row_t< 14 >() == size_t(14));
	BOOST_TEST(row_t< 0 >(14) == size_t(14));
	BOOST_TEST((row_init< true, 14 >()) == size_t(14));
	BOOST_TEST((row_init< false, 14 >()) == size_t(14));
	BOOST_TEST((row_init< true, 14 >()).get() == size_t(14));
	BOOST_TEST((row_init< false, 14 >()).get() == size_t(14));

	BOOST_TEST(dim_t< 14 >() == size_t(14));
	BOOST_TEST(dim_t< 0 >(14) == size_t(14));
	BOOST_TEST((dim_init< true, 14 >()) == size_t(14));
	BOOST_TEST((dim_init< false, 14 >()) == size_t(14));
	BOOST_TEST((dim_init< true, 14 >()).get() == size_t(14));
	BOOST_TEST((dim_init< false, 14 >()).get() == size_t(14));
	BOOST_TEST((dim_init< true, 14 >()).col() == size_t(14));
	BOOST_TEST((dim_init< false, 14 >()).col() == size_t(14));
	BOOST_TEST((dim_init< true, 14 >()).row() == size_t(14));
	BOOST_TEST((dim_init< false, 14 >()).row() == size_t(14));

	BOOST_TEST(col_t< 14 >() == 14_C);
	BOOST_TEST(col_t< 0 >(14) == 14_C_rt);

	// TODO: Suppress this:
	BOOST_TEST(col_t< 14 >() == 14_R);
	BOOST_TEST(col_t< 0 >(14) == 14_R_rt);
}
