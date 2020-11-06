/** @file SI.h https://github.com/trailfrenzy/SIwithET
  * contains the the class template which represent any different unit type to enforce The Principle Dimensional Homogeneity.
*/
#ifndef SI_INCLUDE_H_07MAY2003
#define SI_INCLUDE_H_07MAY2003
#include "Struct_Symbol.h"
#include <concepts>

namespace SystemOfUnits /// covers the basics of the system
{
   /// the class which is the heart of this library
   template
      < LENGTH L,      int iL    // length
      , TIME t,        int it    // time
      , MASS M,        int iM    // mass
      , TEMPERATURE T, int iT    // temperature
      , CURRENT Q,     int iQ =0 // charge
   >
   class unitType : public Trait_Unit
   {
      long double m_amount; /// the scalar value of the object. On the Microsoft compiler the double and long double are the same.

   public:
      using t_float = decltype(m_amount);///< Others may want to know this information

      /// Dimensions as enum
      enum:int
         { eL = iL   /*!< Dimension of Length */
         , et = it   /*!< Dimension of Time */
         , eM = iM   /*!< Dimension of Mass */
         , eT = iT   /*!< Dimension of Temperature */
         , eQ = iQ   /*!< Dimension of Charge */
      };

      /// Used in all class methods and friend functions for their noexcept()
      enum:bool{ b_noexcept = noexcept(L) && noexcept(t) && noexcept(M) && noexcept(T) && noexcept(Q) };
      //enum: bool{ b_noexcept = true };
      static_assert(b_noexcept, "Why is this false?");

      // Quantity as typedefs
      using Length = L;      /*!<  Quantity type for Length */
      using Time = t;        /*!<  Quantity type for Time */
      using Mass= M;         /*!<  Quantity type for Mass */
      using Temperature = T; /*!<  Quantity type for Temperature */
      using Charge = Q ;     /*!<  Quantity type for Charge */

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
     /// Important to prevent implicit assignment of new amount to existing objects.
     unitType& operator=(t_float val) = delete;

      /** returns the scalar value of the object.  Would like to eliminate this method but is used by conversion_cast<> and testing.
          Method is a crutch for any novice of the library.
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

      /** product operator
         @param float type defined in the class
         @param unitType right-handed side
         @return the same type which was passed as the right side parameter.
      */
      friend constexpr auto operator*(t_float lf, unitType const& rt) noexcept
      {
         return unitType(lf * rt.m_amount);
      }

      /** product operator
         @param unitType left-handed side
         @param float type defined in the class
         @return the same type which was passed as the left side parameter.
      */
      friend constexpr unitType operator*(unitType const& lf, t_float rt) noexcept
      {
         return unitType(lf.m_amount * rt);
      }

      /** ratio operator
         @param Numerator unitType left-handed side
         @param Deonminator float type defined in the class
         @return the same type which was passed as the Numberator.
      */
      friend constexpr unitType operator/(unitType const& lf, t_float rt) noexcept
      {
         return unitType(lf.m_amount / rt);
      }

      /** ratio operator or inverse operator
         @param Numerator float type defined in the class
         @param Deonminator unitType right-handed side
         @return the same type which was passed as the Numberator.
      */
      friend constexpr auto operator/(t_float lf, unitType rt) noexcept
      {
         using RT = decltype(rt);

         return unitType< RT::Length, -1*RT::eL
                        , RT::Time, -1 * RT::et
                        , RT::Mass, -1 * RT::eM
                        , RT::Temperature, -1 * RT::eT
                        , RT::Charge, -1 * RT::eQ >
            (lf / rt.m_amount);
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
   template< typename T > struct is_UnitType : std::integral_constant<bool, std::is_base_of< Trait_Unit, T>::value > {};

   /// Concept for what a SI Unit is. The name 'UnitSpecies' is from "Elements of Programming" , Alexander Stepanove, Paul McJones, Semigroup Press, Sec 1.7. 
   /// We call a collection of requirments a concpet, Tyeps represent spcies, concpts reprsents genera.
   /// All of the different UnitType's which are defined by the template above belong to the species of UnitSpecies.
   template< typename T> concept UnitSpecies = is_UnitType<T>::value;

   /// Derived units. Derived units are defined as products of powers of the base units. When the numerical
   /// factor of this product is one, the derived units are called coherent derived units.The base
   /// and coherent derived units of the SI form a coherent set, designated the set of coherent SI
   /// units.The word “coherent” here means that equations between the numerical values of
   /// quantities take exactly the same form as the equations between the quantities themselves.
   /// Some of the coherent derived units in the SI are given special names.
   template< UnitSpecies UNIT_TYPE, char const * NAME >
   struct CoherentUnit : public UNIT_TYPE
   {
      using Base_Type = UNIT_TYPE;

      constexpr CoherentUnit(double val) noexcept : UNIT_TYPE(val)
      {
         static_assert(is_UnitType< UNIT_TYPE>::value);
      }

      /// The specialized name for the coherent unit type.
      /// @return char const name of the coherent type.
      static constexpr auto unitName() noexcept { return NAME; }
   };

   /// Used at compile time to find if type is of a Coherent Unit Type.
   template< typename T> struct is_CoherentUnit : std::integral_constant<bool, false> {};

   template< typename T, char const* N > struct is_CoherentUnit< CoherentUnit<T, N > > : std::integral_constant<bool, true> {};

   /// struct is used to create no dimension unit type. Used in the operators.h for (* /)
   struct NoDim : NO_DIM
   {
      /// Lets using classes know if class is used as a base
      enum:bool{ IsBase = false};

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
   template< LENGTH LEN, TIME TIM, MASS MAS, TEMPERATURE TEM, CURRENT CHR > struct MakeType
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
   template< DIMENSION ARG > struct MakeFrom : helpers::Trait_SymbolForDimension
   {
      /// inverse of fromBase()
      constexpr static double toBase() noexcept(noexcept(ARG)) { return ARG::fromBase(); }
   };

} /// end of namespace SystemOfUnits

namespace SOU = SystemOfUnits; ///< Shortcut to the namespace.

/** 
 @mainpage My Personal Index Page
 @section copyright_sec Copyright
 Copyright © 2003-2020 "Curt" Leslie L. Martin, All rights reserved.
 curt.leslie.lewis.martin@gmail.com

 Permission to use, copy, modify, and distribute this software for any
 purpose is hereby granted without fee, provided that this copyright and
 permissions notice appear in all copies and derivatives.

 This software is provided "as is" without express or implied warranty.

 see https://www.bipm.org/en/measurement-units/
 see https://www.nist.gov/pml/weights-and-measures/metric-si/si-units
 @section Introduction
 
 The Systems Of Units (SystemOfUnits) Library was created out the author's desire to solve a problem where
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