#include <benchmark/benchmark.h>

#include <boost/numeric/ublas/matrix.hpp>

#include <random>
#include <string>

#include "../../../include/get_binaryop.hpp"


template < typename Op, typename T >
void BM_binaryop(
	benchmark::State& state, Op op,
	std::pair< int, int > d1,
	std::pair< int, int > d2
){
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution< T > dis(
		std::numeric_limits< T >::min(),
		std::numeric_limits< T >::max()
	);

	boost::numeric::ublas::matrix< T > m1(d1.first, d1.second);

	for(size_t y = 0; y < m1.size2(); ++y){
		for(size_t x = 0; x < m1.size1(); ++x){
			m1(x, y) = dis(gen);
		}
	}

	boost::numeric::ublas::matrix< T > m2(d2.first, d2.second);

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


template < typename T = void >
struct prod{
	constexpr T operator()(T const& lhs, T const& rhs)const{
		return boost::numeric::ublas::prod(lhs, rhs);
	}
};

template <>
struct prod< void >{
	template < typename T, typename U>
	constexpr decltype(auto) operator()(T&& lhs, U&& rhs)const{
		return boost::numeric::ublas::prod(
			static_cast< T&& >(lhs),
			static_cast< U&& >(rhs)
		);
	}
};


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
			register_fn(prod<>(), [](auto d){
				return std::make_pair(d.second, d.first);
			});
		}break;
	}

	benchmark::Initialize(&argc, argv);
	benchmark::RunSpecifiedBenchmarks();
}
