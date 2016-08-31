#include <benchmark/benchmark.h>

#include <mitrax/operator.hpp>

#include <boost/hana/core/make.hpp>
#include <boost/hana/equal.hpp>
#include <boost/hana/tuple.hpp>
#include <boost/hana/for_each.hpp>

#include "include/random_vector.hpp"


using namespace mitrax;
using namespace mitrax::literals;

namespace hana = boost::hana;


template < typename T, typename D1 >
void BM_make(benchmark::State& state, D1 d1){
	auto r = mitrax::random_vector< T >(d1.point_count());

	while(state.KeepRunning()){
		auto m = make_matrix_fn(d1,
			[&r, d1](auto x, auto y){
				return r[y * d1.cols() + x];
			}, memory_heap);

		benchmark::DoNotOptimize(m);
	}
}

int main(int argc, char** argv){
	using f4 = float;

	hana::for_each(hana::make_tuple(
			dims< 2, 2 >(),
			dims< 4, 2 >(),
			dims< 8, 2 >(),
			dims< 8, 4 >(),
			dims< 8, 8 >(),
			dims< 8, 16 >(),
			dims< 8, 32 >(),
			dims< 8, 64 >(),
			dims< 16, 64 >(),
			dims< 32, 64 >(),
			dims< 64, 64 >(),
			dims< 128, 64 >(),
			dims< 256, 64 >(),
			dims< 256, 128 >(),
			dims< 256, 256 >()
		), [](auto d1){
			using dim1_t = decltype(d1);
			benchmark::RegisterBenchmark(
				std::to_string(d1.point_count()).c_str(),
				BM_make< f4, dim1_t >, d1
			);
		}
	);

	benchmark::Initialize(&argc, argv);
	benchmark::RunSpecifiedBenchmarks();
}
