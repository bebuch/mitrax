#include <benchmark/benchmark.h>

#include <Eigen/Core>

#include <string>


using namespace Eigen;


template < typename T1, typename T2 >
void BM_matrix_multiplication(
	benchmark::State& state, std::pair< int, int > dims
){
	auto m1 = Matrix< T1, Dynamic, Dynamic >::Random(dims.first, dims.second);
	auto m2 = Matrix< T2, Dynamic, Dynamic >::Random(dims.second, dims.first);

	while(state.KeepRunning()){
		auto res = m1 * m2;
	}
}

int main(int argc, char** argv){
	using f4 = float;

	for(auto& dim: std::vector< std::pair< int, int > >{
		{2, 2},
		{4, 2},
		{8, 2},
		{16, 2},
		{16, 4},
		{16, 8},
		{16, 16},
		{16, 32},
		{16, 64},
		{16, 128},
		{16, 256}
	}){
		benchmark::RegisterBenchmark(
			std::to_string(dim.first * dim.second).c_str(),
			BM_matrix_multiplication< f4, f4 >,
			dim
		);
	}

	benchmark::Initialize(&argc, argv);
	benchmark::RunSpecifiedBenchmarks();
}
