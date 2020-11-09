/**
	The purpose of the this class is to provide a compile time raise to the power of E during
	compile time.  E can only be an integer type.
	Intended to only be used by conversion_cast<> template function and not intended for outside users or
	functions.
   EXAMPLE:
	The following is an example on how to use:
	SI::P< IN::Length >::thePower<eL>::toBase()
*/
#ifndef POWER_TEMPLATE_H_INCLUDE
#define POWER_TEMPLATE_H_INCLUDE
#pragma once

#include "template_help.h"
#include "Struct_Symbol.h"

namespace SystemOfUnits
{
   /// namespace helpers is not intended to be used outside of namespace SystemOfUnits
   namespace helpers
   {
      /// container struct that contains the nested structs.
      template< Dimensional T> struct P
      {
         /// forward declaration of the struct.
         template< int E > struct thePower;

         /// specialized version when the power is 1.
         template<> struct thePower<1>
         {
            constexpr static double toBase() noexcept( noexcept(T))
            {
               return T::toBase();
            }
         };

         /// specialized class when the power is 0.
         template<> struct thePower<0>
         {
            constexpr static double toBase() noexcept
            {
               return 1.0;
            }
         };

         /// specialized class when the power is -1.
         template<> struct thePower<-1>
         {
            constexpr static double toBase() noexcept(noexcept(T))
            {
               return 1.0 / T::toBase();
            }
         };

         /// the generic version the struct. must be after the specialized versions.
         template< int E > struct thePower
         {
            constexpr static double toBase()noexcept(noexcept(T))
            {
               // it is safe to assume that E will be greater than +1 or 
               // less than -1 and not between
               return IF< (E > 0), thePower< E-1 >, thePower< E+1 > >::RET::toBase()
                  * IF< (E > 0), thePower< 1>, thePower<-1> >::RET::toBase();
            }
         };

      }; // end of class P
   }
} // end of namespace SI

// Copyright © 2005-2019 "Curt" Leslie L. Martin, All rights reserved.
// curt.leslie.lewis.martin@gmail.com
//
// Permission to use, copy, modify, and distribute this software for any
// purpose is hereby granted without fee, provided that this copyright and
// permissions notice appear in all copies and derivatives.
//
// This software is provided "as is" without express or implied warranty.

#endif