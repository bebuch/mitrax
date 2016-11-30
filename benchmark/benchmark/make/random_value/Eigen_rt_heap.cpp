#include <benchmark/benchmark.h>

#include <Eigen/Core>

#include "../../../include/random_vector.hpp"


using namespace Eigen;


template < typename T >
[[gnu::noinline]]
void BM_make(benchmark::State& state, std::pair< int, int > d1){
	auto r = mitrax::random_vector< T >(d1.second * d1.first);

	while(state.KeepRunning()){
		auto m = Matrix< T, Dynamic, Dynamic >(d1.second, d1.first);

		for(int y = 0; y < m.rows(); ++y){
			for(int x = 0; x < m.cols(); ++x){
				m(y, x) = r[y * m.cols() + x];
			}
		}

		benchmark::DoNotOptimize(m);
	}
}

int main(int argc, char** argv){
	using f4 = float;

	for(auto& d1: std::vector< std::pair< int, int > >{
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
			std::to_string(d1.first * d1.second).c_str(),
			BM_make< f4 >, d1
		);
	}

	benchmark::Initialize(&argc, argv);
	benchmark::RunSpecifiedBenchmarks();
}
