//-----------------------------------------------------------------------------
// Copyright (c) 2016-2018 Benjamin Buch
//
// https://github.com/bebuch/mitrax
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt)
//-----------------------------------------------------------------------------
#define BOOST_TEST_MODULE mitrax concepts
#include <boost/test/unit_test.hpp>

#include <mitrax/detail/concepts.hpp>


using namespace mitrax;


BOOST_AUTO_TEST_SUITE(suite_concepts)


template < typename T >
using check_foo = decltype(std::declval< T >().foo());

template < typename T >
using has_foo = compiles< T, check_foo >;

template < typename T >
using check_bar = decltype(std::declval< T >().bar());

template < typename T >
using has_bar = compiles< T, check_bar >;


struct A{};
struct B{ void foo(); };
struct C{ void bar(); };
struct D: B, C{};


template < typename T >
auto call_foo() -> requires< bool, T, has_foo >{ return true; }

template < typename T >
auto call_foo() -> fallback< bool, T, has_foo >{ return false; }


template < typename T >
auto call_bar() -> requires< bool, T, has_bar >{ return true; }

template < typename T >
auto call_bar() -> fallback< bool, T, has_bar >{ return false; }


template < typename T >
auto call_foobar() -> requires< bool, T, has_foo, has_bar >{ return true; }

template < typename T >
auto call_foobar() -> fallback< bool, T, has_foo, has_bar >{ return false; }


BOOST_AUTO_TEST_CASE(test_concepts){
	BOOST_TEST((call_foo< A >() == false));
	BOOST_TEST((call_foo< B >() == true));
	BOOST_TEST((call_foo< C >() == false));
	BOOST_TEST((call_foo< D >() == true));

	BOOST_TEST((call_bar< A >() == false));
	BOOST_TEST((call_bar< B >() == false));
	BOOST_TEST((call_bar< C >() == true));
	BOOST_TEST((call_bar< D >() == true));

	BOOST_TEST((call_foobar< A >() == false));
	BOOST_TEST((call_foobar< B >() == false));
	BOOST_TEST((call_foobar< C >() == false));
	BOOST_TEST((call_foobar< D >() == true));
}


BOOST_AUTO_TEST_SUITE_END()
