// -----------------------------------------------------------------------------
// Copyright (c) 2015-2016 Benjamin Buch
//
// https://github.com/bebuch/mitrax
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt)
// -----------------------------------------------------------------------------
#define BOOST_TEST_MODULE mitrax flat_iterator
#include <boost/test/unit_test.hpp>

#include <mitrax/iterator/flat.hpp>

#include <complex>
#include <iostream>


using namespace mitrax;


template < typename T >
auto rt_id(T&& v){
	return boost::typeindex::type_id_runtime(static_cast< T&& >(v));
}

template < typename T >
auto const id = boost::typeindex::type_id< T >();



BOOST_AUTO_TEST_SUITE(suite_flat_iterator)


BOOST_AUTO_TEST_CASE(test_1D){
	int array[2] = {1, 2};

	auto iter = flat_iterator< int, 2 >(&array);

	BOOST_TEST(iter[0] == 1);
	BOOST_TEST(iter[1] == 2);

	BOOST_TEST(*(iter + 0) == 1);
	BOOST_TEST(*(iter + 1) == 2);

	BOOST_TEST(*(iter -  0) == 1);
	BOOST_TEST(*(iter - -1) == 2);

	BOOST_TEST(*iter++ == 1);
	BOOST_TEST(*iter++ == 2);

	BOOST_TEST(*--iter == 2);
	BOOST_TEST(*--iter == 1);
	BOOST_TEST(*++iter == 2);
	BOOST_TEST(*iter-- == 2);
	BOOST_TEST(*iter == 1);

	BOOST_TEST(*(0 + iter) == 1);
	BOOST_TEST(*(1 + iter) == 2);

	BOOST_TEST((iter + 1 - iter) == 1);
}

BOOST_AUTO_TEST_CASE(test_2D){
	int array[2][3] = {{1, 2, 3}, {4, 5, 6}};

	auto iter = flat_iterator< int, 2, 3 >(&array);

	BOOST_TEST(iter[0] == 1);
	BOOST_TEST(iter[1] == 2);
	BOOST_TEST(iter[2] == 3);
	BOOST_TEST(iter[3] == 4);
	BOOST_TEST(iter[4] == 5);
	BOOST_TEST(iter[5] == 6);

	BOOST_TEST(iter[0] == 1);
	BOOST_TEST(iter[1] == 2);

	BOOST_TEST(*(iter + 0) == 1);
	BOOST_TEST(*(iter + 1) == 2);

	BOOST_TEST(*(iter -  0) == 1);
	BOOST_TEST(*(iter - -1) == 2);

	BOOST_TEST(*iter++ == 1);
	BOOST_TEST(*iter++ == 2);

	BOOST_TEST(*--iter == 2);
	BOOST_TEST(*--iter == 1);
	BOOST_TEST(*++iter == 2);
	BOOST_TEST(*iter-- == 2);
	BOOST_TEST(*iter == 1);

	BOOST_TEST(*(0 + iter) == 1);
	BOOST_TEST(*(1 + iter) == 2);

	BOOST_TEST((iter + 1 - iter) == 1);
}

BOOST_AUTO_TEST_CASE(test_3D){
	int array[2][3][4] = {
		{{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}},
		{{13, 14, 15, 16}, {17, 18, 19, 20}, {21, 22, 23, 24}}
	};

	auto iter = flat_iterator< int, 2, 3, 4 >(&array);

	BOOST_TEST(iter[0] == 1);
	BOOST_TEST(iter[1] == 2);
	BOOST_TEST(iter[2] == 3);
	BOOST_TEST(iter[3] == 4);
	BOOST_TEST(iter[4] == 5);
	BOOST_TEST(iter[5] == 6);
	BOOST_TEST(iter[6] == 7);
	BOOST_TEST(iter[7] == 8);
	BOOST_TEST(iter[8] == 9);
	BOOST_TEST(iter[9] == 10);
	BOOST_TEST(iter[10] == 11);
	BOOST_TEST(iter[11] == 12);
	BOOST_TEST(iter[12] == 13);
	BOOST_TEST(iter[13] == 14);
	BOOST_TEST(iter[14] == 15);
	BOOST_TEST(iter[15] == 16);
	BOOST_TEST(iter[16] == 17);
	BOOST_TEST(iter[17] == 18);
	BOOST_TEST(iter[18] == 19);
	BOOST_TEST(iter[19] == 20);
	BOOST_TEST(iter[20] == 21);
	BOOST_TEST(iter[21] == 22);
	BOOST_TEST(iter[22] == 23);
	BOOST_TEST(iter[23] == 24);

	BOOST_TEST(iter[0] == 1);
	BOOST_TEST(iter[1] == 2);

	BOOST_TEST(*(iter + 0) == 1);
	BOOST_TEST(*(iter + 1) == 2);

	BOOST_TEST(*(iter -  0) == 1);
	BOOST_TEST(*(iter - -1) == 2);

	BOOST_TEST(*iter++ == 1);
	BOOST_TEST(*iter++ == 2);

	BOOST_TEST(*--iter == 2);
	BOOST_TEST(*--iter == 1);
	BOOST_TEST(*++iter == 2);
	BOOST_TEST(*iter-- == 2);
	BOOST_TEST(*iter == 1);

	BOOST_TEST(*(0 + iter) == 1);
	BOOST_TEST(*(1 + iter) == 2);

	BOOST_TEST((iter + 1 - iter) == 1);
}


BOOST_AUTO_TEST_SUITE_END()
