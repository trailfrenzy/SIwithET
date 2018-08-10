#include <gtest/gtest.h>
#include "pow.h"

using namespace SystemOfUnits;

namespace {
	struct Mock
	{
		static double toBase() { return 2.0; }
	};
}

TEST(powerTest, Zero)
{
	ASSERT_TRUE(helpers::P<int>::thePower<0>::toBase() == 1.0) << "To the zeroth order is always 1.0";
	ASSERT_TRUE(helpers::P<Mock>::thePower<0>::toBase() == 1.0) << "To the zeroth order is always 1.0";
}

TEST( powerTest, One )
{
	ASSERT_TRUE(helpers::P<Mock>::thePower<1>::toBase() == 2.0) << "Power to first order returns self";
}

TEST(powerTest, Two)
{
	ASSERT_TRUE(helpers::P<Mock>::thePower<2>::toBase() == 4.0);
}

TEST(powerTest, Three)
{
	ASSERT_DOUBLE_EQ(helpers::P<Mock>::thePower<3>::toBase(), 8.0);
}
TEST(powerTest, Four)
{
	ASSERT_DOUBLE_EQ(helpers::P<Mock>::thePower<4>::toBase(), 16.0);
}
TEST(powerTest, Five){ ASSERT_DOUBLE_EQ(helpers::P<Mock>::thePower<5>::toBase(), 32.0);}
TEST(powerTest, NegOne)
{
	ASSERT_DOUBLE_EQ(helpers::P<Mock>::thePower<-1>::toBase(), 0.50) << "should be one half";
}
TEST(powerTest, NegTwo)
{
	ASSERT_DOUBLE_EQ(helpers::P<Mock>::thePower<-2>::toBase(), 0.250) << "should be one quarter";
}
