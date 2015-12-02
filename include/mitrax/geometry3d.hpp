//-----------------------------------------------------------------------------
// Copyright (c) 2015 Benjamin Buch
//
// https://github.com/bebuch/mitrax
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt)
//-----------------------------------------------------------------------------
#ifndef _mitrax__geometry3d__hpp_INCLUDED_
#define _mitrax__geometry3d__hpp_INCLUDED_

#include "matrix.hpp"


namespace mitrax{ namespace geometry3d{


	template < typename T >
	using point = raw_col_vector< T, 3 >;

	template < typename T >
	class line{
	public:
		using point = point< T >;

		constexpr line(point const& p0, point const& p1):
			p(p_), u(u_), p_(p0), u_(p1 - p0) {}

		constexpr point operator()(T const& s)const{
			return p_ + s * u_;
		}

		point const& p;
		point const& u;

	private:
		point p_;
		point u_;
	};

	template < typename T >
	class plane{
	public:
		using point = point< T >;

		struct general_form_t{
			point p;
			point n;
		};

		struct point_normal_form_t{
			T a;
			T b;
			T c;
			T d;
		};

		constexpr plane(point const& p0, point const& p1, point const& p2):
			p(p_), u(u_), v(v_), p_(p0), u_(p1 - p0), v_(p2 - p0) {}

		constexpr point operator()(T const& s, T const& t)const{
			return p_ + s * u_ + t * v_;
		}

		point const& p;
		point const& u;
		point const& v;

		constexpr point_normal_form_t point_normal_form()const{
			auto g = general_form();
			return {
				g.n[0], g.n[1], g.n[2],
				g.p[0] * g.n[0] + g.p[1] * g.n[1] + g.p[2] * g.n[2]
			};
		}

		constexpr general_form_t general_form()const{
			return { p, cross_product(u, v) };
		}

	private:
		point p_;
		point u_;
		point v_;
	};

	template < typename T >
	constexpr point< T > intersect(plane< T > const& p, line< T > const& l){
		auto g = p.point_normal_form();

		auto lambda = g.a * l.u[0] + g.b * l.u[1] + g.c * l.u[2];

		if(lambda == 0) throw std::logic_error(
			"no intersection point between line and plane"
		);

		return l(
			(g.d - (g.a * l.p[0] + g.b * l.p[1] + g.c * l.p[2])) / lambda
		);
	}

	template < typename T >
	constexpr point< T > intersect(line< T > const& l, plane< T > const& p){
		return intersect(p, l);
	}


} }


#endif
