#include <benchmark/benchmark.h>

#include <mitrax/dim.hpp>

#include "../../../../include/Eigen/sobel.hpp"

#include <random>


using namespace mitrax;
using namespace mitrax::literals;


template < typename T >
[[gnu::noinline]]
void bm(benchmark::State& state, rt_dim_pair_t d){
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution< T > dis(
		std::numeric_limits< T >::min(),
		std::numeric_limits< T >::max()
	);

	Eigen::Matrix< T, Eigen::Dynamic, Eigen::Dynamic > m(
		size_t(d.rows()), size_t(d.cols())
	);
	for(int y = 0; y < m.rows(); ++y){
		for(int x = 0; x < m.cols(); ++x){
			m(y, x) = dis(gen);
		}
	}

	while(state.KeepRunning()){
		auto res = Eigen::sobel_x< T >(m);

		benchmark::DoNotOptimize(res);
	}
}

#include "main.hpp"
