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
         enum { IsBase = true };/// Lets using classes know if class is used as a base.
         constexpr static char const * str() noexcept { return "meter"; }/// Called by WhatAmI when creating the string describing the type.
         constexpr static double toBase() noexcept { return 1.0; }///  Multiply by toBase() to get base value.
         constexpr static double fromBase() noexcept { return 1.0; }/// Multiply by fromBase() to get diminsional value.
         typedef Meter Base;/// Typedef of the actual base
      };
      struct Kilometer : LENGTH /// represents quantity length of a kilometer
      {
         enum { IsBase = false };/// Lets using classes know if class is used as a base.
         constexpr static char const * str() noexcept { return "kilometer"; }/// Called by WhatAmI when creating the string describing the type.
         ///  Multiply by toBase() to get base value.
         constexpr static double toBase() noexcept { return 1000.0; } // ex meter = kilometer * toBase();
         constexpr static double fromBase() noexcept { return 1.0 / toBase(); }/// Multiply by fromBase() to get diminsional value.
         typedef Meter Base;/// Typedef of the actual base
      };
      struct Centimeter : LENGTH /// represents quantity length of a centimeter
      {
         enum { IsBase = false };/// Lets using classes know if class is used as a base.
         constexpr static char const * str() noexcept { return "centimeter"; }/// Called by WhatAmI when creating the string describing the type.
         constexpr static double fromBase() noexcept { return 100.0; }/// Multiply by fromBase() to get diminsional value.
         // ex meter = centimeter * toBase();
         constexpr static double toBase() noexcept { return 1.0/100.0; }///  Multiply by toBase() to get base value.
         typedef Meter Base;/// Typedef of the actual base
      };
      struct Milimeter : LENGTH /// represents quantity length of a milimeter
      {
         enum { IsBase = false };/// Lets using classes know if class is used as a base.
         constexpr static char const * str() noexcept { return "milimeter";}/// Called by WhatAmI when creating the string describing the type.
         constexpr static double fromBase() noexcept { return 1000.0; }/// Multiply by fromBase() to get diminsional value.
         constexpr static double toBase() noexcept { return 1.0/fromBase(); }///  Multiply by toBase() to get base value.
         typedef Meter Base;/// Typedef of the actual base
      };

      using MASS = SystemOfUnits::helpers::T_Symbol<'M'>;
      struct gram : MASS /// represents quantity mass of a gram
      {
         enum { IsBase = true };/// Lets using classes know if class is used as a base.
         constexpr static char const * str() noexcept { return "gram"; }/// Called by WhatAmI when creating the string describing the type.
         constexpr static double toBase() noexcept { return 1.0; }///  Multiply by toBase() to get base value.
         constexpr static double fromBase() noexcept { return 1.0; }/// Multiply by fromBase() to get diminsional value.
         typedef gram Base;/// Typedef of the actual base
      };
      struct kilogram : MASS /// represents quantity mass of a kilogram.
      {
         enum { IsBase = false };/// Lets using classes know if class is used as a base.
         constexpr static char const * str() noexcept { return "kilogram"; }/// Called by WhatAmI when creating the string describing the type.
         constexpr static double toBase() noexcept { return 1000.0; }///  Multiply by toBase() to get base value.
         constexpr static double fromBase() noexcept { return 1.0 / toBase() ; }/// Multiply by fromBase() to get diminsional value.
         typedef gram Base;/// Typedef of the actual base
      };
      struct miligram : MASS /// represents quantity mass of miligram.
      {
         enum { IsBase = false };/// Lets using classes know if class is used as a base.
         constexpr static char const * str() noexcept { return "miligram"; }/// Called by WhatAmI when creating the string describing the type.
         constexpr static double toBase() noexcept { return 1.0 / fromBase(); }///  Multiply by toBase() to get base value.
         constexpr static double fromBase() noexcept { return 1000.0; }/// Multiply by fromBase() to get diminsional value.
         typedef gram Base;/// Typedef of the actual base
      };

      enum { THETA = 233 }; // from www.asciitable.com
      using TEMPERATURE = SystemOfUnits::helpers::T_Symbol< char(THETA) >;

      struct kelvin : TEMPERATURE /// represents quantity tempeture of kelvin
      {
         enum { IsBase = true };/// Lets using classes know if class is used as a base.
         constexpr static char const * str() noexcept { return "Kelvin"; }/// Called by WhatAmI when creating the string describing the type.
         constexpr static double toBase(double val) noexcept { return val; }
         constexpr static double fromBase(double val) noexcept { return val; }
		 typedef kelvin Base;/// Typedef of the actual base
      };
      /// @warning Do not use
      struct celsius : TEMPERATURE/// represents quanity tempeture celsius.
      {
         enum { IsBase = false };/// Lets using classes know if class is used as a base.
         constexpr static char const * str()  noexcept { return "°C"; }/// Called by WhatAmI when creating the string describing the type.
         // currently only kelvin is the only tempeture offered in compound
         constexpr static double toBase( double C ) noexcept { return C + 273.15; }///  Multiply by toBase() to get base value.
         constexpr static double fromBase( double K ) noexcept { return K - 273.15; }/// Multiply by fromBase() to get diminsional value.
		 using Base = kelvin;
      };

      using CHARGE = SystemOfUnits::helpers::T_Symbol<'Q'>;
      struct coulomb : CHARGE /// represents quantity charge coulomb.
      {
         enum{ IsBase = true };/// Lets using classes know if class is used as a base.
         constexpr static char const * str() noexcept { return "coulomb"; }/// Called by WhatAmI when creating the string describing the type.
         constexpr static double toBase() noexcept { return 1.0; }///  Multiply by toBase() to get base value.
         constexpr static double fromBase() noexcept { return 1.0; }/// Multiply by fromBase() to get diminsional value.
         typedef coulomb Base;/// Typedef of the actual base
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