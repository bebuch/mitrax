//-----------------------------------------------------------------------------
// Copyright (c) 2015 Benjamin Buch
//
// https://github.com/bebuch/mitrax
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt)
//-----------------------------------------------------------------------------
#define BOOST_TEST_MODULE mitrax test suite
#define BOOST_TEST_NO_MAIN
#include <boost/test/unit_test.hpp>

int main(int argc, char** argv, char** /*envp*/){
	return boost::unit_test::unit_test_main(&init_unit_test, argc, argv);
}
