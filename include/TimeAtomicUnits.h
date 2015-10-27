/** @page timePage Describes The Time Tags

The time tags are used by both Metric and English Units of measurement.  Since it is used
by both libraries it is indepent of both.

*/
#ifndef TIMEATOMICUNITS_H_INCLUDE
#define TIMEATOMICUNITS_H_INCLUDE

namespace SystemOfUnits
{
   /// Namespace contains the tags used to identify time.
   namespace Time
   {
      namespace AtomicUnit
      {
         /// tag class for time.  Base Unit for time.
         struct second
         {
            enum { IsBase = true };
            typedef second Base;
            static char const * str() { return "second"; }
            static double toBase() { return 1.0; }
            static double fromBase() { return 1.0; }
         };
         /// tag class for time.
         struct minute
         {
            enum { IsBase = false };
            typedef second Base;
            static char const * str() { return "minute"; }
            static double toBase() { return 60.0; }
            static double fromBase() { return 1.0 / toBase(); }
         };
         /// tag clase for time.
         struct hour
         {
            enum { IsBase = false };
            typedef second Base;
            static char const * str() { return "hour"; }
            static double toBase() { return 60.0 * 60.0; }
            static double fromBase() { return 1.0 / toBase(); }
         };
      }
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

