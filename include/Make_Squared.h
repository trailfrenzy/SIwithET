#ifndef SYSTEM_OF_UNITS_MAKE_SQUARED_H
#define SYSTEM_OF_UNITS_MAKE_SQUARED_H
#include "SI.h"

namespace SystemOfUnits
{
   /// template used to create a type has been squared.
   /// Since C++11 the templeate is not used as much since it was used more to automatically produce a result type prior to auto in C++11. Still availible for use.
   template< UnitSpecies UNIT > struct MakeSQ
   {
      using type = UnitType
         < typename UNIT::Length, UNIT::eL + UNIT::eL // 
         , typename UNIT::Time, UNIT::et + UNIT::et
         , typename UNIT::Mass, UNIT::eM + UNIT::eM
         , typename UNIT::Temperature, UNIT::eT + UNIT::eT
         , typename UNIT::Charge, UNIT::eQ + UNIT::eQ
         >;
   };
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

