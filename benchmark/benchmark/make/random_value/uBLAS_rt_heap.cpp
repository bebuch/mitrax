#include <benchmark/benchmark.h>

#include <boost/numeric/ublas/matrix.hpp>

#include "../../../include/random_vector.hpp"


template < typename T >
[[gnu::noinline]]
void BM_make(benchmark::State& state, std::pair< int, int > d1){
	auto r = mitrax::random_vector< T >(d1.second * d1.first);

	while(state.KeepRunning()){
		boost::numeric::ublas::matrix< T > m(d1.first, d1.second);

		for(size_t y = 0; y < m.size2(); ++y){
			for(size_t x = 0; x < m.size1(); ++x){
				m(x, y) = r[y * m.size1() + x];
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
