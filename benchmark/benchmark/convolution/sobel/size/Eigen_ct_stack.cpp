#include <benchmark/benchmark.h>

#include "../../../../include/Eigen/sobel.hpp"


using namespace Eigen;

template < typename T >
[[gnu::noinline]]
void BM_sobel2(benchmark::State& state, std::pair< int, int > d1){
	auto m = Matrix< T, Eigen::Dynamic, Eigen::Dynamic >::
		Random(d1.second, d1.first);

	while(state.KeepRunning()){
		auto res = sobel_x< T >(m);

		benchmark::DoNotOptimize(res);
	}
}


int main(int argc, char** argv) {
	using f4 = float;

	for(auto& d1: std::vector< std::pair< int, int > >{
		{64, 64},
		{256, 256},
		{1024, 1024}
	}){
		benchmark::RegisterBenchmark(
			std::to_string(d1.first * d1.second).c_str(),
			BM_sobel2< f4 >, d1
		);
	}

	benchmark::Initialize(&argc, argv);
	benchmark::RunSpecifiedBenchmarks();
}
