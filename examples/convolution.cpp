//-----------------------------------------------------------------------------
// Copyright (c) 2016 Benjamin Buch
//
// https://github.com/bebuch/mitrax
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt)
//-----------------------------------------------------------------------------
#include <mitrax/png.hpp>
#include <mitrax/convert.hpp>
#include <mitrax/convolution/edge_operators.hpp>

#include <iostream>
#include <iomanip>
#include <sstream>
#include <chrono>
#include <ctime>
#include <cmath>


template < typename CharT, typename Traits >
inline std::basic_ostream< CharT, Traits >& time_to_string(
	std::basic_ostream< CharT, Traits >& os,
	std::chrono::system_clock::time_point const& time =
		std::chrono::system_clock::now()
){
	auto microseconds = std::chrono::duration_cast<
			std::chrono::microseconds
		>(time.time_since_epoch());
	auto localtime = std::chrono::system_clock::to_time_t(time);
	auto datetime = *std::localtime(&localtime);

	return os
		<< std::fixed << std::setfill('0')
		<< std::setw(4) << 1900 + datetime.tm_year << "-"
		<< std::setw(2) << 1 + datetime.tm_mon << "-"
		<< std::setw(2) << datetime.tm_mday << " "
		<< std::setw(2) << datetime.tm_hour << ":"
		<< std::setw(2) << datetime.tm_min << ":"
		<< std::setw(2) << datetime.tm_sec << " "
		<< std::setw(3) << microseconds.count() / 1000 % 1000 << '.'
		<< std::setw(3) << microseconds.count() % 1000;
}

template <
	typename CharT,
	typename Traits = std::char_traits< CharT >,
	typename Allocator = std::allocator< CharT >
>
inline std::basic_string< CharT, Traits, Allocator > time_to_string(
	std::chrono::system_clock::time_point const& time =
		std::chrono::system_clock::now()
){
	std::basic_ostringstream< CharT, Traits, Allocator > os;

	time_to_string(os, time);

	return os.str();
}

inline std::string time_to_string(
	std::chrono::system_clock::time_point const& time =
		std::chrono::system_clock::now()
){
	return time_to_string< char >(time);
}

class info{
public:
	static std::size_t unique_id(){
		static std::atomic< std::size_t > next_id(0);
		return next_id++;
	}

	info(): id_(unique_id()), start_(std::chrono::system_clock::now()) {}

	void pre(){
		auto end = std::chrono::system_clock::now();

		os_ << std::setfill('0') << std::setw(6) << id_ << ' ';

		time_to_string(os_, start_);

		os_ << " ( " << std::setfill(' ') << std::setprecision(3)
			<< std::setw(12)
			<< std::chrono::duration< double, std::milli >(
					end - start_
				).count() << "ms ) ";
	}

	~info(){
		std::cout << os_.str() << std::endl;
	}

	template < typename T >
	friend info& operator<<(info& log, T&& data){
		log.os_ << static_cast< T&& >(data);
		return log;
	}

private:
	std::size_t id_;
	std::ostringstream os_;
	std::chrono::system_clock::time_point const start_;
};


template < typename Log, typename Body >
inline decltype(auto) log(Log&& f, Body&& body){
	info log;

	return [](auto&& f, auto&& body, auto& log)->decltype(auto){
			try{
				decltype(auto) result = body();
				log.pre();
				f(log);
				return result;
			}catch(...){
				log.pre();
				f(log);
				log << " (failed with exception)";
				throw;
			}
		}(static_cast< Log&& >(f), static_cast< Body&& >(body), log);
}



int main()try{
	using namespace mitrax;
	using namespace mitrax::literals;

	auto m = make_matrix_v< std::uint16_t >(3264_Cd, 2448_Rd);
	mitrax::png::load(m, "image_01.png");

	auto normalize = [](auto const& m){
		auto minmax_iters = std::minmax_element(m.begin(), m.end());
		auto min = *minmax_iters.first;
		auto max = *minmax_iters.second;
		auto diff = max - min;

		return make_matrix_fn(m.dims(), [&m, min, diff](auto x, auto y){
			return static_cast< std::uint8_t >(
				(m(x, y) - min) * 255 / diff
			);
		});
	};

	{
		auto mx = log(
			[](info& os){ os << "roberts_cross_x"; },
			[&m]{ return roberts_cross_x< float >(m); }
		);
		auto my = log(
			[](info& os){ os << "roberts_cross_y"; },
			[&m]{ return roberts_cross_y< float >(m); }
		);
		auto mm = log(
			[](info& os){ os << "gradient_magnitude"; },
			[&mx, &my]{ return gradient_magnitude(mx, my); }
		);
		auto ma = log(
			[](info& os){ os << "gradient_magnitude_approximately"; },
			[&mx, &my]{ return gradient_magnitude_approximately(mx, my); }
		);
		auto md = log(
			[](info& os){ os << "gradient_direction"; },
			[&mx, &my]{ return gradient_direction(mx, my); }
		);

		mitrax::png::save(normalize(mx), "image_X0.png");
		mitrax::png::save(normalize(my), "image_Y0.png");
		mitrax::png::save(normalize(mm), "image_M0.png");
		mitrax::png::save(normalize(ma), "image_A0.png");
		mitrax::png::save(normalize(md), "image_D0.png");
	}

	{
		auto mx = log(
			[](info& os){ os << "prewitt_x"; },
			[&m]{ return prewitt_x< float >(m); }
		);
		auto my = log(
			[](info& os){ os << "prewitt_y"; },
			[&m]{ return prewitt_y< float >(m); }
		);
		auto mm = log(
			[](info& os){ os << "gradient_magnitude"; },
			[&mx, &my]{ return gradient_magnitude(mx, my); }
		);
		auto ma = log(
			[](info& os){ os << "gradient_magnitude_approximately"; },
			[&mx, &my]{ return gradient_magnitude_approximately(mx, my); }
		);
		auto md = log(
			[](info& os){ os << "gradient_direction"; },
			[&mx, &my]{ return gradient_direction(mx, my); }
		);

		mitrax::png::save(normalize(mx), "image_X1.png");
		mitrax::png::save(normalize(my), "image_Y1.png");
		mitrax::png::save(normalize(mm), "image_M1.png");
		mitrax::png::save(normalize(ma), "image_A1.png");
		mitrax::png::save(normalize(md), "image_D1.png");
	}

	{
		auto mx = log(
			[](info& os){ os << "sobel_x"; },
			[&m]{ return sobel_x< float >(m); }
		);
		auto my = log(
			[](info& os){ os << "sobel_y"; },
			[&m]{ return sobel_y< float >(m); }
		);
		auto mm = log(
			[](info& os){ os << "gradient_magnitude"; },
			[&mx, &my]{ return gradient_magnitude(mx, my); }
		);
		auto ma = log(
			[](info& os){ os << "gradient_magnitude_approximately"; },
			[&mx, &my]{ return gradient_magnitude_approximately(mx, my); }
		);
		auto md = log(
			[](info& os){ os << "gradient_direction"; },
			[&mx, &my]{ return gradient_direction(mx, my); }
		);

		mitrax::png::save(normalize(mx), "image_X2.png");
		mitrax::png::save(normalize(my), "image_Y2.png");
		mitrax::png::save(normalize(mm), "image_M2.png");
		mitrax::png::save(normalize(ma), "image_A2.png");
		mitrax::png::save(normalize(md), "image_D2.png");
	}

	{
		auto mx = log(
			[](info& os){ os << "scharr_x"; },
			[&m]{ return scharr_x< float >(m); }
		);
		auto my = log(
			[](info& os){ os << "scharr_y"; },
			[&m]{ return scharr_y< float >(m); }
		);
		auto mm = log(
			[](info& os){ os << "gradient_magnitude"; },
			[&mx, &my]{ return gradient_magnitude(mx, my); }
		);
		auto ma = log(
			[](info& os){ os << "gradient_magnitude_approximately"; },
			[&mx, &my]{ return gradient_magnitude_approximately(mx, my); }
		);
		auto md = log(
			[](info& os){ os << "gradient_direction"; },
			[&mx, &my]{ return gradient_direction(mx, my); }
		);

		mitrax::png::save(normalize(mx), "image_X3.png");
		mitrax::png::save(normalize(my), "image_Y3.png");
		mitrax::png::save(normalize(mm), "image_M3.png");
		mitrax::png::save(normalize(ma), "image_A3.png");
		mitrax::png::save(normalize(md), "image_D3.png");
	}
}catch(std::exception const& e){
	std::cerr << "Terminate with exception: " << e.what() << "\n";
}catch(...){
	std::cerr << "Terminate with unknown exception.\n";
}
