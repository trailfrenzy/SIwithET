
#ifndef SOU_TEMPETURE_INCLUDE_H
#define SOU_TEMPETURE_INCLUDE_H
#include "Struct_Symbol.h"

namespace SystemOfUnits 
{
   namespace Temperature  // Tempeture
   {
      //enum { THETA = 233 }; // from www.asciitable.com
      constexpr char THETA = 233; // 'Ø';//L'\u0233'; 

      using TEMPERATURE = helpers::T_Symbol< THETA >;
      struct kelvin : TEMPERATURE
      {
         enum { IsBase = true }; /// Lets using classes know if class is used as a base.
         static char const * str() { return "Kelvin"; }/// Called by WhatAmI when creating the string describing the type.
         static double toBase( double val) { return val; } 
         static double fromBase( double val) { return val; }
		 using Base = kelvin;
         //typedef Metric::AtomicUnit::Meter Base;/// Typedef of the actual base
      };

      struct celsius : TEMPERATURE
      {
         enum { IsBase = false }; /// Lets using classes know if class is used as a base.
         static char const * str() { return "°C"; }/// Called by WhatAmI when creating the string describing the type.
         static double toBase( double C ) { return C + 273.15; } // ex Kelvin = toBase(Celsius);
         static double fromBase( double K ) { return K - 273.15; }
		 using Base = kelvin;
		 //typedef Metric::AtomicUnit::Meter Base;/// Typedef of the actual base 
      };

	  struct fahrenheit : TEMPERATURE
	  {
		  enum { IsBase = false }; /// Lets using classes know if class is used as a base.
		  static char const * str() { return "°F"; }/// Called by WhatAmI when creating the string describing the type. K = 5/9 (° F - 32) + 273
		  static double toBase(double F) { return (5.0/9.0)*(F - 32.0) + 273.15; }
		  static double fromBase(double K) { return (9.0/5.0)*(K - 273.15) + 32.0; } // ° F = 9/5 (K - 273) + 32
		  using Base = kelvin;
	  };
   }

}
// Copyright © 2005-2015 "Curt" Leslie L. Martin, All rights reserved.
// curt.leslie.lewis.martin@gmail.com
//
// Permission to use, copy, modify, and distribute this software for any
// purpose is hereby granted without fee, provided that this copyright and
// permissions notice appear in all copies and derivatives.
//
// This software is provided "as is" without express or implied warranty.

#endif