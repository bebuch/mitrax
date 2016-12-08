#include <benchmark/benchmark.h>

#include <Eigen/Core>

#include <mitrax/dim.hpp>


using namespace mitrax;
using namespace mitrax::literals;


template < typename T >
[[gnu::noinline]]
void bm(benchmark::State& state, T v, rt_dim_pair_t d){
	while(state.KeepRunning()){
		Eigen::Matrix< T, Eigen::Dynamic, Eigen::Dynamic > m(
			size_t(d.rows()), size_t(d.cols())
		);
		m.fill(v);

		benchmark::DoNotOptimize(m);
	}
}


#include <boost/hana/tuple.hpp>
#include <boost/hana/for_each.hpp>


namespace init{

	constexpr auto dimensions = boost::hana::make_tuple(
			dim_pair(2_c, 2_r),
			dim_pair(4_c, 2_r),
			dim_pair(8_c, 2_r),
			dim_pair(8_c, 4_r),
			dim_pair(8_c, 8_r),
			dim_pair(8_c, 16_r),
			dim_pair(8_c, 32_r),
			dim_pair(8_c, 64_r),
			dim_pair(16_c, 64_r),
			dim_pair(32_c, 64_r),
			dim_pair(64_c, 64_r),
			dim_pair(128_c, 64_r),
			dim_pair(256_c, 64_r),
			dim_pair(256_c, 128_r),
			dim_pair(256_c, 256_r)
		);

}

#include "main.hpp"
