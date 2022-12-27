#pragma once
#ifndef SOI_DIMENSION_INCLUDE_H
#define SOI_DIMENSION_INCLUDE_H
#include "list.hpp"
#include "Struct_Symbol.h"
#include "SI.h"
#include <string>

namespace SystemOfUnits
{
   namespace helpers
   {
      /// Solidus is the name of the slash
      using SOLIDUS = SystemOfUnits::helpers::SymbolForDimension<'/'>;

      struct base_SingleDim {};

      template< Dimensional T, int D, typename char_type = char > 
      struct t_SingleDim : public base_SingleDim
      {
         using t_BaseUnit = T;
         enum:int { DIM = D };
         enum:char unsigned { CHAR = t_BaseUnit::sym };
         using Tstring = typename std::basic_string<char_type>;

         /// Produces a string of a dimension and absolute.
         static auto c_str() noexcept(noexcept(Tstring() ) && noexcept(t_BaseUnit))-> Tstring
         {
            if constexpr (CHAR == SOLIDUS::sym) { return { CHAR }; }
            else if constexpr (DIM == 0) { return {}; } // if DIM==0 then its is dimensionless.
            else if constexpr (DIM == 1 || DIM == -1) 
            {
               return { '[', static_cast<char_type>(CHAR) ,']' };
            }
            else // greater than one add a '^' carrot
            {
               enum { absDIM = (DIM < 0) ? -1 * DIM : DIM };
               return { '[', CHAR, ']', '^', '0' + absDIM };
            }
         }
      };

      /// Added to the sorted List to display.
      using t_SingleSolidus = t_SingleDim< SOLIDUS, 0 >;

      template< typename T >
      struct is_SingleDim
      {
         constexpr static bool value = std::is_base_of< base_SingleDim, T > ::value;
      };

      template<typename T> concept SingleDimRule = is_SingleDim<T>::value;

   } // end of namespace helpers

   /// Used in sorting the dimensions below.
   template <helpers::SingleDimRule a, helpers::SingleDimRule b>
   struct ORD {
      enum :bool { VALUE = a::DIM > b::DIM };
   };

   template< UnitSpecies T > 
   inline std::string Dim(T const )
   {
       static_assert(SystemOfUnits::is_UnitType<T>::value, "Why is this not true! The concept failed");

      if constexpr (T::isZeroDimensions()) return ""; // no dim, bale out fast!
      else
      {
         using SystemOfUnits::helpers::t_SingleDim;
         using TYPE = T;

         using t_SingleLen = t_SingleDim< typename TYPE::Length, TYPE::eL>;
         using t_SingleTime = t_SingleDim< typename TYPE::Time, TYPE::et>;
         using t_SingleMass = t_SingleDim< typename TYPE::Mass, TYPE::eM>;
         using t_SingleCharge = t_SingleDim< typename TYPE::Charge, TYPE::eQ >;
         using t_SingleTemp = t_SingleDim< typename TYPE::Temperature, TYPE::eT>;

         using t_List = Meta::LIST6< t_SingleLen,  t_SingleTime,  t_SingleMass,  t_SingleTemp,  t_SingleCharge, helpers::t_SingleSolidus >::TYPE;

         using t_Sorted = typename Meta::SORT<ORD, t_List >::TYPE;
         
         using DIM0 = typename Meta::At<  t_Sorted, 0 >::RET;
         using DIM1 = typename Meta::At<  t_Sorted, 1 >::RET;
         using DIM2 = typename Meta::At<  t_Sorted, 2 >::RET;
         using DIM3 = typename Meta::At<  t_Sorted, 3 >::RET;
         using DIM4 = typename Meta::At<  t_Sorted, 4 >::RET;
         using DIM5 = typename Meta::At<  t_Sorted, 5 >::RET;

         enum :bool { isFrontNeg = DIM0::DIM <= 0, isLastNeg = DIM5::DIM < 0 };

         std::string retStr;

         if constexpr (isFrontNeg)
         {
             retStr += '1';
             retStr += DIM0::c_str();
             retStr += DIM1::c_str();
             retStr += DIM2::c_str();
             retStr += DIM3::c_str();
             retStr += DIM4::c_str();
             retStr += DIM5::c_str();
         }
         else if constexpr (not isFrontNeg and isLastNeg)
         {
             // has a '\' Solidus in string
             retStr += DIM0::c_str();
             retStr += DIM1::c_str();
             retStr += DIM2::c_str();
             retStr += DIM3::c_str();
             retStr += DIM4::c_str();
             retStr += DIM5::c_str();
         }
         else
         {
             // No '/' Solidus in the string.
             retStr += DIM0::c_str();
             if constexpr (DIM1::DIM ) retStr += DIM1::c_str();
             if constexpr (DIM2::DIM )retStr += DIM2::c_str();
             if constexpr (DIM3::DIM )retStr += DIM3::c_str();
             if constexpr (DIM4::DIM )retStr += DIM4::c_str();
             if constexpr (DIM5::DIM )retStr += DIM5::c_str();
         }
         return retStr;
      }
   };


}
#endif // !SOI_DIMENSION_INCLUDE_H

// Copyright © 2005-2022 "Curt" Leslie L. Martin, All rights reserved.
// curt.leslie.lewis.martin@gmail.com
//
// Permission to use, copy, modify, and distribute this software for any
// purpose is hereby granted without fee, provided that this copyright and
// permissions notice appear in all copies and derivatives.
//
// This software is provided "as is" without express or implied warranty.
