#include <benchmark/benchmark.h>

#include <Eigen/Core>

#include <mitrax/dim.hpp>

#include <random>
#include <string>

#include "../../../include/get_binaryop.hpp"


using namespace mitrax;
using namespace mitrax::literals;


template < typename T, typename Op, typename D1, typename D2 >
[[gnu::noinline]]
void bm(benchmark::State& state, Op op, D1 d1, D2 d2){
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution< T > dis(
		std::numeric_limits< T >::min(),
		std::numeric_limits< T >::max()
	);

	using namespace Eigen;

	auto m1 = Matrix< T, D1::ct_cols, D1::ct_rows >(
		size_t(d1.cols()), size_t(d1.rows())
	);
	for(int y = 0; y < m1.rows(); ++y){
		for(int x = 0; x < m1.cols(); ++x){
			m1(x, y) = dis(gen);
		}
	}

	auto m2 = Matrix< T, D2::ct_cols, D2::ct_rows >(
		size_t(d2.cols()), size_t(d2.rows())
	);
	for(int y = 0; y < m2.rows(); ++y){
		for(int x = 0; x < m2.cols(); ++x){
			m2(x, y) = dis(gen);
		}
	}

	while(state.KeepRunning()){
		auto res = op(m1, m2);
		benchmark::DoNotOptimize(res);
	}
}


#include <boost/hana/tuple.hpp>
#include <boost/hana/for_each.hpp>


namespace init{

	auto dimensions = boost::hana::make_tuple(
			dim_pair(2_C, 2_R),
			dim_pair(4_C, 2_R),
			dim_pair(8_C, 2_R),
			dim_pair(8_C, 4_R),
			dim_pair(8_C, 8_R),
			dim_pair(8_C, 16_R),
			dim_pair(8_C, 32_R),
			dim_pair(8_C, 64_R),
			dim_pair(16_C, 64_R),
			dim_pair(32_C, 64_R),
			dim_pair(64_C, 64_R)/*,
			dim_pair(128_C, 64_R),
			dim_pair(256_C, 64_R),
			dim_pair(256_C, 128_R),
			dim_pair(256_C, 256_R)*/
		);

	using type = float;

	using plus = std::plus<>;
	using multiplies = std::multiplies<>;

}

#include "main.hpp"
