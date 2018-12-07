
#include <gtest/gtest.h>
#include "MetricTypes.h"
#include "WhatAmI.h"
#include "operators.h"
/*
The joule is a derived unit of energy in the International System of Units. It is equal to the energy transferred to an object when a force of one newton acts on that object in the direction of its motion through a distance of one metre. Wikipedia
SI base units: kg⋅m2⋅s−2
Unit system: SI derived unit
Unit of: Energy
CGS units: 1×107 erg
1 J in: is equal to
Named after: James Prescott Joule
*/

//using t_Joule = Metric::AUMetric::MakeDim<2, -2, 1, 0, 0>::type;
using t_MakeType = SOU::MakeType< Metric::AtomicUnit::Meter, AT::second, Metric::AtomicUnit::kilogram, Metric::AtomicUnit::kelvin, Metric::AtomicUnit::coulomb >;
using t_Joule = t_MakeType::MakeDim<2, -2, 1, 0, 0>::type;
using t_kilogram = t_MakeType::MakeDim<0, 0, 1, 0, 0>::type;

using t_Grav = t_MakeType::MakeDim< 3, -2, -1, 0, 0 >::type;
const t_Grav GRAVITY = 6.6740831e-11;

TEST(Diminsion, Joule) {
	t_Joule joule{ 45.033 };
	EXPECT_EQ(SystemOfUnits::Diminsion(joule), "[L]^2[M]/[T]^2");
	EXPECT_EQ(SystemOfUnits::WhatAmI(joule), "meter^2*second^(-2)*kilogram");
	//EXPECT_TRUE(SystemOfUnits::Diminsion(joule) == std::string("L^2⋅t^-2⋅M"));
}

/*
The newton (symbol: N) is the International System of Units (SI) derived unit of force. It is named after Isaac Newton in recognition of his work on classical ...
SI base units‎: ‎1 kg⋅m⋅s−2	Unit of‎: ‎Force
Unit system‎: ‎SI derived unit	1 N in‎: ‎is equal to
*/
using t_Newton = t_MakeType::MakeDim<1, -2, 1, 0, 0 >::type;

TEST(Diminsion, Newton) {
	t_Newton N{ 45.5885 };
	EXPECT_EQ(SystemOfUnits::Diminsion(N),"[L][M]/[T]^2");
	EXPECT_EQ(SystemOfUnits::WhatAmI(N), "meter*second^(-2)*kilogram");
}

TEST(Joule, Product) {
	t_Newton N{ 45.0 };
	Metric::t_meter M{ 5.0 };
	auto J = N * M;
	EXPECT_EQ(SystemOfUnits::Diminsion(J), "[L]^2[M]/[T]^2");
	EXPECT_EQ(SystemOfUnits::WhatAmI(J), "meter^2*second^(-2)*kilogram");
	EXPECT_DOUBLE_EQ(225.0, J.amount());
}

TEST(Joule, Ratio) {
	t_Joule J{ 45.0 };
	t_Newton N{ 5.0 };
	auto M = J / N;
	EXPECT_DOUBLE_EQ(9.0, M.amount());
	EXPECT_EQ(SystemOfUnits::WhatAmI(M), std::string("meter"));
}
using t_Meter = t_MakeType::MakeDim<1, 0, 0, 0, 0>::type;
using t_MeterSq = t_MakeType::MakeDim<2, 0, 0, 0, 0>::type;
using t_Second = t_MakeType::MakeDim<0, 1, 0, 0, 0>::type;

TEST(Joule, Pressure) {
	t_Newton N{ 45.0 };
	t_MeterSq M2 = 9.0;
	auto Pressure = N / M2;
	EXPECT_DOUBLE_EQ(5.0, Pressure.amount()) << "Building up for the ideal gas law"; // kg/(m·s2)
	//EXPECT_EQ( SystemOfUnits::WhatAmI( P ), "")
}

TEST(Joule, Watt) {
   auto Watt = t_Newton(300.0) * t_Meter(20.0) / t_Second(4.0);
   EXPECT_EQ("[L]^2[M]/[T]^3", SystemOfUnits::Diminsion(Watt));
}

TEST(Joule, Gravity) {
	t_kilogram const M1 = 5.0;
	t_kilogram const M2 = 3.0;
	t_Meter const r = 10.0;

	auto F = GRAVITY * M1 * M2 / (r*r);
	EXPECT_EQ(SystemOfUnits::Diminsion(F), SystemOfUnits::Diminsion(t_Newton(2.0)));
}

TEST(Joule, GravityDim) {
	EXPECT_EQ("[L]^3/[M][T]^2", SystemOfUnits::Diminsion(GRAVITY));
}

// Copyright © 2005-2018 "Curt" Leslie L. Martin, All rights reserved.
// curt.leslie.lewis.martin@gmail.com
//
// Permission to use, copy, modify, and distribute this software for any
// purpose is hereby granted without fee, provided that this copyright and
// permissions notice appear in all copies and derivatives.
//
// This software is provided "as is" without express or implied warranty.
