//-----------------------------------------------------------------------------
// Copyright (c) 2015-2016 Benjamin Buch
//
// https://github.com/bebuch/mitrax
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt)
//-----------------------------------------------------------------------------
#include <boost/test/unit_test.hpp>

#include <mitrax/join.hpp>
#include <mitrax/compare.hpp>


using boost::typeindex::type_id;
using boost::typeindex::type_id_runtime;
using namespace mitrax;
using namespace mitrax::literals;


BOOST_AUTO_TEST_SUITE(test_suite_householder_transformation)


namespace{


	template < typename T, typename U >
	constexpr bool equal(T const& a, U const& b){
		using std::abs;
		return abs(a - b) < 0.00001;
	}

	template < typename T, typename U >
	constexpr bool matrix_equal(T const& a, U const& b){
		using std::abs;
		auto m = a - b;
		return std::any_of(m.begin(), m.end(), [](auto v){
			return v < 0.00001;
		});
	}


	constexpr auto ref3x3 = make_matrix(3_C, 3_R, {
		{0, 1, 2},
		{3, 4, 5},
		{6, 7, 8}
	});


	constexpr auto ref6x6 = make_matrix(6_C, 6_R, {
		{0, 1, 2, 0, 1, 2},
		{3, 4, 5, 3, 4, 5},
		{6, 7, 8, 6, 7, 8},
		{0, 1, 2, 0, 1, 2},
		{3, 4, 5, 3, 4, 5},
		{6, 7, 8, 6, 7, 8}
	});

}


BOOST_AUTO_TEST_CASE(test_join){
	constexpr auto m1 = make_matrix(2_C, 2_R, {{0, 1}, {3, 4}});
	constexpr auto m2 = make_matrix(1_C, 2_R, {{2}, {5}});
	constexpr auto m3 = make_matrix(2_C, 1_R, {{6, 7}});
	constexpr auto m4 = make_matrix(1_C, 1_R, {{8}});
	
	constexpr auto m5 = join(join_v(
		join_h(m1, m2),
		join_h(m3, m4)
	));

	constexpr auto m6 = join(join_h(
		join_v(m1, m3),
		join_v(m2, m4)
	));

	constexpr auto m7 = join(
		join_v(join_h(join_v(m1, m3), join_v(m2, m4), m5), join_h(m5, m6)));

	BOOST_TEST((m5 == ref3x3));
	BOOST_TEST((m6 == ref3x3));
	BOOST_TEST((m7 == ref6x6));
}


BOOST_AUTO_TEST_SUITE_END()
