// NOTE to myself Add a section for Add, subtraction, Mult and Div, WhatAmI  my be the unit test.
/**
File @file contains the operators for multiplication and division which cannot be done by
itself.

 @page page1 Multiplication and Division Operators

 @section MAD Multiplication and Division Operators
 Multiplication and division where a little more difficult to implement where the result is 
 completly different from the two arguments.  The result type should be know by the the developer
 who uses the code when the division and multiplication operators are used.  For example:
 @code meter x = 3;
 meter y = 4.0;
 meterSq z = x * y; @endcode

 Where the following will not work:
 @code meter z = x * y; //error @endcode

 Multiplication and division operators can also have scalars in their arguments on either side.
 @code meter z = 3.0 * y; @endcode
 or
 @code meter z = y * 3.0; @endcode

 The idea is to prevent a user software developer to mismatch the to multiplier argument types with the
 product result type.

*/
#ifndef UNIT_TYPES_OPERATORS_INCLUDE_H
#define UNIT_TYPES_OPERATORS_INCLUDE_H
#pragma once
#include "SI.h"                           /// why we are here
#include "template_help.h"
#include "WhatAmI.h"
#include <type_traits>

namespace SystemOfUnits
{
   template<typename T> concept Arithmetic = std::is_arithmetic<T>::value;

   namespace operators
   {
      /** \brief The trait idea came from "C++ Templates", pg 332.
       The main reason for the template A_Trait was when using the 32-bit compiler and passing built in types.
       trait is used to allow built in types to be used as args in operator's mul and div 
       The @code A_Trait<T1,T2> @endcode templates are used during has hidden templates that are
       created during multiplication and division operations using the SI templates.  @code A_Trait<T1,T2> @endcode
       allows operators "*" and "/" to use references of the SI types and values for built in types.
       */
      template < UnitSpecies T, UnitSpecies T2 > struct A_Trait
      {
         /// used as the argument for the operators. Seems to like a good idea to make one copy and move it all the way down.
         using ArgRef = T &&;

         /// constant reference. Original 32-bit version went with ref, but have not seen any changes in 64-bit if us by value.
         using ExprRef = T const;

         /// the dimensions of the trait
         enum : int
         { eL = T::eL   /// Length Dimensional 
         , et = T::et   /// Time Dimensional
         , eM = T::eM   /// Mass Dimensional
         , eT = T::eT   /// Temperature Dimensional
         , eQ = T::eQ   /// Charge Dimensional
         };

         ///  Returns wheather the class is a zero dimensions or not.
         constexpr static bool isZeroDimensions() noexcept { return eL == 0 && et == 0 && eM == 0 && eT == 0 && eQ == 0; }

         using Length = typename T::Length;        /// Length type of the incoming arg.
         using Time = typename T::Time;            /// Time type of the incoming arg.
         using Mass = typename T::Mass;            /// Mass type of the incoming arg.
         using Temperature = typename T::Temperature;  /// Temperature of the incoming arg.
         using Charge = typename T::Charge;        /// Charge of the incoming arg.
      };

      /// Base class to Mul_Result and Div_Result
      /** NOTE:
      "Expression Templates, Chap 18", C++ Templates The Complete Guide, Addison-Wesley,
      David Vandevoorde and Nicolai M. Josuttis, 2003.

      The ideas for these two classes came from the above reference.

      A good article to read more about expression templates see:
      "String Concatenation & Expression Templates", Craig Henderson, 'C/C++ Users Journal', June 2005

	  Remember that all enums and types are calculated at compile time.
      */
      template< typename T1, typename T2 > class Base
      {
         /// private struct used in the the two operators (* / )
         template< Dimensional A1, Dimensional A2 > struct CombineBaseTypes
         {
            constexpr static double toBase() noexcept( noexcept(A1) && noexcept(A1) )
            { 
               return A1::toBase() * A2::toBase() * A1::fromBase() * A1::fromBase(); 
            }
         };

      public:
         using R1 = A_Trait<T1, T2>; /// the type of the left side of the arg
         using R2 = A_Trait<T2, T1>; /// the type of the right side of the arg

         /// Do both the traits have the same base dimensions?
         constexpr static bool is_same_BASE() noexcept
         {
            return
               std::is_same<R1::Length::Base, R2::Length::Base>::value
               && std::is_same<R1::Time::Base, R2::Time::Base >::value
               && std::is_same<R1::Mass::Base, R2::Mass::Base >::value
               && std::is_same<R1::Temperature::Base, R2::Temperature::Base >::value
               && std::is_same<R1::Charge::Base, R2::Charge::Base >::value;
         }

         /// public enum is used to let users know that the types did not match
         /// ie so feet and meters are not mixed up but both are base units. Used in static_assert()
         enum ALLTYPES_THE_SAME : bool {
            val = is_same_BASE() //is_same_BASE<R1, R2 >::value
            || R1::isZeroDimensions()
            || R2::isZeroDimensions()
         };

         // Below is a compile time check to compare if the length as same type ie meter to meter, not meter to kilometer
         // enum value is true if the two types are the same.
         enum :bool { IsLengthSame = std::is_same< typename R1::Length, typename R2::Length >::value };
         enum :bool { IsTimeSame = std::is_same< typename R1::Time, typename R2::Time   >::value };
         enum :bool { IsMassSame = std::is_same< typename R1::Mass, typename R2::Mass   >::value };
         enum :bool { IsTempSame = std::is_same< typename R1::Temperature, typename R2::Temperature >::value };
         enum :bool { IsChargeSame = std::is_same< typename R1::Charge, typename R2::Charge >::value };

         /* the 5 proposed traits are used in the result() function of the two inhereted classes */
           /// the proposed length type of the result
         using LenType = typename IF
            < R1::eL == 0 || R2::eL == 0
            , NoDim
            , typename IF
            < IsLengthSame
            , NoDim
            , typename IF
            < !R1::Length::IsBase && !R2::Length::IsBase
            , CombineBaseTypes<typename R1::Length, typename R2::Length>
            , typename IF<R2::Length::IsBase, typename SystemOfUnits::MakeFrom<typename R1::Length>, typename R2::Length >::RET
            >::RET
            >::RET
            >::RET;

         /// the proposed time type of the result
         using TimeType = typename IF
            < R1::et == 0 || R2::et == 0
            , NoDim
            , typename IF
            < IsTimeSame
            , NoDim
            , typename IF
            < !R1::Time::IsBase && !R2::Time::IsBase
            , CombineBaseTypes<typename R1::Time, typename R2::Time>
            , typename IF<R2::Time::IsBase, SystemOfUnits::MakeFrom<typename R1::Time>, typename R2::Time >::RET
            >::RET 
            >::RET
            >::RET;

         /// the proposed mass type of the result
         using MassType = typename IF
            < R1::eM == 0 || R2::eM == 0
            , NoDim
            , typename IF
               < IsMassSame
               , NoDim
               , typename IF
                  < !R1::Mass::IsBase && !R2::Mass::IsBase
                  , CombineBaseTypes<typename R1::Mass, typename R2::Mass>
                  , typename IF<R2::Mass::IsBase, SystemOfUnits::MakeFrom<typename R1::Mass>, typename R2::Mass >::RET
                  >::RET 
               >::RET
            >::RET;

         /// the proposed temperature type of the result
         using TempetureType = typename IF
            < R1::eT == 0 || R2::eT == 0
            , NoDim
            , typename IF
            < IsTempSame
            , NoDim
            , typename IF
            < !R1::Temperature::IsBase && !R2::Temperature::IsBase
            , CombineBaseTypes<typename R1::Temperature, typename R2::Temperature>
            , typename IF<R2::Temperature::IsBase, SystemOfUnits::MakeFrom<typename R1::Temperature>, typename R2::Temperature >::RET
            >::RET 
            >::RET
            >::RET;

         /// the proposed mass type of the result
         using ChargeType = typename IF
            < R1::eQ == 0 || R2::eQ == 0
            , NoDim
            , typename IF
            < IsChargeSame
            , NoDim
            , typename IF
            < !R1::Charge::IsBase && !R2::Charge::IsBase
            , CombineBaseTypes<typename R1::Charge, typename R2::Charge>
            , typename IF<R2::Charge::IsBase, SystemOfUnits::MakeFrom<typename R1::Charge>, typename R2::Charge >::RET
            >::RET
            >::RET
            >::RET;

      };

      /// a class for objects that represents the multiplication of two operands
      template< typename T1, typename T2 >
      class Mul_Result : public operators::Base< T1, T2 >
      {
		  using t_base = Base< T1, T2 >;

        typename const t_base::R1::ExprRef m_r1;    /// first operand reference
        typename const t_base::R2::ExprRef m_r2;    /// second operand reference
      public:
		  using R1 = t_base::R1;
		  using R2 = t_base::R2;

         /// multiplication is addition of the powers 
         enum Dim : int { Z = 0
              , eL = R1::eL + R2::eL   /// Length Dimensional 
              , et = R1::et + R2::et   /// Time Dimensional 
              , eM = R1::eM + R2::eM   /// Mass Dimensional 
              , eT = R1::eT + R2::eT   /// Temperature Dimensional 
              , eQ = R1::eQ + R2::eQ };/// Charge Dimensional 

         // Yes, these lines are long, but kept long to help the eye catch an error.
         using Length      = typename IF< Dim::eL == Dim::Z, typename R1::Length, typename IF<R1::eL != 0,      typename R1::Length,      typename R2::Length>::RET >::RET;
         using Time        = typename IF< Dim::et == Dim::Z, typename R1::Time, typename IF<R1::et != 0,        typename R1::Time,        typename R2::Time  >::RET >::RET;
         using Mass        = typename IF< Dim::eM == Dim::Z, typename R1::Mass, typename IF<R1::eM != 0,        typename R1::Mass,        typename R2::Mass  >::RET >::RET;
         using Temperature = typename IF< Dim::eT == Dim::Z, typename R1::Temperature, typename IF<R1::eT != 0, typename R1::Temperature, typename R2::Temperature>::RET >::RET;
         using Charge      = typename IF< Dim::eQ == Dim::Z, typename R1::Charge, typename IF<R1::eQ != 0,      typename R1::Charge,      typename R2::Charge>::RET >::RET;

         /// all results are based on the first argument operands type, if NoDim then base on the second argument.
         using TResult = SystemOfUnits::UnitType
            < Length, Dim::eL
            , Time, Dim::et
            , Mass, Dim::eM
            , Temperature, Dim::eT
            , Charge, Dim::eQ
            >;

         /// constructor initializes references to the operands.
         /// @param R1::ArgRef r1 is the right hand side.
         /// @param R2::ArgRef r2 is the left hand side.
         constexpr Mul_Result( typename R1::ArgRef r1, typename R2::ArgRef r2 )
            noexcept(noexcept(R1::ArgRef) && noexcept(R2::ArgRef ) )
            : m_r1(std::move(r1)), m_r2(std::move(r2)){}

         /// computes when requested
         /// @return TResult which is found at compile time which is a double or UnitType<>
         constexpr typename auto result() const noexcept(noexcept(m_r1) && noexcept(m_r2) )
         {
            using namespace SystemOfUnits;

            // line will compiler error if not the same compatible types
            static_assert( t_base::ALLTYPES_THE_SAME::val, "line will compiler error if not the same compatible types" );
            static_assert(Dim::eT == Dim::Z || Dim::eT == 1 || Dim::eT == -1, "T must not be greater abs(1)");

            return TResult
               ( m_r1.amount() 
               * t_base::LenType::toBase()
               * t_base::TimeType::toBase()
               * t_base::MassType::toBase()  // TODO: what about Temperature and charge?
               * t_base::ChargeType::toBase()
               * m_r2.amount()
               );
         }
      };

      /// a class for objects that represents the division of two operands
      template< typename T1, typename T2 >
      class Div_Result : public operators::Base< T1, T2 >
      {
         using t_base = Base< T1, T2 >;
         typename t_base::R1::ExprRef m_r1;    /// first operand reference
         typename t_base::R2::ExprRef m_r2;    /// second operand reference

      public:
         using R1 = t_base::R1;
         using R2 = t_base::R2;

         /// division is based on subtracting the two dimensions of the operands
         enum Dim:int{ Z = 0
            , eL = R1::eL - R2::eL   /// Length Dimensional 
            , et = R1::et - R2::et   /// Time Dimensional 
            , eM = R1::eM - R2::eM   /// Mass Dimensional 
            , eT = R1::eT - R2::eT   /// Temperature Dimensional 
            , eQ = R1::eQ - R2::eQ   /// Charge Dimensional 
         };

         // Yes, these lines are long, but kept long to help the eye catch an error.
         using Length      = typename IF< Dim::eL==Dim::Z, typename R1::Length,      typename IF<R1::eL!=0, typename R1::Length,      typename R2::Length>::RET >::RET;
         using Time        = typename IF< Dim::et==Dim::Z, typename R1::Time,        typename IF<R1::et!=0, typename R1::Time  ,      typename R2::Time  >::RET >::RET;
         using Mass        = typename IF< Dim::eM==Dim::Z, typename R1::Mass,        typename IF<R1::eM!=0, typename R1::Mass  ,      typename R2::Mass  >::RET >::RET;
         using Temperature = typename IF< Dim::eT==Dim::Z, typename R1::Temperature, typename IF<R1::eT!=0, typename R1::Temperature, typename R2::Temperature>::RET >::RET;
         using Charge      = typename IF< Dim::eQ==Dim::Z, typename R1::Charge   ,   typename IF<R1::eQ!=0, typename R1::Charge,      typename R2::Charge>::RET >::RET;

         /// all results are based on the first argument operands type, if NoDim then base on the second argument.
         using TResult = SystemOfUnits::UnitType
            < Length, Dim::eL
            , Time, Dim::et
            , Mass, Dim::eM
            , Temperature, Dim::eT
            , Charge, Dim::eQ
            >;

         /// constructor.
         /// @param R1::ArgRef r1 is the right hand side.
         /// @param R2::ArgRef r2 is the left hand side.
         constexpr Div_Result( typename R1::ArgRef r1, typename R2::ArgRef r2 )
            noexcept(noexcept(R1::ArgRef) && noexcept(R2::ArgRef)) 
            : m_r1(std::move(r1)), m_r2(std::move(r2)){}

         /// computes when requested
         /// @return TResult which is found at compile time
         constexpr typename auto result() const noexcept( noexcept(m_r1) && noexcept(m_r2))
         {
            // line will compiler error if not the same compatible types
            static_assert(t_base::ALLTYPES_THE_SAME::val, "line will compile error if not the same compatible types" );
            static_assert(Dim::eT == Dim::Z || Dim::eT == 1 || Dim::eT == -1 ,"T must not be greater abs(1)");

            return TResult
               ( 
               m_r1.amount() 
               / t_base::LenType::toBase()
               / t_base::TimeType::toBase()
               / t_base::MassType::toBase()
               / t_base::ChargeType::toBase()
               / m_r2.amount() 
               );
         }
      };
   }  // end of namespace operators

   /**
   @page 5 Stream Manipulator for SystemOfUnits::UnitType template to produce dimeninsions only for the type in the stream.
   The template for the manipulator class is based from "Advanced Metaprogramming in Classic C++" page 464 by Davide Di Gennaro ©2015. ISBN 978-1-4842-1011-6.

   Stream manipulators are one of the least known and more expressive pieces of the C++ Standard  They are simply functions which take a stream as an argument.  Since their signature is fixed, streams have a special insertion operator to run them.

   @code t_metricCube m3 = 8.2;
   std::cout << ShowDim << m3 << '\n';
   @endcode

   The output is: @code "8.2 [L]^3" @endcode

   All insertions after @code ShowDim @endcode atcually calls to @code ShowDim_t::operator<< @endcode, not to std::ostream.
   The code generates a unique signature for the manipulator with the proxy itself.  The effect of the manipulator insertion is lost after the next insertion.
   */
   /// Stream Manipulator class ShowDim_t.  
   template< class TOUT >
   class ShowDim_t
   {
      TOUT &out;  /// TOUT can be std::cout, std::ofstream, std::stringstream, or anyother stream which uses insertors.
   public:
      ShowDim_t(TOUT &r) : out(r){}

      /// pass by value instead of reference for built in types.
      template< Arithmetic A> ShowDim_t operator<<(A a) { out << a; return *this; }

      /// Used by the UnitType to display the acutal diminsion
      template< UnitSpecies S > ShowDim_t operator<<(S val)
      {
         using t_unit = S; // SystemOfUnits::UnitType<L, iL, t, it, M, iM, T, iT, Q, iQ>;
         using t_char = typename TOUT::char_type;  // will not compile if TOUT does not have char_type.
         out << val << ' ' << t_Diminsion<t_char, t_unit>(val);
         return *this;
      }

      /// Used by any type besides UnitType and Arithmetic types
      template< typename T > ShowDim_t& operator<<(const T& val)
      {
         out << val;
         return *this;
      }

      /// converts the class to the stream implicitly. Is the last function called by the stream when the Manipulator is used.
      operator TOUT &() const { return out; }
   };

   /// Actual Manipulator used in the stream. The word "dimension" is more universally accepted in other languages besides English.  Replacement for ShowDim. Use of "dimension" is better than "dim" or "ShowDim".  
   template< class TOUT > inline auto dimension() -> ShowDim_t<TOUT>* { return 0; }

   template< class TOUT >
   class ShowUnits_t
   {
      /// TOUT can be std::cout, std::ofstream, std::stringstream, or anyother stream which uses insertors.
      TOUT &ref;
   public:
      ShowUnits_t(TOUT &r) : ref(r){}

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
      operator TOUT &() const { return ref; }
   };

   template< class TOUT > inline auto units() -> ShowUnits_t<TOUT>* { return 0; }


}  // end of namespace SystemOfUnits

/// The functions below require their presence in the global namespace. The alternative is to provide the namespace each time these functions are used.

/// function is used to impliment the stream manipulator SystemOfUnits::UnitType dimensions.  
template< class TOUT >
inline auto operator<<(TOUT & out, SystemOfUnits::ShowDim_t<TOUT>* (*)() ) // -> SystemOfUnits::ShowDim_t<TOUT>
{
   return SystemOfUnits::ShowDim_t<TOUT>(out);
}

template< class TOUT >
inline auto operator<<(TOUT & out, SystemOfUnits::ShowUnits_t<TOUT>* (*)()) //-> SystemOfUnits::ShowDim_t<TOUT>
{
   return SystemOfUnits::ShowUnits_t<TOUT>(out);
}

/// template function which is multiplication operator of two different operands
template < SystemOfUnits::UnitSpecies R1, SystemOfUnits::UnitSpecies R2 >
/** product operator
   @param UnitType left-handed side. Copy is made then moved to Result template operator.
   @param UnitType right-handed side. Copy is made then moved to Result template operator.
   @return the same type is the product of the left and right hand side UnitType.
*/
constexpr inline auto operator*( R1 r1, R2 r2 ) // TODO: write tests for constexpr
noexcept( noexcept(SystemOfUnits::operators::Mul_Result<R1, R2>))
{
   return SystemOfUnits::operators::Mul_Result<R1, R2>(std::move(r1), std::move(r2)).result();
}

/// template function which is divisional operator of two different operands
template< SystemOfUnits::UnitSpecies R1, SystemOfUnits::UnitSpecies R2 >
/** ratio operator
   @param Numerator UnitType left-handed side. Copy is made then moved to Result template operator.
   @param Denominator UnitType left-handed side. Copy is made then moved to Result template operator.
   @return the ratio of the Numerator type by the Denominator type.
*/
constexpr inline auto operator/( R1 r1, R2 r2 )
noexcept(noexcept(SystemOfUnits::operators::Div_Result<R1, R2>))
{
   return SystemOfUnits::operators::Div_Result<R1, R2>(std::move(r1), std::move(r2)).result();
}

// Copyright © 2005-2020 "Curt" Leslie L. Martin, All rights reserved.
// curt.leslie.lewis.martin@gmail.com
//
// Permission to use, copy, modify, and distribute this software for any
// purpose is hereby granted without fee, provided that this copyright and
// permissions notice appear in all copies and derivatives.
//
// This software is provided "as is" without express or implied warranty.

#endif