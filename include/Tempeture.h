#ifndef SOU_TEMPETURE_INCLUDE_H
#define SOU_TEMPETURE_INCLUDE_H

namespace SystemOfUnits 
{
   namespace Tempeture
   {
      struct kelvin
      {
         enum { IsBase = true }; /// Lets using classes know if class is used as a base.
         static char const * str() { return "kelvin"; }/// Called by WhatAmI when creating the string describing the type.
         static double toBase( double val) { return val; } 
         static double fromBase( double val) { return val; }
         //typedef Metric::AtomicUnit::Meter Base;/// Typedef of the actual base
      };

      struct celsius
      {
         enum { IsBase = false }; /// Lets using classes know if class is used as a base.
         static char const * str() { return "celsius"; }/// Called by WhatAmI when creating the string describing the type.
         static double toBase( double val ) { return val + 273.15; }
         static double fromBase( double val ) { return val - 273.15; }

         //typedef Metric::AtomicUnit::Meter Base;/// Typedef of the actual base 
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
