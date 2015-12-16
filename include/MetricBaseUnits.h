
#ifndef METRICBASEUNITS_H_INCLUDE
#define METRICBASEUNITS_H_INCLUDE
#pragma once
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
      struct Meter /// @anchor repesent quantity length of a meter.
      {
         enum { IsBase = true };/// Lets using classes know if class is used as a base.
         static char const * str() { return "meter"; }/// Called by WhatAmI when creating the string describing the type.
         static double toBase() { return 1.0; }///  Multiply by toBase() to get base value.
         static double fromBase() { return 1.0; }/// Multiply by fromBase() to get diminsional value.
         typedef Meter Base;/// Typedef of the actual base
      };
      struct Kilometer /// represents quantity length of a kilometer
      {
         enum { IsBase = false };/// Lets using classes know if class is used as a base.
         static char const * str() { return "kilometer"; }/// Called by WhatAmI when creating the string describing the type.
         ///  Multiply by toBase() to get base value.
         static double toBase() { return 1000.0; } // ex meter = kilometer * toBase();
         static double fromBase() { return 1.0 / toBase(); }/// Multiply by fromBase() to get diminsional value.
         typedef Meter Base;/// Typedef of the actual base
      };
      struct Centimeter /// represents quantity length of a centimeter
      {
         enum { IsBase = false };/// Lets using classes know if class is used as a base.
         static char const * str() { return "centimeter"; }/// Called by WhatAmI when creating the string describing the type.
         static double fromBase() { return 100.0; }/// Multiply by fromBase() to get diminsional value.
         // ex meter = centimeter * toBase();
         static double toBase() { return 1.0/100.0; }///  Multiply by toBase() to get base value.
         typedef Meter Base;/// Typedef of the actual base
      };
      struct Milimeter /// represents quantity length of a milimeter
      {
         enum { IsBase = false };/// Lets using classes know if class is used as a base.
         static char const * str() { return "milimeter";}/// Called by WhatAmI when creating the string describing the type.
         static double fromBase() { return 1000.0; }/// Multiply by fromBase() to get diminsional value.
         static double toBase() { return 1.0/fromBase(); }///  Multiply by toBase() to get base value.
         typedef Meter Base;/// Typedef of the actual base
      };

      struct gram /// represents quantity mass of a gram
      {
         enum { IsBase = true };/// Lets using classes know if class is used as a base.
         static char const * str() { return "gram"; }/// Called by WhatAmI when creating the string describing the type.
         static double toBase() { return 1.0; }///  Multiply by toBase() to get base value.
         static double fromBase() { return 1.0; }/// Multiply by fromBase() to get diminsional value.
         typedef gram Base;/// Typedef of the actual base
      };
      struct kilogram /// represents quantity mass of a kilogram.
      {
         enum { IsBase = false };/// Lets using classes know if class is used as a base.
         static char const * str() { return "kilogram"; }/// Called by WhatAmI when creating the string describing the type.
         static double toBase() { return 1000.0; }///  Multiply by toBase() to get base value.
         static double fromBase() { return 1.0 / toBase() ; }/// Multiply by fromBase() to get diminsional value.
         typedef gram Base;/// Typedef of the actual base
      };
      struct miligram /// represents quantity mass of miligram.
      {
         enum { IsBase = false };/// Lets using classes know if class is used as a base.
         static char const * str() { return "miligram"; }/// Called by WhatAmI when creating the string describing the type.
         static double toBase() { return 1.0 / fromBase(); }///  Multiply by toBase() to get base value.
         static double fromBase() { return 1000.0; }/// Multiply by fromBase() to get diminsional value.
         typedef gram Base;/// Typedef of the actual base
      };
      struct kelvin /// represents quantity tempeture of kelvin
      {
         enum { IsBase = true };/// Lets using classes know if class is used as a base.
         static char const * str() { return "Kelvin"; }/// Called by WhatAmI when creating the string describing the type.
         static double toBase() { return 1.0; }///  Multiply by toBase() to get base value.
         static double fromBase() { return 1.0; }/// Multiply by fromBase() to get diminsional value.
         typedef kelvin Base;/// Typedef of the actual base
      };
      /// @warning Do not use
      struct celsius /// represents quanity tempeture celsius. NOT AVAILBE FOR USE.
      {
         enum { IsBase = false };/// Lets using classes know if class is used as a base.
         static char const * str() { return "Celsius"; }/// Called by WhatAmI when creating the string describing the type.
         // currently only kelvin is the only tempeture offered in compound
         static double toBase( double C )   { return C + 273.15; }///  Multiply by toBase() to get base value.
         static double fromBase( double K ) { return K - 273.15; }/// Multiply by fromBase() to get diminsional value.
      };

      struct coulomb /// represents quantity charge coulomb.
      {
         enum{ IsBase = true };/// Lets using classes know if class is used as a base.
         static char const * str() { return "coulomb"; }/// Called by WhatAmI when creating the string describing the type.
         static double toBase() { return 1.0; }///  Multiply by toBase() to get base value.
         static double fromBase() { return 1.0; }/// Multiply by fromBase() to get diminsional value.
         typedef coulomb Base;/// Typedef of the actual base
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