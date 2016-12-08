//-----------------------------------------------------------------------------
// Copyright (c) 2015-2016 Benjamin Buch
//
// https://github.com/bebuch/mitrax
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt)
//-----------------------------------------------------------------------------
#define BOOST_TEST_MODULE mitrax data
#include <boost/test/unit_test.hpp>

#include <mitrax/make_matrix.hpp>


using namespace mitrax;
using namespace mitrax::literals;


template < typename T >
auto rt_id(T&& v){
	return boost::typeindex::type_id_runtime(static_cast< T&& >(v));
}

template < typename T >
auto const id = boost::typeindex::type_id< T >();

constexpr int data[2][2] = {{0, 1}, {2, 3}};
constexpr int ref_i[4] = {0, 1, 2, 3};


BOOST_AUTO_TEST_SUITE(suite_data)


BOOST_AUTO_TEST_CASE(test_data){
	auto m1 = make_matrix(2_c, 2_r, data);
	constexpr auto m2 = make_matrix(2_c, 2_r, data);
	auto m3 = make_matrix(2_cd, 2_r, data);
	auto const m4 = make_matrix(2_cd, 2_r, data);
	auto m5 = make_matrix(2_c, 2_rd, data);
	auto const m6 = make_matrix(2_c, 2_rd, data);
	auto m7 = make_matrix(2_cd, 2_rd, data);
	auto const m8 = make_matrix(2_cd, 2_rd, data);

	BOOST_TEST(std::equal(ref_i, ref_i + 4, m1.data()));
	BOOST_TEST(std::equal(ref_i, ref_i + 4, m2.data()));
	BOOST_TEST(std::equal(ref_i, ref_i + 4, m3.data()));
	BOOST_TEST(std::equal(ref_i, ref_i + 4, m4.data()));
	BOOST_TEST(std::equal(ref_i, ref_i + 4, m5.data()));
	BOOST_TEST(std::equal(ref_i, ref_i + 4, m6.data()));
	BOOST_TEST(std::equal(ref_i, ref_i + 4, m7.data()));
	BOOST_TEST(std::equal(ref_i, ref_i + 4, m8.data()));
}


BOOST_AUTO_TEST_SUITE_END()
