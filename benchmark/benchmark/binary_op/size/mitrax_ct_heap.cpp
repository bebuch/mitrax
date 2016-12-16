#include <benchmark/benchmark.h>

#include <mitrax/operator.hpp>

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

	auto m1 = make_matrix_fn(d1,
		[&dis, &gen](auto, auto){
			return dis(gen);
		}, maker::heap);

	auto m2 = make_matrix_fn(d2,
		[&dis, &gen](auto, auto){
			return dis(gen);
		}, maker::heap);

	while(state.KeepRunning()){
		auto res = op(m1, m2);
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
