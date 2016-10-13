//-----------------------------------------------------------------------------
// Copyright (c) 2015-2016 Benjamin Buch
//
// https://github.com/bebuch/mitrax
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt)
//-----------------------------------------------------------------------------
#define BOOST_TEST_MODULE mitrax gauss_newton_algorithm
#include <boost/test/unit_test.hpp>

#include <mitrax/gauss_newton_algorithm.hpp>
#include <mitrax/io/matrix.hpp>

#include <iostream>


using boost::typeindex::type_id;
using boost::typeindex::type_id_runtime;
using namespace mitrax;
using namespace mitrax::literals;


template < typename T >
auto rt_id(T&& v){
	return type_id_runtime(static_cast< T&& >(v));
}

template < typename T >
auto const id = type_id< T >();


BOOST_AUTO_TEST_SUITE(suite_gauss_newton_algorithm)


// BOOST_AUTO_TEST_CASE(test_gauss_newton_algorithm_linear_fit){
// 	auto f = [](
// 			raw_col_vector< double, 2 > const& p,
// 			std::tuple< double, double > const& v
// 		){
// 			return std::get< 1 >(v) * p[0] + p[1] - std::get< 0 >(v);
// 		};
//
// 	boost::container::vector< std::tuple< double, double > > data{
// 		std::make_tuple(2., 2.),
// 		std::make_tuple(3., 3.),
// 		std::make_tuple(4., 4.),
// 		std::make_tuple(5., 5.)
// 	};
//
// 	constexpr auto start = make_vector< double >(2_R, 1);
//
// 	std::cout << "gauss-newton:" << std::endl;
// 	auto res = gauss_newton_algorithm(f, start, 1e-10, data);
// 	std::cout << res << std::endl;
// }
//
// BOOST_AUTO_TEST_CASE(test_gauss_levenberg_marquardt_linear_fit){
// 	auto f = [](
// 			raw_col_vector< double, 2 > const& p,
// 			std::tuple< double, double > const& v
// 		){
// 			return std::get< 1 >(v) * p[0] + p[1] - std::get< 0 >(v);
// 		};
//
// 	boost::container::vector< std::tuple< double, double > > data{
// 		std::make_tuple(2., 2.),
// 		std::make_tuple(3., 3.),
// 		std::make_tuple(4., 4.),
// 		std::make_tuple(5., 5.)
// 	};
//
// 	constexpr auto start = make_vector< double >(2_R, 1);
//
// 	std::cout << "levenberg-marquardt:" << std::endl;
// 	auto res = levenberg_marquardt_algorithm(
// 		f, start, 1e-10, 1., 0.3, 0.9, data
// 	);
// 	std::cout << res << std::endl;
// }
//
//
// BOOST_AUTO_TEST_CASE(test_gauss_newton_algorithm_cycle_fit){
// 	using value_type = raw_col_vector< double, 2 >;
//
// 	auto f = [](
// 			raw_col_vector< double, 3 > const& p,
// 			std::tuple< value_type > const& v
// 		){
// 			auto x = std::get< 0 >(v)[0];
// 			auto y = std::get< 0 >(v)[1];
// 			auto px = p[0];
// 			auto py = p[1];
// 			auto pr = p[2];
// 			auto xd = x - px;
// 			auto yd = y - py;
// 			return std::sqrt(xd * xd + yd * yd) - pr;
// 		};
//
// 	boost::container::vector< std::tuple< value_type > > data{
// 		std::make_tuple(make_vector< double >(2_R, {2, 2})),
// 		std::make_tuple(make_vector< double >(2_R, {4, 4})),
// 		std::make_tuple(make_vector< double >(2_R, {2, 4})),
// 		std::make_tuple(make_vector< double >(2_R, {4, 2}))
// 	};
//
// 	constexpr auto start = make_vector< double >(3_R, 1);
//
// 	std::cout << "gauss-newton:" << std::endl;
// 	auto res = gauss_newton_algorithm(f, start, 1e-10, data);
// 	std::cout << res << std::endl;
// }
//
// BOOST_AUTO_TEST_CASE(test_gauss_levenberg_marquardt_cycle_fit){
// 	using value_type = raw_col_vector< double, 2 >;
//
// 	auto f = [](
// 			raw_col_vector< double, 3 > const& p,
// 			std::tuple< value_type > const& v
// 		){
// 			auto x = std::get< 0 >(v)[0];
// 			auto y = std::get< 0 >(v)[1];
// 			auto px = p[0];
// 			auto py = p[1];
// 			auto pr = p[2];
// 			auto xd = x - px;
// 			auto yd = y - py;
// // 			return std::sqrt(xd * xd + yd * yd) - pr;
// 			return xd * xd + yd * yd - pr * pr;
// 		};
//
// 	boost::container::vector< std::tuple< value_type > > data{
// 		std::make_tuple(make_vector< double >(2_R, {2, 2})),
// 		std::make_tuple(make_vector< double >(2_R, {4, 4})),
// 		std::make_tuple(make_vector< double >(2_R, {2, 4})),
// 		std::make_tuple(make_vector< double >(2_R, {4, 2}))
// 	};
//
// 	constexpr auto start = make_vector< double >(3_R, 1);
//
// 	std::cout << "levenberg-marquardt:" << std::endl;
// 	auto res = levenberg_marquardt_algorithm(
// 		f, start, 1e-10, 1., 0.1, 0.9, data
// 	);
// 	std::cout << res << std::endl;
//
// 	std::cout << f(res, data[0]) << std::endl;
// 	std::cout << f(res, data[1]) << std::endl;
// 	std::cout << f(res, data[2]) << std::endl;
// 	std::cout << f(res, data[3]) << std::endl;
// }

// BOOST_AUTO_TEST_CASE(test_gauss_newton_algorithm){
// 	constexpr auto start = make_vector< double >(8_R, 1);
//
// 	auto f = [](
// 			raw_col_vector< double, 8 > const& p,
// 			raw_col_vector< double, 3 > const& y,
// 			raw_col_vector< double, 3 > const& v
// 		){
// 			auto const m = make_matrix< double >(3_D, {
// 				{p[0], p[1], p[2]},
// 				{p[3], p[4], p[5]},
// 				{p[6], p[7], 1}
// 			});
// 			auto r = m * v - y;
// 			auto r2 = element_multiplies(r, r);
// 			double res = 1;
// 			for(auto v: r2) res += v;
// 			return res;
// 		};
//
// 	using value_type = raw_col_vector< double, 3 >;
//
// 	boost::container::vector< std::pair< value_type, value_type > > data{
// 		std::make_tuple(
// 			make_vector< double >(3_R, {5, 5, 1}),
// 			make_vector< double >(3_R, {6, 6, 1})
// 		),
// 		std::make_tuple(
// 			make_vector< double >(3_R, {5, 3, 1}),
// 			make_vector< double >(3_R, {6, 4, 1})
// 		),
// 		std::make_tuple(
// 			make_vector< double >(3_R, {3, 5, 1}),
// 			make_vector< double >(3_R, {4, 6, 1})
// 		),
// 		std::make_tuple(
// 			make_vector< double >(3_R, {3, 3, 1}),
// 			make_vector< double >(3_R, {4, 4, 1})
// 		)
// 	};
//
// 	{
// 		using namespace mitrax;
// 		using namespace mitrax::literals;
//
// 		auto x0 = data[0].second[0];
// 		auto y0 = data[0].second[1];
// 		auto x1 = data[1].second[0];
// 		auto y1 = data[1].second[1];
// 		auto x2 = data[2].second[0];
// 		auto y2 = data[2].second[1];
// 		auto x3 = data[3].second[0];
// 		auto y3 = data[3].second[1];
//
// 		double tx0 = data[0].first[0];
// 		double ty0 = data[0].first[1];
// 		double tx1 = data[1].first[0];
// 		double ty1 = data[1].first[1];
// 		double tx2 = data[2].first[0];
// 		double ty2 = data[2].first[1];
// 		double tx3 = data[3].first[0];
// 		double ty3 = data[3].first[1];
//
// 		auto b = make_matrix< double >(9_C, 9_R, {
// 			{x0, y0, 1,  0,  0, 0, -tx0 * x0, -tx0 * y0, -tx0},
// 			{ 0,  0, 0, x0, y0, 1, -ty0 * x0, -ty0 * y0, -ty0},
// 			{x1, y1, 1,  0,  0, 0, -tx1 * x1, -tx1 * y1, -tx1},
// 			{ 0,  0, 0, x1, y1, 1, -ty1 * x1, -ty1 * y1, -ty1},
// 			{x2, y2, 1,  0,  0, 0, -tx2 * x2, -tx2 * y2, -tx2},
// 			{ 0,  0, 0, x2, y2, 1, -ty2 * x2, -ty2 * y2, -ty2},
// 			{x3, y3, 1,  0,  0, 0, -tx3 * x3, -tx3 * y3, -tx3},
// 			{ 0,  0, 0, x3, y3, 1, -ty3 * x3, -ty3 * y3, -ty3},
// 			{ 0,  0, 0,  0,  0, 0,         0,         0,    0}
// 		});
//
// 		auto vec = matrix_kernel(b);
//
// 		auto res = make_matrix< double >(3_C, 3_R, {
// 			{vec[0], vec[1], vec[2]},
// 			{vec[3], vec[4], vec[5]},
// 			{vec[6], vec[7], vec[8]}
// 		});
//
// 		std::cout << "direkt:" << std::endl;
// 		std::cout << res << std::endl;
// 	}
//
// 	std::cout << "gauss-newton:" << std::endl;
// 	auto res = gauss_newton_algorithm(f, start, 0.00000000001, data);
// 	std::cout << res << std::endl;
// // 	std::cout << res << std::endl;
// }


BOOST_AUTO_TEST_SUITE_END()
