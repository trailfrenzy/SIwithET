/** @page timePage Describes The Time Tags

The time tags are used by both Metric and English Units of measurement.  Since it is used
by both libraries it is indepent of both.

*/
#ifndef TIMEATOMICUNITS_H_INCLUDE
#define TIMEATOMICUNITS_H_INCLUDE
#include"Struct_Symbol.h"

namespace SystemOfUnits
{
   /// Namespace contains the tags used to identify time.
   ///  Currently non of the time in this file is associated with the time provided in the C++ std <chrono>.
   /// All times are based from the second and this does not stop a user from defining their own time types.
   namespace Time
   {
      /// Provides the symbol for dimensions.
      using TIME = helpers::SymbolForDimension<'T'>;

      namespace AtomicUnit
      {
         /// tag class for time.  Base Unit for time.
         struct second : TIME
         {
            enum:bool{ IsBase = true };
            typedef second Base;
            constexpr static char const * str() noexcept{ return "second"; }
            constexpr static double toBase() noexcept { return 1.0; }
            constexpr static double fromBase() noexcept { return 1.0; }
         };
         /// tag class for time.
         struct minute : TIME
         {
            enum:bool{ IsBase = false };
            typedef second Base;
            constexpr static char const * str() noexcept { return "minute"; }
            constexpr static double toBase() noexcept { return 60.0; }
            constexpr static double fromBase() noexcept { return 1.0 / toBase(); }
         };
         /// tag class for time.
         struct hour : TIME
         {
            enum:bool{ IsBase = false };
            typedef second Base;
            constexpr static char const * str() noexcept { return "hour"; }
            constexpr static double toBase() noexcept { return 60.0 * 60.0; }
            constexpr static double fromBase() noexcept { return 1.0 / toBase(); }
         };
      }
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