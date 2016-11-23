#include <benchmark/benchmark.h>

#include <mitrax/operator.hpp>

#include <boost/hana/core/make.hpp>
#include <boost/hana/equal.hpp>
#include <boost/hana/tuple.hpp>
#include <boost/hana/for_each.hpp>

#include <random>
#include <string>

#include "../../../include/get_binaryop.hpp"


using namespace mitrax;
using namespace mitrax::literals;

namespace hana = boost::hana;


template < typename Op, typename T, typename D1, typename D2 >
void BM_binaryop(benchmark::State& state, Op op, D1 d1, D2 d2){
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution< T > dis(
		std::numeric_limits< T >::min(),
		std::numeric_limits< T >::max()
	);
	auto m1 = make_matrix_fn(d1,
		[&dis, &gen](auto, auto){
			return dis(gen);
		}, maker::heap);

	auto m2 = make_matrix_fn(d2,
		[&dis, &gen](auto, auto){
			return dis(gen);
		}, maker::heap);

	while(state.KeepRunning()){
		auto res = op(m1, m2);
		benchmark::DoNotOptimize(res);
	}
}

int main(int argc, char** argv){
	using f4 = float;

	auto register_fn = [](auto op, auto transfrom_dim){
		hana::for_each(hana::make_tuple(
				dim_pair(2_C, 2_R),
				dim_pair(4_C, 2_R),
				dim_pair(8_C, 2_R),
				dim_pair(8_C, 4_R),
				dim_pair(8_C, 8_R),
				dim_pair(8_C, 16_R),
				dim_pair(8_C, 32_R),
				dim_pair(8_C, 64_R),
				dim_pair(16_C, 64_R),
				dim_pair(32_C, 64_R),
				dim_pair(64_C, 64_R)
// 				dim_pair(128_C, 64_R),
// 				dim_pair(256_C, 64_R),
// 				dim_pair(256_C, 128_R),
// 				dim_pair(256_C, 256_R)
			), [op, transfrom_dim](auto d1){
				auto d2 = transfrom_dim(d1);
				using dim1_t = decltype(d1);
				using dim2_t = decltype(d2);
				benchmark::RegisterBenchmark(
					std::to_string(d1.point_count()).c_str(),
					BM_binaryop< decltype(op), f4, dim1_t, dim2_t >,
					op, d1, d2
				);
			}
		);
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
