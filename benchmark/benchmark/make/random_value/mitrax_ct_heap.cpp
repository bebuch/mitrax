#include <benchmark/benchmark.h>

#include <mitrax/make_matrix.hpp>

#include "../../../include/random_vector.hpp"


using namespace mitrax;
using namespace mitrax::literals;


template < typename T, typename D >
[[gnu::noinline]]
void bm(benchmark::State& state, D d){
	auto r = mitrax::random_vector< T >(d.point_count());

	while(state.KeepRunning()){
		auto m = make_matrix_i(d, r.begin(), maker::heap);

		benchmark::DoNotOptimize(m);
	}
}


#include <boost/hana/tuple.hpp>
#include <boost/hana/for_each.hpp>


namespace init{

	constexpr auto dimensions = boost::hana::make_tuple(
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

}

#include "main.hpp"
