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
#include "pixel.hpp"

#include <string>
#include <type_traits>

#include <png++/png.hpp>


namespace mitrax{ namespace png{


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

		template <> struct png_type< pixel::ga8 >
			{ using type = ::png::ga_pixel; };
		template <> struct png_type< pixel::ga8u >
			{ using type = ::png::ga_pixel; };
		template <> struct png_type< pixel::ga16 >
			{ using type = ::png::ga_pixel_16; };
		template <> struct png_type< pixel::ga16u >
			{ using type = ::png::ga_pixel_16; };

		template <> struct png_type< pixel::rgb8 >
			{ using type = ::png::rgb_pixel; };
		template <> struct png_type< pixel::rgb8u >
			{ using type = ::png::rgb_pixel; };
		template <> struct png_type< pixel::rgb16 >
			{ using type = ::png::rgb_pixel_16; };
		template <> struct png_type< pixel::rgb16u >
			{ using type = ::png::rgb_pixel_16; };

		template <> struct png_type< pixel::rgba8 >
			{ using type = ::png::rgba_pixel; };
		template <> struct png_type< pixel::rgba8u >
			{ using type = ::png::rgba_pixel; };
		template <> struct png_type< pixel::rgba16 >
			{ using type = ::png::rgba_pixel_16; };
		template <> struct png_type< pixel::rgba16u >
			{ using type = ::png::rgba_pixel_16; };

		template < typename T >
		using png_type_t = typename png_type< T >::type;


		template < typename T, typename PNG_Pixel >
		T const& pngxx2mitrax(PNG_Pixel const& v){
			static_assert(
				sizeof(T) == sizeof(PNG_Pixel),
				"Matrix pixel type T is not compatible with type PNG_Pixel"
			);
			static_assert(
				std::is_pod_v< T >, "Matrix pixel type T must be a POD-type"
			);
			static_assert(
				std::is_trivially_copyable_v< PNG_Pixel >,
				"Type PNG_Pixel must be trivially copyable"
			);

			return *reinterpret_cast< T const* >(&v);
		}

		template < typename PNG_Pixel, typename T >
		PNG_Pixel const& mitrax2pngxx(T const& v){
			static_assert(
				sizeof(T) == sizeof(PNG_Pixel),
				"Matrix pixel type T is not compatible with type PNG_Pixel"
			);
			static_assert(
				std::is_pod_v< T >, "Matrix pixel type T must be a POD-type"
			);
			static_assert(
				std::is_trivially_copyable_v< PNG_Pixel >,
				"Type PNG_Pixel must be trivially copyable"
			);

			return *reinterpret_cast< PNG_Pixel const* >(&v);
		}


	}


	template < typename M, col_t Cols, row_t Rows >
	void load(matrix< M, Cols, Rows >& m, std::string const& filename){
		using value_type = value_type_t< M >;

		::png::image< detail::png_type_t< value_type > > output;
		output.read(filename);

		if(
			size_t(m.cols()) != output.get_width() ||
			size_t(m.rows()) != output.get_height()
		){
			throw std::runtime_error("Can't load PNG-File, dims are wrong.");
		}

		for(std::size_t y = 0; y < output.get_height(); ++y){
			for(std::size_t x = 0; x < output.get_width(); ++x){
				m(c_t(x), r_t(y)) =
					detail::pngxx2mitrax< value_type >(output[y][x]);
			}
		}
	}


	template < typename M, col_t Cols, row_t Rows >
	void save(matrix< M, Cols, Rows > const& m, std::string const& filename){
		using value_type = value_type_t< M >;
		using image_type = ::png::image< detail::png_type_t< value_type > >;
		using ivalue_type = typename image_type::traits::pixel_type;

		image_type output(size_t(m.cols()), size_t(m.rows()));

		for(std::size_t y = 0; y < output.get_height(); ++y){
			for(std::size_t x = 0; x < output.get_width(); ++x){
				output[y][x] =
					detail::mitrax2pngxx< ivalue_type >(m(c_t(x), r_t(y)));
			}
		}

		output.write(filename);
	}


} }


#endif
