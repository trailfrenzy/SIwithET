#ifndef METRICBASEUNITS_H_INCLUDE
#define METRICBASEUNITS_H_INCLUDE
#pragma once
#include "Struct_Symbol.h"
/// represents the SI-Metric system of measurment
namespace Metric
{
   /** namespace of the quantity types.
 @page page4 SI-Metric base types

    Atomic comes from Martin Fowler's pg 36.
    Atomic units are not intended to be used by outside class template unitType.

	A property Tag is a type used to name and identify properties.
   */
   namespace AtomicUnit
   {
      using LENGTH = SystemOfUnits::helpers::T_Symbol<'L'>;

      struct Meter : LENGTH /// @anchor repesent quantity length of a meter.
      {
         enum:bool{ IsBase = true };/// Lets using classes know if class is used as a base.
         constexpr static char const * str() noexcept { return "meter"; }/// Called by WhatAmI when creating the string describing the type.
         constexpr static double toBase() noexcept { return 1.0; }///  Multiply by toBase() to get base value.
         constexpr static double fromBase() noexcept { return 1.0; }/// Multiply by fromBase() to get diminsional value.
         typedef Meter Base;/// Typedef of the actual base
      };
      struct Kilometer : LENGTH /// represents quantity length of a kilometer
      {
         enum:bool{ IsBase = false };/// Lets using classes know if class is used as a base.
         constexpr static char const * str() noexcept { return "kilometer"; }/// Called by WhatAmI when creating the string describing the type.
         ///  Multiply by toBase() to get base value.
         constexpr static double toBase() noexcept { return 1000.0; } // ex meter = kilometer * toBase();
         constexpr static double fromBase() noexcept { return 1.0 / toBase(); }/// Multiply by fromBase() to get diminsional value.
         typedef Meter Base;/// Typedef of the actual base
      };
      struct Centimeter : LENGTH /// represents quantity length of a centimeter
      {
         enum:bool{ IsBase = false };/// Lets using classes know if class is used as a base.
         constexpr static char const * str() noexcept { return "centimeter"; }/// Called by WhatAmI when creating the string describing the type.
         constexpr static double fromBase() noexcept { return 100.0; }/// Multiply by fromBase() to get diminsional value.
         // ex meter = centimeter * toBase();
         constexpr static double toBase() noexcept { return 1.0/100.0; }///  Multiply by toBase() to get base value.
         typedef Meter Base;/// Typedef of the actual base
      };
      struct Milimeter : LENGTH /// represents quantity length of a milimeter
      {
         enum:bool{ IsBase = false };/// Lets using classes know if class is used as a base.
         constexpr static char const * str() noexcept { return "milimeter";}/// Called by WhatAmI when creating the string describing the type.
         constexpr static double fromBase() noexcept { return 1000.0; }/// Multiply by fromBase() to get diminsional value.
         constexpr static double toBase() noexcept { return 1.0/fromBase(); }///  Multiply by toBase() to get base value.
         typedef Meter Base;/// Typedef of the actual base
      };

      using MASS = SystemOfUnits::helpers::T_Symbol<'M'>;
      struct gram : MASS /// represents quantity mass of a gram
      {
         enum:bool{ IsBase = true };/// Lets using classes know if class is used as a base.
         constexpr static char const * str() noexcept { return "gram"; }/// Called by WhatAmI when creating the string describing the type.
         constexpr static double toBase() noexcept { return 1.0; }///  Multiply by toBase() to get base value.
         constexpr static double fromBase() noexcept { return 1.0; }/// Multiply by fromBase() to get diminsional value.
         typedef gram Base;/// Typedef of the actual base
      };
      struct kilogram : MASS /// represents quantity mass of a kilogram.
      {
         enum:bool{ IsBase = false };/// Lets using classes know if class is used as a base.
         constexpr static char const * str() noexcept { return "kilogram"; }/// Called by WhatAmI when creating the string describing the type.
         constexpr static double toBase() noexcept { return 1000.0; }///  Multiply by toBase() to get base value.
         constexpr static double fromBase() noexcept { return 1.0 / toBase() ; }/// Multiply by fromBase() to get diminsional value.
         typedef gram Base;/// Typedef of the actual base
      };
      struct miligram : MASS /// represents quantity mass of miligram.
      {
         enum:bool{ IsBase = false };/// Lets using classes know if class is used as a base.
         constexpr static char const * str() noexcept { return "miligram"; }/// Called by WhatAmI when creating the string describing the type.
         constexpr static double toBase() noexcept { return 1.0 / fromBase(); }///  Multiply by toBase() to get base value.
         constexpr static double fromBase() noexcept { return 1000.0; }/// Multiply by fromBase() to get diminsional value.
         typedef gram Base;/// Typedef of the actual base
      };

      enum { THETA = 233 }; // from www.asciitable.com
      using TEMPERATURE = SystemOfUnits::helpers::T_Symbol< char(THETA) >;

      struct kelvin : TEMPERATURE /// represents quantity tempeture of kelvin
      {
         enum:bool{ IsBase = true };/// Lets using classes know if class is used as a base.
         constexpr static char const * str() noexcept { return "Kelvin"; }/// Called by WhatAmI when creating the string describing the type.
         constexpr static double toBase(double val) noexcept { return val; }
         constexpr static double fromBase(double val) noexcept { return val; }
		 typedef kelvin Base;/// Typedef of the actual base
      };
      /// @warning Do not use
      struct celsius : TEMPERATURE/// represents quanity tempeture celsius.
      {
         enum:bool{ IsBase = false };/// Lets using classes know if class is used as a base.
         constexpr static char const * str()  noexcept { return "°C"; }/// Called by WhatAmI when creating the string describing the type.
         // currently only kelvin is the only tempeture offered in compound
         constexpr static double toBase( double C ) noexcept { return C + 273.15; }///  Multiply by toBase() to get base value.
         constexpr static double fromBase( double K ) noexcept { return K - 273.15; }/// Multiply by fromBase() to get diminsional value.
		 using Base = kelvin;
      };

/*
The ampere is defined by taking the fixed numerical value of the elementary charge e to be 1.602176634 × 10?19 when expressed in the unit C, which is equal to A s, where the second is defined in terms of ??Cs.

The SI unit of electric potential difference is the volt (V) 1 V = 1 W/A.

The SI unit of electric resistance is the ohm (?). 1 ? = 1 V/A.
*/
      using ELECTRIC_CURRENT = SystemOfUnits::helpers::T_Symbol<'A'>;
      struct ampere : ELECTRIC_CURRENT /// represents quantity electric current.
      {
         enum:bool{ IsBase = true };/// Lets using classes know if class is used as a base.
         constexpr static char const * str() noexcept { return "ampere"; }/// Called by WhatAmI when creating the string describing the type.
         constexpr static double toBase() noexcept { return 1.0; }///  Multiply by toBase() to get base value.
         constexpr static double fromBase() noexcept { return 1.0; }/// Multiply by fromBase() to get diminsional value.
         using Base = ampere;/// Typedef of the actual base
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

/* see https://www.nist.gov/pml/weights-and-measures/si-units-length
The meter (m) is defined by taking the fixed numerical value of the speed of light in vacuum c to be 299,792,458 when expressed in the unit m s?1, where the second is defined in terms of ??Cs.

The meter was once defined by a physical artifact - two marks inscribed on a platinum-iridium bar. The Length - Evolution from Measurement Standard to a Fundamental Constant explains the evolution of the definition of the meter. Follow these changes over time in the NIST Length Timeline .

From the meter, several other units of measure are derived such as the:

unit of speed is the meter per second (m/s). The speed of light in vacuum is 299 792 458 meters per second.
unit of acceleration is the meter per second per second (m/s2).
unit of area is the square meter (m2).
unit of volume is the cubic meter (m3). The liter (1 cubic decimeter), although not an SI unit, is accepted for use with the SI and is commonly used to measure fluid volume.
*/

#endif
