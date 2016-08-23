//-----------------------------------------------------------------------------
// Copyright (c) 2016 Benjamin Buch
//
// https://github.com/bebuch/mitrax
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt)
//-----------------------------------------------------------------------------
#ifndef _mitrax__png__hpp_INCLUDED_
#define _mitrax__png__hpp_INCLUDED_

#include "matrix_interface.hpp"

#include <string>

#include <png++/png.hpp>


namespace mitrax{ namespace png{


	template < typename T, typename PNG_type >
	struct basic_ga{
		T g, a;

		basic_ga(): g(0), a(0) {}

		basic_ga(T g, T a):
			g(g), a(a) {}

		basic_ga(::png::basic_ga_pixel< PNG_type > const& v):
			g(v.value), a(v.alpha) {}

		operator ::png::basic_ga_pixel< PNG_type >()const{
			return {g, a};
		}
	};

	using ga8 = basic_ga< std::uint8_t, unsigned char >;
	using ga16 = basic_ga< std::uint16_t, unsigned short >;


	template < typename T, typename PNG_type >
	struct basic_rgb{
		T r, g, b;

		basic_rgb(): r(0), g(0), b(0) {}

		basic_rgb(T r, T g, T b):
			r(r), g(g), b(b) {}

		basic_rgb(::png::basic_rgb_pixel< PNG_type > const& v):
			r(v.red), g(v.green), b(v.blue) {}

		operator ::png::basic_rgb_pixel< PNG_type >()const{
			return {r, g, b};
		}
	};

	using rgb8 = basic_rgb< std::uint8_t, unsigned char >;
	using rgb16 = basic_rgb< std::uint16_t, unsigned short >;


	template < typename T, typename PNG_type >
	struct basic_rgba{
		T r, g, b, a;

		basic_rgba(): r(0), g(0), b(0), a(0) {}

		basic_rgba(T r, T g, T b, T a):
			r(r), g(g), b(b), a(a) {}

		basic_rgba(::png::basic_rgba_pixel< PNG_type > const& v):
			r(v.red), g(v.green), b(v.blue), a(v.alpha) {}

		operator ::png::basic_rgba_pixel< PNG_type >()const{
			return {r, g, b, a};
		}
	};

	using rgba8 = basic_rgba< std::uint8_t, unsigned char >;
	using rgba16 = basic_rgba< std::uint16_t, unsigned short >;


	namespace detail{


		template < typename T >
		struct png_type;

		template <> struct png_type< char >
			{ using type = ::png::gray_pixel; };
		template <> struct png_type< signed char >
			{ using type = ::png::gray_pixel; };
		template <> struct png_type< unsigned char >
			{ using type = ::png::gray_pixel; };
		template <> struct png_type< std::int16_t >
			{ using type = ::png::gray_pixel_16; };
		template <> struct png_type< std::uint16_t >
			{ using type = ::png::gray_pixel_16; };
		template <> struct png_type< png::ga8 >
			{ using type = ::png::ga_pixel; };
		template <> struct png_type< png::ga16 >
			{ using type = ::png::ga_pixel_16; };
		template <> struct png_type< png::rgb8 >
			{ using type = ::png::rgb_pixel; };
		template <> struct png_type< png::rgb16 >
			{ using type = ::png::rgb_pixel_16; };
		template <> struct png_type< png::rgba8 >
			{ using type = ::png::rgba_pixel; };
		template <> struct png_type< png::rgba16 >
			{ using type = ::png::rgba_pixel_16; };

		template < typename T >
		using png_type_t = typename png_type< T >::type;


	}


	template < typename M, size_t Cols, size_t Rows >
	void load(matrix< M, Cols, Rows >& m, std::string const& filename){
		using value_type = value_type_t< M >;

		::png::image< detail::png_type_t< value_type > > output;
		output.read(filename);

		if(m.cols() != output.get_width() || m.rows() != output.get_height()){
			throw std::runtime_error("Can't load PNG-File, dims are wrong.");
		}

		for(std::size_t y = 0; y < output.get_height(); ++y){
			for(std::size_t x = 0; x < output.get_width(); ++x){
				m(x, y) = static_cast< value_type >(output[y][x]);
			}
		}
	}


	template < typename M, size_t Cols, size_t Rows >
	void save(matrix< M, Cols, Rows > const& m, std::string const& filename){
		using value_type = value_type_t< M >;
		using image_type = ::png::image< detail::png_type_t< value_type > >;
		using ivalue_type = typename image_type::traits::pixel_type;

		image_type output(m.cols(), m.rows());

		for(std::size_t y = 0; y < output.get_height(); ++y){
			for(std::size_t x = 0; x < output.get_width(); ++x){
				output[y][x] = static_cast< ivalue_type >(m(x, y));
			}
		}

		output.write(filename);
	}


} }


#endif
