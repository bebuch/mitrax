#include <benchmark/benchmark.h>

#include <mitrax/operator.hpp>

#include "../../../include/random_vector.hpp"


using namespace mitrax;
using namespace mitrax::literals;


template < typename T, typename D >
void BM_make(benchmark::State& state, D d1){
	auto r = mitrax::random_vector< T >(d1.point_count());

	while(state.KeepRunning()){
		auto m = make_matrix_fn(d1,
			[&r, d1](auto x, auto y){
				return r[y * d1.cols() + x];
			});

		benchmark::DoNotOptimize(m);
	}
}

int main(int argc, char** argv){
	using f4 = float;

	for(auto& d1: std::vector< dims_t< 0, 0 > >{
		{2, 2},
		{4, 2},
		{8, 2},
		{8, 4},
		{8, 8},
		{8, 16},
		{8, 32},
		{8, 64},
		{16, 64},
		{32, 64},
		{64, 64},
		{128, 64},
		{256, 64},
		{256, 128},
		{256, 256}
	}){
		benchmark::RegisterBenchmark(
			std::to_string(d1.point_count()).c_str(),
			BM_make< f4, dims_t< 0, 0 > >, d1
		);
	}

	benchmark::Initialize(&argc, argv);
	benchmark::RunSpecifiedBenchmarks();
}
