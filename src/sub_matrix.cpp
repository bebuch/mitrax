// //-----------------------------------------------------------------------------
// // Copyright (c) 2015 Benjamin Buch
// //
// // https://github.com/bebuch/mitrax
// //
// // Distributed under the Boost Software License, Version 1.0. (See accompanying
// // file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt)
// //-----------------------------------------------------------------------------
// #include <boost/test/unit_test.hpp>
// 
// #include <mitrax/raw_matrix.hpp>
// #include <mitrax/compare.hpp>
// 
// 
// using boost::typeindex::type_id;
// using boost::typeindex::type_id_runtime;
// using namespace mitrax;
// using namespace mitrax::literals;
// 
// 
// namespace{
// 
// 
// 	constexpr auto ref = to_square_matrix< int, 3 >({
// 		{0, 1, 2},
// 		{3, 4, 5},
// 		{6, 7, 8}
// 	});
// 
// 
// 	template < typename M >
// 	constexpr bool check1(M const& m){
// 		return
// 			m.cols() == 2 &&
// 			m.rows() == 2 &&
// 			m(0, 0) == 0 &&
// 			m(1, 0) == 1 &&
// 			m(0, 1) == 3 &&
// 			m(1, 1) == 4;
// 	}
// 
// 	template < typename M >
// 	constexpr bool check2(M const& m){
// 		return
// 			m.cols() == 2 &&
// 			m.rows() == 2 &&
// 			m(0, 0) == 1 &&
// 			m(1, 0) == 2 &&
// 			m(0, 1) == 4 &&
// 			m(1, 1) == 5;
// 	}
// 
// 	template < typename M >
// 	constexpr bool check3(M const& m){
// 		return
// 			m.cols() == 2 &&
// 			m.rows() == 2 &&
// 			m(0, 0) == 3 &&
// 			m(1, 0) == 4 &&
// 			m(0, 1) == 6 &&
// 			m(1, 1) == 7;
// 	}
// 
// 	template < typename M >
// 	constexpr bool check4(M const& m){
// 		return
// 			m.cols() == 2 &&
// 			m.rows() == 2 &&
// 			m(0, 0) == 4 &&
// 			m(1, 0) == 5 &&
// 			m(0, 1) == 7 &&
// 			m(1, 1) == 8;
// 	}
// 
// 
// }
// 
// 
// BOOST_AUTO_TEST_CASE(test_sub_matrix_2x2){
// 	constexpr auto m = ref;
// 
// 	constexpr auto sub = m.sub_matrix(0, 0, 2_dim, 2_dim);
// 	auto type = type_id< raw_matrix< int, 2, 2 > >();
// 	BOOST_TEST(type_id_runtime(sub) == type);
// 
// 
// 	constexpr auto eq1 = check1(m.sub_matrix(0, 0, 2_dim, 2_dim));
// 	BOOST_TEST(eq1);
// 
// 	constexpr auto eq2 = check2(m.sub_matrix(1, 0, 2_dim, 2_dim));
// 	BOOST_TEST(eq2);
// 
// 	constexpr auto eq3 = check3(m.sub_matrix(0, 1, 2_dim, 2_dim));
// 	BOOST_TEST(eq3);
// 
// 	constexpr auto eq4 = check4(m.sub_matrix(1, 1, 2_dim, 2_dim));
// 	BOOST_TEST(eq4);
// }
// 
// BOOST_AUTO_TEST_CASE(test_sub_matrix_0x2){
// 	auto m = ref;
// 
// 	auto sub = m.sub_matrix(0, 0, 2, 2_dim);
// 	auto type = type_id< raw_matrix< int, 0, 2 > >();
// 	BOOST_TEST(type_id_runtime(sub) == type);
// 
// 	auto eq1 = check1(m.sub_matrix(0, 0, 2, 2_dim));
// 	BOOST_TEST(eq1);
// 
// 	auto eq2 = check2(m.sub_matrix(1, 0, 2, 2_dim));
// 	BOOST_TEST(eq2);
// 
// 	auto eq3 = check3(m.sub_matrix(0, 1, 2, 2_dim));
// 	BOOST_TEST(eq3);
// 
// 	auto eq4 = check4(m.sub_matrix(1, 1, 2, 2_dim));
// 	BOOST_TEST(eq4);
// }
// 
// BOOST_AUTO_TEST_CASE(test_sub_matrix_2x0){
// 	auto m = ref;
// 
// 	auto sub = m.sub_matrix(0, 0, 2_dim, 2);
// 	auto type = type_id< raw_matrix< int, 2, 0 > >();
// 	BOOST_TEST(type_id_runtime(sub) == type);
// 
// 	auto eq1 = check1(m.sub_matrix(0, 0, 2_dim, 2));
// 	BOOST_TEST(eq1);
// 
// 	auto eq2 = check2(m.sub_matrix(1, 0, 2_dim, 2));
// 	BOOST_TEST(eq2);
// 
// 	auto eq3 = check3(m.sub_matrix(0, 1, 2_dim, 2));
// 	BOOST_TEST(eq3);
// 
// 	auto eq4 = check4(m.sub_matrix(1, 1, 2_dim, 2));
// 	BOOST_TEST(eq4);
// }
// 
// BOOST_AUTO_TEST_CASE(test_sub_matrix_0x0){
// 	auto m = ref;
// 
// 	auto sub = m.sub_matrix(0, 0, 2, 2);
// 	auto type = type_id< raw_matrix< int, 0, 0 > >();
// 	BOOST_TEST(type_id_runtime(sub) == type);
// 
// 	auto eq1 = check1(m.sub_matrix(0, 0, 2, 2));
// 	BOOST_TEST(eq1);
// 
// 	auto eq2 = check2(m.sub_matrix(1, 0, 2, 2));
// 	BOOST_TEST(eq2);
// 
// 	auto eq3 = check3(m.sub_matrix(0, 1, 2, 2));
// 	BOOST_TEST(eq3);
// 
// 	auto eq4 = check4(m.sub_matrix(1, 1, 2, 2));
// 	BOOST_TEST(eq4);
// }
