namespace init{

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
		}
	);

	benchmark::Initialize(&argc, argv);
	benchmark::RunSpecifiedBenchmarks();
}
