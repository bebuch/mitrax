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


using namespace mitrax;
using namespace mitrax::literals;


namespace{


	BOOST_AUTO_TEST_CASE(test_size_ct){
		BOOST_TEST(14_dim == size_t(14));
	}

	BOOST_AUTO_TEST_CASE(test_ptrdiff_ct){
		BOOST_TEST(14_diff == ptrdiff_t(14));
	}


}
