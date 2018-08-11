
#ifndef SI_WHATAMI_H_INCLUDE
#define SI_WHATAMI_H_INCLUDE
#pragma once
#include <string>
#include <sstream>
#include "SI.h"

/**
 @page page3 What am I

 @section WhatAmI()
 The function template provides a way to find out what the type is at run time.  It is
 used mainly for user debugging.

*/
namespace SystemOfUnits
{
   /// namespace used by classes and methods inside namespace SI
   namespace helpers
   {
      /// used by what am i
      /// @prama std::stringstream is used to create the return stream
      template< typename TYPE, int DIM > void printAtom( std::stringstream &ret )
      {
         if( DIM ) // value known at compile time
         {
            ret << TYPE::str();
            ret << '^';
            ret << DIM;
            ret << ' ';
         }
      }
   }

   /// method owned by the class which prints the type of class
   /// @prama SystemOfUnits::unitType
   /// @return std::string
   /// @note future work is to remove the blank space after each string.
   template< typename T >
   inline std::string WhatAmI( T )
   {
      std::stringstream buf;
      // use a template map to sort these later
      helpers::printAtom< T::Length, T::eL >( buf );
      helpers::printAtom< T::Time,   T::et >( buf );
      helpers::printAtom< T::Mass,   T::eM >( buf );
      helpers::printAtom< T::Tempeture, T::eT >( buf );
      helpers::printAtom< T::Charge, T::eQ >( buf );

      return buf.str().erase(buf.str().size() -1 ); // removes the last space char in the buffer
   }

   /// If user pushes a double into the template.
   template<> inline std::string WhatAmI(double) { return ""; }
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