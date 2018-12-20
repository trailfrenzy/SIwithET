// file contains tests for tempeture which is different from other dimensions in its unique conversions it does.
#include <gtest/gtest.h>
#include "Tempeture.h"
#include "MetricTypes.h"
#include "conversion_cast.h"
#include "WhatAmI.h"

namespace AU = Metric::AU;
using AUMetric = Metric::AUMetric;

using t_Kelvin = AUMetric::MakeDim<0, 0, 0, 1, 0>::type;

using t_Far = SOU::unitType< AU::Meter, 0, AT::minute, 0, AU::gram, 0, SOU::Temperature::fahrenheit, 1, AU::coulomb, 0 >;
using t_Cel = SOU::unitType< AU::Meter, 0, AT::minute, 0, AU::gram, 0, SOU::Temperature::celsius, 1, AU::coulomb, 0 >;

TEST(Temperature, ToBase) {
	EXPECT_NEAR( t_Cel::Tempeture::toBase(0.0), 273.15, 0.01);  // to K
	EXPECT_NEAR(t_Kelvin::Tempeture::toBase(0.0), 0.0, 0.01);
}
TEST(Temperature, FromBase) {
	EXPECT_NEAR(t_Kelvin::Tempeture::fromBase(0.0), 0.0, 0.01);
	EXPECT_NEAR(t_Cel::Tempeture::fromBase(273.15), 0.0, 0.01);
}
TEST(Temerature, ToFromBase) {
	auto out = t_Cel::Tempeture::toBase(0.0);
	EXPECT_DOUBLE_EQ(out, 273.15);
	out = t_Kelvin::Tempeture::fromBase(out);
	EXPECT_DOUBLE_EQ(out, 273.15) << "worked but the one below doesn't";
}

TEST(Temperature, StartKtoC_conversion_cast) {
	t_Kelvin K(0.0);
	t_Cel C = SOU::conversion_cast<t_Cel>(K);
	EXPECT_NEAR(C.amount(), -273.15, 0.01) << "is it close?";
}
TEST(Temperature, StartCtoK_conversion_cast) {
	t_Cel C(0.0);
	EXPECT_DOUBLE_EQ(C.amount(), 0.0);
	t_Kelvin K = SOU::conversion_cast<t_Kelvin>(C);
	EXPECT_NEAR(K.amount(), 273.15, 0.01);
}
TEST(Temerature, FtoC_conversion_cast) {
	t_Far F(32.0);
	t_Cel C = SOU::conversion_cast<t_Cel>(F);
	EXPECT_NEAR(C.amount(), (0.0), 0.01);
}
TEST(Temerature, CtoF_conversion_cast) {
	t_Cel C{ 100.0 };
	t_Far F = SOU::conversion_cast<t_Far>(C);
	EXPECT_NEAR(F.amount(), 212.0, 0.01);
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
