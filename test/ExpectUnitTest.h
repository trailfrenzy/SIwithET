/*
   Provides an implimentation of comparing UnitType to the built in type or to another UnitType.
   Made as a compliment to gtest since prior to this the comparing of UnitTypes required conversion to double in the test.
*/
#ifndef SYSTEM_OF_UNITS_EXPECT_UNIT_EQ
#define SYSTEM_OF_UNITS_EXPECT_UNIT_EQ
#include "SI.h"
#include <gtest/gtest.h>

template< SOU::UnitSerial T, SOU::UnitSerial U > auto EXPECT_UNIT_EQ(T t, U u)
{
   static_assert(std::is_same< T, U>::value, "These two types must be the same, if not do not compile");

   EXPECT_PRED_FORMAT2(::testing::internal::CmpHelperFloatingPointEQ<T>, t, u);
}

template< SOU::UnitSerial T > auto EXPECT_UNIT_EQ(T t, double u)
{
   // TODO Set up for return type someday.
   /* return *//* did not work will return some other day. */
   EXPECT_PRED_FORMAT2(::testing::internal::CmpHelperFloatingPointEQ<double>, t.amount(), u);
}

template< SOU::UnitSerial U > auto EXPECT_UNIT_EQ(double t, U u)
{
   EXPECT_PRED_FORMAT2(::testing::internal::CmpHelperFloatingPointEQ<double>, t, u.amount());
}

#endif

// Copyright © 2005-2020 "Curt" Leslie L. Martin, All rights reserved.
// curt.leslie.lewis.martin@gmail.com
//
// Permission to use, copy, modify, and distribute this software for any
// purpose is hereby granted without fee, provided that this copyright and
// permissions notice appear in all copies and derivatives.
//
// This software is provided "as is" without express or implied warranty.
