/** @file SI.h
  * contains the the class template which represent any different unit type to enforce Dimensional Homogeneity.
*/
#ifndef SI_INCLUDE_H_07MAY2003
#define SI_INCLUDE_H_07MAY2003

namespace SystemOfUnits /// covers the basics of the system
{
   /// the class which is the heart of this library
   template
      < typename L, int iL    // length
      , typename t, int it    // time
      , typename M, int iM    // mass
      , typename T, int iT    // temperature
      , typename Q, int iQ =0 // charge
   >
   class unitType
   {
      long double m_amount; /// the scalar value of the object

   public:
      using t_float = long double;

      /// Dimensions as enum
      enum:int
         { eL = iL /*!< Dimension of Length */
         , et = it   /*!< Dimension of Time */
         , eM = iM   /*!< Dimension of Mass */
         , eT = iT   /*!< Dimension of Tempeture */
         , eQ = iQ   /*!< Dimension of Charge */
      };

      /// Used in all class methods and friend functions for their noexcept()
      enum:bool{ b_noexcept = noexcept(L) && noexcept(t) && noexcept(M) && noexcept(T) && noexcept(Q) };
      static_assert(b_noexcept, "Why is this false?");

      // Quantity as typedefs
      using Length = L;    /*!<  Quantity type for Length */
      using Time = t;      /*!<  Quantity type for Time */
      using Mass= M;      /*!<  Quantity type for Mass */
      using Tempeture = T; /*!<  Quantity type for Tempeture */
      using Charge = Q ;    /*!<  Quantity type for Charge */

      /// default constructor (does not initialize scalar with default value, just like a built in type).
      unitType() noexcept(b_noexcept) = default;

      /// rule of 6, provide a default destructor if one of the 6 is provided.
      ~unitType() noexcept(b_noexcept) = default;

      /// constructor from a scalar
      /** constructor from a scalar value.
      Constructor from a double type is made explicit to prevent comparison of non-types.  Forces strong type comparison.
      The non-explicit constructor allowed for comparison of unitType to built in type. Prevents implicit use.
      Without the explicit a user could introduce a double to equation where only a unitType is correct.
       * @param a double is used to initialize the original value
      */
      explicit constexpr unitType( t_float m ) noexcept(b_noexcept) : m_amount(m){}

      /** copy-constructor from the same unitType.
      * @param a unitType of the same type.
        copy constructor was explicit but removed when testing for pass by value instread of pass by reference. One Less machine instruction when pass by ref.
      */
      constexpr unitType(unitType const &val ) noexcept(b_noexcept) = default;
      constexpr unitType(unitType &&val) noexcept(b_noexcept) = default;

	  /** assignment operator
	  * @param value which the left-handed object will be assigned
	  * @return the current object
	  */
     constexpr unitType &operator=(unitType const &) & noexcept(b_noexcept) = default;

     /// default move-assignment operator
     constexpr unitType &operator=(unitType &&rt) && noexcept(b_noexcept) = default;

     /// prevent assigning scalar values to an existing unit but still allows assnment to a new type.
     /// Important to prevent novice users from assigning new amount to existing objects
     unitType& operator=(t_float val) = delete;

      /** returns the scalar value of the object.  Would like to eliminate this method but is used by conversion_cast<> and testing.
          Method is a crutch for any novice of the library.
      TODO: Use EXPECT_TRUE() instead of EXPECT_DOUBLE_EQ()
        * @return the scalar value of the type. */
      constexpr auto amount() const noexcept(b_noexcept) { return m_amount; }

      /** comparison operator which enforces Dimensional Homogeneity
       * @param unitType (or numeric type) on the left hand side
       * @param unitType (or numeric type) on the right hand side
       * @return bool true if the left and right are equal, false if not
      */
      friend constexpr bool operator==( unitType const &lf, unitType const &rt ) noexcept(b_noexcept)
      { return lf.m_amount == rt.m_amount; }

      /// provided to allow testing using ASSERT_TRUE() which will not use method amount()
      friend constexpr bool operator==(unitType const &lf, double rt) noexcept(b_noexcept) { return lf.m_amount == rt; }
      friend constexpr bool operator==(double lf, unitType const & rt) noexcept(b_noexcept) { return lf == rt.m_amount; }

      // not-comparison operator
      /** not-comparison operator
       * @param unitType (or numeric type) on the left hand side
       * @param unitType (or numeric type) on the right hand side
       * @return bool true if the left and right are not equal, false if equal
      */
      friend constexpr bool operator!=( unitType const &lf, unitType const &rt ) noexcept(b_noexcept)
      { return !(lf == rt); }

      /** less than operator
      * @param unitType on the left hand side
      * @param unitType on the right hand side
      * @return bool true if the left side is less than the right side
      */
      friend constexpr bool operator<(unitType const &lf, unitType const &rt) noexcept(b_noexcept)
      { return lf.m_amount < rt.m_amount; }

      /** greater than operator
      * @param unitType on the left hand side
      * @param unitType on the right hand side
      * @return bool true if the left side is greater than the right side
      */
      friend constexpr bool operator>(unitType const &lf, unitType const &rt) noexcept(b_noexcept)
      { return rt < lf; }

      /** less than equal operator
       * @param unitType on the left hand side
       * @param unitType on the right hand side
       * @return bool true if the left side is less than or equal to the right side
      */
      friend constexpr bool operator<=( unitType const &lf, unitType const &rt ) noexcept(b_noexcept)
      { return !(rt < lf); }

      /** greater than equal operator
       * @param unitType on the left hand side
       * @param unitType on the right hand side
       * @return bool true if the left side is greater than or equal to the right side
      */
      friend constexpr bool operator>=( unitType const &lf, unitType const &rt ) noexcept(b_noexcept)
      { return !(lf < rt); }

      /** addition assignment operator
       * @param unitType value which the left-handed object will be added with
       * @return the current object which was increased by the right-handed value
      */
      constexpr unitType &operator+=( unitType const &rt ) noexcept(b_noexcept)
      {
         m_amount += rt.m_amount;
         return *this;
      }

      /** difference assignment operator
       * @param value which the left-handed object will be differenced against
       * @return the current object
      */
      constexpr unitType &operator-=( unitType const &rt ) noexcept(b_noexcept)
      {
         m_amount -= rt.m_amount;
         return *this;
      }

      /** multiplication assignment operator
       *  must be with a scalar type.  Impossible with an other unitType (think about it)
       * @param double which is multiplied against the current object
       * @return the current object
      */
      constexpr unitType &operator *=( double rt ) noexcept(b_noexcept)
      {
         m_amount *= rt;
         return *this;
      }

      /** division assignment operator
          must be with a scalar type.  Impossible with an other unitType. (think about it)
       * @param double which is multiplied against the current object
       * @return the current object
      */
      constexpr unitType &operator /=( double rt ) noexcept(b_noexcept)
      {
         m_amount /= rt;
         return *this;
      }

      /** addition operator
         @param unitType left-handed side
         @param unitType right-handed side
         @return a new unitType of the same type as the left and right sides.
      */
      friend constexpr unitType operator+( unitType const &lf, unitType const &rt ) noexcept(b_noexcept)
      {
         return unitType( lf.m_amount + rt.m_amount );
      }

      /** difference operator
         @param unitType left-handed side
         @param unitType right-handed side
         @return a new unitType of the same type as the left and right sides.
      */
      friend constexpr unitType operator-( unitType const &lf, unitType const &rt ) noexcept(b_noexcept)
      {
         return unitType( lf.m_amount - rt.m_amount);
      }

      /** stream inserter operator
        @param output stream which may be any type (i.e. wchar_t or char_t)
        @param unitType The value amount inserted into the stream.  See manipulators in operators.h for inserting dimensions into the stream.
        @return The same output stream which was passed as a input parameter.
        Will work with any stream type which defines an inserter for a double.
      */
      template< typename TOUT> friend TOUT &operator<<(TOUT &out, unitType const &val)
      {
         out << val.m_amount;
         return out;
      }

      // TODO How to impliment a stream extractor
      // ideally not used with a serilizer since the type is not extract from the stream only the built in type.
      template< typename TIN> friend TIN &operator>>(TIN &in, unitType &val)
      {
         in >> val.m_amount;
         return in;
      }
   };

   /// Type trait struct which tests if the type is of UnitType class template above or not.
   template< typename T > struct is_UnitType { enum:bool{ value = false }; }; // primary template for everything not a UnitType
   template  /// for only UnitType only
      < typename L, int iL    // length
      , typename t, int it    // time
      , typename M, int iM    // mass
      , typename T, int iT    // temperature
      , typename Q, int iQ  // charge
      >
      struct is_UnitType< unitType<L, iL, t, it, M, iM, T, iT, Q, iQ> >
   {
      enum:bool{ value = true};
   };

   /// template used to create a type has been squared
   template< typename UNIT > struct MakeSQ
   {
      using type = unitType
         < typename UNIT::Length, UNIT::eL + UNIT::eL // cannot use * , uses operator*
         , typename UNIT::Time,   UNIT::et + UNIT::et
         , typename UNIT::Mass,   UNIT::eM + UNIT::eM
         , typename UNIT::Tempeture, UNIT::eT + UNIT::eT
         , typename UNIT::Charge, UNIT::eQ + UNIT::eQ
         >;
   };

   /// struct is used to create no dimension unit type. Used in the operators.h for (* /)
   struct NoDim
   {
      /// Lets using classes know if class is used as a base
      enum:bool{ IsBase = false};
      enum:unsigned char{sym = ' ' };
      /// Called by WhatAmI when creating the string describing the type.
      constexpr static char const * str() noexcept { return ""; }
      ///  Multiply by toBase() to get base value.
      constexpr static double toBase() noexcept { return 1.0; }
      /// Multiply by fromBase() to get diminsional value
      constexpr static double fromBase() noexcept { return 1.0; }
      /// Typedef of the actual base
      using  Base = NoDim;
   };

   /// Used in making the dimensions
   template< typename T, int D> struct t_BaseDim
   {
      using t_BaseUnit = T;
      enum:int{ DIM = D };
   };

   /// Create a struct base on the quantity types.
   /// Used as a builder to create different types with the same quantities.  See builder pattern.
   template< typename LEN, typename TIM, typename MAS, typename TEM = NoDim, typename CHR = NoDim > struct MakeType
   {
      /// template is used to create unitTypes with just the dimension types.
      template<int L, int t, int M, int T, int Q> struct MakeDim
      {
         using type = unitType< LEN, L, TIM, t, MAS, M, TEM, T, CHR, Q >;
      };

      template<int L, int t, int M > struct MakeDim<L, t, M, 0, 0>
      {
         using type = unitType< LEN, L, TIM, t, MAS, M, TEM, 0, CHR, 0 >;
      };
   };

   /// a type with no dimensions or quantity types.  The same size as a double.
   using tNoUnit = unitType< NoDim, 0, NoDim, 0, NoDim, 0, NoDim, 0, NoDim, 0 >;

   /// used to call fromBase() while using the toBase() static method.  Used in conversion_cast<>.
   template< typename ARG > struct MakeFrom
   {
      /// inverse of fromBase()
      constexpr static double toBase() noexcept(noexcept(ARG)) { return ARG::fromBase(); }
   };
} /// end of namespace SystemOfUnits

namespace SOU = SystemOfUnits;

/** 
 @mainpage My Personal Index Page
 @section copyright_sec Copyright
 Copyright © 2003-2019 "Curt" Leslie L. Martin, All rights reserved.
 curt.leslie.lewis.martin@gmail.com

 Permission to use, copy, modify, and distribute this software for any
 purpose is hereby granted without fee, provided that this copyright and
 permissions notice appear in all copies and derivatives.

 This software is provided "as is" without express or implied warranty.

 see https://www.nist.gov/pml/weights-and-measures/metric-si/si-units
 @section Introduction
 The Systems Of Units (SOU) Library was created out the author's desire to solve a problem where
 known engineering and scientific unit types will not mix to produce the wrong result type.  The library
 automatically does unit conversions during compile time or will produce a compile time error if types
 are mixed incorrectly.
 Any physically meaningful equation (and any inequality) will have the same dimensions on its left and right sides, a property known as dimensional homogeneity. Checking for dimensional homogeneity is a common application of dimensional analysis, serving as a plausibility check on derived equations and computations. It also serves as a guide and constraint in deriving equations that may describe a physical system in the absence of a more rigorous derivation.
 The library provides strong type-checking of different unit types at compile time.  It does not wait for
 runtime to find errors the compiler will detect.
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