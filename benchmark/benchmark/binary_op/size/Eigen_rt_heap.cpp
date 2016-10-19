#include <benchmark/benchmark.h>

#include <Eigen/Core>

#include <string>

#include "../../../include/get_binaryop.hpp"


using namespace Eigen;


template < typename Op, typename T >
void BM_binaryop(
	benchmark::State& state, Op op,
	std::pair< int, int > d1,
	std::pair< int, int > d2
){
	auto m1 = Matrix< T, Dynamic, Dynamic >::Random(d1.first, d1.second);
	auto m2 = Matrix< T, Dynamic, Dynamic >::Random(d2.first, d2.second);

	while(state.KeepRunning()){
		auto res = op(m1, m2);
		benchmark::DoNotOptimize(res);
	}
}

int main(int argc, char** argv){
	using f4 = float;

	auto register_fn = [](auto op, auto transfrom_dim){
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
			auto d2 = transfrom_dim(d1);
			benchmark::RegisterBenchmark(
				std::to_string(d1.first * d1.second).c_str(),
				BM_binaryop< decltype(op), f4 >,
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
				return std::make_pair(d.second, d.first);
			});
		}break;
	}

	benchmark::Initialize(&argc, argv);
	benchmark::RunSpecifiedBenchmarks();
}
