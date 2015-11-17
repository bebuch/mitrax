//-----------------------------------------------------------------------------
// Copyright (c) 2015 Benjamin Buch
//
// https://github.com/bebuch/mitrax
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt)
//-----------------------------------------------------------------------------
#ifndef _mitrax__convert__hpp_INCLUDED_
#define _mitrax__convert__hpp_INCLUDED_

#include "dim.hpp"

#include <boost/container/vector.hpp>

#include <array>
#include <utility>


namespace mitrax{


	namespace detail{


		template < typename T, typename U, size_t N, size_t ... I >
		constexpr auto
		convert(std::array< U, N >&& v, std::index_sequence< I ... >){
			return std::array< T, N >{{
				static_cast< T >(std::move(v[I])) ...
			}};
		}

		template < typename T, typename U, size_t N, size_t ... I >
		constexpr auto
		convert(std::array< U, N >& v, std::index_sequence< I ... >){
			return std::array< T, N >{{
				static_cast< T >(v[I]) ...
			}};
		}

		template < typename T, typename U, size_t N, size_t ... I >
		constexpr auto
		convert(std::array< U, N > const& v, std::index_sequence< I ... >){
			return std::array< T, N >{{
				static_cast< T >(v[I]) ...
			}};
		}


		template < typename T, size_t N >
		constexpr auto convert(std::true_type, std::array< T, N >&& v){
			return std::move(v);
		}

		template < typename T, size_t N >
		constexpr auto convert(std::true_type, std::array< T, N >& v){
			return v;
		}

		template < typename T, size_t N >
		constexpr auto convert(std::true_type, std::array< T, N > const& v){
			return v;
		}


		template < typename T, typename U, size_t N >
		constexpr auto convert(std::false_type, std::array< U, N >&& v){
			return convert< T >(
				std::move(v), std::make_index_sequence< N >()
			);
		}

		template < typename T, typename U, size_t N >
		constexpr auto convert(std::false_type, std::array< U, N >& v){
			return convert< T >(
				v, std::make_index_sequence< N >()
			);
		}

		template < typename T, typename U, size_t N >
		constexpr auto convert(std::false_type, std::array< U, N > const& v){
			return convert< T >(
				v, std::make_index_sequence< N >()
			);
		}


		template < typename T >
		auto convert(std::true_type, boost::container::vector< T >&& v){
			return std::move(v);
		}

		template < typename T >
		auto convert(std::true_type, boost::container::vector< T >& v){
			return v;
		}

		template < typename T >
		auto convert(std::true_type, boost::container::vector< T > const& v){
			return v;
		}


		template < typename T, typename U >
		auto convert(std::false_type, boost::container::vector< U >&& v){
			return boost::container::vector< T >(
				std::make_move_iterator(v.begin()),
				std::make_move_iterator(v.end())
			);
		}

		template < typename T, typename U >
		auto convert(std::false_type, boost::container::vector< U >& v){
			return boost::container::vector< T >(v.begin(), v.end());
		}

		template < typename T, typename U >
		auto convert(std::false_type, boost::container::vector< U > const& v){
			return boost::container::vector< T >(v.begin(), v.end());
		}


		template < size_t N, typename T, size_t ... I >
		auto to_array(
			boost::container::vector< T >&& v,
			std::index_sequence< I ... >
		){
			return std::array< T, N >{{ std::move(v[I]) ... }};
		}

		template < size_t N, typename T, size_t ... I >
		auto to_array(
			boost::container::vector< T >& v,
			std::index_sequence< I ... >
		){
			return std::array< T, N >{{ v[I] ... }};
		}

		template < size_t N, typename T, size_t ... I >
		auto to_array(
			boost::container::vector< T > const& v,
			std::index_sequence< I ... >
		){
			return std::array< T, N >{{ v[I] ... }};
		}


	}


	template < typename T, typename U, size_t N >
	constexpr auto convert(std::array< U, N >&& v){
		return detail::convert< T >(std::is_same< T, U >(), std::move(v));
	}

	template < typename T, typename U, size_t N >
	constexpr auto convert(std::array< U, N >& v){
		return detail::convert< T >(std::is_same< T, U >(), v);
	}

	template < typename T, typename U, size_t N >
	constexpr auto convert(std::array< U, N > const& v){
		return detail::convert< T >(std::is_same< T, U >(), v);
	}


	template < typename T, typename U >
	auto convert(boost::container::vector< U >&& v){
		return detail::convert< T >(std::is_same< T, U >(), std::move(v));
	}

	template < typename T, typename U >
	auto convert(boost::container::vector< U >& v){
		return detail::convert< T >(std::is_same< T, U >(), v);
	}

	template < typename T, typename U >
	auto convert(boost::container::vector< U > const& v){
		return detail::convert< T >(std::is_same< T, U >(), v);
	}


	template < typename T, typename U, size_t N >
	constexpr auto convert(
		std::true_type /*to_static*/,
		std::array< U, N >&& v
	){
		return convert< T >(std::move(v));
	}

	template < typename T, typename U, size_t N >
	constexpr auto convert(
		std::true_type /*to_static*/,
		std::array< U, N >& v
	){
		return convert< T >(v);
	}

	template < typename T, typename U, size_t N >
	constexpr auto convert(
		std::true_type /*to_static*/,
		std::array< U, N > const& v
	){
		return convert< T >(v);
	}


	template < typename T, typename U, size_t N >
	auto convert(
		std::true_type /*to_static*/,
		boost::container::vector< U >&& v
	){
		// TODO: Do it faster!!!
		auto d = convert< T >(std::move(v));
		return detail::to_array< N >(
			std::move(d),
			std::make_index_sequence< N >()
		);
	}

	template < typename T, typename U, size_t N >
	auto convert(
		std::true_type /*to_static*/,
		boost::container::vector< U >& v
	){
		// TODO: Do it faster!!!
		auto d = convert< T >(v);
		return detail::to_array< N >(
			std::move(d),
			std::make_index_sequence< N >()
		);
	}

	template < typename T, typename U, size_t N >
	auto convert(
		std::true_type /*to_static*/,
		boost::container::vector< U > const& v
	){
		// TODO: Do it faster!!!
		auto d = convert< T >(v);
		return detail::to_array< N >(
			std::move(d),
			std::make_index_sequence< N >()
		);
	}


	template < typename T, typename U, size_t N >
	constexpr auto convert(
		std::false_type /*to_static*/,
		std::array< U, N >&& v
	){
		// TODO: Do it faster!!!
		auto d = convert< T >(std::move(v));
		return boost::container::vector< T >(
			std::make_move_iterator(d.begin()),
			std::make_move_iterator(d.end())
		);
	}

	template < typename T, typename U, size_t N >
	constexpr auto convert(
		std::false_type /*to_static*/,
		std::array< U, N >& v
	){
		// TODO: Do it faster!!!
		auto d = convert< T >(v);
		return boost::container::vector< T >(
			std::make_move_iterator(d.begin()),
			std::make_move_iterator(d.end())
		);
	}

	template < typename T, typename U, size_t N >
	constexpr auto convert(
		std::false_type /*to_static*/,
		std::array< U, N > const& v
	){
		// TODO: Do it faster!!!
		auto d = convert< T >(v);
		return boost::container::vector< T >(
			std::make_move_iterator(d.begin()),
			std::make_move_iterator(d.end())
		);
	}


	template < typename T, typename U, size_t N >
	auto convert(
		std::false_type /*to_static*/,
		boost::container::vector< U >&& v
	){
		return convert< T >(std::move(v));
	}

	template < typename T, typename U, size_t N >
	auto convert(
		std::false_type /*to_static*/,
		boost::container::vector< U >& v
	){
		return convert< T >(v);
	}

	template < typename T, typename U, size_t N >
	auto convert(
		std::false_type /*to_static*/,
		boost::container::vector< U > const& v
	){
		return convert< T >(v);
	}


}


#endif
