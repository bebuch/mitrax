#include <benchmark/benchmark.h>

#include "../../../../include/Eigen/sobel.hpp"


using namespace Eigen;

template < typename T >
[[gnu::noinline]]
void BM_sobel2(benchmark::State& state, std::pair< int, int > d){
	auto m = Matrix< T, Eigen::Dynamic, Eigen::Dynamic >::
		Random(d.second, d.first);

	while(state.KeepRunning()){
		auto res = sobel_x< T >(m);

		benchmark::DoNotOptimize(res);
	}
}


int main(int argc, char** argv) {
	using f4 = float;

	for(auto& d: std::vector< std::pair< int, int > >{
		{1024, 1024}
	}){
		benchmark::RegisterBenchmark(
			std::to_string(d.first * d.second).c_str(),
			BM_sobel2< f4 >, d
		);
	}

	benchmark::Initialize(&argc, argv);
	benchmark::RunSpecifiedBenchmarks();
}
