//#include <SI.h>
#include <gtest/gtest.h>
#include "MetricTypes.h"
#include"WhatAmI.h"

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
   ASSERT_EQ("[A]", SystemOfUnits::Diminsion(amp));
}

static constexpr char const Watt_str[] = "Watt";

// move to MetricTypes when done testing
constexpr auto operator"" _watt(long double d)
{
   using Watt = Metric::AUMetric::MakeDim<2, -3, 1, 0, 0>::type;
   using t_nameWatt = SystemOfUnits::SIwithDIM<Watt, Watt_str >;

   return t_nameWatt(d);
}

static constexpr char const name[] = "Watt"; // must be global

TEST(Current, IsWattType)
{
   using Watt = Metric::AUMetric::MakeDim<2, -3, 1, 0, 0>::type;
   using t_nameWatt = SystemOfUnits::SIwithDIM<Watt, name >;

   t_nameWatt watt(4.5);
   ASSERT_TRUE(SystemOfUnits::is_SIwithDIM< t_nameWatt>::value)<< "Tested in SITest.cpp too";

   ASSERT_TRUE(watt == 4.5);
   ASSERT_EQ("Watt", SystemOfUnits::WhatAmI(watt));
}

TEST(Current, WattUDL) {
   auto watt = 67.8_watt;
   ASSERT_TRUE(watt == 67.8);
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