/*
   Provides an implimentation of comparing UnitType to the built in type or to another UnitType.
   Made as a compliment to gtest since prior to this the comparing of UnitTypes required conversion to double in the test.
*/
#ifndef SYSTEM_OF_UNITS_EXPECT_UNIT_EQ
#define SYSTEM_OF_UNITS_EXPECT_UNIT_EQ
#include "SI.h"
#include <gtest/gtest.h>

/// <summary>
/// Wraps the macro EXPECT_PRED_FORMAT2 in function which can be called over again. Easier for the compiler to decide to inline it or call it.
/// </summary>
/// <param name="t"></param>
/// <param name="u"></param>
/// <returns></returns>
inline auto TheMacro(double t, double u)
{
   EXPECT_PRED_FORMAT2(::testing::internal::CmpHelperFloatingPointEQ<double>, t, u);
}

template< SOU::UnitSpecies T, SOU::UnitSpecies U > auto EXPECT_UNIT_EQ(T t, U u)
{
   static_assert(std::is_same< T, U>::value, "These two types must be the same, if not do not compile");

   TheMacro(t.amount(), u.amount());
}

template< SOU::UnitSpecies T > auto EXPECT_UNIT_EQ(T t, double u)
{
   // TODO Set up for return type someday.
   /* return *//* did not work will return some other day. */
   TheMacro(t.amount(), u);
}

template< SOU::UnitSpecies U > auto EXPECT_UNIT_EQ(double t, U u)
{
   TheMacro(t, u.amount());
}

#endif
//template< typename T, typename U > struct IsBothSOU
//{
//   constexpr static bool value = SOU::is_UnitType<T>::value && SOU::is_UnitType<U>::value;
//};
//
//#define EXPECT_UNIT_EQ( t, u ) \
//   if constexpr( IsBothSOU<decltype(t), decltype(u) >::value ) { \
//      static_assert(std::is_same< decltype(t), decltype(u)>::value, "These two types must be the same, if not do not compile"); \
//      EXPECT_PRED_FORMAT2(::testing::internal::CmpHelperFloatingPointEQ<double>, t.amount(), u.amount()); \
//   } \
//   else if constexpr( SOU::is_UnitType<decltype(t)>::value ) \
//      EXPECT_PRED_FORMAT2(::testing::internal::CmpHelperFloatingPointEQ<double>, t.amount(), u); \
//   else if constexpr( SOU::is_UnitType<decltype(u)>::value ) \
//      EXPECT_PRED_FORMAT2(::testing::internal::CmpHelperFloatingPointEQ<double>, t, u.amount()); \
//   else {static_assert(false, "Non-UnitTypes where passes as arguments"); }

// Copyright © 2005-2020 "Curt" Leslie L. Martin, All rights reserved.
// curt.leslie.lewis.martin@gmail.com
//
// Permission to use, copy, modify, and distribute this software for any
// purpose is hereby granted without fee, provided that this copyright and
// permissions notice appear in all copies and derivatives.
//
// This software is provided "as is" without express or implied warranty.
