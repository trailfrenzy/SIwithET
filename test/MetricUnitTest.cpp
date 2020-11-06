#include <gtest\gtest.h>
//#include "EnglishTypes.h"
#include "MetricTypes.h"
#include "operators.h"
#include "conversion_cast.h"

TEST(MetricUnitTest, BasicTest)
{
	typedef Metric::AtomicUnit::Meter m;
	EXPECT_EQ(std::string("meter"), std::string(m::str()));
	static_assert(m::IsBase == true);
   static_assert(m::toBase() == 1.0);
   static_assert(m::fromBase() == 1.0);
}
TEST(MetricUnitTest, BasicTestLength)
{
	typedef Metric::AtomicUnit::Meter m;
	typedef Metric::AtomicUnit::Kilometer km;
   static_assert(1000.0 == km::toBase());
}

using namespace SystemOfUnits::literals;

TEST(UDL_Metric, meter)
{
   auto sq = 4.0_meter * 5.0_meter;
   ASSERT_EQ(sq.amount(), 20.0);
   ASSERT_STREQ(SOU::Diminsion(sq).c_str(), "[L]^2");
}

TEST(UDL_Metric, kph) {
   constexpr auto val = 100.0_kph;
   static_assert( val == 100.0);
   ASSERT_STREQ(SOU::Diminsion(val).c_str(), "[L]/[T]");
}

TEST(UDL_Metric, kilometer) {
   constexpr auto L1 = 1000.0_meter;
   constexpr auto L2 = 1.0_kilometer;
   //ASSERT_TRUE(L1 == L2) << "both values are equal";
   ASSERT_TRUE(L1 == SOU::conversion_cast<Metric::t_meter>(L2) ) << "both values are equal, but need to convert km to m";
   ASSERT_TRUE(SOU::conversion_cast<Metric::t_kilometer>(L1) == L2);
}

// Copyright © 2005-2019 "Curt" Leslie L. Martin, All rights reserved.
// curt.leslie.lewis.martin@gmail.com
//
// Permission to use, copy, modify, and distribute this software for any
// purpose is hereby granted without fee, provided that this copyright and
// permissions notice appear in all copies and derivatives.
//
// This software is provided "as is" without express or implied warranty.

