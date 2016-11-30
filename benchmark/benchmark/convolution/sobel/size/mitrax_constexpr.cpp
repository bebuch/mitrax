#include <benchmark/benchmark.h>

#include <mitrax/convolution/edge_operators.hpp>

#include <random>


using namespace mitrax;
using namespace mitrax::literals;


template < typename T, typename D >
[[gnu::noinline]]
void BM_sobel2(benchmark::State& state, D d1){
	using value_type = T;

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution< value_type > dis(
		std::numeric_limits< value_type >::min(),
		std::numeric_limits< value_type >::max()
	);

	auto m = make_matrix_fn(d1, [&dis, &gen](auto, auto){
		return dis(gen);
	});

	while(state.KeepRunning()){
		auto res = sobel_x< T >(m);

		benchmark::DoNotOptimize(res);
	}
}


int main(int argc, char** argv) {
	using f4 = float;

	for(auto& d1: std::vector< auto_dim_pair_t< 0, 0 > >{
		{1024_Cd, 1024_Rd}
	}){
		benchmark::RegisterBenchmark(
			std::to_string(d1.point_count()).c_str(),
			BM_sobel2< f4, auto_dim_pair_t< 0, 0 > >, d1
		);
	}

	benchmark::Initialize(&argc, argv);
	benchmark::RunSpecifiedBenchmarks();
}
