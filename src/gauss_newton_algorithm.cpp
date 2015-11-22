//-----------------------------------------------------------------------------
// Copyright (c) 2015 Benjamin Buch
//
// https://github.com/bebuch/mitrax
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt)
//-----------------------------------------------------------------------------
#include <boost/test/unit_test.hpp>

#include <mitrax/gauss_newton_algorithm.hpp>
#include <mitrax/output.hpp>

#include <iostream>


using boost::typeindex::type_id;
using boost::typeindex::type_id_runtime;
using namespace mitrax;
using namespace mitrax::literals;


namespace{


	template < typename T >
	auto rt_id(T&& v){
		return type_id_runtime(static_cast< T&& >(v));
	}

	template < typename T >
	auto const id = type_id< T >();


}


BOOST_AUTO_TEST_SUITE(test_suite_gauss_newton_algorithm)


BOOST_AUTO_TEST_CASE(test_gauss_newton_algorithm){
	constexpr auto start = make_col_vector(9_R, 1.f);

	auto f = [](
			raw_col_vector< float, 9 > const& p,
			raw_col_vector< float, 3 > const& v
		){
			auto const m = make_square_matrix< float >(3_D, {
				{p[0], p[1], p[2]},
				{p[3], p[4], p[5]},
				{p[6], p[7], p[8]}
			});
			return m * v;
		};

	using value_type = raw_col_vector< float, 3 >;

	boost::container::vector< std::pair< value_type, value_type > > data{
		std::make_pair(
			make_col_vector< float >(3_R, {160, 160, 1}),
			make_col_vector< float >(3_R, {237.721f, 219.589f, 1})
		),
		std::make_pair(
			make_col_vector< float >(3_R, {160, 20, 1}),
			make_col_vector< float >(3_R, {240.042f, 584.902f, 1})
		),
		std::make_pair(
			make_col_vector< float >(3_R, {20, 160, 1}),
			make_col_vector< float >(3_R, {500.132f, 265.289f, 1})
		),
		std::make_pair(
			make_col_vector< float >(3_R, {20, 20, 1}),
			make_col_vector< float >(3_R, {527.155f, 600.192f, 1})
		)
	};

	constexpr auto threshold = make_col_vector(3_R, 0.0001f);

	auto res = gauss_newton_algorithm(f, start, threshold, data);
	(void)res;
// 	std::cout << res << std::endl;
}


BOOST_AUTO_TEST_SUITE_END()
