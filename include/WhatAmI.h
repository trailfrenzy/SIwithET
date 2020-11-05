#ifndef SI_WHATAMI_H_INCLUDE
#define SI_WHATAMI_H_INCLUDE
#pragma once
#include <string>
#include <sstream>
#include "SI.h"
#include"Struct_Symbol.h"
#include "list.hpp"

/**
 @page page3 What am I

 @section WhatAmI()
 The function template provides a way to find out what the type is at run time.  It is
 used mainly for user debugging.  Most of the work to produce the result of WhatAmI() is
 completed at compile time. Only the connecting the strings is did at run time.

*/
namespace SystemOfUnits
{
   /// namespace used by classes and methods inside namespace SI
   namespace helpers
   {
      /// used by what am i
      /// @prama std::stringstream is used to create the return stream
      //template< typename TYPE, int DIM > void printAtom( std::ostringstream &ret )
      template< DIMENSION TYPE, int DIM, typename TOUT > void printAtom(TOUT &ret)
         noexcept( noexcept(TOUT) && noexcept(TYPE))
      {
         if constexpr( DIM != 0) // value known at compile time
         {
            ret << TYPE::str();
   			if constexpr (DIM > 1)
            {
               ret << '^' << DIM;
			   }
            if constexpr (DIM < 0)
            {
               ret << "^(" << DIM << ')';
            }

            ret << '*'; // need to remove if last DIM
         }
      }
   }

   /// method owned by the class which prints the type of class
   /// @prama SystemOfUnits::unitType
   /// @return std::string
   /// @note future work is to remove the blank space after each string.
   template< typename char_type, typename T >
   inline auto UnitName( T const & )
      noexcept(noexcept(std::basic_ostringstream<char_type>) && noexcept(T) )
   {
      if constexpr (is_CoherentUnit<T>::value) return std::basic_string<char_type>{T::unitName()};
      if constexpr (!is_UnitType<T>::value) return std::basic_string<char_type>{};
      else
      {
         std::basic_ostringstream<char_type> buf;

         // use a template map to sort these later
         helpers::printAtom< T::Length, T::eL >(buf);
         helpers::printAtom< T::Time, T::et >(buf);
         helpers::printAtom< T::Mass, T::eM >(buf);
         helpers::printAtom< T::Temperature, T::eT >(buf);
         helpers::printAtom< T::Charge, T::eQ >(buf);

         return buf.str().erase(buf.str().size() - 1); // removes the last space char in the buffer
      }
   }

   /// Returns in std::string what the type the UnitType is.
   template< typename T > inline std::string WhatAmI(T const &val)
   {
      using t_char = std::ostringstream::char_type;
      return UnitName<t_char>(val);
   }

   namespace helpers
   {
      /// The pair stringstream is used to make the first numerator and second denominator in dimensions.
	   using t_bufPair = std::pair< std::ostringstream, std::ostringstream >;
	   enum { THETA = 233 }; // from www.asciitable.com

      template < char C, int T, typename T_BufPair > inline auto& OneDim(T_BufPair &buf)
         noexcept( noexcept(t_bufPair::first_type)&&noexcept(t_bufPair::second_type) )
      {
         // only the numerator or denomitator is used not both, if ZERO then none are used.
         if constexpr (T > 0) {
            buf.first << '[' << C << ']';
            if (T > 1) buf.first << '^' << T;
         }
         if constexpr (T < 0) {
            buf.second << '[' << C << ']';
            if (T < -1) buf.second << '^' << abs(T);
         }
         return buf;
      }
   }

   /**
    @page page4 Diminsion

    @section Diminsion
    The function template provides a string of the UnitType's dimensions.  As in
    a meter is [L] and a kilogram is a [M].  Most of the work of producing the 
    result is completed at compile time.
   */
   template< typename char_type, typename T >
   inline auto t_Diminsion(T const &) -> std::basic_string<char_type>
   {
      if constexpr (!is_UnitType<T>::value) return {}; // not a UnitType bale and get out.

      else if constexpr(!T::eL && !T::eM && !T::et && !T::eT && !T::eQ) return {}; // no dim, bale out fast!
      else
      {
         std::pair< std::basic_ostringstream<char_type>, std::basic_ostringstream<char_type> > buf;

         using namespace helpers;
         if constexpr (0 != T::eL) OneDim<T::Length::sym, T::eL >(buf);
         if constexpr (0 != T::eM) OneDim<T::Mass::sym, T::eM >(buf);
         if constexpr (0 != T::et) OneDim<T::Time::sym, T::et >(buf);
         if constexpr (0 != T::eT) OneDim<T::Temperature::sym, T::eT >(buf);
         if constexpr (0 != T::eQ) OneDim<T::Charge::sym, T::eQ >(buf);

         std::basic_ostringstream<char_type> out;

         // if numerator is empty insert a 1 into the stream.
         if (buf.first.tellp() != std::streampos(0)) out << buf.first.str();
         else out << '1';

         // if denominator has a value then insert a slash prior to the values.
         if (buf.second.tellp() != std::streampos(0)) out << '/' << buf.second.str();

         return out.str();
      }
   }

   /// Used to provide the diminsions of the SystemOfUnits::UnitType
   template<typename T > auto Diminsion(T const &val )
   {
      return t_Diminsion<char>(val);
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