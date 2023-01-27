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
      /// The pair stringstream is used to make the first numerator and second denominator in dimensions.
      using t_bufPair = std::pair< std::ostringstream, std::ostringstream >;

      template<typename char_type>
      inline
      auto PairToString(std::pair< std::basic_ostringstream<char_type>, std::basic_ostringstream<char_type> > &buf)
      {
         std::basic_ostringstream<char_type> out;

         // if numerator is empty insert a 1 into the stream.
         if (buf.first.tellp() != std::streampos(0)) out << buf.first.str();
         else out << '1';

         // if denominator has a value then insert a slash prior to the values.
         if (buf.second.tellp() != std::streampos(0)) out << '/' << buf.second.str();

         return out.str();
      }

      /// used by what am i
      /// @prama std::stringstream is used to create the return stream
      template< Dimensional TYPE, int DIM, typename T_BufPair >
      inline
      void printAtom(T_BufPair& buf)
         noexcept( noexcept(T_BufPair) && noexcept(TYPE))
      {
         if constexpr (DIM > 0)
         {
            // inserts a space if not the first one on the stream.
            if (buf.first.tellp() != std::streampos(0)) buf.first << ' ';

            buf.first << TYPE::str();
            if constexpr (DIM > 1) {
               buf.first << '^' << DIM;
            }
         }
         if constexpr (DIM < 0)
         {
            // inserts a space if not the first one on the stream.
            if (buf.second.tellp() != std::streampos(0)) buf.second << ' ';

            buf.second << TYPE::str();
            if constexpr (DIM < -1) {
               buf.second << '^' << (-1 * DIM);
            }
         }
      }
   }

   /// method owned by the class which prints the type of class
   /// @prama SystemOfUnits::UnitType
   /// @return std::string
   /// @note The function builds the sequence of stream inserters at compile time but will still call the stream inserters at run time. 
   template< typename char_type, typename T >
   inline auto UnitName( T )
   {
      typedef T Type ;
      // CoherentUnit has a name defined by the user or system.
      if constexpr (is_CoherentUnit<T>::value) return std::basic_string<char_type>{T::unitName()};
      else if constexpr (!is_UnitType<T>::value) return std::basic_string<char_type>{};
      else if constexpr (Type::isZeroDimensions()) return std::basic_string<char_type>{};
      else
      {
         std::pair< std::basic_ostringstream<char_type>, std::basic_ostringstream<char_type> > buf;

         // use a template map to sort these later
         if constexpr (T::eL) helpers::printAtom< typename T::Length, T::eL >(buf);
         if constexpr (T::et) helpers::printAtom< typename T::Time, T::et >(buf);
         if constexpr (T::eM) helpers::printAtom< typename T::Mass, T::eM >(buf);
         if constexpr (T::eT) helpers::printAtom< typename T::Temperature, T::eT >(buf);
         if constexpr (T::eQ) helpers::printAtom< typename T::Charge, T::eQ >(buf);
         if constexpr (T::eN) helpers::printAtom< typename T::Substance, T::eN>(buf);
         if constexpr (T::eJ) helpers::printAtom< typename T::Luminous, T::eJ>(buf);

         return helpers::PairToString(buf);
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
      /// Called by Diminsion() below.
      template < char C, int DIM, typename T_BufPair >
      inline auto& OneDim(T_BufPair &buf)
         noexcept( noexcept(t_bufPair::first_type)&&noexcept(t_bufPair::second_type) )
      {
         // only the numerator or denomitator is used not both, if ZERO then none are used.
         if constexpr (DIM > 0) {
            buf.first << '[' << C << ']';
            if constexpr (DIM > 1) buf.first << '^' << DIM;
         }
         if constexpr (DIM < 0) {
            buf.second << '[' << C << ']';
            if constexpr (DIM < -1) buf.second << '^' << (-1 * DIM);
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

      else if constexpr( T::isZeroDimensions() ) return {}; // no dim, bale out fast!
      else
      {
         std::pair< std::basic_ostringstream<char_type>, std::basic_ostringstream<char_type> > buf;

         using namespace helpers;
         if constexpr (0 != T::eL) OneDim<T::Length::sym, T::eL >(buf);
         if constexpr (0 != T::eM) OneDim<T::Mass::sym, T::eM >(buf);
         if constexpr (0 != T::et) OneDim<T::Time::sym, T::et >(buf);
         if constexpr (0 != T::eT) OneDim<T::Temperature::sym, T::eT >(buf);
         if constexpr (0 != T::eQ) OneDim<T::Charge::sym, T::eQ >(buf);
         if constexpr (0 != T::eN) OneDim<T::Substance::sym, T::eN>(buf);
         if constexpr (0 != T::eJ) OneDim<T::Luminus::sym, T::eJ>(buf);

         return helpers::PairToString<char_type>(buf);
      }
   }

   /// Used to provide the diminsions of the SystemOfUnits::UnitType
   template<typename T > auto Diminsion(T const &val )
   {
      return t_Diminsion<char>(val);
   }

   template< class TOUT >
   class ShowUnits_t
   {
       /// TOUT can be std::cout, std::ofstream, std::stringstream, or anyother stream which uses insertors.
       TOUT& ref;
   public:
       ShowUnits_t(TOUT& r) : ref(r) {}

       ///  The built-in types are arithmetic so pass by value and not by reference.
       template< Arithmetic A> ShowUnits_t& operator<<(A a) { ref << a; return *this; }

       template< UnitSpecies S> ShowUnits_t& operator<<(S val)
       {
           using t_char = typename TOUT::char_type;  // will not compile if TOUT does not have char_type.
           ref << val << ' ' << SystemOfUnits::UnitName<t_char>(val);
           return *this;
       }

       /// Used by any type which is not a built-in or UnitType
       template< typename T > ShowUnits_t& operator<<(const T& val)
       {
           ref << val;
           return *this;
       }

       /// converts the class to the stream implicitly. Is the last function called by the stream when the Manipulator is used.
       operator TOUT& () const { return ref; }
   };

   template< class TOUT > inline auto units() -> ShowUnits_t<TOUT>* { return 0; }

}

template< class TOUT >
inline auto operator<<(TOUT& out, SystemOfUnits::ShowUnits_t<TOUT>* (*)()) //-> SystemOfUnits::ShowDim_t<TOUT>
{
    return SystemOfUnits::ShowUnits_t<TOUT>(out);
}


// Copyright © 2005-2023 "Curt" Leslie L. Martin, All rights reserved.
// curt.leslie.lewis.martin@gmail.com
//
// Permission to use, copy, modify, and distribute this software for any
// purpose is hereby granted without fee, provided that this copyright and
// permissions notice appear in all copies and derivatives.
//
// This software is provided "as is" without express or implied warranty.

#endif