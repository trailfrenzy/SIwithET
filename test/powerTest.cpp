#include <gtest/gtest.h>
#include "pow.h"

using namespace SystemOfUnits;

namespace {
   /// Mock is designed so SOU::UnitType is not used during the test so if failures happens its with thePower<> template.
	struct Mock
	{
		constexpr static double toBase() { return 2.0; }
	};
}

TEST(powerTest, NoExcept)
{
   ASSERT_TRUE(noexcept(helpers::P<Mock>::thePower<2>()));
}

TEST(powerTest, Zero)
{
   ASSERT_DOUBLE_EQ(helpers::P<int>::thePower<0>::toBase(), 1.0) << "To the zeroth order is always 1.0";
   ASSERT_DOUBLE_EQ(helpers::P<Mock>::thePower<0>::toBase(), 1.0) << "To the zeroth order is always 1.0";
}

TEST( powerTest, One )
{
   ASSERT_DOUBLE_EQ(helpers::P<Mock>::thePower<1>::toBase(), 2.0) << "Power to first order returns self";
}

TEST(powerTest, Two)
{
   ASSERT_DOUBLE_EQ(helpers::P<Mock>::thePower<2>::toBase(), 4.0);
}

TEST(powerTest, Three)
{
	ASSERT_DOUBLE_EQ(helpers::P<Mock>::thePower<3>::toBase(), 8.0);
}
TEST(powerTest, Four)
{
	ASSERT_DOUBLE_EQ(helpers::P<Mock>::thePower<4>::toBase(), 16.0);
}
TEST(powerTest, Five) { ASSERT_DOUBLE_EQ(helpers::P<Mock>::thePower<5>::toBase(), 32.0); }
TEST(powerTest, Six) { ASSERT_DOUBLE_EQ(helpers::P<Mock>::thePower<6>::toBase(), 64.0); }
TEST(powerTest, NegOne)
{
	ASSERT_DOUBLE_EQ(helpers::P<Mock>::thePower<-1>::toBase(), 0.50) << "should be one half";
}
TEST(powerTest, NegTwo)
{
	ASSERT_DOUBLE_EQ(helpers::P<Mock>::thePower<-2>::toBase(), 0.250) << "should be one quarter";
}

TEST(powerTest, NegFour) {
	ASSERT_DOUBLE_EQ(helpers::P<Mock>::thePower<-4>::toBase(), 0.0625) << "check the assembly to verify if was calc at compile time";
}

// Copyright © 2005-2019 "Curt" Leslie L. Martin, All rights reserved.
// curt.leslie.lewis.martin@gmail.com
//
// Permission to use, copy, modify, and distribute this software for any
// purpose is hereby granted without fee, provided that this copyright and
// permissions notice appear in all copies and derivatives.
//
// This software is provided "as is" without express or implied warranty.
