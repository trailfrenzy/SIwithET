
#ifndef SI_WHATAMI_H_INCLUDE
#define SI_WHATAMI_H_INCLUDE
#pragma once
#include <string>
#include <sstream>
#include "SI.h"
#include"Struct_Symbol.h"
#include "list.hpp"
//#include "template_help.h"

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
      //template< typename TYPE, int DIM > void printAtom( std::ostringstream &ret )
      template< typename TYPE, int DIM, typename TOUT > void printAtom(TOUT &ret)
      {
         if( DIM ) // value known at compile time
         {
            ret << TYPE::str();
   			if (DIM > 1) 
            {
               ret << '^' << DIM;
			   }
            if (DIM < 0)
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
   {
      std::basic_ostringstream<char_type> buf;

      // use a template map to sort these later
      helpers::printAtom< T::Length, T::eL >( buf );
      helpers::printAtom< T::Time,   T::et >( buf );
      helpers::printAtom< T::Mass,   T::eM >( buf );
      helpers::printAtom< T::Tempeture, T::eT >( buf );
      helpers::printAtom< T::Charge, T::eQ >( buf );

      return buf.str().erase(buf.str().size() -1 ); // removes the last space char in the buffer
   }

   /// Returns in std::string what the type the UnitType is.
   template< typename T > inline std::string WhatAmI(T const &val) {
      using t_char = std::ostringstream::char_type;
      return UnitName<t_char>(val);
   }

   /// If user pushes a double into the template.
   template<> inline std::string WhatAmI(double const &) { return ""; }

   namespace helpers
   {
      /// The pair stringstream is used to make the first numerator and second denominator in dimensions.
	   using t_bufPair = std::pair< std::ostringstream, std::ostringstream >;
	   enum { THETA = 233 }; // from www.asciitable.com

      template < char C, int T, typename T_BufPair > inline auto& OneDim(T_BufPair &buf)
      {
         // only the numerator or denomitator is used not both, if ZERO then none are used.
         if (T > 0) {
            buf.first << '[' << C << ']';
            if (T > 1) buf.first << '^' << T;
         }
         if (T < 0) {
            buf.second << '[' << C << ']';
            if (T < -1) buf.second << '^' << abs(T);
         }
         return buf;
      }

      //template < class UNIT > struct t_base
      //{
      //   using t_UNIT = UNIT;
      //   typedef typename SystemOfUnits::t_BaseDim< typename t_UNIT::L, t_UNIT::iL > LEN;
      //};
 
      template< typename T, int D, typename char_type = char > struct t_SingleDim
      {
         using t_BaseUnit = T;
         enum { DIM = D, CHAR = t_BaseUnit::sym };
         using string = typename std::basic_string<char_type>;

         static auto c_str() -> string
         {
            string str;
            if (CHAR == SOLIDUS::sym) str = CHAR;
            else if (DIM == 0) {} //return "";
            else if (DIM == 1 || DIM == -1) {
               str = { '[', CHAR ,']' };
            }
            else {
               enum { absDIM = (DIM < 0) ? -1 * DIM : DIM };
               str = { '[', CHAR, ']', '^', '0' + absDIM };
            }
            return str;
         }
      };

      /// Solidus is the name of the slash
      using SOLIDUS = SystemOfUnits::helpers::T_Symbol<'/'>;
   }
   
   /// Used in sorting the dimensions below.
   template <class a, class b> struct ORD {
      enum { VALUE = a::DIM > b::DIM };
   };
   
   /// NOTE: Not ready for use.
   template< class T > inline std::string Dim( T const &)
   {
      if (!T::eL && !T::eM && !T::et && !T::eT && !T::eQ) return ""; // no dim, bale out fast!
      using SystemOfUnits::helpers::t_SingleDim;

     typedef typename Meta::LIST5< t_SingleDim< T::Length, T::eL>, t_SingleDim< T::Time, T::et>, t_SingleDim< T::Mass, T::eM>, t_SingleDim< T::Tempeture, T::eT>, t_SingleDim< T::Charge, T::eQ > >::TYPE t_List;

      using  t_Sorted = typename Meta::SORT<ORD, t_List >::TYPE;
      using DIM0 = typename Meta::At< t_Sorted, 0 >::RET;
      using DIM1 = typename Meta::At< t_Sorted, 1 >::RET;
      using DIM2 = typename Meta::At< t_Sorted, 2 >::RET;
      using DIM3 = typename Meta::At< t_Sorted, 3 >::RET;
      using DIM4 = typename Meta::At< t_Sorted, 4 >::RET;

      //enum{ isDIM0 = SystemOfUnits::IF<(DIM0::DIM < 0), true, false>::RET };
      enum{ isDIM0_Neg = DIM0::DIM <= 0, isDIM4_Pos = DIM4::DIM >= 0 };

      std::string retStr;
      if (isDIM0_Neg) {
         retStr += "1/";
         if (DIM0::DIM) retStr += DIM0::c_str();
         if (DIM1::DIM) retStr += DIM1::c_str();
         if (DIM2::DIM) retStr += DIM2::c_str();
         if (DIM3::DIM) retStr += DIM3::c_str();
         if (DIM4::DIM) retStr += DIM4::c_str();
      }

      return retStr;
   };

   template< typename char_type, typename T >
   inline auto t_Diminsion(T const &) -> std::basic_string<char_type>
   {
      if (!T::eL && !T::eM && !T::et && !T::eT && !T::eQ) return {}; // no dim, bale out fast!

      std::pair< std::basic_ostringstream<char_type>, std::basic_ostringstream<char_type> > buf;
	   
	   using namespace helpers;
	   if( T::eL) OneDim<T::Length::sym, T::eL >(buf);
	   if( T::eM) OneDim<T::Mass::sym, T::eM >(buf);
	   if(T::et) OneDim<T::Time::sym, T::et >(buf);
	   if(T::eT) OneDim<T::Tempeture::sym, T::eT >(buf);
	   if(T::eQ) OneDim<T::Charge::sym, T::eQ >(buf);

	   std::basic_ostringstream<char_type> out;

      // if numerator is empty insert a 1 into the stream.
	   if (buf.first.tellp() != std::streampos(0) ) out << buf.first.str();
	   else out << '1';

      // if denominator has a value then insert a slash prior to the values.
	   if (buf.second.tellp() != std::streampos(0)) out << '/' << buf.second.str();

	   return out.str();
   }

//#include <type_traits>
   /// Specialized template when the type is dimensionless.
   template< typename char_type >
   inline auto t_Diminsion(double const &)->std::basic_string<char_type>
   {
      return {};
   }

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