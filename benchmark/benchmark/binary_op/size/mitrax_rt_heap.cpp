#include <benchmark/benchmark.h>

#include <mitrax/operator.hpp>

#include <random>
#include <string>

#include "../../../include/get_binaryop.hpp"


using namespace mitrax;
using namespace mitrax::literals;


template < typename Op, typename T, typename D >
void BM_binaryop(benchmark::State& state, Op op, D dims1, D dims2){
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution< T > dis(
		std::numeric_limits< T >::min(),
		std::numeric_limits< T >::max()
	);

	auto m1 = make_matrix_fn(dims1,
		[&dis, &gen](auto, auto){
			return dis(gen);
		});

	auto m2 = make_matrix_fn(dims2,
		[&dis, &gen](auto, auto){
			return dis(gen);
		});

	while(state.KeepRunning()){
		auto res = op(m1, m2);
		benchmark::DoNotOptimize(res);
	}
}

int main(int argc, char** argv){
	using f4 = float;

	auto register_fn = [](auto op, auto transfrom_dim){
		for(auto& d1: std::vector< auto_dim_pair_t< 0, 0 > >{
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
			auto d2 = transfrom_dim(d1);
			benchmark::RegisterBenchmark(
				std::to_string(d1.point_count()).c_str(),
				BM_binaryop< decltype(op), f4, auto_dim_pair_t< 0, 0 > >,
				op, d1, d2
			);
		}
	};

	switch(mitrax::get_binaryop(argc, argv)){
		case mitrax::op::unknown: return 1;
		case mitrax::op::plus:{
			register_fn(std::plus<>(), [](auto d){ return d; });
		}break;
		case mitrax::op::mul:{
			register_fn(std::multiplies<>(), [](auto d){
				return dim_pair(d.rows().as_col(), d.cols().as_row());
			});
		}break;
	}

	benchmark::Initialize(&argc, argv);
	benchmark::RunSpecifiedBenchmarks();
}
