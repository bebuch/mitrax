//-----------------------------------------------------------------------------
// Copyright (c) 2015-2016 Benjamin Buch
//
// https://github.com/bebuch/mitrax
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt)
//-----------------------------------------------------------------------------
#ifndef _mitrax__dim__hpp_INCLUDED_
#define _mitrax__dim__hpp_INCLUDED_

#include <functional>
#include <stdexcept>

#include "utility.hpp"


namespace mitrax{


	template < typename Derived >
	struct dim_base;


	template < bool Cct, size_t C >
	struct col_t: dim_base< col_t< Cct, C > >{
		using dim_base< col_t< Cct, C > >::dim_base;
	};

	template < bool Rct, size_t R >
	struct row_t: dim_base< row_t< Rct, R > >{
		using dim_base< row_t< Rct, R > >::dim_base;
	};

	template < bool Nct, size_t N >
	struct dim_t: dim_base< dim_t< Nct, N > >{
		using dim_base< dim_t< Nct, N > >::dim_base;
	};


	template < template < bool, size_t > typename DimT, size_t N >
	struct dim_base< DimT< true, N > >{
		static_assert(N != 0);

		static constexpr size_t value = N;

		using value_type = size_t;

		constexpr dim_base()noexcept = default;

		explicit constexpr operator size_t()const noexcept{ return value; }

		constexpr auto as_col()const noexcept{ return col_t< true, N >(); }
		constexpr auto as_row()const noexcept{ return row_t< true, N >(); }
		constexpr auto as_dim()const noexcept{ return dim_t< true, N >(); }
	};

	template < template < bool, size_t > typename DimT, size_t N >
	struct dim_base< DimT< false, N > >{
		static constexpr size_t value = N;

		using value_type = size_t;

		constexpr dim_base()noexcept = default;
		constexpr dim_base(DimT< true, N >&&)noexcept{}
		constexpr dim_base(DimT< true, N > const&)noexcept{}

		constexpr operator size_t()const noexcept{ return value; }

		constexpr auto as_col()const noexcept{ return col_t< false, N >(); }
		constexpr auto as_row()const noexcept{ return row_t< false, N >(); }
		constexpr auto as_dim()const noexcept{ return dim_t< false, N >(); }
	};

	template < template < bool, size_t > typename DimT >
	struct dim_base< DimT< false, 0 > >{
	public:
		static constexpr size_t value = 0;

		using value_type = size_t;

		explicit constexpr dim_base(size_t n = 0)noexcept: v_(n) {}

		template < bool Nct, size_t N >
		constexpr dim_base(DimT< Nct, N >&&)noexcept: v_(N) {}

		template < bool Nct, size_t N >
		constexpr dim_base(DimT< Nct, N > const&)noexcept: v_(N) {}

		constexpr operator size_t()const noexcept{ return v_; }

		constexpr auto as_col()const noexcept{ return col_t< false, 0 >(v_); }
		constexpr auto as_row()const noexcept{ return row_t< false, 0 >(v_); }
		constexpr auto as_dim()const noexcept{ return dim_t< false, 0 >(v_); }

	private:
		size_t v_;
	};


	template < bool Cct, size_t C, bool Rct, size_t R >
	class dim_pair_t: private col_t< Cct, C >, private row_t< Rct, R >{
	public:
		static constexpr size_t ct_cols = C;
		static constexpr size_t ct_rows = R;


		constexpr dim_pair_t()noexcept = default;

		constexpr dim_pair_t(
			col_t< Cct, C > cols, row_t< Rct, R > rows
		)noexcept:
			col_t< Cct, C >(cols), row_t< Rct, R >(rows) {}

		template < bool Ccto, size_t Co, bool Rcto, size_t Ro >
		constexpr dim_pair_t(dim_pair_t< Ccto, Co, Rcto, Ro > const& d)noexcept:
			col_t< Cct, C >(d.cols()), row_t< Rct, R >(d.rows()) {}


		constexpr col_t< Cct, C > cols()const noexcept{ return *this; }
		constexpr row_t< Rct, R > rows()const noexcept{ return *this; }


		constexpr void set_cols(col_t< Cct, C > c)noexcept{
			static_cast< col_t< Cct, C >& >(*this) = c;
		}

		constexpr void set_rows(row_t< Rct, R > r)noexcept{
			static_cast< row_t< Rct, R >& >(*this) = r;
		}

		constexpr void set(col_t< Cct, C > c, row_t< Rct, R > r)noexcept{
			set_cols(c);
			set_rows(r);
		}


		size_t point_count()const{
			return size_t(cols()) * size_t(rows());
		}
	};


	template < size_t C, size_t R >
	using auto_dim_pair_t = dim_pair_t< C != 0, C, R != 0, R >;


	constexpr auto dim_pair(size_t c, size_t r)noexcept{
		return dim_pair_t< false, 0, false, 0 >(
			col_t< false, 0 >(c), row_t< false, 0 >(r));
	}

	template < bool Cct, size_t C >
	constexpr auto dim_pair(col_t< Cct, C > c, size_t r)noexcept{
		return dim_pair_t< Cct, C, false, 0 >(c, row_t< false, 0 >(r));
	}

	template < bool Rct, size_t R >
	constexpr auto dim_pair(size_t c, row_t< Rct, R > r)noexcept{
		return dim_pair_t< false, 0, Rct, R >(col_t< false, 0 >(c), r);
	}

	template < bool Cct, size_t C, bool Rct, size_t R >
	constexpr auto dim_pair(col_t< Cct, C > c, row_t< Rct, R > r)noexcept{
		return dim_pair_t< Cct, C, Rct, R >(c, r);
	}

	template < bool Dct, size_t D >
	constexpr auto dim_pair(dim_t< Dct, D > d)noexcept{
		return dim_pair(d.as_col(), d.as_row());
	}

	// TODO; static_assert instead of deleting
	template < typename T, bool Cct, size_t C >
	void dim_pair(T, col_t< Cct, C >) = delete;

	template < typename T, bool Rct, size_t R >
	void dim_pair(row_t< Rct, R >, T) = delete;

	template < bool Cct, size_t C, bool Rct, size_t R >
	void dim_pair(row_t< Rct, R >, col_t< Cct, C >) = delete;

	template < bool Cct, size_t C, bool Rct, size_t R >
	void dim_pair(col_t< Rct, R >, col_t< Cct, C >) = delete;

	template < bool Cct, size_t C, bool Rct, size_t R >
	void dim_pair(row_t< Rct, R >, row_t< Cct, C >) = delete;


	constexpr auto cols(size_t c)noexcept{ return col_t< false, 0 >(c); }
	constexpr auto rows(size_t r)noexcept{ return row_t< false, 0 >(r); }
	constexpr auto dims(size_t d)noexcept{ return dim_t< false, 0 >(d); }


	template < size_t I >
	constexpr auto cols()noexcept{ return col_t< true, I >(); }

	template < size_t I >
	constexpr auto rows()noexcept{ return row_t< true, I >(); }

	template < size_t I >
	constexpr auto dims()noexcept{ return dim_t< true, I >(); }


	template < size_t I >
	constexpr auto cols_rt()noexcept{ return col_t< false, I >(); }

	template < size_t I >
	constexpr auto rows_rt()noexcept{ return row_t< false, I >(); }

	template < size_t I >
	constexpr auto dims_rt()noexcept{ return dim_t< false, I >(); }


}


namespace mitrax::detail{


	template < template < bool, size_t > typename DimT, typename Op >
	struct arithmetic_op_t{
		template < bool Ict1, size_t I1, bool Ict2, size_t I2 >
		constexpr auto operator()(
			DimT< Ict1, I1 >, DimT< Ict2, I2 >
		)const noexcept{
			return DimT< Ict1 || Ict2, Op()(I1, I2) >();
		}

		template < bool Ict2, size_t I2 >
		constexpr auto operator()(
			DimT< false, 0 > d1, DimT< Ict2, I2 > d2
		)const noexcept{
			return DimT< false, 0 >(Op()(size_t(d1), size_t(d2)));
		}

		template < bool Ict1, size_t I1 >
		constexpr auto operator()(
			DimT< Ict1, I1 > d1, DimT< false, 0 > d2
		)const noexcept{
			return DimT< false, 0 >(Op()(size_t(d1), size_t(d2)));
		}

		constexpr auto operator()(
			DimT< false, 0 > d1, DimT< false, 0 > d2
		)const noexcept{
			return DimT< false, 0 >(Op()(size_t(d1), size_t(d2)));
		}

		template < bool Ict1, size_t I1 >
		constexpr auto operator()(
			DimT< Ict1, I1 > d1, size_t d2
		)const noexcept{
			return DimT< false, 0 >(Op()(size_t(d1), d2));
		}

		template < bool Ict2, size_t I2 >
		constexpr auto operator()(
			size_t d1, DimT< Ict2, I2 > d2
		)const noexcept{
			return DimT< false, 0 >(Op()(d1, size_t(d2)));
		}
	};


	template <
		template < bool, size_t > typename DimT1,
		template < bool, size_t > typename DimT2 >
	struct is_same_dim: std::false_type{};

	template < template < bool, size_t > typename DimT >
	struct is_same_dim< DimT, DimT >: std::true_type{};

	template <
		template < bool, size_t > typename DimT1,
		template < bool, size_t > typename DimT2 >
	constexpr auto is_same_dim_v = is_same_dim< DimT1, DimT2 >();


	template < typename Op,
		template < bool, size_t > typename DimT1, bool Cct1, size_t C1,
		template < bool, size_t > typename DimT2, bool Cct2, size_t C2 >
	constexpr auto
	arithmetic_op(DimT1< Cct1, C1 > c1, DimT2< Cct2, C2 > c2)noexcept{
		static_assert(is_same_dim_v< DimT1, DimT2 >,
			"You can not mix col_t, row_t and dim_t.");
		return detail::arithmetic_op_t< DimT1, Op >()(c1, c2);
	}

	template < typename Op,
		template < bool, size_t > typename DimT, bool Cct1, size_t C1,
		typename T, enable_if_t< std::is_integral_v< T > > = 0 >
	constexpr auto arithmetic_op(DimT< Cct1, C1 > c1, T c2)noexcept{
		return detail::arithmetic_op_t< DimT, Op >()(c1, c2);
	}

	template < typename Op,
		template < bool, size_t > typename DimT, bool Cct2, size_t C2,
		typename T, enable_if_t< std::is_integral_v< T > > = 0 >
	constexpr auto arithmetic_op(T c1, DimT< Cct2, C2 > c2)noexcept{
		return detail::arithmetic_op_t< DimT, Op >()(c1, c2);
	}


	template < typename T >
	struct is_a_dim: std::false_type{};

	template < bool Dct, size_t D >
	struct is_a_dim< col_t< Dct, D > >: std::true_type{};

	template < bool Dct, size_t D >
	struct is_a_dim< row_t< Dct, D > >: std::true_type{};

	template < bool Dct, size_t D >
	struct is_a_dim< dim_t< Dct, D > >: std::true_type{};

	template < typename T >
	constexpr auto is_a_dim_v = is_a_dim< T >();


	template < template < bool, size_t > typename DimT >
	struct is_a_dim_template: std::false_type{};

	template <>
	struct is_a_dim_template< col_t >: std::true_type{};

	template <>
	struct is_a_dim_template< row_t >: std::true_type{};

	template <>
	struct is_a_dim_template< dim_t >: std::true_type{};

	template < template < bool, size_t > typename DimT >
	constexpr auto is_a_dim_template_v = is_a_dim_template< DimT >();


	template < typename ... T >
	using enable_if_dim_op_t =
		enable_if_t<
			one_of(is_a_dim_v< T > ...) &&
			all_of(is_a_dim_v< T > || std::is_integral_v< T > ...) >;


}


namespace mitrax{


	template < typename L, typename R, detail::enable_if_dim_op_t< L, R > = 0 >
	constexpr auto operator+(L l, R r)noexcept{
		return detail::arithmetic_op< std::plus< size_t > >(l, r);
	}

	template < typename L, typename R, detail::enable_if_dim_op_t< L, R > = 0 >
	constexpr auto operator-(L l, R r)noexcept{
		return detail::arithmetic_op< std::minus< size_t > >(l, r);
	}

	template < typename L, typename R, detail::enable_if_dim_op_t< L, R > = 0 >
	constexpr auto operator*(L l, R r)noexcept{
		return detail::arithmetic_op< std::multiplies< size_t > >(l, r);
	}

	template < typename L, typename R, detail::enable_if_dim_op_t< L, R > = 0 >
	constexpr auto operator/(L l, R r)noexcept{
		return detail::arithmetic_op< std::divides< size_t > >(l, r);
	}

	template < typename L, typename R, detail::enable_if_dim_op_t< L, R > = 0 >
	constexpr auto operator%(L l, R r)noexcept{
		return detail::arithmetic_op< std::modulus< size_t > >(l, r);
	}

	template < typename L, typename R, detail::enable_if_dim_op_t< L, R > = 0 >
	constexpr auto operator==(L l, R r)noexcept{
		return size_t(l) == size_t(r);
	}

	template < typename L, typename R, detail::enable_if_dim_op_t< L, R > = 0 >
	constexpr auto operator!=(L l, R r)noexcept{
		return size_t(l) != size_t(r);
	}

	template < typename L, typename R, detail::enable_if_dim_op_t< L, R > = 0 >
	constexpr auto operator<(L l, R r)noexcept{
		return size_t(l) < size_t(r);
	}

	template < typename L, typename R, detail::enable_if_dim_op_t< L, R > = 0 >
	constexpr auto operator<=(L l, R r)noexcept{
		return size_t(l) <= size_t(r);
	}

	template < typename L, typename R, detail::enable_if_dim_op_t< L, R > = 0 >
	constexpr auto operator>(L l, R r)noexcept{
		return size_t(l) > size_t(r);
	}

	template < typename L, typename R, detail::enable_if_dim_op_t< L, R > = 0 >
	constexpr auto operator>=(L l, R r)noexcept{
		return size_t(l) >= size_t(r);
	}


	template <
		bool Cct1, size_t C1, bool Rct1, size_t R1,
		bool Cct2, size_t C2, bool Rct2, size_t R2 >
	constexpr auto operator+(
		dim_pair_t< Cct1, C1, Rct1, R1 > const& d1,
		dim_pair_t< Cct2, C2, Rct2, R2 > const& d2
	)noexcept{
		return dim_pair(d1.cols() + d2.cols(), d1.rows() + d2.rows());
	}

	template <
		bool Cct1, size_t C1, bool Rct1, size_t R1,
		bool Cct2, size_t C2, bool Rct2, size_t R2 >
	constexpr auto operator-(
		dim_pair_t< Cct1, C1, Rct1, R1 > const& d1,
		dim_pair_t< Cct2, C2, Rct2, R2 > const& d2
	)noexcept{
		return dim_pair(d1.cols() - d2.cols(), d1.rows() - d2.rows());
	}

	template <
		bool Cct1, size_t C1, bool Rct1, size_t R1,
		bool Cct2, size_t C2, bool Rct2, size_t R2 >
	constexpr auto operator*(
		dim_pair_t< Cct1, C1, Rct1, R1 > const& d1,
		dim_pair_t< Cct2, C2, Rct2, R2 > const& d2
	)noexcept{
		return dim_pair(d1.cols() * d2.cols(), d1.rows() * d2.rows());
	}

	template <
		bool Cct1, size_t C1, bool Rct1, size_t R1,
		bool Cct2, size_t C2, bool Rct2, size_t R2 >
	constexpr auto operator/(
		dim_pair_t< Cct1, C1, Rct1, R1 > const& d1,
		dim_pair_t< Cct2, C2, Rct2, R2 > const& d2
	)noexcept{
		return dim_pair(d1.cols() / d2.cols(), d1.rows() / d2.rows());
	}

	template <
		bool Cct1, size_t C1, bool Rct1, size_t R1,
		bool Cct2, size_t C2, bool Rct2, size_t R2 >
	constexpr auto operator%(
		dim_pair_t< Cct1, C1, Rct1, R1 > const& d1,
		dim_pair_t< Cct2, C2, Rct2, R2 > const& d2
	)noexcept{
		return dim_pair(d1.cols() % d2.cols(), d1.rows() % d2.rows());
	}

	template < bool Cct, size_t C, bool Rct, size_t R, bool Dct, size_t D >
	constexpr auto operator*(
		dim_pair_t< Cct, C, Rct, R > const& d, dim_t< Dct, D > v
	)noexcept{
		return dim_pair(d.cols() * v.as_col(), d.rows() * v.as_row());
	}

	template < bool Cct, size_t C, bool Rct, size_t R, bool Dct, size_t D >
	constexpr auto operator/(
		dim_pair_t< Cct, C, Rct, R > const& d, dim_t< Dct, D > v
	)noexcept{
		return dim_pair(d.cols() / v.as_col(), d.rows() / v.as_row());
	}

	template < bool Cct, size_t C, bool Rct, size_t R, bool Dct, size_t D >
	constexpr auto operator%(
		dim_pair_t< Cct, C, Rct, R > const& d, dim_t< Dct, D > v
	)noexcept{
		return dim_pair(d.cols() % v.as_col(), d.rows() % v.as_row());
	}


	template <
		bool Cct1, size_t C1, bool Rct1, size_t R1,
		bool Cct2, size_t C2, bool Rct2, size_t R2 >
	constexpr auto operator==(
		dim_pair_t< Cct1, C1, Rct1, R1 > const& d1,
		dim_pair_t< Cct2, C2, Rct2, R2 > const& d2
	)noexcept{
		return d1.cols() == d2.cols() && d1.rows() == d2.rows();
	}

	template <
		bool Cct1, size_t C1, bool Rct1, size_t R1,
		bool Cct2, size_t C2, bool Rct2, size_t R2 >
	constexpr auto operator!=(
		dim_pair_t< Cct1, C1, Rct1, R1 > const& d1,
		dim_pair_t< Cct2, C2, Rct2, R2 > const& d2
	)noexcept{
		return !(d1 == d2);
	}


}


namespace mitrax::detail{


	template < size_t N >
	constexpr size_t parse_int(char const(&arr)[N])noexcept{
		size_t number = 0;
		size_t base = 1;
		for(size_t i = 0; i < N; ++i){
			number += (static_cast< int >(arr[N - 1 - i]) - 48) * base;
			base *= 10;
		}
		return number;
	}


}


namespace mitrax::literals{


	template < char ... C >
	constexpr auto operator"" _C()noexcept{
		static_assert(
			detail::parse_int< sizeof...(C) >({C ...}),
			"Compile time cols can not be 0, use '_Cd' prefix instead"
		);
		return cols< detail::parse_int< sizeof...(C) >({C ...}) >();
	}

	template < char ... C >
	constexpr auto operator"" _Cd()noexcept{
		return cols_rt< detail::parse_int< sizeof...(C) >({C ...}) >();
	}

	template < char ... C >
	constexpr auto operator"" _R()noexcept{
		static_assert(
			detail::parse_int< sizeof...(C) >({C ...}),
			"Compile time rows can not be 0, use '_Rd' prefix instead"
		);
		return rows< detail::parse_int< sizeof...(C) >({C ...}) >();
	}

	template < char ... C >
	constexpr auto operator"" _Rd()noexcept{
		return rows_rt< detail::parse_int< sizeof...(C) >({C ...}) >();
	}

	template < char ... C >
	constexpr auto operator"" _D()noexcept{
		static_assert(
			detail::parse_int< sizeof...(C) >({C ...}),
			"Compile time dims can not be 0, use '_Dd' prefix instead"
		);
		return dims< detail::parse_int< sizeof...(C) >({C ...}) >();
	}

	template < char ... C >
	constexpr auto operator"" _Dd()noexcept{
		return dims_rt< detail::parse_int< sizeof...(C) >({C ...}) >();
	}


}


namespace mitrax::detail{


	template < typename T, typename U >
	constexpr auto get_first_of_same_ct(T a, U b){
		static_assert(a == b, "dimensions are not the same");
		return a;
	}

	template < typename T, typename U >
	constexpr auto get_first_of_same_rt(T a, U b){
		if(a != b){
			throw std::logic_error("dimensions are not the same");
		}
		return a;
	}


	template <
		template < bool, size_t > typename DimT, size_t N1, size_t N2 >
	constexpr auto get_ct_if_available(
		DimT< true, N1 > a, DimT< true, N2 > b
	){
		return get_first_of_same_ct(a, b);
	}

	template <
		template < bool, size_t > typename DimT, size_t N1, size_t N2 >
	constexpr auto get_ct_if_available(
		DimT< false, N1 > a, DimT< false, N2 > b
	){
		return get_first_of_same_ct(a, b);
	}

	template <
		template < bool, size_t > typename DimT, size_t N1, size_t N2 >
	constexpr auto get_ct_if_available(
		DimT< true, N1 > a, DimT< false, N2 > b
	){
		return get_first_of_same_ct(a, b);
	}

	template <
		template < bool, size_t > typename DimT, size_t N1, size_t N2 >
	constexpr auto get_ct_if_available(
		DimT< false, N1 > a, DimT< true, N2 > b
	){
		return get_first_of_same_ct(b, a);
	}

	template < template < bool, size_t > typename DimT, size_t N1 >
	constexpr auto get_ct_if_available(
		DimT< true, N1 > a, DimT< false, 0 > b
	){
		return get_first_of_same_rt(a, b);
	}

	template < template < bool, size_t > typename DimT, size_t N1 >
	constexpr auto get_ct_if_available(
		DimT< false, N1 > a, DimT< false, 0 > b
	){
		return get_first_of_same_rt(a, b);
	}

	template < template < bool, size_t > typename DimT, size_t N2 >
	constexpr auto get_ct_if_available(
		DimT< false, 0 > a, DimT< true, N2 > b
	){
		return get_first_of_same_rt(b, a);
	}

	template < template < bool, size_t > typename DimT, size_t N2 >
	constexpr auto get_ct_if_available(
		DimT< false, 0 > a, DimT< false, N2 > b
	){
		return get_first_of_same_rt(b, a);
	}

	template < template < bool, size_t > typename DimT >
	constexpr auto get_ct_if_available(
		DimT< false, 0 > a, DimT< false, 0 > b
	){
		return get_first_of_same_rt(a, b);
	}

	template < template < bool, size_t > typename DimT, bool Nct, size_t N >
	constexpr auto get_same(DimT< Nct, N > d){
		return d;
	}

	template <
		template < bool, size_t > typename DimT,
		bool Nct1, size_t N1,
		bool Nct2, size_t N2,
		bool ... NctN, size_t ... Nn
	> constexpr auto get_same(
		DimT< Nct1, N1 > d1,
		DimT< Nct2, N2 > d2,
		DimT< NctN, Nn > ... dn
	){
		return get_same< DimT >(
			get_ct_if_available< DimT >(d1, d2), dn ...);
	}


}


namespace mitrax{


	template <
		template < bool, size_t > typename DimT, bool ... Nct, size_t ... N,
		enable_if_t< detail::is_a_dim_template_v< DimT > > = 0 >
	constexpr auto get(DimT< Nct, N > ... v){
		return detail::get_same< DimT >(v ...);
	}

	template < bool ... Cct, size_t ... C, bool ... Rct, size_t ... R >
	constexpr auto get(dim_pair_t< Cct, C, Rct, R > const& ... v){
		return dim_pair(get(v.cols() ...), get(v.rows() ...));
	}


	using rt_col_t = col_t< false, 0 >;

	using rt_row_t = row_t< false, 0 >;

	using rt_dim_t = dim_t< false, 0 >;

	using rt_dim_pair_t = auto_dim_pair_t< 0, 0 >;


	struct memory_order{
		struct col_t: std::false_type{};
		struct row_t: std::true_type{};

		static constexpr auto col = col_t();
		static constexpr auto row = row_t();
	};


}


#endif
