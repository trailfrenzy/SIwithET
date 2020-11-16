#include "SI.h"
#include <gtest\gtest.h>
#include "ExpectUnitTest.h"
//#include "MetricTypes.h"

namespace SystemOfUnits {
   struct NoUnit : public tNoUnit
   {
      NoUnit(t_float val) : tNoUnit(val) {} /// Needed since UnitType has an explicit constructor.
      //NoUnit(float val) : tNoUnit(val) {}
   };
}

static_assert( SOU::is_UnitType< SOU::NoUnit>::value , "NoUnit is suppose to be a UnitType" );
static_assert(SOU::is_UnitType< SOU::tNoUnit>::value, "tNoUnit is a UnitType");

TEST(NoUnit, Constructor_tNoUnit)
{
   SOU::tNoUnit noDim( 5.0 );
   SOU::tNoUnit noDim2(7.0f);
   SOU::tNoUnit noDim3(4);
   SOU::tNoUnit noDim4(5u);
}

TEST(NoUnit, Constructor_NoUnit)
{
   SOU::NoUnit noDim1(5.0);
   SOU::NoUnit noDim2(5.2f);

   SOU::NoUnit noDim3 = 4.5f;
   SOU::NoUnit noDim4 = 5;

   SOU::NoUnit noDim5(5ll);
   SOU::NoUnit noDim6(5u);
}

TEST(NoUnit, NoUnitValueZero) {
   SOU::tNoUnit val(0.0);
   EXPECT_UNIT_EQ(val, 0.0);
}

TEST(NoUnit, NoUnitValue) {
   SOU::tNoUnit val(6.0);
   EXPECT_UNIT_EQ(val, 6.0);
}


//TEST(NoUnit, AddtionScaler)
//{
//   SOU::NoUnit noDim1 = 6.0;
//   auto val = noDim1 + 7.0;
//}

// Copyright © 2005-2020 "Curt" Leslie L. Martin, All rights reserved.
// curt.leslie.lewis.martin@gmail.com
//
// Permission to use, copy, modify, and distribute this software for any
// purpose is hereby granted without fee, provided that this copyright and
// permissions notice appear in all copies and derivatives.
//
// This software is provided "as is" without express or implied warranty.
