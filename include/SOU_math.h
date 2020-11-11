#ifndef SYSTEM_OF_UNIT_MATH_H
#define SYSTEM_OF_UNIT_MATH_H
#include "SystemOfUnits.h"
#include <cmath>

namespace SystemOfUnits::math
{
   template< SOU::UnitSpecies S >
   inline constexpr auto log(S s) noexcept
   {
      static_assert(s.isZeroDimensions(), "To use log() the argument must have zero dimensions"); //TODO look at making a concept for this rule.
      if constexpr (std::is_same_v< double, S::t_float>) return ::log(s.amount());
      if constexpr (std::is_same_v< long double, S::t_float>) return ::logl(s.amount());
      else return ::logf(s.amount());
   }

   template< SOU::UnitSpecies S >
   inline constexpr auto sin(S s) noexcept
   {
      static_assert(s.isZeroDimensions(), "To use log() the argument must have zero dimensions"); //TODO look at making a concept for this rule.
      if constexpr (std::is_same_v< double, S::t_float>) return ::sin(s.amount());
      if constexpr (std::is_same_v< long double, S::t_float>) return ::sinl(s.amount());
      else return ::sinf(s.amount());
   }

   template< SOU::UnitSpecies S >
   inline constexpr auto cos(S s) noexcept
   {
      static_assert(s.isZeroDimensions(), "To use log() the argument must have zero dimensions"); //TODO look at making a concept for this rule.
      if constexpr (std::is_same_v< double, S::t_float>) return ::cos(s.amount());
      if constexpr (std::is_same_v< long double, S::t_float>) return ::cosl(s.amount());
      else return ::cosf(s.amount());
   }

   template< SOU::UnitSpecies S >
   inline constexpr auto tan(S s) noexcept
   {
      static_assert(s.isZeroDimensions(), "To use log() the argument must have zero dimensions"); //TODO look at making a concept for this rule.
      if constexpr (std::is_same_v< double, S::t_float>) return ::tan(s.amount());
      if constexpr (std::is_same_v< long double, S::t_float>) return ::tanl(s.amount());
      else return ::tanf(s.amount());
   }
}

#endif // ! SYSTEM_OF_UNIT_MATH_H

// Copyright © 2002-2020 "Curt" Leslie L. Martin, All rights reserved.
// curt.leslie.lewis.martin@gmail.com
//
// Permission to use, copy, modify, and distribute this software for any
// purpose is hereby granted without fee, provided that this copyright and
// permissions notice appear in all copies and derivatives.
//
// This software is provided "as is" without express or implied warranty.
