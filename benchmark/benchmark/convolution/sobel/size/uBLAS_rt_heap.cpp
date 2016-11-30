#include <benchmark/benchmark.h>

#include "../../../../include/uBLAS/sobel.hpp"

#include <random>


template < typename T >
[[gnu::noinline]]
void BM_sobel2(benchmark::State& state, std::pair< int, int > d1){
	using value_type = T;

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution< value_type > dis(
		std::numeric_limits< value_type >::min(),
		std::numeric_limits< value_type >::max()
	);

	boost::numeric::ublas::matrix< T > m(d1.first, d1.second);

	for(size_t y = 0; y < m.size2(); ++y){
		for(size_t x = 0; x < m.size1(); ++x){
			m(x, y) = dis(gen);
		}
	}

	while(state.KeepRunning()){
		auto res = uBLAS::sobel_x< T >(m);

		benchmark::DoNotOptimize(res);
	}
}

int main(int argc, char** argv) {
	using f4 = float;

	for(auto& d1: std::vector< std::pair< int, int > >{
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
