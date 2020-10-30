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
   namespace operators
   {
      template<typename T> concept Arithmetic = std::is_arithmetic<T>::value;

      /** \brief The trait idea came from "C++ Templates", pg 332.
       trait is used to allow built in types to be used as args in operator's mul and div 
       The @code A_Trait<T1,T2> @endcode templates are used during has hidden templates that are
       created during multiplication and division operations using the SI templates.  @code A_Trait<T1,T2> @endcode
       allows operators "*" and "/" to use references of the SI types and values for built in types.
       */
      template < UnitSerial T, UnitSerial T2 > struct A_Trait
      {
         static_assert(SOU::is_UnitType<T>::value, "Must be a SOU::UnitType");
         static_assert(SOU::is_UnitType<T2>::value || std::is_arithmetic<T2>::value, "Must be a SOU::UnitType or arithmetic type");
         /// used as the argument for the operators
         using ArgRef = T const &;
         /// constant reference
         using ExprRef = T const &;

         /// the dimensions of the trait
         enum
         { eL = T::eL   /// Length Dimension 
         , et = T::et   /// Time Dimension
         , eM = T::eM   /// Mass Dimension
         , eT = T::eT   /// Temperature Dimension
         , eQ = T::eQ   /// Charge Dimension
         };

         using Length = typename T::Length;        /// Length type of the incoming arg.
         using Time = typename T::Time;            /// Time type of the incoming arg.
         using Mass = typename T::Mass;            /// Mass type of the incoming arg.
         using Temperature = typename T::Temperature;  /// Temperature of the incoming arg.
         using Charge = typename T::Charge;        /// Charge of the incoming arg.
      };

      /** NOTE:
       #define MAKE_ATRAIT() is use to make specilized templated of built in types
       Used to make multiplications of built in types against the types produced by SI template.
	   For example \code meter = meter * 4;   \endcode or \code feet = feet * 5.0; \endcode
	   It is not a good habit of using built in scalar types, but the option needs to be provided.
      Not sure if there is another option to creating the specilized templates than using MACROS.
      Currently MAKE_ATRAIT is the only MACRO used in the SI Project.
	  */

      // TODO explore using std::enable_if<> with std::is_arithmetic<>

      //template< typename T2 > struct A_Trait< XX, T2 >
      //{
      //   /** Used as the argument for the operators, with the built in types it is a pass by value.  */
      //   using ArgRef = const XX;

      //   /** For the built in types, still need to use a SI unit type, but one that is dimension less */
      //   using ExprRef = const tNoUnit;

      //   /** Keep the dimensions at zero */
      //   enum { eL = 0, et = 0, eM = 0, eT = 0, eQ = 0 };

      //   typedef typename T2::Length Length;
      //   typedef typename T2::Time Time;
      //   typedef typename T2::Mass Mass;
      //   typedef typename T2::Temperature Temperature;
      //   typedef typename T2::Charge Charge;
      //};


#define MAKE_ATRAIT
#ifndef MAKE_ATRAIT
#define MAKE_ATRAIT( XX ) template< typename T2 > struct A_Trait< XX, T2 >\
      {\
      /** Used as the argument for the operators, with the built in types it is a pass by value.  */\
      using ArgRef = const NoUnit;\
      /** For the built in types, still need to use a SI unit type, but one that is dimension less */\
      using ExprRef = const NoUnit; \
      /** Keep the dimensions at zero */\
      enum { eL = 0, et = 0, eM = 0, eT=0, eQ=0 };\
      typedef typename T2::Length Length;\
      typedef typename T2::Time Time;\
      typedef typename T2::Mass Mass;\
      typedef typename T2::Temperature Temperature;\
      typedef typename T2::Charge Charge;\
      };

      /// creates struct A_Trait<double, typename T2>
      MAKE_ATRAIT(double);
      MAKE_ATRAIT(double long);

      /// creates struct A_Trait<float, typename T2>
      //MAKE_ATRAIT(float);

      /// creates struct A_Trait<int, typename T2>
      //MAKE_ATRAIT(int);

      /// creates struct A_Trait<unsigned, typename T2>
      //MAKE_ATRAIT(unsigned);

      /// creates struct A_Trait<long, typename T2>
      //MAKE_ATRAIT(long);

      /// creates struct A_Trait<unsigned long, typename T2>
      //MAKE_ATRAIT(unsigned long);

      /// creates struct A_Trait<short, typename T2>
      //MAKE_ATRAIT(short);

      /// creates struct A_Trait<unsigned short, typename T2>
      //MAKE_ATRAIT(unsigned short);
      //MAKE_ATRAIT(long long);
      //MAKE_ATRAIT(unsigned long long);
#endif 

      template< typename R1, typename R2 >
      struct is_same_BASE {
         enum : bool {
            value =
            std::is_same<R1::Length::Base, R2::Length::Base>::value
            && std::is_same<R1::Time::Base, R2::Time::Base >::value
            && std::is_same<R1::Mass::Base, R2::Mass::Base >::value
            && std::is_same<R1::Temperature::Base, R2::Temperature::Base >::value
            && std::is_same<R1::Charge::Base, R2::Charge::Base >::value
         };
      };
      template< typename R1 > struct is_zero_dimensions
      {
         enum : bool { value = R1::eL == 0 && R1::et == 0 && R1::eM == 0 && R1::eT == 0 && R1::eQ == 0 };
      };

      /// base class to Mul_Result and Div_Result
      /** NOTE:
      "Expression Templates, Chap 18", C++ Templates The Complete Guide, Addison-Wesley,
      David Vandevoorde and Nicolai M. Josuttis, 2003.

      The ideas for these two classes came from the above reference.

      A good article to read more about expression templates see:
      "String Concatenation & Expression Templates", Craig Henderson, 'C/C++ Users Journal', June 2005

	  Remember that all enums and types are calculated at compile time.
      */
      template< typename T1, typename T2 > class base
      {
         /// private struct used in the the two operators (* / )
         template< typename A1, typename A2 > struct CombineBaseTypes
         {
            constexpr static double toBase() noexcept( noexcept(A1) && noexcept(A1) )
            { 
               return A1::toBase() * A2::toBase() * A1::fromBase() * A1::fromBase(); 
            }
         };

      public:
         using R1 = A_Trait<T1, T2>; /// the type of the left side of the arg
         using R2 = A_Trait<T2, T1>; /// the type of the right side of the arg

         /// public enum is used to let users know that the types did not match
         /// ie so feet and meters are not mixed up but both are base units
         enum ALLTYPES_THE_SAME : bool {
            val = is_same_BASE<R1, R2 >::value
            || is_zero_dimensions<R1>::value
            || is_zero_dimensions<R2>::value
            , T = true
         };

         // Below is a compile time check to compare if the length as same type ie meter to meter, not meter to kilometer
         // enum value is true if the two types are the same.
         enum :bool { IsLengthSame = std::is_same< typename R1::Length, typename R2::Length >::value };
         enum :bool { IsTimeSame = std::is_same< typename R1::Time, typename R2::Time   >::value };
         enum :bool { IsMassSame = std::is_same< typename R1::Mass, typename R2::Mass   >::value };
         enum :bool { IsTempSame = std::is_same< typename R1::Temperature, typename R2::Temperature >::value };
         enum :bool { IsChargeSame = std::is_same< typename R1::Charge, typename R2::Charge >::value };

         /* what are the 4 proposed traits used for */
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
            , typename IF<R2::Length::IsBase, typename SOU::MakeFrom<typename R1::Length>, typename R2::Length >::RET
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
            , typename IF<R2::Time::IsBase, SOU::MakeFrom<typename R1::Time>, typename R2::Time >::RET
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
                  , typename IF<R2::Mass::IsBase, SOU::MakeFrom<typename R1::Mass>, typename R2::Mass >::RET
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
            , typename IF<R2::Temperature::IsBase, SOU::MakeFrom<typename R1::Temperature>, typename R2::Temperature >::RET
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
            , typename IF<R2::Charge::IsBase, SOU::MakeFrom<typename R1::Charge>, typename R2::Charge >::RET
            >::RET
            >::RET
            >::RET;

      };

      /// a class for objects that represents the multiplication of two operands
      template< typename T1, typename T2 >
      class Mul_Result : public operators::base< T1, T2 >
      {
		  using t_base = base< T1, T2 >;

        typename const t_base::R1::ExprRef m_r1;    /// first operand reference
        typename const t_base::R2::ExprRef m_r2;    /// second operand reference
      public:
		  using R1 = t_base::R1;
		  using R2 = t_base::R2;
         /// multiplication is addition of the powers 
         enum Dim : int { Z = 0
              , eL = R1::eL + R2::eL   /// Length Dimension 
              , et = R1::et + R2::et   /// Time Dimension 
              , eM = R1::eM + R2::eM   /// Mass Dimension 
              , eT = R1::eT + R2::eT   /// Temperature Dimension 
              , eQ = R1::eQ + R2::eQ };/// Charge Dimension 

         /// informs user during the compile process if the result has no dimensions.
         enum isNoDim : bool { val = is_zero_dimensions<Dim>::value };

         using Length = typename IF< Dim::eL== Dim::Z, typename R1::Length,   typename IF<R1::eL!=0, typename R1::Length, typename R2::Length>::RET >::RET;

         using Time = typename IF< Dim::et== Dim::Z, typename R1::Time  ,    typename IF<R1::et!=0, typename R1::Time  , typename R2::Time  >::RET >::RET;
         using Mass = typename IF< Dim::eM== Dim::Z, typename R1::Mass,      typename IF<R1::eM!=0, typename R1::Mass  , typename R2::Mass  >::RET >::RET;
         using Temperature = typename IF< Dim::eT== Dim::Z, typename R1::Temperature, typename IF<R1::eT!=0, typename R1::Temperature, typename R2::Temperature>::RET >::RET;
         using Charge = typename IF< Dim::eQ== Dim::Z, typename R1::Charge   , typename IF<R1::eQ!=0, typename R1::Charge, typename R2::Charge>::RET >::RET;

         /// all results are based on the first operands type, if NoDim then base on the second.
         using TBeforeResult = SOU::unitType
            < Length, Dim::eL
            , Time, Dim::et
            , Mass, Dim::eM
            , Temperature, Dim::eT
            , Charge, Dim::eQ
            >;

      public:
         /// if not dimensions then the return type is double
         using TResult = typename IF<isNoDim::val, tNoUnit::t_float, typename TBeforeResult >::RET;

         /// constructor initializes references to the operands.
         /// @param R1::ArgRef r1 is the right hand side.
         /// @param R2::ArgRef r2 is the left hand side.
         constexpr Mul_Result( typename const R1::ArgRef r1, typename const R2::ArgRef r2 )
            noexcept(noexcept(R1::ArgRef) && noexcept(R2::ArgRef ) )
            : m_r1(r1), m_r2(r2){}

         /// computes when requested
         /// @return TResult which is found at compile time which is a double or UnitType<>
         constexpr typename auto result() const noexcept(noexcept(m_r1) && noexcept(m_r2) )
         {
            using namespace SOU;

            // line will compiler error if not the same compatible types
            static_assert( t_base::ALLTYPES_THE_SAME::val, "line will compiler error if not the same compatible types" );
            // temperature is not supported in more than 1 dimension
            static_assert(Dim::eT == 0 || Dim::eT == 1 || Dim::eT == -1, "temperature is not supported in more than 1 dimension" );

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
      class Div_Result : public operators::base< T1, T2 >
      {
         using t_base = base< T1, T2 >;
         typename t_base::R1::ExprRef m_r1;    /// first operand reference
         typename t_base::R2::ExprRef m_r2;    /// second operand reference

      public:
         using R1 = t_base::R1;
         using R2 = t_base::R2;
         /// division is based on subtracting the two dimensions of the operands
         enum Dim:int{ Z = 0
            , eL = R1::eL - R2::eL   /// Length Dimension 
            , et = R1::et - R2::et   /// Time Dimension 
            , eM = R1::eM - R2::eM   /// Mass Dimension 
            , eT = R1::eT - R2::eT   /// Temperature Dimension 
            , eQ = R1::eQ - R2::eQ
         };/// Charge Dimension 

         /// informs us during the compile process that the result has no dimensions.
         enum isNoDim : bool { val = is_zero_dimensions<Dim>::value };

         using Length = typename IF< Dim::eL==Dim::Z, typename R1::Length,    typename IF<R1::eL!=0, typename R1::Length, typename R2::Length>::RET >::RET;
         using  Time = typename IF< Dim::et==Dim::Z, typename R1::Time,     typename IF<R1::et!=0, typename R1::Time  , typename R2::Time  >::RET >::RET;
         using Mass = typename IF< Dim::eM==Dim::Z, typename R1::Mass,      typename IF<R1::eM!=0, typename R1::Mass  , typename R2::Mass  >::RET >::RET;
         using Temperature = typename IF< Dim::eT==Dim::Z, typename R1::Temperature, typename IF<R1::eT!=0, typename R1::Temperature, typename R2::Temperature>::RET >::RET;
         using Charge = typename IF< Dim::eQ==Dim::Z, typename R1::Charge   , typename IF<R1::eQ!=0, typename R1::Charge, typename R2::Charge>::RET >::RET;

         /// the type it will be if the dims are not 0
         using TBeforeResult = SOU::unitType
            < Length, Dim::eL
            , Time, Dim::et
            , Mass, Dim::eM
            , Temperature, Dim::eT
            , Charge, Dim::eQ
            >;
         /// enum is used so let user know that the types did not match
         /// all results are based on the first operands type, if NoDim then base on the second.
         using TResult = typename IF<isNoDim::val, tNoUnit::t_float, typename TBeforeResult >::RET;

         /// constructor.
         /// @param R1::ArgRef r1 is the right hand side.
         /// @param R2::ArgRef r2 is the left hand side.
         constexpr Div_Result( typename R1::ArgRef r1, typename R2::ArgRef r2 )
            noexcept(noexcept(R1::ArgRef) && noexcept(R2::ArgRef)) 
            : m_r1(r1), m_r2(r2){}

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
      ShowDim_t(TOUT &r) : out(r){} // TBD: Make private but will require the inserter which calls it in the same namespace.

      /// pass by value instead of reference.
      ShowDim_t& operator<<(char c) { out << c; return *this; }
      ShowDim_t& operator<<(int i) { out << i; return *this; }
      ShowDim_t& operator<<(unsigned u) { out << u; return *this; }

      /// Used by any type besides UnitType
      template< typename T > ShowDim_t& operator<<(const T& val)
      {
         if constexpr (is_UnitType<T>::value)
         {
            using t_unit = T; // SOU::unitType<L, iL, t, it, M, iM, T, iT, Q, iQ>;
            using t_char = typename TOUT::char_type;  // will not compile if TOUT does not have char_type.
            out << val << ' ' << t_Diminsion<t_char, t_unit>(val);
         }
         else
         {
            out << val;
         }
         return *this;
      }

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
      ShowUnits_t(TOUT &r) : ref(r){} // TBD: Make private but will require the inserter which calls it to be in the same namespace.

      /// pass by value instead of reference. If in the same stream the user inserts one of these built in types.
      ShowUnits_t& operator<<(char c) { ref << c; return *this; }
      ShowUnits_t& operator<<(int i) { ref << i; return *this; }
      ShowUnits_t& operator<<(unsigned u) { ref << u; return *this; }

      /// Used by any type including UnitType. Compiler decides if a UnitType and to and names.
      template< typename T > ShowUnits_t& operator<<(const T& val)
      {
         if constexpr (is_UnitType<T>::value)
         {
            using t_char = typename TOUT::char_type;  // will not compile if TOUT does not have char_type.
            ref << val << ' ' << SOU::UnitName<t_char>(val);
         }
         else{
            ref << val;
         }
         return *this;
      }

      operator TOUT &() const { return ref; }
   };

   template< class TOUT > inline auto units() -> ShowUnits_t<TOUT>* { return 0; }


}  // end of namespace SystemOfUnits

/// The functions below require their presence in the global namespace. The alternative is to provide the namespace each time these functions are used.

/// function is used to impliment the stream manipulator SOU::UnitType dimensions.  
template< class TOUT >
inline auto operator<<(TOUT & out, SOU::ShowDim_t<TOUT>* (*)() ) // -> SOU::ShowDim_t<TOUT>
{
   return SOU::ShowDim_t<TOUT>(out);
}

template< class TOUT >
inline auto operator<<(TOUT & out, SOU::ShowUnits_t<TOUT>* (*)()) //-> SOU::ShowDim_t<TOUT>
{
   return SOU::ShowUnits_t<TOUT>(out);
}

/// template function which is multiplication operator of two different operands
template < SOU::UnitSerial R1, SOU::UnitSerial R2 >
constexpr inline auto operator*( R1 const &r1, R2 const &r2 )
noexcept( noexcept(SOU::operators::Mul_Result<R1, R2>))
{
   return SOU::operators::Mul_Result<R1, R2>(r1, r2).result();
}

/// template function which is divisional operator of two different operands
template< SOU::UnitSerial R1, SOU::UnitSerial R2 >
constexpr inline auto operator/( R1 const &r1, R2 const &r2 )
noexcept(noexcept(SOU::operators::Div_Result<R1, R2>))
{
   //if constexpr (SOU::is_UnitType<R1>::value && SOU::is_UnitType<R2>::value)
   {
      return SOU::operators::Div_Result<R1, R2>(r1, r2).result();
   }
   //if constexpr (std::is_arithmetic<R1>::value && SOU::is_UnitType<R2>::value)
   //{
   //   return SOU::operators::Div_Result< SOU::tNoUnit, R2>(SOU::tNoUnit(r1), r2).result();
   //}
   //return SOU::operators::Div_Result<R1,R2>(r1,r2).result();
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