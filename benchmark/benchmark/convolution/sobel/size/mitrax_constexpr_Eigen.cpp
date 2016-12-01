#include <benchmark/benchmark.h>

#include <mitrax/convolution/edge_operators.hpp>
#include <mitrax/matrix/eigen.hpp>

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

	auto m = make_matrix_fn(d, [&dis, &gen](auto, auto){
		return dis(gen);
	}, maker::eigen);

	while(state.KeepRunning()){
		auto res = sobel_x< T >(m);

		benchmark::DoNotOptimize(res);
	}
}

#include "main.hpp"
