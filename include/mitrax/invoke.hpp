//-----------------------------------------------------------------------------
// Copyright (c) 2016 Benjamin Buch
//
// https://github.com/bebuch/mitrax
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt)
//-----------------------------------------------------------------------------
#ifndef _mitrax__invoke__hpp_INCLUDED_
#define _mitrax__invoke__hpp_INCLUDED_

#include "utility.hpp"

#include <type_traits>
#include <functional>


namespace mitrax{


	template < typename T >
	class reference_wrapper;

	template < typename T >
	struct is_reference_wrapper: std::false_type{};

	template < typename T >
	struct is_reference_wrapper< reference_wrapper< T > >:
		std::true_type{};

	template < typename T >
	struct is_reference_wrapper< std::reference_wrapper< T > >:
		std::true_type{};

	template < typename T >
	constexpr bool is_reference_wrapper_v = is_reference_wrapper< T >::value;


}


namespace mitrax::detail{


	template < typename Base, typename T, typename Derived, typename ... Args,
		enable_if_t< std::is_function_v< T > &&
			std::is_base_of_v< Base, std::decay_t< Derived > > > = 0 >
	constexpr decltype(auto)
	invoke_impl(T Base::*pmf, Derived&& ref, Args&& ... args)
	noexcept(noexcept(
		(static_cast< Derived&& >(ref).*pmf)
			(static_cast< Args&& >(args) ...)
	)){
		return (static_cast< Derived&& >(ref).*pmf)
			(static_cast< Args&& >(args) ...);
	}

	template < typename Base, typename T, typename RefWrap, typename ... Args,
		enable_if_t< std::is_function_v< T > &&
			is_reference_wrapper_v< std::decay_t< RefWrap > > > = 0 >
	constexpr decltype(auto)
	invoke_impl(T Base::*pmf, RefWrap&& ref, Args&& ... args)
	noexcept(noexcept((ref.get().*pmf)(static_cast< Args&& >(args) ...))){
		return (ref.get().*pmf)(static_cast< Args&& >(args) ...);
	}

	template < typename Base, typename T, typename Pointer, typename ... Args,
		enable_if_t< std::is_function_v< T > &&
			!is_reference_wrapper_v< std::decay_t< Pointer > > &&
			!std::is_base_of_v< Base, std::decay_t< Pointer > > > = 0 >
	constexpr decltype(auto)
	invoke_impl(T Base::*pmf, Pointer&& ptr, Args&& ... args)
	noexcept(noexcept(
		((*static_cast< Pointer&& >(ptr)).*pmf)
			(static_cast< Args&& >(args) ...)
	)){
		return ((*static_cast< Pointer&& >(ptr)).*pmf)
			(static_cast< Args&& >(args) ...);
	}

	template < typename Base, typename T, typename Derived,
		enable_if_t< !std::is_function_v< T > &&
			std::is_base_of_v< Base, std::decay_t< Derived > > > = 0 >
	constexpr decltype(auto) invoke_impl(T Base::*pmd, Derived&& ref)
	noexcept(noexcept(static_cast< Derived&& >(ref).*pmd)){
		return static_cast< Derived&& >(ref).*pmd;
	}

	template < typename Base, typename T, typename RefWrap,
		enable_if_t< !std::is_function_v< T > &&
			is_reference_wrapper_v< std::decay_t< RefWrap > > > = 0 >
	constexpr decltype(auto) invoke_impl(T Base::*pmd, RefWrap&& ref)
	noexcept(noexcept(ref.get().*pmd)){
		return ref.get().*pmd;
	}

	template < typename Base, typename T, typename Pointer,
		enable_if_t< !std::is_function_v< T > &&
			!is_reference_wrapper_v< std::decay_t< Pointer > > &&
			!std::is_base_of_v< Base, std::decay_t< Pointer > > > = 0 >
	constexpr decltype(auto) invoke_impl(T Base::*pmd, Pointer&& ptr)
	noexcept(noexcept((*static_cast< Pointer&& >(ptr)).*pmd)){
		return (*static_cast< Pointer&& >(ptr)).*pmd;
	}

	template < typename F, typename ... Args,
		enable_if_t< !std::is_member_pointer_v< std::decay_t< F > > > = 0 >
	constexpr decltype(auto) invoke_impl(F&& f, Args&& ... args)
	noexcept(noexcept(static_cast< F&& >(f)(static_cast< Args&& >(args) ...))){
		return static_cast< F&& >(f)(static_cast< Args&& >(args) ...);
	}


}


namespace mitrax{


	template < typename F, typename ... ArgTypes >
	constexpr decltype(auto) invoke(F&& f, ArgTypes&& ... args)
	noexcept(noexcept(detail::invoke_impl
		(static_cast< F&& >(f), static_cast< ArgTypes&& >(args) ...)
	)){
		return detail::invoke_impl
			(static_cast< F&& >(f), static_cast< ArgTypes&& >(args) ...);
	}


}


#include "reference_wrapper.hpp"


#endif
