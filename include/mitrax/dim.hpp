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


	enum class col_t: size_t{};
	enum class row_t: size_t{};
	enum class dim_t: size_t{};

// 	enum class x_ct: size_t{};
// 	enum class y_ct: size_t{};
// 	enum class i_ct: size_t{};


}


namespace mitrax::detail{


	template < typename CT > struct is_a_dim_t: std::false_type{};
	template <> struct is_a_dim_t< col_t >: std::true_type{};
	template <> struct is_a_dim_t< row_t >: std::true_type{};
	template <> struct is_a_dim_t< dim_t >: std::true_type{};
	template < typename CT > constexpr auto is_a_dim_t_v = is_a_dim_t< CT >();

	template < typename ... CT >
	using enable_if_dim_t_t = enable_if_t< all_of(is_a_dim_t_v< CT > ...) >;

	template < typename Op, typename CT1, typename CT2 >
	constexpr auto dim_t_op(Op op, CT1 n1, CT2 n2)noexcept{
		static_assert(std::is_same_v< CT1, CT2 >,
			"You must not mix col_t, row_t and dim_t.");
		return CT1(op(size_t(n1), size_t(n2)));
	}

	template < typename Op, typename CT1, typename CT2 >
	constexpr bool dim_t_comp(Op op, CT1 n1, CT2 n2)noexcept{
		static_assert(std::is_same_v< CT1, CT2 >,
			"You must not mix col_t, row_t and dim_t.");
		return op(size_t(n1), size_t(n2));
	}


}


namespace mitrax{


	template < typename CT1, typename CT2,
		detail::enable_if_dim_t_t< CT1, CT2 > = 0 >
	constexpr auto operator+(CT1 n1, CT2 n2)noexcept{
		return detail::dim_t_op(std::plus< size_t >(), n1, n2);
	}

	template < typename CT1, typename CT2,
		detail::enable_if_dim_t_t< CT1, CT2 > = 0 >
	constexpr auto operator-(CT1 n1, CT2 n2)noexcept{
		return detail::dim_t_op(std::minus< size_t >(), n1, n2);
	}

	template < typename CT1, typename CT2,
		detail::enable_if_dim_t_t< CT1, CT2 > = 0 >
	constexpr auto operator*(CT1 n1, CT2 n2)noexcept{
		return detail::dim_t_op(std::multiplies< size_t >(), n1, n2);
	}

	template < typename CT1, typename CT2,
		detail::enable_if_dim_t_t< CT1, CT2 > = 0 >
	constexpr auto operator/(CT1 n1, CT2 n2)noexcept{
		return detail::dim_t_op(std::divides< size_t >(), n1, n2);
	}

	template < typename CT1, typename CT2,
		detail::enable_if_dim_t_t< CT1, CT2 > = 0 >
	constexpr auto operator%(CT1 n1, CT2 n2)noexcept{
		return detail::dim_t_op(std::modulus< size_t >(), n1, n2);
	}


	template < typename CT1, typename CT2,
		detail::enable_if_dim_t_t< CT1, CT2 > = 0 >
	constexpr bool operator==(CT1 n1, CT2 n2)noexcept{
		return detail::dim_t_comp(std::equal_to< size_t >(), n1, n2);
	}

	template < typename CT1, typename CT2,
		detail::enable_if_dim_t_t< CT1, CT2 > = 0 >
	constexpr bool operator!=(CT1 n1, CT2 n2)noexcept{
		return detail::dim_t_comp(std::not_equal_to< size_t >(), n1, n2);
	}

	template < typename CT1, typename CT2,
		detail::enable_if_dim_t_t< CT1, CT2 > = 0 >
	constexpr bool operator<(CT1 n1, CT2 n2)noexcept{
		return detail::dim_t_comp(std::less< size_t >(), n1, n2);
	}

	template < typename CT1, typename CT2,
		detail::enable_if_dim_t_t< CT1, CT2 > = 0 >
	constexpr bool operator>(CT1 n1, CT2 n2)noexcept{
		return detail::dim_t_comp(std::greater< size_t >(), n1, n2);
	}

	template < typename CT1, typename CT2,
		detail::enable_if_dim_t_t< CT1, CT2 > = 0 >
	constexpr bool operator<=(CT1 n1, CT2 n2)noexcept{
		return detail::dim_t_comp(std::less_equal< size_t >(), n1, n2);
	}

	template < typename CT1, typename CT2,
		detail::enable_if_dim_t_t< CT1, CT2 > = 0 >
	constexpr bool operator>=(CT1 n1, CT2 n2)noexcept{
		return detail::dim_t_comp(std::greater_equal< size_t >(), n1, n2);
	}


}


namespace mitrax::literals{


	constexpr col_t operator"" _C(unsigned long long c)noexcept{
		return col_t(c);
	}

	constexpr row_t operator"" _R(unsigned long long r)noexcept{
		return row_t(r);
	}

	constexpr dim_t operator"" _D(unsigned long long d)noexcept{
		return dim_t(d);
	}


}


namespace mitrax{


	using namespace literals;


	template < bool Nct, typename CT, CT N >
	struct dim_base;


	template < bool Cct, col_t C >
	struct col: dim_base< Cct, col_t, C >{
		using dim_base< Cct, col_t, C >::dim_base;
	};

	template < bool Rct, row_t R >
	struct row: dim_base< Rct, row_t, R >{
		using dim_base< Rct, row_t, R >::dim_base;
	};

	template < bool Dct, dim_t D >
	struct dim: dim_base< Dct, dim_t, D >{
		using dim_base< Dct, dim_t, D >::dim_base;
	};


	template < bool Nct, typename CT, CT N > struct dim_type;

	template < bool Cct, col_t C > struct dim_type< Cct, col_t, C >{
		using type = col< Cct, C >;
	};

	template < bool Rct, row_t R > struct dim_type< Rct, row_t, R >{
		using type = row< Rct, R >;
	};

	template < bool Dct, dim_t D > struct dim_type< Dct, dim_t, D >{
		using type = dim< Dct, D >;
	};

	template < bool Nct, typename CT, CT N >
	using dim_type_t = typename dim_type< Nct, CT, N >::type;


	template < typename CT, CT N >
	struct dim_base< true, CT, N >{
		static_assert(N != CT(0));

		static constexpr CT value = N;

		using value_type = CT;

		constexpr dim_base()noexcept = default;

		explicit constexpr operator CT()const noexcept{ return value; }
		explicit constexpr operator size_t()const noexcept{
			return size_t(this->operator CT());
		}

		constexpr auto as_col()const noexcept{
			return col< true, col_t(N) >();
		}

		constexpr auto as_row()const noexcept{
			return row< true, row_t(N) >();
		}

		constexpr auto as_dim()const noexcept{
			return dim< true, dim_t(N) >();
		}
	};

	template < typename CT, CT N >
	struct dim_base< false, CT, N >{
		static constexpr CT value = N;

		using value_type = CT;

		constexpr dim_base()noexcept = default;
		constexpr dim_base(dim_base< true, CT, N >&&)noexcept{}
		constexpr dim_base(dim_base< true, CT, N > const&)noexcept{}

		explicit constexpr operator CT()const noexcept{ return value; }
		explicit constexpr operator size_t()const noexcept{
			return size_t(this->operator CT());
		}

		constexpr auto as_col()const noexcept{
			return col< false, col_t(N) >();
		}

		constexpr auto as_row()const noexcept{
			return row< false, row_t(N) >();
		}

		constexpr auto as_dim()const noexcept{
			return dim< false, dim_t(N) >();
		}
	};


	template < typename CT >
	struct rt_dim_base{
	public:
		static constexpr CT value = CT(0);

		using value_type = CT;

		explicit constexpr rt_dim_base(CT n = CT(0))noexcept: v_(n) {}

		template < bool Nct, CT N >
		constexpr rt_dim_base(dim_base< Nct, CT, N >&& n)noexcept:
			v_(CT(n)) {}

		template < bool Nct, CT N >
		constexpr rt_dim_base(dim_base< Nct, CT, N > const& n)noexcept:
			v_(CT(n)) {}


		explicit constexpr operator CT()const noexcept{ return v_; }
		explicit constexpr operator size_t()const noexcept{
			return size_t(this->operator CT());
		}

		constexpr auto as_col()const noexcept{
			return col< false, col_t(0) >(col_t(v_));
		}

		constexpr auto as_row()const noexcept{
			return row< false, row_t(0) >(row_t(v_));
		}

		constexpr auto as_dim()const noexcept{
			return dim< false, dim_t(0) >(dim_t(v_));
		}

	private:
		CT v_;
	};

	template <>
	struct dim_base< false, col_t, 0_C >: rt_dim_base< col_t >{
		using rt_dim_base< col_t >::rt_dim_base;
	};

	template <>
	struct dim_base< false, row_t, 0_R >: rt_dim_base< row_t >{
		using rt_dim_base< row_t >::rt_dim_base;
	};

	template <>
	struct dim_base< false, dim_t, 0_D >: rt_dim_base< dim_t >{
		using rt_dim_base< dim_t >::rt_dim_base;
	};


	template < bool Cct, col_t C, bool Rct, row_t R >
	class dim_pair_t: private col< Cct, C >, private row< Rct, R >{
	public:
		static constexpr col_t ct_cols = C;
		static constexpr row_t ct_rows = R;


		constexpr dim_pair_t()noexcept = default;

		constexpr dim_pair_t(
			col< Cct, C > cols, row< Rct, R > rows
		)noexcept:
			col< Cct, C >(cols), row< Rct, R >(rows) {}

		template < bool Ccto, col_t Co, bool Rcto, row_t Ro >
		constexpr dim_pair_t(dim_pair_t< Ccto, Co, Rcto, Ro > const& d)noexcept:
			col< Cct, C >(d.cols()), row< Rct, R >(d.rows()) {}


		constexpr col< Cct, C > cols()const noexcept{ return *this; }
		constexpr row< Rct, R > rows()const noexcept{ return *this; }


		constexpr void set_cols(col< Cct, C > c)noexcept{
			static_cast< col< Cct, C >& >(*this) = c;
		}

		constexpr void set_rows(row< Rct, R > r)noexcept{
			static_cast< row< Rct, R >& >(*this) = r;
		}

		constexpr void set(col< Cct, C > c, row< Rct, R > r)noexcept{
			set_cols(c);
			set_rows(r);
		}


		size_t point_count()const{
			return size_t(cols()) * size_t(rows());
		}
	};


	template < col_t C, row_t R >
	using auto_dim_pair_t = dim_pair_t< C != 0_C, C, R != 0_R, R >;


	constexpr auto dim_pair(col_t c, row_t r)noexcept{
		return dim_pair_t< false, 0_C, false, 0_R >(
			col< false, 0_C >(c), row< false, 0_R >(r));
	}

	template < bool Cct, col_t C >
	constexpr auto dim_pair(col< Cct, C > c, row_t r)noexcept{
		return dim_pair_t< Cct, C, false, 0_R >(c, row< false, 0_R >(r));
	}

	template < bool Rct, row_t R >
	constexpr auto dim_pair(col_t c, row< Rct, R > r)noexcept{
		return dim_pair_t< false, 0_C, Rct, R >(col< false, 0_C >(c), r);
	}

	template < bool Cct, col_t C, bool Rct, row_t R >
	constexpr auto dim_pair(col< Cct, C > c, row< Rct, R > r)noexcept{
		return dim_pair_t< Cct, C, Rct, R >(c, r);
	}

	template < bool Dct, dim_t D >
	constexpr auto dim_pair(dim< Dct, D > d)noexcept{
		return dim_pair(d.as_col(), d.as_row());
	}

	// TODO; static_assert instead of deleting
	template < typename T, bool Cct, col_t C >
	void dim_pair(T, col< Cct, C >) = delete;

	template < typename T, bool Rct, row_t R >
	void dim_pair(row< Rct, R >, T) = delete;

	template < bool Cct, col_t C, bool Rct, row_t R >
	void dim_pair(row< Rct, R >, col< Cct, C >) = delete;

	template < bool Cct, col_t C, bool Rct, row_t R >
	void dim_pair(col< Rct, R >, col< Cct, C >) = delete;

	template < bool Cct, col_t C, bool Rct, row_t R >
	void dim_pair(row< Rct, R >, row< Cct, C >) = delete;


	constexpr auto cols(col_t c)noexcept{ return col< false, 0_C >(c); }
	constexpr auto rows(row_t r)noexcept{ return row< false, 0_R >(r); }
	constexpr auto dims(dim_t d)noexcept{ return dim< false, 0_D >(d); }


	template < col_t C >
	constexpr auto cols()noexcept{ return col< true, C >(); }

	template < row_t R >
	constexpr auto rows()noexcept{ return row< true, R >(); }

	template < dim_t D >
	constexpr auto dims()noexcept{ return dim< true, D >(); }


	template < col_t C >
	constexpr auto cols_rt()noexcept{ return col< false, C >(); }

	template < row_t R >
	constexpr auto rows_rt()noexcept{ return row< false, R >(); }

	template < dim_t D >
	constexpr auto dims_rt()noexcept{ return dim< false, D >(); }


}


namespace mitrax::detail{


	template < typename Op,
		bool Nct1, typename CT1, CT1 N1, bool Nct2, typename CT2, CT2 N2 >
	constexpr auto dim_op(
		Op op, dim_base< Nct1, CT1, N1 > n1, dim_base< Nct2, CT2, N2 > n2
	)noexcept{
		static_assert(std::is_same_v< CT1, CT2 >,
			"You must not mix col, row and dim.");

		if constexpr(N1 != CT1(0) && N2 != CT2(0)){
			return dim_type_t< Nct1 || Nct2, CT1,
				CT1(op(size_t(n1), size_t(n2))) >();
		}else{
			return dim_type_t< false, CT1, CT1(0) >
				(CT1(op(size_t(n1), size_t(n2))));
		}
	}

	template < typename Op,
		bool Nct1, typename CT1, CT1 N1, bool Nct2, typename CT2, CT2 N2 >
	constexpr auto dim_comp(
		Op op, dim_base< Nct1, CT1, N1 > n1, dim_base< Nct2, CT2, N2 > n2
	)noexcept{
		static_assert(std::is_same_v< CT1, CT2 >,
			"You must not mix col, row and dim.");

		return op(size_t(n1), size_t(n2));
	}


}


namespace mitrax{


	template < bool Nct1, typename CT1, CT1 N1, bool Nct2, typename CT2, CT2 N2,
		detail::enable_if_dim_t_t< CT1, CT2 > = 0 >
	constexpr auto operator+(
		dim_base< Nct1, CT1, N1 > n1, dim_base< Nct2, CT2, N2 > n2
	)noexcept{
		return detail::dim_op(std::plus< size_t >(), n1, n2);
	}

	template < bool Nct1, typename CT1, CT1 N1, bool Nct2, typename CT2, CT2 N2,
		detail::enable_if_dim_t_t< CT1, CT2 > = 0 >
	constexpr auto operator-(
		dim_base< Nct1, CT1, N1 > n1, dim_base< Nct2, CT2, N2 > n2
	)noexcept{
		return detail::dim_op(std::minus< size_t >(), n1, n2);
	}

	template < bool Nct1, typename CT1, CT1 N1, bool Nct2, typename CT2, CT2 N2,
		detail::enable_if_dim_t_t< CT1, CT2 > = 0 >
	constexpr auto operator*(
		dim_base< Nct1, CT1, N1 > n1, dim_base< Nct2, CT2, N2 > n2
	)noexcept{
		return detail::dim_op(std::multiplies< size_t >(), n1, n2);
	}

	template < bool Nct1, typename CT1, CT1 N1, bool Nct2, typename CT2, CT2 N2,
		detail::enable_if_dim_t_t< CT1, CT2 > = 0 >
	constexpr auto operator/(
		dim_base< Nct1, CT1, N1 > n1, dim_base< Nct2, CT2, N2 > n2
	)noexcept{
		return detail::dim_op(std::divides< size_t >(), n1, n2);
	}

	template < bool Nct1, typename CT1, CT1 N1, bool Nct2, typename CT2, CT2 N2,
		detail::enable_if_dim_t_t< CT1, CT2 > = 0 >
	constexpr auto operator%(
		dim_base< Nct1, CT1, N1 > n1, dim_base< Nct2, CT2, N2 > n2
	)noexcept{
		return detail::dim_op(std::modulus< size_t >(), n1, n2);
	}


	template < bool Nct1, typename CT1, CT1 N1, bool Nct2, typename CT2, CT2 N2,
		detail::enable_if_dim_t_t< CT1, CT2 > = 0 >
	constexpr auto operator==(
		dim_base< Nct1, CT1, N1 > n1, dim_base< Nct2, CT2, N2 > n2
	)noexcept{
		return detail::dim_comp(std::equal_to< size_t >(), n1, n2);
	}

	template < bool Nct1, typename CT1, CT1 N1, bool Nct2, typename CT2, CT2 N2,
		detail::enable_if_dim_t_t< CT1, CT2 > = 0 >
	constexpr auto operator!=(
		dim_base< Nct1, CT1, N1 > n1, dim_base< Nct2, CT2, N2 > n2
	)noexcept{
		return detail::dim_comp(std::not_equal_to< size_t >(), n1, n2);
	}

	template < bool Nct1, typename CT1, CT1 N1, bool Nct2, typename CT2, CT2 N2,
		detail::enable_if_dim_t_t< CT1, CT2 > = 0 >
	constexpr auto operator<(
		dim_base< Nct1, CT1, N1 > n1, dim_base< Nct2, CT2, N2 > n2
	)noexcept{
		return detail::dim_comp(std::less< size_t >(), n1, n2);
	}

	template < bool Nct1, typename CT1, CT1 N1, bool Nct2, typename CT2, CT2 N2,
		detail::enable_if_dim_t_t< CT1, CT2 > = 0 >
	constexpr auto operator>(
		dim_base< Nct1, CT1, N1 > n1, dim_base< Nct2, CT2, N2 > n2
	)noexcept{
		return detail::dim_comp(std::greater< size_t >(), n1, n2);
	}

	template < bool Nct1, typename CT1, CT1 N1, bool Nct2, typename CT2, CT2 N2,
		detail::enable_if_dim_t_t< CT1, CT2 > = 0 >
	constexpr auto operator<=(
		dim_base< Nct1, CT1, N1 > n1, dim_base< Nct2, CT2, N2 > n2
	)noexcept{
		return detail::dim_comp(std::less_equal< size_t >(), n1, n2);
	}

	template < bool Nct1, typename CT1, CT1 N1, bool Nct2, typename CT2, CT2 N2,
		detail::enable_if_dim_t_t< CT1, CT2 > = 0 >
	constexpr auto operator>=(
		dim_base< Nct1, CT1, N1 > n1, dim_base< Nct2, CT2, N2 > n2
	)noexcept{
		return detail::dim_comp(std::greater_equal< size_t >(), n1, n2);
	}


	template <
		bool Cct1, col_t C1, bool Rct1, row_t R1,
		bool Cct2, col_t C2, bool Rct2, row_t R2 >
	constexpr auto operator+(
		dim_pair_t< Cct1, C1, Rct1, R1 > const& d1,
		dim_pair_t< Cct2, C2, Rct2, R2 > const& d2
	)noexcept{
		return dim_pair(d1.cols() + d2.cols(), d1.rows() + d2.rows());
	}

	template <
		bool Cct1, col_t C1, bool Rct1, row_t R1,
		bool Cct2, col_t C2, bool Rct2, row_t R2 >
	constexpr auto operator-(
		dim_pair_t< Cct1, C1, Rct1, R1 > const& d1,
		dim_pair_t< Cct2, C2, Rct2, R2 > const& d2
	)noexcept{
		return dim_pair(d1.cols() - d2.cols(), d1.rows() - d2.rows());
	}

	template <
		bool Cct1, col_t C1, bool Rct1, row_t R1,
		bool Cct2, col_t C2, bool Rct2, row_t R2 >
	constexpr auto operator*(
		dim_pair_t< Cct1, C1, Rct1, R1 > const& d1,
		dim_pair_t< Cct2, C2, Rct2, R2 > const& d2
	)noexcept{
		return dim_pair(d1.cols() * d2.cols(), d1.rows() * d2.rows());
	}

	template <
		bool Cct1, col_t C1, bool Rct1, row_t R1,
		bool Cct2, col_t C2, bool Rct2, row_t R2 >
	constexpr auto operator/(
		dim_pair_t< Cct1, C1, Rct1, R1 > const& d1,
		dim_pair_t< Cct2, C2, Rct2, R2 > const& d2
	)noexcept{
		return dim_pair(d1.cols() / d2.cols(), d1.rows() / d2.rows());
	}

	template <
		bool Cct1, col_t C1, bool Rct1, row_t R1,
		bool Cct2, col_t C2, bool Rct2, row_t R2 >
	constexpr auto operator%(
		dim_pair_t< Cct1, C1, Rct1, R1 > const& d1,
		dim_pair_t< Cct2, C2, Rct2, R2 > const& d2
	)noexcept{
		return dim_pair(d1.cols() % d2.cols(), d1.rows() % d2.rows());
	}

	template < bool Cct, col_t C, bool Rct, row_t R, bool Dct, dim_t D >
	constexpr auto operator*(
		dim_pair_t< Cct, C, Rct, R > const& d, dim< Dct, D > v
	)noexcept{
		return dim_pair(d.cols() * v.as_col(), d.rows() * v.as_row());
	}

	template < bool Cct, col_t C, bool Rct, row_t R, bool Dct, dim_t D >
	constexpr auto operator/(
		dim_pair_t< Cct, C, Rct, R > const& d, dim< Dct, D > v
	)noexcept{
		return dim_pair(d.cols() / v.as_col(), d.rows() / v.as_row());
	}

	template < bool Cct, col_t C, bool Rct, row_t R, bool Dct, dim_t D >
	constexpr auto operator%(
		dim_pair_t< Cct, C, Rct, R > const& d, dim< Dct, D > v
	)noexcept{
		return dim_pair(d.cols() % v.as_col(), d.rows() % v.as_row());
	}


	template <
		bool Cct1, col_t C1, bool Rct1, row_t R1,
		bool Cct2, col_t C2, bool Rct2, row_t R2 >
	constexpr auto operator==(
		dim_pair_t< Cct1, C1, Rct1, R1 > const& d1,
		dim_pair_t< Cct2, C2, Rct2, R2 > const& d2
	)noexcept{
		return d1.cols() == d2.cols() && d1.rows() == d2.rows();
	}

	template <
		bool Cct1, col_t C1, bool Rct1, row_t R1,
		bool Cct2, col_t C2, bool Rct2, row_t R2 >
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
	constexpr auto operator"" _CS()noexcept{
		static_assert(
			detail::parse_int< sizeof...(C) >({C ...}),
			"Compile time cols can not be 0, use '_CD' prefix instead"
		);
		return cols< col_t(detail::parse_int< sizeof...(C) >({C ...})) >();
	}

	template < char ... C >
	constexpr auto operator"" _CD()noexcept{
		return cols_rt< col_t(detail::parse_int< sizeof...(C) >({C ...})) >();
	}

	template < char ... C >
	constexpr auto operator"" _RS()noexcept{
		static_assert(
			detail::parse_int< sizeof...(C) >({C ...}),
			"Compile time rows can not be 0, use '_RD' prefix instead"
		);
		return rows< row_t(detail::parse_int< sizeof...(C) >({C ...})) >();
	}

	template < char ... C >
	constexpr auto operator"" _RD()noexcept{
		return rows_rt< row_t(detail::parse_int< sizeof...(C) >({C ...})) >();
	}

	template < char ... C >
	constexpr auto operator"" _DS()noexcept{
		static_assert(
			detail::parse_int< sizeof...(C) >({C ...}),
			"Compile time dims can not be 0, use '_DD' prefix instead"
		);
		return dims< dim_t(detail::parse_int< sizeof...(C) >({C ...})) >();
	}

	template < char ... C >
	constexpr auto operator"" _DD()noexcept{
		return dims_rt< dim_t(detail::parse_int< sizeof...(C) >({C ...})) >();
	}


}


namespace mitrax::detail{


	template < typename CT, bool Nct1, CT N1, bool Nct2, CT N2 >
	constexpr auto get_ct_if_available(
		dim_base< Nct1, CT, N1 > n1, dim_base< Nct2, CT, N2 > n2
	){
		if constexpr(N1 != CT(0) && N2 != CT(0)){
			static_assert(N1 == N2, "dimensions are not the same");
			return dim_type_t< Nct1 || Nct2, CT, N1 >();
		}else{
			if(n1 != n2) throw std::logic_error("dimensions are not the same");
			if constexpr(N1 == CT(0) && N2 == CT(0)){
				return dim_type_t< false, CT, CT(0) >(CT(n1));
			}else{
				return dim_type_t< Nct1 || Nct2, CT, (N1 > N2 ? N1 : N2) >();
			}
		}
	}


	template < bool Nct, typename CT, CT N >
	constexpr auto get_same(dim_base< Nct, CT, N > d){
		return dim_type_t< Nct, CT, N >(d);
	}

	template < typename CT, bool Nct1, CT N1, bool Nct2, CT N2,
		bool ... Nctn, CT ... Nn >
	constexpr auto get_same(
		dim_base< Nct1, CT, N1 > d1,
		dim_base< Nct2, CT, N2 > d2,
		dim_base< Nctn, CT, Nn > ... dn
	){
		return get_same(get_ct_if_available(d1, d2), dn ...);
	}


}


namespace mitrax{


	template < bool ... Nct, typename ... CT, CT ... N >
	constexpr auto get(dim_base< Nct, CT, N > ... v){
		static_assert(is_all_v< std::is_same, CT ... >,
			"You must not mix col, row and dim.");
		return detail::get_same(v ...);
	}

	template < bool ... Cct, col_t ... C, bool ... Rct, row_t ... R >
	constexpr auto get(dim_pair_t< Cct, C, Rct, R > const& ... v){
		return dim_pair(get(v.cols() ...), get(v.rows() ...));
	}


	using rt_col = col< false, 0_C >;

	using rt_row = row< false, 0_R >;

	using rt_dim = dim< false, 0_D >;

	using rt_dim_pair_t = auto_dim_pair_t< 0_C, 0_R >;


	struct memory_order{
		struct col_wise_t: std::false_type{};
		struct row_wise_t: std::true_type{};

		static constexpr auto col_wise = col_wise_t();
		static constexpr auto row_wise = row_wise_t();
	};


}


#endif
