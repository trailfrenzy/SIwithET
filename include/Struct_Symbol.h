// Struct supports the dimensional function. Used internally, not for use outside of SOU.
/// File contains the consepts used to define a SI::Units
#ifndef SYSTEM_OF_UNITS_HELPERS_STRUCT_T_SYMBOL_H
#define SYSTEM_OF_UNITS_HELPERS_STRUCT_T_SYMBOL_H

#include <concepts>

namespace SystemOfUnits {
   namespace helpers
   {
      /**
      @page 6 Dimensions of quantities.
      Physical quantities can be organized in a system of dimensions, where the system used is
      decided by convention. Each of the seven base quantities used in the SI is regarded as
      having its own dimension. The symbols used for the base quantities and the symbols used
      to denote their dimension are represented by the class template below..

      SymbolForDimension is the base class for all the Base Types used in building a UnitType.
      Pass the dimension as a single letter as the template argument. The single letter is represent the base unit diminsion.
      Use the typical symbol found from https://www.bipm.org/en/measurement-units/ "The International System of Units(SI), 9th edition 2019, pg 136 section 2.3.3, Table 3.

      All other quantities, with the exception of counts, are derived quantities, which may be
      written in terms of base quantities according to the equations of physics. The dimensions of
      the derived quantities are written as products of powers of the dimensions of the base
      quantities using the equations that relate the derived quantities to the base quantities.
      In general the dimension of any quantity Q is written in the form of a dimensional product,

                  dim Q = T^α L^β M^γ I^δ Θ^ε N^ζ J^η
      */
      template<unsigned char C > struct SymbolForDimension
      {
         enum :char unsigned { sym = C };  /// used on the input of template OneDim<>

         // ideally the function is used by the sorting template and its output.  Currently not used.
         template<typename t_char = char>
         constexpr static inline auto Symstr() noexcept-> t_char const*
         {
            // creation of a static character string array.
            constexpr t_char static str[] = { '[', sym ,']', '\0' };
            return str;
         }
      };
   }

   template< typename BASE_UNIT > struct is_LENGTH
   {
      //enum :bool { value = BASE_UNIT::sym == 'L' || BASE_UNIT::sym == ' ' };
      constexpr static bool value = BASE_UNIT::sym == 'L' || BASE_UNIT::sym == ' ';
   };

   template<typename BASE_UNIT > struct is_TIME
   {
      //enum:bool{ value = BASE_UNIT::sym == 'T' || BASE_UNIT::sym == ' ' };
      constexpr static bool value = BASE_UNIT::sym == 'T' || BASE_UNIT::sym == ' ';
   };

   template<typename BASE_UNIT > struct is_MASS
   {
      //enum :bool { value = BASE_UNIT::sym == 'M' || BASE_UNIT::sym == ' ' };
      constexpr static bool value = BASE_UNIT::sym == 'M' || BASE_UNIT::sym == ' ';
   };

   template<typename BASE_UNIT > struct is_TEMPERATURE
   {
      //enum :bool { value = BASE_UNIT::sym == 233 || BASE_UNIT::sym == ' ' };
      constexpr static bool value = BASE_UNIT::sym == 233 || BASE_UNIT::sym == ' ';
   };

   template<typename BASE_UNIT > struct is_CURRENT
   {
      //enum :bool { value = BASE_UNIT::sym == 'A' || BASE_UNIT::sym == ' ' };
      constexpr static bool value = BASE_UNIT::sym == 'A' || BASE_UNIT::sym == ' ';
   };

   // Concepts used as the rules in building SI::Units

   /// Constrait for Length to ensure only a Length type is passed for an arugment.
   template<typename T> concept LENGTH = is_LENGTH<T>::value && sizeof(T) == 1;

   /// Constrait for Time to ensure only a Time type is passed for an arugment.
   template<typename T> concept TIME = is_TIME<T>::value && sizeof(T) == 1;

   /// Constrait for Mass to ensure only a Mass type is passed for an arugment.
   template<typename T> concept MASS = is_MASS<T>::value && sizeof(T) == 1;

   /// Constrait for Temperature to ensure only a Temperature type is passed for an arugment.
   template<typename T> concept TEMPERATURE = is_TEMPERATURE<T>::value && sizeof(T) == 1;

   /// Constrait for Current to ensure only a Current type is passed for an arugment.
   template<typename T> concept CURRENT = is_CURRENT<T>::value && sizeof(T) == 1;

}
#endif

// Copyright © 2005-2020 "Curt" Leslie L. Martin, All rights reserved.
// curt.leslie.lewis.martin@gmail.com
//
// Permission to use, copy, modify, and distribute this software for any
// purpose is hereby granted without fee, provided that this copyright and
// permissions notice appear in all copies and derivatives.
//
// This software is provided "as is" without express or implied warranty.
