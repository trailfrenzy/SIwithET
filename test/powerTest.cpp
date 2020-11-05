#include <gtest/gtest.h>
#include "pow.h"

using namespace SystemOfUnits;

namespace {
   /// Mock is designed so SOU::UnitType is not used during the test so if failures happens with the thePower<> template, the same failure will happen with UnitType.
	struct Mock
	{
		constexpr static double toBase() noexcept { return 2.0; }
	};
}

TEST(powerTest, NoExcept)
{
	static_assert(noexcept(helpers::P<Mock>::thePower<2>()));
}

TEST(powerTest, Zero)
{
	static_assert(helpers::P<int>::thePower<0>::toBase() == 1.0, "To the zeroth order is always 1.0");
	static_assert(helpers::P<Mock>::thePower<0>::toBase() == 1.0, "To the zeroth order is always 1.0");
}

TEST( powerTest, One )
{
	static_assert(helpers::P<Mock>::thePower<1>::toBase() == 2.0, "Power to first order returns self");
}

TEST(powerTest, Two)
{
	static_assert(helpers::P<Mock>::thePower<2>::toBase() == 4.0, "It took place at compile time" );
}

TEST(powerTest, Three)
{
	static_assert(helpers::P<Mock>::thePower<3>::toBase() == 8.0, "It took place at compile time");
}
TEST(powerTest, Four)
{
	static_assert(helpers::P<Mock>::thePower<4>::toBase() == 16.0, "It took place at compile time");
}
TEST(powerTest, Five) {
	static_assert(helpers::P<Mock>::thePower<5>::toBase() == 32.0, "It took place at compile time");
}
TEST(powerTest, Six) { 
	static_assert(helpers::P<Mock>::thePower<6>::toBase() == 64.0, "It took place at compile time");
}
TEST(powerTest, NegOne)
{
	static_assert(helpers::P<Mock>::thePower<-1>::toBase() == 0.50, "should be one half");
}
TEST(powerTest, NegTwo)
{
	static_assert(helpers::P<Mock>::thePower<-2>::toBase() == 0.250, "should be one quarter");
}

TEST(powerTest, NegFour) {
	static_assert(helpers::P<Mock>::thePower<-4>::toBase() == 0.0625, "It took place at compile time");
}

// All the tests are completed at compile time in this file.

// Copyright © 2005-2020 "Curt" Leslie L. Martin, All rights reserved.
// curt.leslie.lewis.martin@gmail.com
//
// Permission to use, copy, modify, and distribute this software for any
// purpose is hereby granted without fee, provided that this copyright and
// permissions notice appear in all copies and derivatives.
//
// This software is provided "as is" without express or implied warranty.
