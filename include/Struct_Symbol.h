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
      template< typename T > struct is_SymbolForDimension
          : std::integral_constant<bool, std::is_base_of< SystemOfUnits::helpers::Trait_SymbolForDimension, T >::value > {};

      enum :char unsigned { THETA = 233 }; // from www.asciitable.com
   }

   /// Base classes for the dimensions of the base units
   using Length          = helpers::SymbolForDimension<'L'>;
   using Mass            = helpers::SymbolForDimension<'M'>;
   using Time            = helpers::SymbolForDimension<'T'>;
   using Temperature     = helpers::SymbolForDimension< char(helpers::THETA) >;
   using ElectricCurrent = helpers::SymbolForDimension<'I'>;
   using Substance       = helpers::SymbolForDimension<'N'>;
   using Luminous        = helpers::SymbolForDimension<'J'>;
   using NO_DIM          = helpers::SymbolForDimension<' '>;

   // Contrait for one of the type Dimensions. The adjective dimensional refers to relating to the actual thing.
   template< typename T > concept Dimensional = helpers::is_SymbolForDimension<T>::value;

   template< Dimensional BASE_UNIT > struct is_Dimensionless : std::integral_constant<bool, BASE_UNIT::sym == ' ' >{};

   template< Dimensional BASE_UNIT > struct is_Length : std::integral_constant<bool, BASE_UNIT::sym == 'L' > {};

   template<Dimensional BASE_UNIT > struct is_Time : std::integral_constant<bool, BASE_UNIT::sym == 'T' > {};

   template<Dimensional BASE_UNIT > struct is_Mass : std::integral_constant<bool, BASE_UNIT::sym == 'M' > {};

   template<Dimensional BASE_UNIT > struct is_Temperature : std::integral_constant<bool, BASE_UNIT::sym == helpers::THETA > {};

   template<Dimensional BASE_UNIT > struct is_Current : std::integral_constant<bool, BASE_UNIT::sym == 'I' > {};

   template<Dimensional BASE_UNIT > struct is_Substance : std::integral_constant<bool, BASE_UNIT::sym == 'N' > {};

   template<Dimensional BASE_UNIT > struct is_Luminous : std::integral_constant<bool, BASE_UNIT::sym == 'J' > {};

   // Concepts used as the rules in building SI::Units

   template<typename T> concept Dimensionless = is_Dimensionless<T>::value;

   /// Constrait for Length to ensure only a Length type is passed for an arugment.
   template<typename T> concept LengthRule = is_Length<T>::value || Dimensionless<T>;

   /// Constrait for Time to ensure only a Time type is passed for an arugment.   Timeous is adjective of Time.
   template<typename T> concept TimeRule = is_Time<T>::value || Dimensionless<T>;

   /// Constrait for Mass to ensure only a Mass type is passed for an arugment.
   template<typename T> concept MassRule = is_Mass<T>::value || Dimensionless<T>;

   /// Constrait for Temperature to ensure only a Temperature type is passed for an arugment.
   template<typename T> concept TemperatureRule = is_Temperature<T>::value || Dimensionless<T>;

   /// Constrait for Current to ensure only a Current type is passed for an arugment.
   template<typename T> concept CurrentRule = is_Current<T>::value || Dimensionless<T>;

   /// Constrait for Substance to ensure only a Substance type is passed for an arugment.
   template<typename T> concept SubstanceRule = is_Substance<T>::value || Dimensionless<T>;

   /// Constrait for Luminous to ensure only a Luminous type is passed for an arugment.
   template<typename T> concept LuminousRule = is_Luminous<T>::value || Dimensionless<T>;

   /// Used as the base class for UnitTypes for use in the identity template.
   struct TraitUnit {};
}
#endif

// Copyright © 2005-2023 "Curt" Leslie L. Martin, All rights reserved.
// curt.leslie.lewis.martin@gmail.com
//
// Permission to use, copy, modify, and distribute this software for any
// purpose is hereby granted without fee, provided that this copyright and
// permissions notice appear in all copies and derivatives.
//
// This software is provided "as is" without express or implied warranty.
