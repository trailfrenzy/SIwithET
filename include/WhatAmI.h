
#ifndef SI_WHATAMI_H_INCLUDE
#define SI_WHATAMI_H_INCLUDE
#pragma once
#include <string>
#include <sstream>
#include "SI.h"
#include "list.hpp"

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
			if (DIM != 1) {
				ret << '^';
				ret << DIM;
			}
            ret << '·';
         }
      }
   }

   /// method owned by the class which prints the type of class
   /// @prama SystemOfUnits::unitType
   /// @return std::string
   /// @note future work is to remove the blank space after each string.
   template< typename T >
   inline std::string WhatAmI( T const & )
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
   template<> inline std::string WhatAmI(double const &) { return ""; }

   namespace helpers
   {
	   using t_bufPair = std::pair< std::stringstream, std::stringstream >;
	   enum { THETA = 233 }; // from www.asciitable.com

	   template < char C, int T > inline t_bufPair& OneDim(t_bufPair &buf)
	   {
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

   template< typename T, int D> struct t_BaseDim
   {
      using t_BaseUnit = T;
      enum { DIM = D };

      static char const * c_str()
      {
         if (DIM == 0) return "";
         if (DIM == 1 || DIM == -1) {
            constexpr char str[] = { '[', t_BaseUnit::sym ,']', '\0' };
            return str;
         }
         enum { absDIM = '0' + DIM < 0 ? -1 * DIM : DIM };
         constexpr char str[] = { '[', t_BaseUnit::sym, ']', '^', absDIM, '\0' };
         return str;
      }
   };
   }


   template <class a, class b> struct ORD {
      enum { VALUE = a::DIM > b::DIM };
   };


   template< class T > inline std::string Dim( T const &)
   {
      if (!T::eL && !T::eM && !T::et && !T::eT && !T::eQ) return ""; // no dim, bale out fast!

     // using t_List = Meta::LIST5< t_BaseDim<T::Length, T::eL>, t_BaseDim< T::Time, T::et>, t_BaseDim< //T::Mass, T::eM>, t_BaseDim< T::Tempeture, T::eT>, t_BaseDim< T::Charge, T::eQ > >;

     // using  t_Sorted = typename Meta::SORT<ORD, myList>::TYPE;

      return "";
   };

   template< typename T > constexpr inline std::string Diminsion(T const &)  // Θ
   {
	   if (!T::eL && !T::eM && !T::et && !T::eT && !T::eQ) return ""; // no dim, bale out fast!

	   helpers::t_bufPair buf;
	   
	   using namespace helpers;
	   if( T::eL) OneDim<T::Length::sym, T::eL >(buf);
	   if( T::eM) OneDim<T::Mass::sym, T::eM >(buf);
	   if(T::et) OneDim<T::Time::sym, T::et >(buf);
	   if(T::eT) OneDim<T::Tempeture::sym, T::eT >(buf);
	   if(T::eQ) OneDim<T::Charge::sym, T::eQ >(buf);

	   std::stringstream out;

	   if (buf.first.tellp() != std::streampos(0) ) out << buf.first.str();
	   else out << '1';

	   if (buf.second.tellp() != std::streampos(0)) out << '/' << buf.second.str();

	   return out.str();
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