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
	struct col_init_t;

	template < bool CompileTimeInit, bool CompileTimeTarget, size_t I >
	struct row_init_t;

	template < bool CompileTimeInit, bool CompileTimeTarget, size_t I >
	struct dim_init_t;


	template < bool CompileTimeTarget, size_t I >
	using col_init_ct = col_init_t< true, CompileTimeTarget, I >;

	template < bool CompileTimeTarget, size_t I >
	using row_init_ct = row_init_t< true, CompileTimeTarget, I >;

	template < bool CompileTimeTarget, size_t I >
	using dim_init_ct = dim_init_t< true, CompileTimeTarget, I >;


	template < size_t I >
	struct col_t: size_ct< I >{
		using size_ct< I >::size_ct;

		constexpr auto init()const noexcept{
			return col_init_t< true, true, I >();
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

		constexpr auto init()const noexcept;
		constexpr auto as_row()const noexcept;
		constexpr auto as_dim()const noexcept;
	};


	template < size_t I >
	struct row_t: size_ct< I >{
		using size_ct< I >::size_ct;

		constexpr auto init()const noexcept{
			return row_init_t< true, true, I >();
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

		constexpr auto init()const noexcept;
		constexpr auto as_col()const noexcept;
		constexpr auto as_dim()const noexcept;
	};


	template < size_t I >
	struct dim_t: size_ct< I >{
		using size_ct< I >::size_ct;

		constexpr auto init()const noexcept{
			return dim_init_t< true, true, I >();
		}

		constexpr auto as_col()const noexcept{
			return col_t< I >();
		}

		constexpr auto as_row()const noexcept{
			return row_t< I >();
		}
	};

	template <>
	struct dim_t< 0 >: size_rt{
		using size_rt::size_rt;

		constexpr auto init()const noexcept;
		constexpr auto as_col()const noexcept;
		constexpr auto as_row()const noexcept;
	};


	template < size_t I >
	struct illegal_init_type{
		static_assert(I != I,
			"You can not init with a run time size, "
			"and than use it as a compile time constant!");
	};


	template < size_t I >
	struct col_init_t< true, true, I >: size_ct< I >{
		constexpr auto get()const noexcept{
			return col_t< I >();
		}

		constexpr auto as_row()const noexcept{
			return row_init_t< true, true, I >();
		}

		constexpr auto as_dim()const noexcept{
			return dim_init_t< true, true, I >();
		}
	};

	template < size_t I >
	struct col_init_t< true, false, I >: size_ct< I >{
		constexpr auto get()const noexcept{
			return col_t< 0 >(I);
		}

		constexpr auto as_row()const noexcept{
			return row_init_t< true, false, I >();
		}

		constexpr auto as_dim()const noexcept{
			return dim_init_t< true, false, I >();
		}
	};

	template < size_t I >
	struct col_init_t< false, true, I >: illegal_init_type< I >{};

	template < size_t I >
	struct col_init_t< false, false, I >: illegal_init_type< I >{};

	template <>
	struct col_init_t< false, false, 0 >: size_rt{
		using size_rt::size_rt;

		constexpr auto get()const noexcept;
		constexpr auto as_row()const noexcept;
		constexpr auto as_dim()const noexcept;
	};


	template < size_t I >
	struct row_init_t< true, true, I >: size_ct< I >{
		constexpr auto get()const noexcept{
			return row_t< I >();
		}

		constexpr auto as_col()const noexcept{
			return col_init_t< true, true, I >();
		}

		constexpr auto as_dim()const noexcept{
			return dim_init_t< true, true, I >();
		}
	};

	template < size_t I >
	struct row_init_t< true, false, I >: size_ct< I >{
		constexpr auto get()const noexcept{
			return row_t< 0 >(I);
		}

		constexpr auto as_col()const noexcept{
			return col_init_t< true, false, I >();
		}

		constexpr auto as_dim()const noexcept{
			return dim_init_t< true, false, I >();
		}
	};

	template < size_t I >
	struct row_init_t< false, true, I >: illegal_init_type< I >{};

	template < size_t I >
	struct row_init_t< false, false, I >: illegal_init_type< I >{};

	template <>
	struct row_init_t< false, false, 0 >: size_rt{
		using size_rt::size_rt;

		constexpr auto get()const noexcept;
		constexpr auto as_col()const noexcept;
		constexpr auto as_dim()const noexcept;
	};


	template < size_t I >
	struct dim_init_t< true, true, I >: size_ct< I >{
		constexpr auto get()const noexcept{
			return dim_t< I >();
		}

		constexpr auto as_col()const noexcept{
			return col_init_t< true, true, I >();
		}

		constexpr auto as_row()const noexcept{
			return row_init_t< true, true, I >();
		}
	};

	template < size_t I >
	struct dim_init_t< true, false, I >: size_ct< I >{
		constexpr auto get()const noexcept{
			return dim_t< 0 >(I);
		}

		constexpr auto as_col()const noexcept{
			return col_init_t< true, false, I >();
		}

		constexpr auto as_row()const noexcept{
			return row_init_t< true, false, I >();
		}
	};

	template < size_t I >
	struct dim_init_t< false, true, I >: illegal_init_type< I >{};

	template < size_t I >
	struct dim_init_t< false, false, I >: illegal_init_type< I >{};

	template <>
	struct dim_init_t< false, false, 0 >: size_rt{
		using size_rt::size_rt;

		constexpr auto get()const noexcept;
		constexpr auto as_col()const noexcept;
		constexpr auto as_row()const noexcept;
	};


	constexpr auto col_init_t< false, false, 0 >::get()const noexcept{
		return col_t< 0 >(static_cast< size_t >(*this));
	}

	constexpr auto col_init_t< false, false, 0 >::as_row()const noexcept{
		return row_init_t< false, false, 0 >(static_cast< size_t >(*this));
	}

	constexpr auto col_init_t< false, false, 0 >::as_dim()const noexcept{
		return dim_init_t< false, false, 0 >(static_cast< size_t >(*this));
	}


	constexpr auto row_init_t< false, false, 0 >::get()const noexcept{
		return row_t< 0 >(static_cast< size_t >(*this));
	}

	constexpr auto row_init_t< false, false, 0 >::as_col()const noexcept{
		return col_init_t< false, false, 0 >(static_cast< size_t >(*this));
	}

	constexpr auto row_init_t< false, false, 0 >::as_dim()const noexcept{
		return dim_init_t< false, false, 0 >(static_cast< size_t >(*this));
	}


	constexpr auto dim_init_t< false, false, 0 >::get()const noexcept{
		return dim_t< 0 >(static_cast< size_t >(*this));
	}

	constexpr auto dim_init_t< false, false, 0 >::as_col()const noexcept{
		return col_init_t< false, false, 0 >(static_cast< size_t >(*this));
	}

	constexpr auto dim_init_t< false, false, 0 >::as_row()const noexcept{
		return row_init_t< false, false, 0 >(static_cast< size_t >(*this));
	}


	constexpr auto col_t< 0 >::as_row()const noexcept{
		return row_t< 0 >(static_cast< size_t >(*this));
	}

	constexpr auto col_t< 0 >::as_dim()const noexcept{
		return dim_t< 0 >(static_cast< size_t >(*this));
	}

	constexpr auto col_t< 0 >::init()const noexcept{
		return col_init_t< false, false, 0 >(static_cast< size_t >(*this));
	}


	constexpr auto row_t< 0 >::as_col()const noexcept{
		return col_t< 0 >(static_cast< size_t >(*this));
	}

	constexpr auto row_t< 0 >::as_dim()const noexcept{
		return dim_t< 0 >(static_cast< size_t >(*this));
	}

	constexpr auto row_t< 0 >::init()const noexcept{
		return row_init_t< false, false, 0 >(static_cast< size_t >(*this));
	}


	constexpr auto dim_t< 0 >::as_col()const noexcept{
		return col_t< 0 >(static_cast< size_t >(*this));
	}

	constexpr auto dim_t< 0 >::as_row()const noexcept{
		return row_t< 0 >(static_cast< size_t >(*this));
	}

	constexpr auto dim_t< 0 >::init()const noexcept{
		return dim_init_t< false, false, 0 >(static_cast< size_t >(*this));
	}


	constexpr auto cols(size_t c){
		return col_init_t< false, false, 0 >(c);
	}

	constexpr auto rows(size_t r){
		return row_init_t< false, false, 0 >(r);
	}

	constexpr auto dims(size_t d){
		return dim_init_t< false, false, 0 >(d);
	}


	template < size_t I >
	constexpr auto cols(){
		return col_init_t< true, true, I >();
	}

	template < size_t I >
	constexpr auto rows(){
		return row_init_t< true, true, I >();
	}

	template < size_t I >
	constexpr auto dims(){
		return dim_init_t< true, true, I >();
	}


	template < size_t I >
	constexpr auto cols_rt(){
		return col_init_t< true, false, I >();
	}

	template < size_t I >
	constexpr auto rows_rt(){
		return row_init_t< true, false, I >();
	}

	template < size_t I >
	constexpr auto dims_rt(){
		return dim_init_t< true, false, I >();
	}


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
			return cols< detail::parse_int< sizeof...(C) >({C ...}) >();
		}

		// Adopted from Boost Hana
		template < char ... C >
		constexpr auto operator"" _C_rt(){
			return cols_rt< detail::parse_int< sizeof...(C) >({C ...}) >();
		}

		// Adopted from Boost Hana
		template < char ... C >
		constexpr auto operator"" _R(){
			static_assert(
				detail::parse_int< sizeof...(C) >({C ...}),
				"Compile time rows can not be 0, use '_R_rt' prefix instead"
			);
			return rows< detail::parse_int< sizeof...(C) >({C ...}) >();
		}

		// Adopted from Boost Hana
		template < char ... C >
		constexpr auto operator"" _R_rt(){
			return rows_rt< detail::parse_int< sizeof...(C) >({C ...}) >();
		}

		// Adopted from Boost Hana
		template < char ... C >
		constexpr auto operator"" _D(){
			static_assert(
				detail::parse_int< sizeof...(C) >({C ...}),
				"Compile time dims can not be 0, use '_D_rt' prefix instead"
			);
			return dims< detail::parse_int< sizeof...(C) >({C ...}) >();
		}

		// Adopted from Boost Hana
		template < char ... C >
		constexpr auto operator"" _D_rt(){
			return dims_rt< detail::parse_int< sizeof...(C) >({C ...}) >();
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
