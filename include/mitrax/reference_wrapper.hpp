//-----------------------------------------------------------------------------
// Copyright (c) 2016-2018 Benjamin Buch
//
// https://github.com/bebuch/mitrax
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt)
//-----------------------------------------------------------------------------
#ifndef _mitrax__reference_wrapper__hpp_INCLUDED_
#define _mitrax__reference_wrapper__hpp_INCLUDED_

#include "invoke.hpp"

#include <memory>


namespace mitrax{


	template < typename T >
	class reference_wrapper{
	public:
		using type = T;


		constexpr reference_wrapper(T& ref)noexcept:
			v_(std::addressof(ref)) {}

		reference_wrapper(T&&) = delete;

		constexpr reference_wrapper(reference_wrapper const&)noexcept
			= default;


		constexpr operator T&()const noexcept{
			return *v_;
		}

		constexpr T& get()const noexcept{
			return *v_;
		}


		template < typename ... Args >
		constexpr std::result_of_t< T&(Args&& ...) >
		operator()(Args&& ... args)const
		noexcept(noexcept(
			mitrax::invoke(get(), static_cast< Args&& >(args) ...)
		)){
			return mitrax::invoke(get(), static_cast< Args&& >(args) ...);
		}


	private:
		T* v_;
	};


	template < typename T >
	class move_reference_wrapper{
	public:
		using type = T;


		move_reference_wrapper(T&) = delete;

		move_reference_wrapper(T const&) = delete;

		move_reference_wrapper(T const&&) = delete;

		constexpr move_reference_wrapper(T&& ref)noexcept:
			v_(std::addressof(ref)) {}

		constexpr move_reference_wrapper(move_reference_wrapper const&)noexcept
			= default;


		constexpr operator T&&()const noexcept{
			return std::move(*v_);
		}

		constexpr T&& get()const noexcept{
			return std::move(*v_);
		}


		template < typename ... Args >
		constexpr std::result_of_t< T&&(Args&& ...) >
		operator()(Args&& ... args)const
		noexcept(noexcept(
			mitrax::invoke(get(), static_cast< Args&& >(args) ...)
		)){
			return mitrax::invoke(get(), static_cast< Args&& >(args) ...);
		}


	private:
		T* v_;
	};


	template < typename T >
	constexpr auto ref(T& v)noexcept{
		return reference_wrapper< T >(v);
	}

	template < typename T >
	constexpr auto ref(reference_wrapper< T > v)noexcept{
		return reference_wrapper< T >(v);
	}

	template < typename T >
	constexpr auto ref(move_reference_wrapper< T > v)noexcept{
		return reference_wrapper< T >(static_cast< T& >(v.get()));
	}

	template < typename T >
	void ref(T const&&) = delete;


	template < typename T >
	constexpr auto cref(T const& v)noexcept{
		return reference_wrapper< T const >(v);
	}

	template < typename T >
	constexpr auto cref(reference_wrapper< T > v)noexcept{
		return reference_wrapper< T const >(v);
	}

	template < typename T >
	constexpr auto cref(move_reference_wrapper< T > v)noexcept{
		return reference_wrapper< T const >(static_cast< T& >(v.get()));
	}

	template < typename T >
	void cref(T const&&) = delete;


	template < typename T >
	constexpr auto move_ref(T&& v)noexcept{
		return move_reference_wrapper< T >(std::move(v));
	}

	template < typename T >
	constexpr auto move_ref(move_reference_wrapper< T > v)noexcept{
		return v;
	}

	template < typename T >
	void move_ref(T const&&) = delete;


	template < typename M >
	constexpr auto forward_ref(M& m)noexcept{
		return ref(m);
	}

	template < typename M >
	constexpr auto forward_ref(M const&& m)noexcept{
		return ref(m);
	}

	template < typename M >
	constexpr auto forward_ref(M&& m)noexcept{
		return move_ref(std::move(m));
	}


}


#endif
