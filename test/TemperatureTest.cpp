// file contains tests for tempeture which is different from other dimensions in its unique conversions it does.
#include <gtest/gtest.h>
#include "Tempeture.h"
#include "MetricTypes.h"
#include "conversion_cast.h"
#include "operators.h"
#include "WhatAmI.h"

namespace AU = Metric::AU;
using AUMetric = Metric::AUMetric;

using t_Kelvin = AUMetric::MakeDim<0, 0, 0, 1, 0>::type;
using t_Joule = AUMetric::MakeDim<2, -2, 1, 0, 0>::type;
using t_kilogram = AUMetric::MakeDim<0, 0, 1, 0, 0>::type;

using t_Far = SOU::unitType< AU::Meter, 0, AT::minute, 0, AU::gram, 0, SOU::Temperature::fahrenheit, 1, AU::coulomb, 0 >;
using t_Cel = SOU::unitType< AU::Meter, 0, AT::minute, 0, AU::gram, 0, SOU::Temperature::celsius, 1, AU::coulomb, 0 >;
using t_HeatFluxC = SOU::unitType< AU::Meter, 2, AT::minute, -1, AU::gram, 1, SOU::Temperature::celsius, -1, AU::coulomb, 0 >;

TEST(temperature, ToBase) {
	EXPECT_NEAR( t_Cel::Tempeture::toBase(0.0), 273.15, 0.01);  // to K
	EXPECT_NEAR(t_Kelvin::Tempeture::toBase(0.0), 0.0, 0.01);
}
TEST(temperature, FromBase) {
	EXPECT_NEAR(t_Kelvin::Tempeture::fromBase(0.0), 0.0, 0.01);
	EXPECT_NEAR(t_Cel::Tempeture::fromBase(273.15), 0.0, 0.01);
}
TEST(temperature, ToFromBase) {
	auto out = t_Cel::Tempeture::toBase(0.0);
	EXPECT_DOUBLE_EQ(out, 273.15);
	out = t_Kelvin::Tempeture::fromBase(out);
	EXPECT_DOUBLE_EQ(out, 273.15) << "worked but the one below doesn't";
}

TEST(temperature, StartKtoC_conversion_cast) {
	t_Kelvin K(0.0);
	t_Cel C = SOU::conversion_cast<t_Cel>(K);
	EXPECT_NEAR(C.amount(), -273.15, 0.01) << "is it close?";
}
TEST(temperature, StartCtoK_conversion_cast) {
	t_Cel C(0.0);
	EXPECT_DOUBLE_EQ(C.amount(), 0.0);
	t_Kelvin K = SOU::conversion_cast<t_Kelvin>(C);
	EXPECT_NEAR(K.amount(), 273.15, 0.01);
}
TEST(temperature, FtoC_conversion_cast) {
	t_Far F(32.0);
	t_Cel C = SOU::conversion_cast<t_Cel>(F);
	EXPECT_NEAR(C.amount(), (0.0), 0.01);
}
TEST(temperature, CtoF_conversion_cast) {
	t_Cel C{ 100.0 };
	t_Far F = SOU::conversion_cast<t_Far>(C);
	EXPECT_NEAR(F.amount(), 212.0, 0.01);
}

TEST(temerature, STATIC_Assert) {
   enum { eT = -1 };
   static_assert( eT == -1, "failed since eT is -1" );
   static_assert( eT == -1 || eT == 1 ,"should not fail" );
}

TEST(temperature, Negative_conversion_cast) {
   t_Kelvin K = 100;
   t_Joule  J = 5000;
   t_kilogram kg = 4.0;
   auto HeatCapicity = J / K;
   ASSERT_DOUBLE_EQ(HeatCapicity.amount(), 50.0);

   //ASSERT_TRUE(SOU::dimensions_same< decltype(J), t_Joule >() );
   //SOU::dimensions_same< decltype(HeatCapicity), t_HeatFluxC >();
   //auto Flux = SOU::conversion_cast<t_HeatFluxC>(HeatCapicity);
}

TEST(Dimensions_same, Joule) {
   constexpr t_Joule J = 5000;
   SOU::dimensions_same< decltype(J), t_Joule >();
}

TEST(Diminsion, TEMPERATURE ) {
	t_Cel C{ 100.0 };
	EXPECT_EQ(SOU::WhatAmI(C), "°C") << "May need to comeback to see why the dot is not displayed";

   constexpr char const *cTHETA = u8"\u0233";
   std::wcout << "THEATA is " << cTHETA << '\n';
   std::wcout << "THEATA is " << SOU::helpers::THETA << '\n';

   std::string const theta{ '[', char(SOU::helpers::THETA),  ']' };
	EXPECT_EQ( SOU::Diminsion(C), theta );
}

// Copyright © 2005-2018 "Curt" Leslie L. Martin, All rights reserved.
// curt.leslie.lewis.martin@gmail.com
//
// Permission to use, copy, modify, and distribute this software for any
// purpose is hereby granted without fee, provided that this copyright and
// permissions notice appear in all copies and derivatives.
//
// This software is provided "as is" without express or implied warranty.
