// Struct supports the dimensional function. Used internally, not for use outside of SOU.
/// File contains the consepts used to define a SI::Units
#ifndef SYSTEM_OF_UNITS_HELPERS_STRUCT_T_SYMBOL_H
#define SYSTEM_OF_UNITS_HELPERS_STRUCT_T_SYMBOL_H

#include <concepts>
#include <type_traits>

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

      Physical quantities can be organized in a system of dimensions, where the system used is
      decided by convention. Each of the seven base quantities used in the SI is regarded as
      having its own dimension. The symbols used for the base quantities and the symbols used
      to denote their dimension are shown in Table 3.
      Table 3. Base quantities and dimensions used in the SI
      _____________________________________________________________________________
      Base quantity Typical symbol for quantity Symbol for dimension
      _____________________________________________________________________________
      time                       t              T
      length                     l, x, r, etc.  L
      mass                       m              M
      electric current           I, i           I
      thermodynamic temperature  T              Θ
      amount of substance        n              N
      luminous intensity         Iv             J
      _____________________________________________________________________________

      All other quantities, with the exception of counts, are derived quantities, which may be
      written in terms of base quantities according to the equations of physics. The dimensions of
      the derived quantities are written as products of powers of the dimensions of the base
      quantities using the equations that relate the derived quantities to the base quantities.
      In general the dimension of any quantity Q is written in the form of a dimensional product,

                  dim Q = T^α L^β M^γ I^δ Θ^ε N^ζ J^η
      */

      struct Trait_SymbolForDimension {}; // exists only for use in the concept below.
      template<unsigned char C > struct SymbolForDimension : public Trait_SymbolForDimension
      {
         constexpr static char unsigned sym = C;

         // ideally the function is used by the sorting template and its output.  Currently not used.
         template<typename t_char = char>
         constexpr static inline auto Symstr() noexcept-> t_char const*
         {
            // creation of a static character string array.
            constexpr t_char static str[] = { '[', sym ,']', '\0' };
            return str;
         }
      };

      /**
      For example to use set up a dimension:
      @code using ELECTRIC_CURRENT = SystemOfUnits::helpers::SymbolForDimension<'C'>;       @endcode

      These base dimensions are already established in the library.
      */

      /// <summary>
      /// Uses the Trait to verify if template paramater is actually a SymbolForDimension type.
      /// </summary>
      /// <typeparam name="T"></typeparam>
      template< typename T > struct is_SymbolForDimension // : public std::false_type {};
      {
         constexpr static bool value = std::is_base_of< SystemOfUnits::helpers::Trait_SymbolForDimension, T > ::value;
      };
   }

   enum:char unsigned { THETA = 233 }; // from www.asciitable.com
   /// Base classes for the dimensions of the base units
   using Length          = helpers::SymbolForDimension<'L'>;
   using Mass            = helpers::SymbolForDimension<'M'>;
   using Time            = helpers::SymbolForDimension<'T'>;
   using Temperature     = helpers::SymbolForDimension< char(THETA) >;
   using ElectricCurrent = helpers::SymbolForDimension<'C'>;
   using NO_DIM          = helpers::SymbolForDimension<' '>;

   // Contrait for one of the type Dimensions.
   template< typename T > concept DIMENSION = helpers::is_SymbolForDimension<T>::value;

   template< DIMENSION BASE_UNIT > struct is_Dimensionless
   {
      constexpr static bool value = BASE_UNIT::sym == ' ';
   };

   template< DIMENSION BASE_UNIT > struct is_LENGTH //: std::is_integral<bool, std::is_base_of< SystemOfUnits::helpers::SymbolForDimension<'L'>, T>::value >::value;
   {
      constexpr static bool value = BASE_UNIT::sym == 'L';
   };

   template<DIMENSION BASE_UNIT > struct is_TIME
   {
      constexpr static bool value = BASE_UNIT::sym == 'T';
   };

   template<DIMENSION BASE_UNIT > struct is_MASS
   {
      constexpr static bool value = BASE_UNIT::sym == 'M';
   };

   template<DIMENSION BASE_UNIT > struct is_TEMPERATURE
   {
      constexpr static bool value = BASE_UNIT::sym == THETA;
   };

   template<DIMENSION BASE_UNIT > struct is_CURRENT
   {
      constexpr static bool value = BASE_UNIT::sym == 'C';
   };

   // Concepts used as the rules in building SI::Units

   template<typename T> concept Dimensionless = is_Dimensionless<T>::value;

   /// Constrait for Length to ensure only a Length type is passed for an arugment.
   template<typename T> concept LENGTH = is_LENGTH<T>::value || Dimensionless<T>;

   /// Constrait for Time to ensure only a Time type is passed for an arugment.
   template<typename T> concept TIME = is_TIME<T>::value || Dimensionless<T>;

   /// Constrait for Mass to ensure only a Mass type is passed for an arugment.
   template<typename T> concept MASS = is_MASS<T>::value || Dimensionless<T>;

   /// Constrait for Temperature to ensure only a Temperature type is passed for an arugment.
   template<typename T> concept TEMPERATURE = is_TEMPERATURE<T>::value || Dimensionless<T>;

   /// Constrait for Current to ensure only a Current type is passed for an arugment.
   template<typename T> concept CURRENT = is_CURRENT<T>::value || Dimensionless<T>;

   /// Used as the base class for UnitTypes for use in the identity template.
   struct Trait_Unit {};
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
