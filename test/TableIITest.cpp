/*
Test is based from "Dynamics of Physical Systems", Robert H. Cannon, 1967, McGraw-Hill, Inc
ISBN 07-009754-2, pg 22-28

Used these quantities and dimensions to test how well template unitType held up.
*/
//#include <cppunit/extensions/HelperMacros.h> // the macros and headers needed by CPPUnit
#include <gtest/gtest.h>
#include "SI.h"
#include "MetricBaseUnits.h"
#include "TimeAtomicUnits.h"
#include "operators.h"
#include "WhatAmI.h"
#include <cmath>
#include <string_view>

namespace
{
   namespace AT = SOU::Time::AtomicUnit;

   typedef SOU::MakeType< Metric::AtomicUnit::Meter, AT::second, Metric::AtomicUnit::kilogram, Metric::AtomicUnit::kelvin, Metric::AtomicUnit::coulomb > t_Base;

   typedef t_Base::MakeDim<0,1,0,0,0>::type t_sec;
   typedef t_Base::MakeDim<0,0,1,0,0>::type t_mass; // kilogram
   typedef t_Base::MakeDim<1,0,0,0,0>::type t_m; // meter
   typedef t_Base::MakeDim<1,-2,1,0,0>::type t_n; // newton, f=m*a
   typedef SOU::operators::Mul_Result< t_n, t_m >::TResult t_M; // Moment
   typedef t_Base::MakeDim<1,-1,0,0,0>::type v;  // velocity
   typedef t_Base::MakeDim<1,-2,0,0,0>::type a;  // acceleration
   typedef SOU::operators::Div_Result< t_n, t_m >::TResult k; // translational spring constant
   typedef SOU::operators::Div_Result< t_n, v >::TResult b;  // translational damper
   typedef SOU::operators::Div_Result< t_n, t_Base::MakeDim<2,0,0,0,0>::type >::TResult p; // pressure
   typedef t_Base::MakeDim<0,-1,1,0,0 > w; // mass flow rate
   typedef t_Base::MakeDim<-3,0,1,0,0 > rho; // mass density
}

TEST(TableIITest, TestNewton)
{
	a acc = 9.81;
	t_mass mass = 5.0;

	t_n const N = acc * mass;
	EXPECT_DOUBLE_EQ(49.05, N.amount());
	EXPECT_EQ(std::string_view("meter*second^(-2)*kilogram"), SOU::WhatAmI(N));
	//std::cout << SI::WhatAmI(N);
}

TEST(TableIITest, TestAcceleration)
{
	v V1 = 5.0;
	v V2 = 3.0;
	t_sec t = 2.0;
	a acc = (V1 + V2) / t;
	EXPECT_DOUBLE_EQ(4.0, acc.amount());

	a acc2 = acc + V2 / t;
	EXPECT_DOUBLE_EQ(5.5, acc2.amount());

	/* This line below will fail since no brackets are used.
	   Forces the user to keep their types together before mul or dividing.
		  a acc2 = V1+V2/t;
	*/
}

/**
   Test is to see if dB is produced correctly.
*/
TEST(TableIITest, TestWithlog)
{
	t_sec T1 = 80.0;
	t_sec T2 = 8.0;

	double x = log(T1 / T2);
	EXPECT_DOUBLE_EQ(2.3025850929940456840179914546844, x) << "Test to see if a scalar value is produced";
	EXPECT_DOUBLE_EQ(10.00, T1 / T2);
}

// Copyright © 2002-2018 "Curt" Leslie L. Martin, All rights reserved.
// curt.leslie.lewis.martin@gmail.com
//
// Permission to use, copy, modify, and distribute this software for any
// purpose is hereby granted without fee, provided that this copyright and
// permissions notice appear in all copies and derivatives.
//
// This software is provided "as is" without express or implied warranty.
