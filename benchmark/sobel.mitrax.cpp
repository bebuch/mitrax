#include <benchmark/benchmark.h>

#include <mitrax/convolution/edge_operators.hpp>

#include <random>


using namespace mitrax;
using namespace mitrax::literals;


template < typename InputType, typename ResultType >
void BM_sobel(benchmark::State& state){
	using value_type = InputType;

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution< value_type > dis(
		std::numeric_limits< value_type >::min(),
		std::numeric_limits< value_type >::max()
	);

	auto m = make_matrix_fn(1024_C_rt, 1024_R_rt, [&dis, &gen](auto, auto){
		return dis(gen);
	});

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

	benchmark::RegisterBenchmark("i1->i1", BM_sobel< i1, i1 >);
	benchmark::RegisterBenchmark("u1->i2", BM_sobel< u1, i2 >);
	benchmark::RegisterBenchmark("u1->f4", BM_sobel< u1, f4 >);
	benchmark::RegisterBenchmark("u1->f8", BM_sobel< u1, f8 >);

	benchmark::RegisterBenchmark("i2->i2", BM_sobel< i2, i2 >);
	benchmark::RegisterBenchmark("u2->i4", BM_sobel< u2, i4 >);
	benchmark::RegisterBenchmark("u2->f4", BM_sobel< u2, f4 >);
	benchmark::RegisterBenchmark("u2->f8", BM_sobel< u2, f8 >);

	benchmark::RegisterBenchmark("f4->f4", BM_sobel< f4, f4 >);
	benchmark::RegisterBenchmark("f4->f8", BM_sobel< f4, f8 >);
	benchmark::RegisterBenchmark("f8->f4", BM_sobel< f8, f4 >);
	benchmark::RegisterBenchmark("f8->f8", BM_sobel< f8, f8 >);

	benchmark::Initialize(&argc, argv);
	benchmark::RunSpecifiedBenchmarks();
}
