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

// Copyright © 2005-2015 "Curt" Leslie L. Martin, All rights reserved.
// curt.leslie.lewis.martin@gmail.com
//
// Permission to use, copy, modify, and distribute this software for any
// purpose is hereby granted without fee, provided that this copyright and
// permissions notice appear in all copies and derivatives.
//
// This software is provided "as is" without express or implied warranty.

