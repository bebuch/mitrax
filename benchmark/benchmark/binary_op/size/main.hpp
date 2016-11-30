namespace init{

	using type = float;

}


int main(int argc, char** argv){
	auto register_fn = [](auto op, auto transfrom_dim){
		boost::hana::for_each(init::dimensions, [op, transfrom_dim](auto d1){
				auto d2 = transfrom_dim(d1);
				benchmark::RegisterBenchmark(
					std::to_string(d1.point_count()).c_str(),
					[op, d1, d2](benchmark::State& state){
						bm< init::type >(state, op, d1, d2);
					}
				);
			}
		);
	};

	switch(mitrax::get_binaryop(argc, argv)){
		case mitrax::op::unknown: return 1;
		case mitrax::op::plus:{
			register_fn(init::plus(), [](auto d){ return d; });
		}break;
		case mitrax::op::mul:{
			register_fn(init::multiplies(), [](auto d){
				return dim_pair(d.rows().as_col(), d.cols().as_row());
			});
		}break;
	}

	benchmark::Initialize(&argc, argv);
	benchmark::RunSpecifiedBenchmarks();
}
