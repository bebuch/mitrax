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
void bm(benchmark::State& state, Op op, D1, D2){
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution< T > dis(
		std::numeric_limits< T >::min(),
		std::numeric_limits< T >::max()
	);

	using namespace Eigen;

	Matrix< T, size_t(D1::ct_rows), size_t(D1::ct_cols) > m1;
	for(int y = 0; y < m1.rows(); ++y){
		for(int x = 0; x < m1.cols(); ++x){
			m1(y, x) = dis(gen);
		}
	}

	Matrix< T, size_t(D2::ct_rows), size_t(D2::ct_cols) > m2;
	for(int y = 0; y < m2.rows(); ++y){
		for(int x = 0; x < m2.cols(); ++x){
			m2(y, x) = dis(gen);
		}
	}

	while(state.KeepRunning()){
		auto res = op(m1, m2).eval();
		benchmark::DoNotOptimize(res);
	}
}


#include <boost/hana/tuple.hpp>
#include <boost/hana/for_each.hpp>


namespace init{

	constexpr auto dimensions = boost::hana::make_tuple(
			dim_pair(2_CS, 2_RS),
			dim_pair(4_CS, 2_RS),
			dim_pair(8_CS, 2_RS),
			dim_pair(8_CS, 4_RS),
			dim_pair(8_CS, 8_RS),
			dim_pair(8_CS, 16_RS),
			dim_pair(8_CS, 32_RS),
			dim_pair(8_CS, 64_RS),
			dim_pair(16_CS, 64_RS),
			dim_pair(32_CS, 64_RS),
			dim_pair(64_CS, 64_RS)/*,
			dim_pair(128_CS, 64_RS),
			dim_pair(256_CS, 64_RS),
			dim_pair(256_CS, 128_RS),
			dim_pair(256_CS, 256_RS)*/
		);

	using plus = std::plus<>;
	using multiplies = std::multiplies<>;

}

#include "main.hpp"
