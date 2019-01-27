#include <gtest\gtest.h>
//#include "EnglishTypes.h"
#include "MetricTypes.h"
#include "operators.h"
#include "conversion_cast.h"

TEST(MetricUnitTest, BasicTest)
{
	typedef Metric::AtomicUnit::Meter m;
	EXPECT_EQ(std::string("meter"), std::string(m::str()));
	EXPECT_TRUE(m::IsBase == true);
	EXPECT_TRUE(m::toBase() == 1.0);
	EXPECT_TRUE(m::fromBase() == 1.0);
}
TEST(MetricUnitTest, BasicTestLength)
{
	typedef Metric::AtomicUnit::Meter m;
	typedef Metric::AtomicUnit::Kilometer km;
	EXPECT_EQ(1000.0, km::toBase());
}

TEST(UDL_Metric, meter)
{
   auto sq = 4.0_meter * 5.0_meter;
   ASSERT_EQ(sq.amount(), 20.0);
   ASSERT_STREQ(SOU::Diminsion(sq).c_str(), "[L]^2");
}

TEST(UDL_Metric, kph) {
   auto val = 100.0_kph;
   ASSERT_TRUE(val == 100.0);
   ASSERT_STREQ(SOU::Diminsion(val).c_str(), "[L]/[T]");
}

// Copyright © 2005-2019 "Curt" Leslie L. Martin, All rights reserved.
// curt.leslie.lewis.martin@gmail.com
//
// Permission to use, copy, modify, and distribute this software for any
// purpose is hereby granted without fee, provided that this copyright and
// permissions notice appear in all copies and derivatives.
//
// This software is provided "as is" without express or implied warranty.

