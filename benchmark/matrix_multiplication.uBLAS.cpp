#include <benchmark/benchmark.h>

#include <boost/numeric/ublas/matrix.hpp>

#include <random>
#include <string>


template < typename T >
void BM_matrix_multiplication(
	benchmark::State& state, std::pair< int, int > dims
){
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution< T > dis(
		std::numeric_limits< T >::min(),
		std::numeric_limits< T >::max()
	);

	boost::numeric::ublas::matrix< T > m1(dims.first, dims.second);

	for(size_t y = 0; y < m1.size2(); ++y){
		for(size_t x = 0; x < m1.size1(); ++x){
			m1(x, y) = dis(gen);
		}
	}

	boost::numeric::ublas::matrix< T > m2(dims.second, dims.first);

	for(size_t y = 0; y < m2.size2(); ++y){
		for(size_t x = 0; x < m2.size1(); ++x){
			m2(x, y) = dis(gen);
		}
	}


	while(state.KeepRunning()){
		boost::numeric::ublas::matrix< T > res = prod(m1, m2);
	}
}

int main(int argc, char** argv){
	using f4 = float;

	for(auto& dim: std::vector< std::pair< int, int > >{
		{2, 2},
		{4, 2},
		{8, 2},
		{16, 2},
		{16, 4},
		{16, 8},
		{16, 16},
		{16, 32},
		{16, 64},
		{16, 128},
		{16, 256}
	}){
		benchmark::RegisterBenchmark(
			std::to_string(dim.first * dim.second).c_str(),
			BM_matrix_multiplication< f4 >,
			dim
		);
	}

	benchmark::Initialize(&argc, argv);
	benchmark::RunSpecifiedBenchmarks();
}
