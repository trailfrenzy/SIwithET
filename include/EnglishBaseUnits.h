/// Contains basic elements used to describe the English measurment system.
#ifndef ENGLISHBASEUNITS_H_INCLUDE
#define ENGLISHBASEUNITS_H_INCLUDE
#pragma once
#include "MetricBaseUnits.h"  /// metric is the base for all conversions

namespace English /// namespace than contains the English unit types.
{
   namespace AtomicUnit /// namespace of the quantity types
   {
      struct Foot : Metric::AtomicUnit::LENGTH/// repesent quantity length of a foot.
      {
         enum { IsBase = false }; /// Lets using classes know if class is used as a base.
         constexpr static char const * str() { return "foot"; }/// Called by WhatAmI when creating the string describing the type.
         constexpr static double toBase() { return 0.3048; }///  Multiply by toBase() to get base value.
         constexpr static double fromBase() { return 1.0/toBase(); }/// Multiply by fromBase() to get diminsional value.
         typedef Metric::AtomicUnit::Meter Base;/// Typedef of the actual base
      };

      struct Inch : Metric::AtomicUnit::LENGTH/// represents the quantity length of an inch
      {
         enum { IsBase = false }; /// Lets using classes know if class is used as a base
         constexpr static char const * str() { return "inch"; }/// Called by WhatAmI when creating the string describing the type.
         constexpr static double toBase() { return Foot::toBase() / 12.0; }///  Multiply by toBase() to get base value.
         constexpr static double fromBase() { return 1.0/toBase(); }/// Multiply by fromBase() to get diminsional value
         typedef Metric::AtomicUnit::Meter Base;/// Typedef of the actual base
      };

      struct Yard : Metric::AtomicUnit::LENGTH /// represents the quantity length of an yard
      {
         enum { IsBase = false }; /// Lets using classes know if class is used as a base
         constexpr static char const * str() { return "yard"; }/// Called by WhatAmI when creating the string describing the type.
         constexpr static double toBase() { return Foot::toBase() * 3.0; }///  Multiply by toBase() to get base value.
         constexpr static double fromBase() { return 1.0/toBase(); }/// Multiply by fromBase() to get diminsional value
         typedef Metric::AtomicUnit::Meter Base;/// Typedef of the actual base
      };

      struct Mile : Metric::AtomicUnit::LENGTH /// represents the quantity length of a mile
      {
         enum { IsBase = false }; /// Lets using classes know if class is used as a base
         constexpr static char const * str() { return "mile"; }/// Called by WhatAmI when creating the string describing the type.
         constexpr static double toBase() { return 440.0 * 4.0 * Yard::toBase(); }///  Multiply by toBase() to get base value.
         constexpr static double fromBase() { return 1.0/toBase(); }/// Multiply by fromBase() to get diminsional value
         typedef Metric::AtomicUnit::Meter Base;/// Typedef of the actual base
      };

      /** represents the quantity wieght of a pound.  Note that this is not the same as
      a pound force. */
      struct poundMass : Metric::AtomicUnit::MASS
      {
         enum { IsBase = false }; /// Lets using classes know if class is used as a base
         constexpr static char const * str() { return "lbm"; }/// Called by WhatAmI when creating the string describing the type.
         constexpr static double toBase() { return 0.4536; }///  Multiply by toBase() to get base value.
         constexpr static double fromBase() { return 1.0/toBase(); }/// Multiply by fromBase() to get diminsional value
         typedef Metric::AtomicUnit::gram Base;/// Typedef of the actual base
      };

      struct Slug : Metric::AtomicUnit::MASS /// represents the quantity wight of a slug
      {
         enum { IsBase = false }; /// Lets using classes know if class is used as a base
         constexpr static char const * str() { return "slug"; }/// Called by WhatAmI when creating the string describing the type.
         constexpr static double toBase() { return 32.174 * poundMass::toBase(); }///  Multiply by toBase() to get base value.
         constexpr static double fromBase() { return 1.0/toBase(); }/// Multiply by fromBase() to get diminsional value
         typedef Metric::AtomicUnit::gram Base;/// Typedef of the actual base
      };
   }
}

#endif
// Copyright © 2005-2015 "Curt" Leslie L. Martin, All rights reserved.
// curt.leslie.lewis.martin@gmail.com
//
// Permission to use, copy, modify, and distribute this software for any
// purpose is hereby granted without fee, provided that this copyright and
// permissions notice appear in all copies and derivatives.
//
// This software is provided "as is" without express or implied warranty.
