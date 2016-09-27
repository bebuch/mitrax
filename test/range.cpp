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
#include <boost/mpl/list.hpp>

#include <mitrax/range/value_view_range.hpp>
#include <mitrax/range/value_factory_range.hpp>

#include <complex>
#include <iostream>


using namespace mitrax;


template < typename T >
auto rt_id(T&& v){
	return boost::typeindex::type_id_runtime(static_cast< T&& >(v));
}

template < typename T >
auto const id = boost::typeindex::type_id< T >();



BOOST_AUTO_TEST_SUITE(suite_range)

using types = boost::mpl::list< int, double, std::complex< float > >;


BOOST_AUTO_TEST_CASE_TEMPLATE(test_value_view_range, T, types){
	constexpr auto range = make_value_view_range(T(4));

	static_assert(is_range_v< decltype(range) >);

	BOOST_TEST((range[0] == T(4)));
}

BOOST_AUTO_TEST_CASE_TEMPLATE(test_value_factory_range, T, types){
	constexpr auto range = make_value_factory_range< T >(std::make_tuple(4));

	static_assert(is_range_v< decltype(range) >);

	BOOST_TEST((range[0] == T(4)));
}

BOOST_AUTO_TEST_CASE(test_value_factory_range_complex){
	constexpr auto range = make_value_factory_range< std::complex< float > >
		(std::make_tuple(4, 6));

	static_assert(is_range_v< decltype(range) >);

	BOOST_TEST((range[0] == std::complex< float >(4, 6)));
}


BOOST_AUTO_TEST_SUITE_END()
