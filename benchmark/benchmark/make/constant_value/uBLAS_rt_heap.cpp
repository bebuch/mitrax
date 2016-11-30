#include <benchmark/benchmark.h>

#include <boost/numeric/ublas/matrix.hpp>

#include <mitrax/dim.hpp>


using namespace mitrax;
using namespace mitrax::literals;


template < typename T >
[[gnu::noinline]]
void bm(benchmark::State& state, T v, rt_dim_pair_t d){
	while(state.KeepRunning()){
		boost::numeric::ublas::matrix< T > m(
			size_t(d.cols()), size_t(d.rows()), v
		);

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
