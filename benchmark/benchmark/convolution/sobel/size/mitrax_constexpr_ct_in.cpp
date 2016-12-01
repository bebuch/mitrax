#include <benchmark/benchmark.h>

#include <mitrax/convolution/edge_operators.hpp>

#include <random>


using namespace mitrax;
using namespace mitrax::literals;


template < typename T, typename D >
[[gnu::noinline]]
void bm(benchmark::State& state, D d){
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution< T > dis(
		std::numeric_limits< T >::min(),
		std::numeric_limits< T >::max()
	);

	auto m = make_matrix_fn(d, [&dis, &gen](auto, auto){
		return dis(gen);
	}, maker::heap_t());

	while(state.KeepRunning()){
		auto res = sobel_x< T >(m);

		benchmark::DoNotOptimize(res);
	}
}

#include "main.hpp"
