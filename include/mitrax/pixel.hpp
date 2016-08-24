//-----------------------------------------------------------------------------
// Copyright (c) 2016 Benjamin Buch
//
// https://github.com/bebuch/mitrax
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt)
//-----------------------------------------------------------------------------
#ifndef _mitrax__pixel__hpp_INCLUDED_
#define _mitrax__pixel__hpp_INCLUDED_

#include <cstdint>


namespace mitrax{ namespace pixel{


	template < typename T >
	struct basic_ga{ T g; T a; };

	using ga8  = basic_ga< std::int8_t >;
	using ga16 = basic_ga< std::int16_t >;
	using ga32 = basic_ga< std::int32_t >;
	using ga64 = basic_ga< std::int64_t >;
	using ga8u  = basic_ga< std::uint8_t >;
	using ga16u = basic_ga< std::uint16_t >;
	using ga32u = basic_ga< std::uint32_t >;
	using ga64u = basic_ga< std::uint64_t >;
	using ga32f = basic_ga< float >;
	using ga64f = basic_ga< double >;


	template < typename T >
	struct basic_rgb{ T r; T g; T b; };

	using rgb8  = basic_rgb< std::int8_t >;
	using rgb16 = basic_rgb< std::int16_t >;
	using rgb32 = basic_rgb< std::int32_t >;
	using rgb64 = basic_rgb< std::int64_t >;
	using rgb8u  = basic_rgb< std::uint8_t >;
	using rgb16u = basic_rgb< std::uint16_t >;
	using rgb32u = basic_rgb< std::uint32_t >;
	using rgb64u = basic_rgb< std::uint64_t >;
	using rgb32f = basic_rgb< float >;
	using rgb64f = basic_rgb< double >;


	template < typename T >
	struct basic_rgba{ T r; T g; T b; T a; };

	using rgba8  = basic_rgba< std::int8_t >;
	using rgba16 = basic_rgba< std::int16_t >;
	using rgba32 = basic_rgba< std::int32_t >;
	using rgba64 = basic_rgba< std::int64_t >;
	using rgba8u  = basic_rgba< std::uint8_t >;
	using rgba16u = basic_rgba< std::uint16_t >;
	using rgba32u = basic_rgba< std::uint32_t >;
	using rgba64u = basic_rgba< std::uint64_t >;
	using rgba32f = basic_rgba< float >;
	using rgba64f = basic_rgba< double >;


} }


#endif
