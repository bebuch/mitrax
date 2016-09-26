//-----------------------------------------------------------------------------
// Copyright (c) 2015-2016 Benjamin Buch
//
// https://github.com/bebuch/mitrax
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt)
//-----------------------------------------------------------------------------
#define BOOST_TEST_MODULE mitrax invoke
#include <boost/test/unit_test.hpp>

#include <mitrax/invoke.hpp>


using boost::typeindex::type_id;
using boost::typeindex::type_id_runtime;
using namespace mitrax;


#define CP(expr) [&]{ constexpr auto tmp = expr; return tmp; }()

template < typename T >
auto rt_id(T&& v){
	return boost::typeindex::type_id_runtime(static_cast< T&& >(v));
}

template < typename T >
auto const id = boost::typeindex::type_id< T >();


struct F{
	constexpr int operator()(int v)const noexcept{
		return v;
	}

	constexpr int x(int v)const noexcept{
		return v;
	}
};


BOOST_AUTO_TEST_SUITE(suite_join)


BOOST_AUTO_TEST_CASE(test_join_ct){
	static constexpr F a;

	BOOST_TEST(CP(mitrax::invoke(a, 5) == 5));
	BOOST_TEST(CP(mitrax::invoke(&F::x, a, 5) == 5));

	constexpr auto b = mitrax::ref(a);

	BOOST_TEST(CP(mitrax::invoke(b, 5) == 5));
	BOOST_TEST(CP(mitrax::invoke(&F::x, b, 5) == 5));

	constexpr auto c = mitrax::cref(a);

	BOOST_TEST(CP(mitrax::invoke(c, 5) == 5));
	BOOST_TEST(CP(mitrax::invoke(&F::x, c, 5) == 5));
}


BOOST_AUTO_TEST_SUITE_END()
