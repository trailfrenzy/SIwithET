// cpp file is created only to use with Google Test Framework.
#include <gtest/gtest.h>
#include "template_help.h"	/// The file we are testing.
#include "MetricTypes.h"

TEST(helpUnitTest, TheSameTypeTest)
{
	EXPECT_TRUE((SystemOfUnits::is_same<float, float>::value)) << "Using the built in types for test";
	EXPECT_TRUE((SystemOfUnits::is_same<int, int>::value));
	EXPECT_TRUE((SystemOfUnits::is_same<double, double>::value));
	EXPECT_FALSE((SystemOfUnits::is_same<int, double >::value));
}

TEST(helpUnitTest, IF_Test)
{
	EXPECT_TRUE(4 == 4) << "A test for my own sanity";
	EXPECT_TRUE((SystemOfUnits::is_same< SystemOfUnits::IF<true, int, double >::RET, int >::value));
	EXPECT_TRUE((SystemOfUnits::is_same< SystemOfUnits::IF<false, int, double >::RET, double>::value));
}

TEST(helpUnitTest, MetricMeter) {
	EXPECT_FALSE((SystemOfUnits::is_same<Metric::t_meter, Metric::t_centimeter>::value));
}
TEST(helpUnitTest, MetricGram) {
	EXPECT_FALSE((SystemOfUnits::is_same<Metric::t_gram, Metric::t_kilogram>::value));
}

