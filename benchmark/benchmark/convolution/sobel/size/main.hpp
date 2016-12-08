#include <boost/hana/tuple.hpp>
#include <boost/hana/for_each.hpp>


namespace init{

	constexpr auto dimensions = boost::hana::make_tuple(
			dim_pair(1024_c, 1024_r)
		);

	using type = float;

}


int main(int argc, char** argv){
	boost::hana::for_each(init::dimensions, [](auto d){
			benchmark::RegisterBenchmark(
				std::to_string(d.point_count()).c_str(),
				[d](benchmark::State& state){
					bm< init::type >(state, d);
				}
			);
		});

	benchmark::Initialize(&argc, argv);
	benchmark::RunSpecifiedBenchmarks();
}
