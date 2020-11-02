//#include <SI.h>
#include "MetricTypes.h"
#include "DerivedUnits.h"
#include"WhatAmI.h"
#include "ExpectUnitTest.h"
#include <gtest/gtest.h>

//namespace SystemOfUnits /// covers the basics of the system
//{
//   // TODO: move to SI.h when ready!
//   template< typename UNIT_TYPE, char const * NAME >
//   struct SIwithDIM : UNIT_TYPE
//   {
//      //using t_unitType = t;
//      constexpr SIwithDIM(double val) noexcept : UNIT_TYPE(val)
//      {
//         static_assert(is_UnitType< UNIT_TYPE>::value);
//      }
//
//      static constexpr char const * unitName() noexcept { return NAME; }
//      //static char const * unitDim()  noexcept { return DIM; }
//   };
//
//   /// Used at compile time to find if type is SIwithDIM<>
//   template< typename T> struct is_SIwithDIM { enum :bool { value = false }; };
//   template< typename T, char const * N > struct is_SIwithDIM< SIwithDIM<T, N > >
//   {
//      enum :bool { value = true };
//   };
//}

using Amp = Metric::AUMetric::MakeDim<0, 0, 0, 0, 1>::type;
using Watt = Metric::AUMetric::MakeDim<2, -3, 1, 0, 0>::type;

//    EXPECT_EQ("[L]^2[M]/[T]^3", SystemOfUnits::Diminsion(Watt));
TEST(Current, IsWatt) {
   auto watt = Watt(4.0);
   ASSERT_EQ("[L]^2[M]/[T]^3", SystemOfUnits::Diminsion(watt));
}

TEST(Current, IsAmpere) {
   Amp amp{4.5};
   ASSERT_EQ("[C]", SystemOfUnits::Diminsion(amp));
}


static constexpr char const name[] = "watt"; // must be global

TEST(Current, IsWattType)
{
   using Watt = Metric::AUMetric::MakeDim<2, -3, 1, 0, 0>::type;
   using t_nameWatt = SystemOfUnits::CoherentUnit<Watt, name >;

   t_nameWatt watt(4.5);
   ASSERT_TRUE(SystemOfUnits::is_SIwithDIM< t_nameWatt>::value)<< "Tested in SITest.cpp too";

   EXPECT_UNIT_EQ(watt, 4.5);
   ASSERT_EQ("watt", SystemOfUnits::WhatAmI(watt));
}

TEST(Current, Watt_UDL) {
   auto watt = 67.8_watt;
   EXPECT_UNIT_EQ(watt, 67.8);
   ASSERT_EQ("watt", SystemOfUnits::WhatAmI(watt));
}

TEST(Current, Watt_UDL_Dimension) {
   auto watt = 400.0_watt;

   EXPECT_EQ(SystemOfUnits::Diminsion(watt), "[L]^2[M]/[T]^3");
}

// Copyright © 2005-2020 "Curt" Leslie L. Martin, All rights reserved.
// curt.leslie.lewis.martin@gmail.com
//
// Permission to use, copy, modify, and distribute this software for any
// purpose is hereby granted without fee, provided that this copyright and
// permissions notice appear in all copies and derivatives.
//
// This software is provided "as is" without express or implied warranty.