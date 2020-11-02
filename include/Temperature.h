#ifndef SystemOfUnits_TEMPETURE_INCLUDE_H
#define SystemOfUnits_TEMPETURE_INCLUDE_H
#include "Struct_Symbol.h"

namespace SystemOfUnits 
{
   namespace AtomicUnit
   {
      //enum:unsigned char{ THETA = 233 }; // from www.asciitable.com // 'Ø';//L'\u0233'; 

      struct kelvin : SystemOfUnits::Temperature
      {
         enum:bool{ IsBase = true }; /// Lets using classes know if class is used as a base.
         constexpr static char const * str() noexcept { return "Kelvin"; }/// Called by WhatAmI when creating the string describing the type.
         constexpr static double toBase( double val) noexcept { return val; }
         constexpr static double fromBase( double val) noexcept { return val; }
         using Base = kelvin;
      };

      struct celsius : SystemOfUnits::Temperature
      {
         enum:bool{ IsBase = false }; /// Lets using classes know if class is used as a base.
         constexpr static char const * str() noexcept { return "°C"; }/// Called by WhatAmI when creating the string describing the type.
         constexpr static double toBase( double C ) noexcept { return C + 273.15; } // ex Kelvin = toBase(Celsius);
         constexpr static double fromBase( double K ) noexcept { return K - 273.15; }
		 using Base = kelvin;
      };

	  struct fahrenheit : SystemOfUnits::Temperature
	  {
		  enum:bool{ IsBase = false }; /// Lets using classes know if class is used as a base.
        constexpr static char const * str() noexcept { return "°F"; }/// Called by WhatAmI when creating the string describing the type. K = 5/9 (° F - 32) + 273
        constexpr static double toBase(double F) noexcept { return (5.0/9.0)*(F - 32.0) + 273.15; }
        constexpr static double fromBase(double K) noexcept { return (9.0/5.0)*(K - 273.15) + 32.0; } // ° F = 9/5 (K - 273) + 32
		  using Base = kelvin;
	  };
   }

}
// Copyright © 2005-2019 "Curt" Leslie L. Martin, All rights reserved.
// curt.leslie.lewis.martin@gmail.com
//
// Permission to use, copy, modify, and distribute this software for any
// purpose is hereby granted without fee, provided that this copyright and
// permissions notice appear in all copies and derivatives.
//
// This software is provided "as is" without express or implied warranty.

#endif