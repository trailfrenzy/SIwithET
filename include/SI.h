/** @file SI.h
  * contains the the class template that can represent any different unit type
*/
#ifndef SI_INCLUDE_H_07MAY2003
#define SI_INCLUDE_H_07MAY2003
#pragma once

namespace SystemOfUnits /// covers the basics of the system
{
   /// struct is used to create no dimension unit type
   struct NoDim
   {
      /// Lets using classes know if class is used as a base
      enum { IsBase = false };
      /// Called by WhatAmI when creating the string describing the type.
      static char const * str() { return ""; }
      ///  Multiply by toBase() to get base value.
      static double toBase() { return 1.0; }
      /// Multiply by fromBase() to get diminsional value
      static double fromBase() { return 1.0; }
      /// Typedef of the actual base
      typedef NoDim Base;
   };

   /// the class which is the heart of this library
   template
      < typename L, int iL    // length
      , typename t, int it    // time
      , typename M, int iM    // mass
      , typename T, int iT    // temperature
      , typename Q, int iQ = 0 // charge
   >
   class unitType
   {
      double m_amount; /// the scalar value of the object
   public:
      /// Dimensions as enum
      enum { eL = iL /*!< Dimension of Length */
         , et = it   /*!< Dimension of Time */
         , eM = iM   /*!< Dimension of Mass */
         , eT = iT   /*!< Dimension of Tempeture */
         , eQ = iQ   /*!< Dimension of Charge */
      };

      // Quantity as typedefs
      typedef L Length;    /*!<  Quantity type for Length */
      typedef t Time;      /*!<  Quantity type for Time */
      typedef M Mass;      /*!<  Quantity type for Mass */
      typedef T Tempeture; /*!<  Quantity type for Tempeture */
      typedef Q Charge;    /*!<  Quantity type for Charge */

      /// default constructor (does not initialize scalar with default value, just like a built in type)
      unitType(){}

      /// constructor from a scalar
      /** constructor from a scalar value
       * @param a double that is used to initialize the original value
      */
      unitType( double m ) : m_amount(m){}
	  explicit unitType( unitType const &val ) : m_amount(val.m_amount){}
	  unitType( unitType &&val ) : m_amount( std::move(val.m_amount )){}
	  //unitType& operator=(unitType const &val) : m_amount(val.m_amount) {}
	  unitType& operator=(double m) = delete; // prevent assigning scalar values to an existing unit but still allows assnment to a new type.

      /** returns the scalar value of the object
        * @return the scalar value of the type. */
      double amount()const { return m_amount; }

      /** comparison operator
       * @param unitType on the left hand side
       * @param unitType on the right hand side
       * @return bool true if the left and right are equal, false if not
      */
      friend bool operator==( unitType const &lf, unitType const &rt ) { return lf.m_amount == rt.m_amount; }

      /** comparison operator with a double
       * @param unitType on the left hand side
       * @param double on the right hand side
       * @return bool true if the left and right are equal, false if not
      */
      friend bool operator==( unitType const &lf, double rt ) { return lf.m_amount == rt; }

      /** comparison operator with a double
       * @param double on the left hand side
       * @param unitType on the right hand side
       * @return bool true if the left and right are equal, false if not
      */
      friend bool operator==( double lf, unitType const &rt ) { return lf == rt.m_amount; }

      // not-comparison operator
      /** not-comparison operator
       * @param unitType on the left hand side
       * @param unitType on the right hand side
       * @return bool true if the left and right are not equal, false if equal
      */
      friend bool operator!=( unitType const &lf, unitType const &rt ) { return lf.m_amount != rt.m_amount; }

      /** not-comparison operator with double
       * @param unitType on the left hand side
       * @param double on the right hand side
       * @return bool true if the left and right are not equal, false if equal
      */
      friend bool operator!=( unitType const &lf, double rt ) { return lf.m_amount != rt; }

      /** not-comparison operator
       * @param unitType on the left hand side
       * @param double on the right hand side
       * @return bool true if the left and right are not equal, false if equal
      */
      friend bool operator!=( double lf, unitType const &rt ) { return lf != rt.m_amount; }

      /** less than equal operator
       * @param unitType on the left hand side
       * @param unitType on the right hand side
       * @return bool true if the left side is less than or equal to the right side
      */
      friend bool operator<=( unitType const &lf, unitType const &rt ) { return lf.m_amount <= rt.m_amount; }

      /** greater than equal operator
       * @param unitType on the left hand side
       * @param unitType on the right hand side
       * @return bool true if the left side is greater than or equal to the right side
      */
      friend bool operator>=( unitType const &lf, unitType const &rt ) { return lf.m_amount >= rt.m_amount; }

      /** less than operator
       * @param unitType on the left hand side
       * @param unitType on the right hand side
       * @return bool true if the left side is less than the right side
      */
      friend bool operator< ( unitType const &lf, unitType const &rt ) { return lf.m_amount < rt.m_amount; }

      /** greater than operator
       * @param unitType on the left hand side
       * @param unitType on the right hand side
       * @return bool true if the left side is greater than the right side
      */
      friend bool operator> ( unitType const &lf, unitType const &rt ) { return lf.m_amount > rt.m_amount; }

      /** assignment operator
       * @param value which the left-handed object will be assigned
       * @return the current object
      */
      unitType &operator=( unitType const &rt )
      {
         m_amount = rt.m_amount;
         return *this;
      }

	 // unitType &operator=( double rt )
	 // {
		//m_amount = rt;
		//return *this;
	 // }

      /** addition assignment operator
       * @param unitType value which the left-handed object will be added with
       * @return the current object which was increased by the right-handed value
      */
      unitType &operator+=( unitType const &rt )
      {
         m_amount += rt.m_amount;
         return *this;
      }

      /** difference assignment operator
       * @param value which the left-handed object will be differenced against
       * @return the current object
      */
      unitType &operator-=( unitType const &rt )
      {
         m_amount -= rt.m_amount;
         return *this;
      }

      /** multiplication assignment operator
       *  must be with a scalar type.  Impossible with an other unitType (think about it)
       * @param double which is multiplied against the current object
       * @return the current object
      */
      unitType &operator *=( double rt )
      {
         m_amount *= rt;
         return *this;
      }

      /** division assignment operator
          must be with a scalar type.  Impossible with an other unitType. (think about it)
       * @param double which is multiplied against the current object
       * @return the current object
      */
      unitType &operator /=( double rt )
      {
         m_amount /= rt;
         return *this;
      }

      /** addition operator
         @param unitType left-handed side
         @param unitType right-handed side
         @return a new unitType of the same type as the left and right sides.
      */
      friend unitType operator+( unitType const &lf, unitType const &rt )
      {
         return unitType( lf.amount() + rt.amount() );
      }

      /** difference operator
         @param unitType left-handed side
         @param unitType right-handed side
         @return a new unitType of the same type as the left and right sides.
      */
      friend unitType operator-( unitType const &lf, unitType const &rt )
      {
         return unitType( lf.m_amount - rt.m_amount);
      }
   };

   /// template used to create a type that has been squared
   template< typename UNIT > struct MakeSQ
   {
      typename typedef unitType
         < typename UNIT::Length, UNIT::eL + UNIT::eL // cannot use * , uses operator*
         , typename UNIT::Time,   UNIT::et + UNIT::et
         , typename UNIT::Mass,   UNIT::eM + UNIT::eM
         , typename UNIT::Tempeture, UNIT::eT + UNIT::eT
         , typename UNIT::Charge, UNIT::eQ + UNIT::eQ
         > type;
   };

   /// Create a struct base on the quantity types.
   /// Used as a factory to create different types with the same quantities.
   template< typename LEN, typename TIM, typename MAS, typename TEM = NoDim, typename CHR = NoDim > struct MakeType
   {
      /// template is used to create unitTypes with just the dimension types.
      template<int L, int t, int M, int T, int Q> struct MakeDim
      {
         typedef unitType< LEN, L, TIM, t, MAS, M, TEM, T, CHR, Q > type;
      };

      template<int L, int t, int M > struct MakeDim<L, t, M, 0, 0>
      {
         typedef unitType< LEN, L, TIM, t, MAS, M, TEM, 0, CHR, 0 > type;
      };
   };

   /// a type with no dimensions or quantity types.  The same size as a double.
   typedef unitType< NoDim,0, NoDim,0, NoDim,0, NoDim,0, NoDim,0 > tNoUnit;

   /// used to call fromBase() while using the toBase() static method
   template< typename ARG > struct MakeFrom
   {
      /// inverse of fromBase()
      static double toBase() { return ARG::fromBase(); }
   };
} /// end of namespace SystemOfUnits

namespace SOU = SystemOfUnits;

/** 
 @mainpage My Personal Index Page
 @section copyright_sec Copyright
 Copyright © 2005-2015 "Curt" Leslie L. Martin, All rights reserved.
 curt.leslie.lewis.martin@gmail.com

 Permission to use, copy, modify, and distribute this software for any
 purpose is hereby granted without fee, provided that this copyright and
 permissions notice appear in all copies and derivatives.

 This software is provided "as is" without express or implied warranty.

 @section Introduction
 The Systems Of Units (SOU) Library was created out the author's desire to solve a problem where
 known engineering and scientific unit types will not be mixed to the wrong result type.  The library
 automatically does unit conversions during compile time.  
 The library provides strong type-checking of different unit types at compile time.  It does not wait for
 runtime to find errors that the compiler can detect.
 When writing code to solve an engineering 
 problem it is hard to find what the units are envolved in the equation and if the equation
 cancels out the incorrect units.  For example, what is the unit for the following varible:
 @code double x = 3.0; @endcode
 Is it in feet or meters?  Is Knots or Kilometers per Hour?  Or is it in grams or Kelvin?
 If the types can be enforced at compile time where only meters would work with meters and
 grams would only work with grams.

 For example:
 @code meter x = 4.0; // meter is a typedef
 meter y = 3.0;
 meter xy = x + 3; @endcode
 The compiler will allow two different measurements that are meters to be summed toegethor.
 It will not allow the following:
 @code meter x = 4.0;
 feet y = 10;
 meter xy = x + y; // error @endcode
 However the following would work:
 @code meter xy = x + conversion_cast<meter>(y); @endcode

*/
#endif