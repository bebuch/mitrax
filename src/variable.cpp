//-----------------------------------------------------------------------------
// Copyright (c) 2015 Benjamin Buch
//
// https://github.com/bebuch/mitrax
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt)
//-----------------------------------------------------------------------------
#include <boost/test/unit_test.hpp>

#include <mitrax/variable.hpp>


using namespace mitrax;


BOOST_AUTO_TEST_SUITE(test_suite_variable)


BOOST_AUTO_TEST_CASE(test_variable_free){
	variable< int > x;

	int v = x;
	BOOST_TEST(v == 0);

	bool is_set = x;
	BOOST_TEST(!is_set);

	x = 5;
	v = x;
	BOOST_TEST(v == 5);

	is_set = x;
	BOOST_TEST(is_set);
}


BOOST_AUTO_TEST_CASE(test_variable_value){
	variable< int > x = 3;

	int v = x;
	BOOST_TEST(v == 3);

	bool is_set = x;
	BOOST_TEST(is_set);

	x = 5;
	v = x;
	BOOST_TEST(v == 5);

	is_set = x;
	BOOST_TEST(is_set);
}

BOOST_AUTO_TEST_CASE(test_variable_output_free){
	variable< int > x;

	std::ostringstream os;
	os << x;
	BOOST_TEST(os.str() == "0");
}

BOOST_AUTO_TEST_CASE(test_variable_output_value){
	variable< int > x = 5;

	std::ostringstream os;
	os << x;
	BOOST_TEST(os.str() == "5");
}


BOOST_AUTO_TEST_SUITE_END()
