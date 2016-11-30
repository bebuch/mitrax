#include <benchmark/benchmark.h>

#include <mitrax/operator.hpp>

#include <random>
#include <string>

#include "../../../include/get_binaryop.hpp"


using namespace mitrax;
using namespace mitrax::literals;


template < typename T, typename Op >
[[gnu::noinline]]
void bm(benchmark::State& state, Op op, rt_dim_pair_t d1, rt_dim_pair_t d2){
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution< T > dis(
		std::numeric_limits< T >::min(),
		std::numeric_limits< T >::max()
	);

	auto m1 = make_matrix_fn(d1,
		[&dis, &gen](auto, auto){
			return dis(gen);
		});

	auto m2 = make_matrix_fn(d2,
		[&dis, &gen](auto, auto){
			return dis(gen);
		});

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
			dim_pair(64_C, 64_R),
			dim_pair(128_C, 64_R),
			dim_pair(256_C, 64_R),
			dim_pair(256_C, 128_R),
			dim_pair(256_C, 256_R)
		);

	using type = float;

	using plus = std::plus<>;
	using multiplies = std::multiplies<>;

}

#include "main.hpp"
