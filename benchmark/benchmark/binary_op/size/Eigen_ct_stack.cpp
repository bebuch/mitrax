#include <benchmark/benchmark.h>

#include <mitrax/operator.hpp>

#include <boost/hana/core/make.hpp>
#include <boost/hana/equal.hpp>
#include <boost/hana/tuple.hpp>
#include <boost/hana/for_each.hpp>

#include <Eigen/Core>

#include <random>
#include <string>

#include "../../../include/get_binaryop.hpp"


using namespace mitrax;
using namespace mitrax::literals;

namespace hana = boost::hana;


template < typename Op, typename T, typename D1, typename D2 >
void BM_binaryop(benchmark::State& state, Op op, D1, D2){
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution< T > dis(
		std::numeric_limits< T >::min(),
		std::numeric_limits< T >::max()
	);

	auto m1 = Eigen::Matrix< T, D1::ct_cols, D1::ct_rows >::Random();
	auto m2 = Eigen::Matrix< T, D2::ct_cols, D2::ct_rows >::Random();

	while(state.KeepRunning()){
		auto res = op(m1, m2);
		benchmark::DoNotOptimize(res);
	}
}

int main(int argc, char** argv){
	using f4 = float;

	auto register_fn = [](auto op, auto transfrom_dim){
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
				dims< 128, 64 >()
// 				dims< 256, 64 >(),
// 				dims< 256, 128 >(),
// 				dims< 256, 256 >()
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
				return dims(d.rows().as_col(), d.cols().as_row());
			});
		}break;
	}

	benchmark::Initialize(&argc, argv);
	benchmark::RunSpecifiedBenchmarks();
}
