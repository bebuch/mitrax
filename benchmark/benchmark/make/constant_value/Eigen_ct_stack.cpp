#include <benchmark/benchmark.h>

#include <mitrax/operator.hpp>

#include <boost/hana/core/make.hpp>
#include <boost/hana/equal.hpp>
#include <boost/hana/tuple.hpp>
#include <boost/hana/for_each.hpp>

#include <Eigen/Core>


using namespace mitrax;
using namespace mitrax::literals;

namespace hana = boost::hana;


template < typename T, typename D1 >
[[gnu::noinline]]
void BM_make(benchmark::State& state, T v, D1){
	while(state.KeepRunning()){
		auto m = Eigen::Matrix< T, D1::ct_rows, D1::ct_cols >();
		m.fill(v);

		benchmark::DoNotOptimize(m);
	}
}

int main(int argc, char** argv){
	using f4 = float;

	hana::for_each(hana::make_tuple(
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
			dim_pair(128_C, 64_R)
// 			dim_pair(256_C, 64_R),
// 			dim_pair(256_C, 128_R),
// 			dim_pair(256_C, 256_R)
		), [](auto d1){
			using dim1_t = decltype(d1);
			benchmark::RegisterBenchmark(
				std::to_string(d1.point_count()).c_str(),
				BM_make< f4, dim1_t >, 5, d1
			);
		}
	);

	benchmark::Initialize(&argc, argv);
	benchmark::RunSpecifiedBenchmarks();
}
