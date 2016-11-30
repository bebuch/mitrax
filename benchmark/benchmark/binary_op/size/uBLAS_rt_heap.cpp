#include <benchmark/benchmark.h>

#include <boost/numeric/ublas/matrix.hpp>

#include <mitrax/dim.hpp>

#include <random>
#include <string>

#include "../../../include/get_binaryop.hpp"


using namespace mitrax;
using namespace mitrax::literals;


template < typename T, typename Op >
[[gnu::noinline]]
void bm(benchmark::State& state, Op op, rt_dim_pair_t d1, rt_dim_pair_t d2){
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution< T > dis(
		std::numeric_limits< T >::min(),
		std::numeric_limits< T >::max()
	);

	boost::numeric::ublas::matrix< T > m1(size_t(d1.cols()), size_t(d1.rows()));
	for(size_t y = 0; y < m1.size2(); ++y){
		for(size_t x = 0; x < m1.size1(); ++x){
			m1(x, y) = dis(gen);
		}
	}

	boost::numeric::ublas::matrix< T > m2(size_t(d2.cols()), size_t(d2.rows()));
	for(size_t y = 0; y < m2.size2(); ++y){
		for(size_t x = 0; x < m2.size1(); ++x){
			m2(x, y) = dis(gen);
		}
	}

	while(state.KeepRunning()){
		boost::numeric::ublas::matrix< T > res = op(m1, m2);
		benchmark::DoNotOptimize(res);
	}
}


#include <boost/hana/tuple.hpp>
#include <boost/hana/for_each.hpp>


namespace init{

	auto dimensions = boost::hana::make_tuple(
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
			dim_pair(64_C, 64_R),
			dim_pair(128_C, 64_R),
			dim_pair(256_C, 64_R),
			dim_pair(256_C, 128_R),
			dim_pair(256_C, 256_R)
		);

	using type = float;

	using plus = std::plus<>;
	struct multiplies{
		template < typename T, typename U>
		constexpr decltype(auto) operator()(T&& lhs, U&& rhs)const{
			return boost::numeric::ublas::prod(
				static_cast< T&& >(lhs),
				static_cast< U&& >(rhs)
			);
		}
	};

}

#include "main.hpp"

