#include <gtest/gtest.h>
#include "MetricTypes.h"
#include "WhatAmI.h"
#include "operators.h"
#include "conversion_cast.h"
#include "DerivedUnits.h"
#include "ExpectUnitTest.h"

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
using t_MakeType = SOU::MakeType< Metric::AtomicUnit::Meter, AT::second, Metric::AtomicUnit::kilogram, Metric::AtomicUnit::kelvin, Metric::AtomicUnit::ampere >;
using t_Joule = t_MakeType::MakeDim<2, -2, 1, 0, 0>::type;
using t_kilogram = t_MakeType::MakeDim<0, 0, 1, 0, 0>::type;

using t_Grav = t_MakeType::MakeDim< 3, -2, -1, 0, 0 >::type;
const t_Grav GRAVITY  { 6.6740831e-11 };

TEST(Diminsion, Joule) {
	t_Joule joule{ 45.033 };
	EXPECT_EQ(SystemOfUnits::Diminsion(joule), "[L]^2[M]/[T]^2");
	EXPECT_EQ(SystemOfUnits::WhatAmI(joule), "meter^2*second^(-2)*kilogram");
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
	EXPECT_UNIT_EQ(225.0, J );
}

// TODO: Not ready for implimentation.
namespace SystemOfUnits
{
	template< SOU::UnitSpecies T, SOU::UnitSpecies U >
	struct is_same
	{
		static_assert(std::is_same_v< T::Length, U::Length >);
		static_assert(std::is_same_v< T::Time, U::Time >);
		static_assert(std::is_same_v< T::Mass, U::Mass >);
		static_assert(std::is_same_v< T::Temperature, U::Temperature >);
		static_assert(std::is_same_v< T::Charge, U::Charge >);
		static_assert(T::eL == U::eL);
		static_assert(T::et == U::et);
		static_assert(T::eM == U::eM);
		static_assert(T::eT == U::eT);
		static_assert(T::eQ == U::eQ);

		static constexpr bool value =
			std::is_same_v< T::Length, U::Length > &&
			std::is_same_v< T::Time, U::Time > &&
			std::is_same_v< T::Mass, U::Mass > &&
			std::is_same_v< T::Temperature, U::Temperature > &&
			std::is_same_v< T::Charge, U::Charge > &&
			T::eL == U::eL && T::et == U::et && T::eM == U::eM && T::eT == U::eT && T::eQ == U::eQ;
	};
}

TEST(Joule, MakeNewtonThroughAuto)
{
	constexpr Metric::t_meter m{ 5.0 };
	constexpr Metric::t_second s(0.5);
	constexpr Metric::t_kilogram kg{ 4.0 };
	auto const joule = m * m * kg / (s * s);

	t_Joule J = m * m * kg / (s * s);

	EXPECT_UNIT_EQ(joule, J);
	EXPECT_UNIT_EQ(400.0, joule);

	std::cout << SOU::units << joule << "  " << t_Joule(4.5) << '\n';

	static_assert(SOU::is_UnitType<decltype(joule)>::value );

	static_assert(std::is_same_v< decltype(joule)::Length, t_Joule::Length >);
	static_assert(std::is_same_v< decltype(joule)::Time, t_Joule::Time >);
	static_assert(std::is_same_v< decltype(joule)::Mass, t_Joule::Mass >);
	static_assert(std::is_same_v< decltype(joule)::Temperature, t_Joule::Temperature >);
	static_assert(std::is_same_v< decltype(joule)::Charge, t_Joule::Charge >);

	static_assert( decltype(joule)::eL == t_Joule::eL );
	static_assert( decltype(joule)::et == t_Joule::et );
	static_assert( decltype(joule)::eM == t_Joule::eM );
	static_assert( decltype(joule)::eT == t_Joule::eT );
	static_assert( decltype(joule)::eQ == t_Joule::eQ );

	static_assert(SOU::is_same<t_Joule, t_Joule >::value);
	static_assert(SOU::is_same<decltype(joule), decltype(joule) >::value, "If this fails shows the concept failing");
	static_assert( SOU::is_same<decltype(joule), t_Joule >::value, "See how the compiler generated Joule is the same" );
}

TEST(Joule, Dimensions_same) {
	constexpr t_Joule J(5000);
	constexpr bool bAns = SOU::dimensions_same< decltype(J), t_Joule >();
	EXPECT_TRUE(bAns);
}


TEST(Joule, Ratio) {
	t_Joule J{ 45.0 };
	t_Newton N{ 5.0 };
	auto M = J / N;
	EXPECT_UNIT_EQ(9.0, M );
	EXPECT_EQ(SystemOfUnits::WhatAmI(M), "meter");
}
using t_Meter = t_MakeType::MakeDim<1, 0, 0, 0, 0>::type;
using t_MeterSq = t_MakeType::MakeDim<2, 0, 0, 0, 0>::type;
using t_Second = t_MakeType::MakeDim<0, 1, 0, 0, 0>::type;

TEST(Joule, Pressure) {
	t_Newton N{ 45.0 };
   t_MeterSq M2{ 9.0 };
	auto Pressure = N / M2;
	EXPECT_UNIT_EQ(5.0, Pressure ) << "Building up for the ideal gas law"; // kg/(m·s2)
	//EXPECT_EQ( SystemOfUnits::WhatAmI( P ), "")
}

TEST(Joule, Watt) {
   auto Watt = t_Newton(300.0) * t_Meter(20.0) / t_Second(4.0);
   EXPECT_EQ("[L]^2[M]/[T]^3", SystemOfUnits::Diminsion(Watt));
}

TEST(Joule, Gravity) {
   t_kilogram const M1  { 5.0 };
   t_kilogram const M2  { 3.0 };
   t_Meter const r  { 10.0 };

	auto F = GRAVITY * M1 * M2 / (r*r);
	EXPECT_EQ(SystemOfUnits::Diminsion(F), SystemOfUnits::Diminsion(t_Newton(2.0)));
}

TEST(Joule, GravityDim) {
	EXPECT_EQ("[L]^3/[M][T]^2", SystemOfUnits::Diminsion(GRAVITY));
}

TEST(Joule, PowerRatio)
{
	using namespace SOU::literals;
	auto gain = 45.0_watt / 9.0_watt;
	EXPECT_EQ("", SystemOfUnits::Diminsion(gain));
	static_assert(SOU::is_UnitType<decltype(gain)>::value, "When this is true we will have Decibels");
}

// Copyright © 2005-2020 "Curt" Leslie L. Martin, All rights reserved.
// curt.leslie.lewis.martin@gmail.com
//
// Permission to use, copy, modify, and distribute this software for any
// purpose is hereby granted without fee, provided that this copyright and
// permissions notice appear in all copies and derivatives.
//
// This software is provided "as is" without express or implied warranty.
