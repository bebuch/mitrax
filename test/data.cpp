//-----------------------------------------------------------------------------
// Copyright (c) 2015-2016 Benjamin Buch
//
// https://github.com/bebuch/mitrax
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt)
//-----------------------------------------------------------------------------
#include <boost/test/unit_test.hpp>

#include <mitrax/make_matrix.hpp>


using namespace mitrax;
using namespace mitrax::literals;


BOOST_AUTO_TEST_SUITE(test_suite_data)


namespace{


	template < typename T >
	auto rt_id(T&& v){
		return boost::typeindex::type_id_runtime(static_cast< T&& >(v));
	}

	template < typename T >
	auto const id = boost::typeindex::type_id< T >();

	constexpr int data[2][2] = {{0, 1}, {2, 3}};
	constexpr int ref[4] = {0, 1, 2, 3};


}


BOOST_AUTO_TEST_CASE(test_data){
	auto m1 = make_matrix(2_C, 2_R, data);
	constexpr auto m2 = make_matrix(2_C, 2_R, data);
	auto m3 = make_matrix(2_C_rt, 2_R, data);
	auto const m4 = make_matrix(2_C_rt, 2_R, data);
	auto m5 = make_matrix(2_C, 2_R_rt, data);
	auto const m6 = make_matrix(2_C, 2_R_rt, data);
	auto m7 = make_matrix(2_C_rt, 2_R_rt, data);
	auto const m8 = make_matrix(2_C_rt, 2_R_rt, data);

	BOOST_TEST(std::equal(ref, ref + 4, m1.data()));
	BOOST_TEST(std::equal(ref, ref + 4, m2.data()));
	BOOST_TEST(std::equal(ref, ref + 4, m3.data()));
	BOOST_TEST(std::equal(ref, ref + 4, m4.data()));
	BOOST_TEST(std::equal(ref, ref + 4, m5.data()));
	BOOST_TEST(std::equal(ref, ref + 4, m6.data()));
	BOOST_TEST(std::equal(ref, ref + 4, m7.data()));
	BOOST_TEST(std::equal(ref, ref + 4, m8.data()));
}


BOOST_AUTO_TEST_SUITE_END()
