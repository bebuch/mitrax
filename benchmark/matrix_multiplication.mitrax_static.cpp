#include <benchmark/benchmark.h>

#include <mitrax/operator.hpp>

#include <boost/hana/core/make.hpp>
#include <boost/hana/equal.hpp>
#include <boost/hana/tuple.hpp>
#include <boost/hana/for_each.hpp>

#include <random>
#include <string>


using namespace mitrax;
using namespace mitrax::literals;

namespace hana = boost::hana;


template < typename T, size_t C, size_t R >
void BM_matrix_multiplication(benchmark::State& state){
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution< T > dis(
		std::numeric_limits< T >::min(),
		std::numeric_limits< T >::max()
	);
	auto m1 = make_matrix_fn(cols< C >(), rows< R >(),
		[&dis, &gen](auto, auto){
			return dis(gen);
		});

	auto m2 = make_matrix_fn(cols< R >(), rows< C >(),
		[&dis, &gen](auto, auto){
			return dis(gen);
		});

	while(state.KeepRunning()){
		auto res = m1 * m2;
		benchmark::DoNotOptimize(res);
	}
}

int main(int argc, char** argv){
	using f4 = float;

	hana::for_each(hana::make_tuple(
			dims< 2, 2 >(),
			dims< 4, 2 >(),
			dims< 8, 2 >(),
			dims< 16, 2 >(),
			dims< 16, 4 >(),
			dims< 16, 8 >(),
			dims< 16, 16 >(),
			dims< 16, 32 >(),
			dims< 16, 64 >()
		), [](auto dim){
			using dim_t = decltype(dim);
			benchmark::RegisterBenchmark(
				std::to_string(dim.point_count()).c_str(),
				BM_matrix_multiplication
					< f4, dim_t::static_cols, dim_t::static_rows >
			);
		}
	);

	benchmark::Initialize(&argc, argv);
	benchmark::RunSpecifiedBenchmarks();
}
