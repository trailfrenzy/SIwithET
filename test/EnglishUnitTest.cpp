#include <gtest\gtest.h>
#include "EnglishTypes.h"
#include "MetricTypes.h"
#include "operators.h"
#include "conversion_cast.h"
#include "WhatAmI.h"

namespace
{
   constexpr double delta = 0.000001;
}

TEST(EnglishUnitTest, CubeFoot) {
	English::t_foot foot(1.0);
	auto cubed = foot * foot * foot;
	EXPECT_DOUBLE_EQ(cubed.amount(), 1.0);
	EXPECT_EQ(SystemOfUnits::WhatAmI(cubed), std::string("foot^3"));
}

namespace {
	/// Using the Type factory where all the English types have the same base unit types.
	typedef SOU::MakeType< English::AtomicUnit::Inch, AT::second, English::AtomicUnit::Slug, Metric::AtomicUnit::kelvin, Metric::AtomicUnit::coulomb > MakeEnglishIn;

	using t_Inch = MakeEnglishIn::MakeDim<1, 0, 0, 0, 0>::type;
	//using t_cubeInch = MakeEnglishIn::MakeDim<3, 0, 0, 0, 0>::type;
	using t_cubeInch = MakeEnglishIn::MakeDim<3, 0, 0, 0, 0>::type;
}

TEST(EnglishUnitTest, InchCubeConversion) {
	English::t_foot foot(1.0);
	auto cubeFoot = foot * foot * foot;

	auto cubeInch = SystemOfUnits::conversion_cast<t_cubeInch>(cubeFoot);

	EXPECT_DOUBLE_EQ(cubeInch.amount(), 1728.0);
	EXPECT_EQ(SystemOfUnits::WhatAmI(cubeInch), std::string("inch^3"));
}

TEST(EnglishUnitTest, SmallBox) {
	t_Inch const W = 16 + (3.0 / 8);
	t_Inch const L = 12 + (5.0 / 8);
	t_Inch const H = 12 + (5.0 / 8);

	auto CubeInch = W * L * H;
	using t_CubeFoot = English::MakeEnglish::MakeDim<3, 0, 0, 0, 0>::type;

	auto cubeFoot = SystemOfUnits::conversion_cast<t_CubeFoot>(CubeInch);
	EXPECT_NEAR(1.5104, cubeFoot.amount(), 0.001) << "Should be 1.5 cube feet";
}

/// Test converting Feet per second from Feet / Second.
TEST(EnglishUnitTest, TestFPS)
{
	English::t_foot Feet = 144;
	English::t_second Second = 4;

	English::t_FPS fps = Feet / Second;

	EXPECT_DOUBLE_EQ(36.0, fps.amount());

	English::t_FPSS fpss = fps / English::t_second(2.0);
	EXPECT_DOUBLE_EQ(18.0, fpss.amount());
}
/// Tests converting different types of length.
TEST(EnglishUnitTest, TestLength)
{
	using namespace SOU;

	English::t_mile mile = 1.0;
	English::t_foot feet = SOU::conversion_cast<English::t_foot>(mile);
	EXPECT_DOUBLE_EQ(5280.0, feet.amount());

	feet = English::t_foot(15);
	English::t_yard yard = conversion_cast<English::t_yard>(feet);
	EXPECT_DOUBLE_EQ(5.0, yard.amount());

	English::t_mph mph = 65.0;
	English::t_FPS fps = SOU::conversion_cast<English::t_FPS>(mph);
	EXPECT_NEAR(95.333333333, fps.amount(), delta);
}

// Copyright © 2005-2015 "Curt" Leslie L. Martin, All rights reserved.
// curt.leslie.lewis.martin@gmail.com
//
// Permission to use, copy, modify, and distribute this software for any
// purpose is hereby granted without fee, provided that this copyright and
// permissions notice appear in all copies and derivatives.
//
// This software is provided "as is" without express or implied warranty.
