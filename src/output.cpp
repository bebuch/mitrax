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
// #include <mitrax/output.hpp>
// 
// #include <sstream>
// 
// 
// using boost::typeindex::type_id;
// using boost::typeindex::type_id_runtime;
// using namespace mitrax;
// 
// 
// BOOST_AUTO_TEST_CASE(test_output_3x3){
// 	auto m = to_square_matrix< int, 3 >({
// 		{1, 2, 3},
// 		{4, 5, 6},
// 		{7, 8, 9}
// 	});
// 
// 	std::ostringstream os;
// 	os << m;
// 
// 	BOOST_TEST(os.str() == "[3,3]((1,2,3),(4,5,6),(7,8,9))");
// }
// 
// BOOST_AUTO_TEST_CASE(test_output_2x3){
// 	auto m = make_matrix< int, 2, 3 >({
// 		{1, 2},
// 		{4, 5},
// 		{7, 8}
// 	});
// 
// 	std::ostringstream os;
// 	os << m;
// 
// 	BOOST_TEST(os.str() == "[2,3]((1,2),(4,5),(7,8))");
// }
// 
// BOOST_AUTO_TEST_CASE(test_output_3x2){
// 	auto m = make_matrix< int, 3, 2 >({
// 		{1, 2, 3},
// 		{4, 5, 6}
// 	});
// 
// 	std::ostringstream os;
// 	os << m;
// 
// 	BOOST_TEST(os.str() == "[3,2]((1,2,3),(4,5,6))");
// }
