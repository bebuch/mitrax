namespace init{

	using type = float;

	constexpr auto value = type(0);

}

int main(int argc, char** argv){
	boost::hana::for_each(init::dimensions, [](auto d){
			benchmark::RegisterBenchmark(
				std::to_string(d.point_count()).c_str(),
				[d](benchmark::State& state){
					bm< init::type >(state, init::value, d);
				}
			);
		}
	);

	benchmark::Initialize(&argc, argv);
	benchmark::RunSpecifiedBenchmarks();
}
