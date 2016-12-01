#include <benchmark/benchmark.h>

#include <mitrax/dim.hpp>

#include "../../../../include/uBLAS/sobel.hpp"

#include <random>


using namespace mitrax;
using namespace mitrax::literals;


template < typename T >
[[gnu::noinline]]
void bm(benchmark::State& state, rt_dim_pair_t d){
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution< T > dis(
		std::numeric_limits< T >::min(),
		std::numeric_limits< T >::max()
	);

	boost::numeric::ublas::matrix< T > m(size_t(d.cols()), size_t(d.rows()));
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

#include "main.hpp"
