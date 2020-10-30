/*
   Provides an implimentation of comparing UnitType to the built in type or to another UnitType.
*/
#ifndef SYSTEM_OF_UNITS_EXPECT_UNIT_EQ
#define SYSTEM_OF_UNITS_EXPECT_UNIT_EQ
#include "SI.h"
#include <gtest/gtest.h>

template< SOU::UnitSerial T, SOU::UnitSerial U > void EXPECT_UNIT_EQ(T t, U u)
{
   static_assert(std::is_same< T, U>::value, "These two types must be the same, if not do not compile");

   EXPECT_PRED_FORMAT2(::testing::internal::CmpHelperFloatingPointEQ<T>, t, u);
}

template< SOU::UnitSerial T > void EXPECT_UNIT_EQ(T t, double u)
{
   EXPECT_PRED_FORMAT2(::testing::internal::CmpHelperFloatingPointEQ<double>, t.amount(), u);
}

template< SOU::UnitSerial U > void EXPECT_UNIT_EQ(double t, U u)
{
   EXPECT_PRED_FORMAT2(::testing::internal::CmpHelperFloatingPointEQ<double>, t, u.amount());
}

#endif
