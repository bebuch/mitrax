#include <benchmark/benchmark.h>

#include <mitrax/operator.hpp>

#include <random>
#include <string>


using namespace mitrax;
using namespace mitrax::literals;


template < typename T1, typename T2, typename T >
void BM_matrix_multiplication(benchmark::State& state, T dims){
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution< T1 > dis1(
		std::numeric_limits< T1 >::min(),
		std::numeric_limits< T1 >::max()
	);
	std::uniform_int_distribution< T2 > dis2(
		std::numeric_limits< T2 >::min(),
		std::numeric_limits< T2 >::max()
	);

	auto m1 = make_matrix_fn(dims.cols(), dims.rows(),
		[&dis1, &gen](auto, auto){
			return dis1(gen);
		});

	auto m2 = make_matrix_fn(dims.rows().as_col(), dims.cols().as_row(),
		[&dis2, &gen](auto, auto){
			return dis2(gen);
		});

	while(state.KeepRunning()){
		auto res = m1 * m2;
	}
}

int main(int argc, char** argv){
	using f4 = float;

	for(auto& dim: std::vector< dims_t< 0, 0 > >{
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
			std::to_string(dim.point_count()).c_str(),
			BM_matrix_multiplication< f4, f4, dims_t< 0, 0 > >,
			dim
		);
	}

	benchmark::Initialize(&argc, argv);
	benchmark::RunSpecifiedBenchmarks();
}
