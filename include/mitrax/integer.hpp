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


	template < size_t I >
	struct col_t;

	template < size_t I >
	struct row_t;

	template < size_t I >
	struct dim_t;


	template < bool CompileTimeInit, bool CompileTimeTarget, size_t I >
	struct col_init;

	template < bool CompileTimeInit, bool CompileTimeTarget, size_t I >
	struct row_init;

	template < bool CompileTimeInit, bool CompileTimeTarget, size_t I >
	struct dim_init;


	template < bool CompileTimeTarget, size_t I >
	using col_init_ct = col_init< true, CompileTimeTarget, I >;

	template < bool CompileTimeTarget, size_t I >
	using row_init_ct = row_init< true, CompileTimeTarget, I >;

	template < bool CompileTimeTarget, size_t I >
	using dim_init_ct = dim_init< true, CompileTimeTarget, I >;


	template < size_t I >
	struct col_t: size_ct< I >{
		using size_ct< I >::size_ct;

		constexpr auto lit()const noexcept{
			return col_init< true, true, I >();
		}

		constexpr auto as_row()const noexcept{
			return row_t< I >();
		}

		constexpr auto as_dim()const noexcept{
			return dim_t< I >();
		}
	};

	template <>
	struct col_t< 0 >: size_rt{
		using size_rt::size_rt;

		constexpr auto lit()const noexcept;
		constexpr auto as_row()const noexcept;
		constexpr auto as_dim()const noexcept;
	};


	template < size_t I >
	struct row_t: size_ct< I >{
		using size_ct< I >::size_ct;

		constexpr auto lit()const noexcept{
			return row_init< true, true, I >();
		}

		constexpr auto as_col()const noexcept{
			return col_t< I >();
		}

		constexpr auto as_dim()const noexcept{
			return dim_t< I >();
		}
	};

	template <>
	struct row_t< 0 >: size_rt{
		using size_rt::size_rt;

		constexpr auto lit()const noexcept;
		constexpr auto as_col()const noexcept;
		constexpr auto as_dim()const noexcept;
	};


	template < size_t I >
	struct dim_t: size_ct< I >{
		using size_ct< I >::size_ct;

		constexpr auto lit()const noexcept{
			return dim_init< true, true, I >();
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

		constexpr auto lit()const noexcept;
		constexpr auto col()const noexcept;
		constexpr auto row()const noexcept;
	};


	constexpr auto col_t< 0 >::as_row()const noexcept{
		return row_t< 0 >(static_cast< size_t >(*this));
	}

	constexpr auto col_t< 0 >::as_dim()const noexcept{
		return dim_t< 0 >(static_cast< size_t >(*this));
	}

// 	constexpr auto col_t< 0 >::lit()const noexcept{
// 		return col_init< false, false, 0 >(static_cast< size_t >(*this));
// 	}


	constexpr auto row_t< 0 >::as_col()const noexcept{
		return col_t< 0 >(static_cast< size_t >(*this));
	}

	constexpr auto row_t< 0 >::as_dim()const noexcept{
		return dim_t< 0 >(static_cast< size_t >(*this));
	}

// 	constexpr auto row_t< 0 >::lit()const noexcept{
// 		return row_init< false, false, 0 >(static_cast< size_t >(*this));
// 	}


	constexpr auto dim_t< 0 >::col()const noexcept{
		return col_t< 0 >(static_cast< size_t >(*this));
	}

	constexpr auto dim_t< 0 >::row()const noexcept{
		return row_t< 0 >(static_cast< size_t >(*this));
	}

// 	constexpr auto dim_t< 0 >::lit()const noexcept{
// 		return dim_init< false, false, 0 >(static_cast< size_t >(*this));
// 	}


	template < size_t I >
	struct col_init< true, true, I >: size_ct< I >{
		constexpr auto get()const noexcept{
			return col_t< I >();
		}

		constexpr auto as_row()const noexcept{
			return row_init< true, true, I >();
		}

		constexpr auto as_dim()const noexcept{
			return dim_init< true, true, I >();
		}
	};

	template < size_t I >
	struct col_init< true, false, I >: size_ct< I >{
		constexpr auto get()const noexcept{
			return col_t< 0 >(I);
		}

		constexpr auto as_row()const noexcept{
			return row_init< true, false, I >();
		}

		constexpr auto as_dim()const noexcept{
			return dim_init< true, false, I >();
		}
	};

	template < size_t I >
	struct col_init< false, true, I >: size_ct< I >{
		static_assert(true,
			"You can not init with a run time size, "
			"and than use it as a compile time constant!");
	};


	template < size_t I >
	struct row_init< true, true, I >: size_ct< I >{
		constexpr auto get()const noexcept{
			return row_t< I >();
		}

		constexpr auto as_col()const noexcept{
			return col_init< true, true, I >();
		}

		constexpr auto as_dim()const noexcept{
			return dim_init< true, true, I >();
		}
	};

	template < size_t I >
	struct row_init< true, false, I >: size_ct< I >{
		constexpr auto get()const noexcept{
			return row_t< 0 >(I);
		}

		constexpr auto as_col()const noexcept{
			return col_init< true, false, I >();
		}

		constexpr auto as_dim()const noexcept{
			return dim_init< true, false, I >();
		}
	};

	template < size_t I >
	struct row_init< false, true, I >: size_ct< I >{
		static_assert(true,
			"You can not init with a run time size, "
			"and than use it as a compile time constant!");
	};


	template < size_t I >
	struct dim_init< true, true, I >: size_ct< I >{
		constexpr auto get()const noexcept{
			return dim_t< I >();
		}

		constexpr auto col()const noexcept{
			return col_init< true, true, I >();
		}

		constexpr auto row()const noexcept{
			return row_init< true, true, I >();
		}
	};

	template < size_t I >
	struct dim_init< true, false, I >: size_ct< I >{
		constexpr auto get()const noexcept{
			return dim_t< 0 >(I);
		}

		constexpr auto col()const noexcept{
			return col_init< true, false, I >();
		}

		constexpr auto row()const noexcept{
			return row_init< true, false, I >();
		}
	};

	template < size_t I >
	struct dim_init< false, true, I >: size_ct< I >{
		static_assert(true,
			"You can not init with a run time size, "
			"and than use it as a compile time constant!");
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
				true, true,
				detail::parse_int< sizeof...(C) >({C ...})
			>();
		}

		// Adopted from Boost Hana
		template < char ... C >
		constexpr auto operator"" _C_rt(){
			return col_init<
				true, false,
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
				true, true,
				detail::parse_int< sizeof...(C) >({C ...})
			>();
		}

		// Adopted from Boost Hana
		template < char ... C >
		constexpr auto operator"" _R_rt(){
			return row_init<
				true, false,
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
				true, true,
				detail::parse_int< sizeof...(C) >({C ...})
			>();
		}

		// Adopted from Boost Hana
		template < char ... C >
		constexpr auto operator"" _D_rt(){
			return dim_init<
				true, false,
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
