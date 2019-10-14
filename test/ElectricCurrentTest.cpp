//#include <SI.h>
#include <gtest/gtest.h>
#include "MetricTypes.h"
#include"WhatAmI.h"

using Amp = Metric::AUMetric::MakeDim<0, 0, 0, 0, 1>::type;
using Watt = Metric::AUMetric::MakeDim<2, -3, 1, 0, 0>::type;

//    EXPECT_EQ("[L]^2[M]/[T]^3", SystemOfUnits::Diminsion(Watt));
TEST(Current, IsWatt) {
   auto watt = Watt(4.0);
   ASSERT_EQ("[L]^2[M]/[T]^3", SystemOfUnits::Diminsion(watt));
}

TEST(Current, IsAmpere) {
   Amp amp{4.5};
   ASSERT_EQ("[A]", SystemOfUnits::Diminsion(amp));
}

// move to MetricTypes when done testing
constexpr char const name[] = "Watt";
using Watt = Metric::AUMetric::MakeDim<2, -3, 1, 0, 0>::type;
using t_nameWatt = SystemOfUnits::SIwithDIM<Watt, name >;
//constexpr t_nameWatt operator"" _watt(long double d)
//{
//   using Watt = Metric::AUMetric::MakeDim<2, -3, 1, 0, 0>::type;
//
//   return t_nameWatt(d);
//}

TEST(Current, IsWattType)
{
   t_nameWatt watt(4.5);
   ASSERT_TRUE(SystemOfUnits::is_SIwithDIM< t_nameWatt>::value)<< "Tested in SITest.cpp too";

   ASSERT_TRUE(watt == 4.5);
   ASSERT_EQ("Watt", SystemOfUnits::WhatAmI(watt));

}


// Copyright © 2005-2019 "Curt" Leslie L. Martin, All rights reserved.
// curt.leslie.lewis.martin@gmail.com
//
// Permission to use, copy, modify, and distribute this software for any
// purpose is hereby granted without fee, provided that this copyright and
// permissions notice appear in all copies and derivatives.
//
// This software is provided "as is" without express or implied warranty.