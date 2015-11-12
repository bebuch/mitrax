//-----------------------------------------------------------------------------
// Copyright (c) 2015 Benjamin Buch
//
// https://github.com/bebuch/mitrax
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt)
//-----------------------------------------------------------------------------
#ifndef _mitrax__interger__hpp_INCLUDED_
#define _mitrax__interger__hpp_INCLUDED_

#include <cstddef>
#include <type_traits>


namespace mitrax{


	using size_t = std::size_t;

	using ptrdiff_t = std::ptrdiff_t;


	template < size_t V >
	struct size_ct{
		static constexpr size_t value = V;

		using value_type = size_t;

		using type = size_ct;

		constexpr operator size_t()const noexcept{
			return value;
		}

		constexpr size_t operator()()const noexcept{
			return value;
		}
	};


	struct size_rt: size_ct< 0 >{
	public:
		constexpr size_rt(size_t v): v_(v) {}


		constexpr operator size_t()const noexcept{
			return v_;
		}

		constexpr size_t operator()()const noexcept{
			return v_;
		}

	public:
		size_t v_;
	};


	template < bool CompileTime, size_t I >
	struct col_init;

	template < bool CompileTime, size_t I >
	struct row_init;

	template < bool CompileTime, size_t I >
	struct dim_init;


	template < size_t I >
	struct col_t: size_ct< I >{
		using size_ct< I >::size_ct;

		constexpr auto lit()const noexcept{
			return col_init< true, I >();
		}
	};

	template <>
	struct col_t< 0 >: size_rt{
		using size_rt::size_rt;
	};

	template < size_t I >
	struct row_t: size_ct< I >{
		using size_ct< I >::size_ct;

		constexpr auto lit()const noexcept{
			return row_init< true, I >();
		}
	};

	template <>
	struct row_t< 0 >: size_rt{
		using size_rt::size_rt;
	};

	template < size_t I >
	struct dim_t: size_ct< I >{
		using size_ct< I >::size_ct;

		constexpr auto lit()const noexcept{
			return dim_init< true, I >();
		}

		constexpr auto col()const noexcept{
			return col_t< I >();
		}

		constexpr auto row()const noexcept{
			return row_t< I >();
		}
	};

	template <>
	struct dim_t< 0 >: size_rt{
		using size_rt::size_rt;

		constexpr auto col()const noexcept{
			return col_t< 0 >(static_cast< size_t >(*this));
		}

		constexpr auto row()const noexcept{
			return row_t< 0 >(static_cast< size_t >(*this));
		}
	};


	template < bool CompileTime, size_t I >
	struct col_init: size_ct< I >{
		constexpr auto get()const noexcept{
			return col_t< I >();
		}
	};

	template < size_t I >
	struct col_init< false, I >: size_ct< I >{
		constexpr auto get()const noexcept{
			return col_t< 0 >(I);
		}
	};

	template < bool CompileTime, size_t I >
	struct row_init: size_ct< I >{
		constexpr auto get()const noexcept{
			return row_t< I >();
		}
	};

	template < size_t I >
	struct row_init< false, I >: size_ct< I >{
		constexpr auto get()const noexcept{
			return row_t< 0 >(I);
		}
	};

	template < bool CompileTime, size_t I >
	struct dim_init: size_ct< I >{
		constexpr auto get()const noexcept{
			return dim_t< I >();
		}

		constexpr auto col()const noexcept{
			return col_init< true, I >();
		}

		constexpr auto row()const noexcept{
			return row_init< true, I >();
		}
	};

	template < size_t I >
	struct dim_init< false, I >: size_ct< I >{
		constexpr auto get()const noexcept{
			return dim_t< 0 >(I);
		}

		constexpr auto col()const noexcept{
			return col_init< false, I >();
		}

		constexpr auto row()const noexcept{
			return row_init< false, I >();
		}
	};


	namespace detail{


		// Adopted from Boost Hana
		template < size_t N >
		constexpr size_t parse_int(char const(&arr)[N]){
			size_t number = 0;
			size_t base = 1;
			for(size_t i = 0; i < N; ++i){
				number += (static_cast< int >(arr[N - 1 - i]) - 48) * base;
				base *= 10;
			}
			return number;
		}


	}


	namespace literals{


		// Adopted from Boost Hana
		template < char ... C >
		constexpr auto operator"" _C(){
			static_assert(
				detail::parse_int< sizeof...(C) >({C ...}),
				"Compile time cols can not be 0, use '_C_rt' prefix instead"
			);
			return col_init<
				true,
				detail::parse_int< sizeof...(C) >({C ...})
			>();
		}

		// Adopted from Boost Hana
		template < char ... C >
		constexpr auto operator"" _C_rt(){
			return col_init<
				false,
				detail::parse_int< sizeof...(C) >({C ...})
			>();
		}

		// Adopted from Boost Hana
		template < char ... C >
		constexpr auto operator"" _R(){
			static_assert(
				detail::parse_int< sizeof...(C) >({C ...}),
				"Compile time rows can not be 0, use '_R_rt' prefix instead"
			);
			return row_init<
				true,
				detail::parse_int< sizeof...(C) >({C ...})
			>();
		}

		// Adopted from Boost Hana
		template < char ... C >
		constexpr auto operator"" _R_rt(){
			return row_init<
				false,
				detail::parse_int< sizeof...(C) >({C ...})
			>();
		}

		// Adopted from Boost Hana
		template < char ... C >
		constexpr auto operator"" _D(){
			static_assert(
				detail::parse_int< sizeof...(C) >({C ...}),
				"Compile time dims can not be 0, use '_D_rt' prefix instead"
			);
			return dim_init<
				true,
				detail::parse_int< sizeof...(C) >({C ...})
			>();
		}

		// Adopted from Boost Hana
		template < char ... C >
		constexpr auto operator"" _D_rt(){
			return dim_init<
				false,
				detail::parse_int< sizeof...(C) >({C ...})
			>();
		}


	}


	template < typename T >
	using value_type_t = typename T::value_type;

	template < bool I >
	using bool_t = std::integral_constant< bool, I >;


	constexpr size_t dim(bool is_compile_time, size_t n){
		return is_compile_time ? n : 0;
	}


}


#endif
