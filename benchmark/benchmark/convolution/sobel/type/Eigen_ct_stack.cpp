#include <benchmark/benchmark.h>

#include "../../../../include/Eigen/sobel.hpp"


using namespace Eigen;


template < typename InputType, typename ResultType >
[[gnu::noinline]]
void BM_sobel(benchmark::State& state, std::pair< int, int > d1){
	auto m = Matrix< InputType, Eigen::Dynamic, Eigen::Dynamic >::
		Random(d1.second, d1.first);

	while(state.KeepRunning()){
		auto res = sobel_x< ResultType >(m);
	}
}

int main(int argc, char** argv) {
	using i1 = std::int8_t;
	using u1 = std::uint8_t;
	using i2 = std::int16_t;
	using u2 = std::uint16_t;
	using i4 = std::int32_t;
	using f4 = float;
	using f8 = double;

	for(auto& d1: std::vector< std::pair< int, int > >{
		{1024, 1024}
	}){
		benchmark::RegisterBenchmark("i1->i1", BM_sobel< i1, i1 >, d1);
		benchmark::RegisterBenchmark("u1->i2", BM_sobel< u1, i2 >, d1);
		benchmark::RegisterBenchmark("u1->f4", BM_sobel< u1, f4 >, d1);
		benchmark::RegisterBenchmark("u1->f8", BM_sobel< u1, f8 >, d1);

		benchmark::RegisterBenchmark("i2->i2", BM_sobel< i2, i2 >, d1);
		benchmark::RegisterBenchmark("u2->i4", BM_sobel< u2, i4 >, d1);
		benchmark::RegisterBenchmark("u2->f4", BM_sobel< u2, f4 >, d1);
		benchmark::RegisterBenchmark("u2->f8", BM_sobel< u2, f8 >, d1);

		benchmark::RegisterBenchmark("f4->f4", BM_sobel< f4, f4 >, d1);
		benchmark::RegisterBenchmark("f4->f8", BM_sobel< f4, f8 >, d1);
		benchmark::RegisterBenchmark("f8->f4", BM_sobel< f8, f4 >, d1);
		benchmark::RegisterBenchmark("f8->f8", BM_sobel< f8, f8 >, d1);
	}

	benchmark::Initialize(&argc, argv);
	benchmark::RunSpecifiedBenchmarks();
}
