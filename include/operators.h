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
//#include "boost/type_traits/is_same.hpp"  /// find if two types are the same at compile time
//#include "boost/static_assert.hpp"        /// used for compile time asserts
//#include "boost/mpl/if.hpp"               /// used for compile time if statements

namespace SystemOfUnits
{
   namespace operators
   {
      /** \brief The trait idea came from "C++ Templates", pg 332.
       trait is used to allow built in types to be used as args in operator's mul and div 
       The @code A_Trait<T1,T2> @endcode templates are used during has hidden templates that are
       created during multiplication and division operations using the SI templates.  @code A_Trait<T1,T2> @endcode
       allows operators "*" and "/" to use references of the SI types and values for built in types.
       
       */
      template < typename T, typename T2 > struct A_Trait
      {
         /// used as the argument for the operators
         typedef T const &ArgRef;
         /// constant reference
         typedef T const &ExprRef;

         /// the dimensions of the trait
         enum 
         { eL = T::eL   /// Length Dimension 
         , et = T::et   /// Time Dimension
         , eM = T::eM   /// Mass Dimension
         , eT = T::eT   /// Tempeture Dimension
         , eQ = T::eQ   /// Charge Dimension
         };

         typedef typename T::Length Length;        /// Length type of the incoming arg.
         typedef typename T::Time Time;            /// Time type of the incoming arg.
         typedef typename T::Mass Mass;            /// Mass type of the incoming arg.
         typedef typename T::Tempeture Tempeture;  /// Tempeture of the incoming arg.
         typedef typename T::Charge Charge;        /// Charge of the incoming arg.
      };

      /** NOTE:
       #define MAKE_ATRAIT() is use to make specilized templated of built in types
       Used to make multiplications of built in types against the types produced by SI template.
	   For example \code meter = meter * 4;   \endcode or \code feet = feet * 5.0; \endcode
	   It is not a good habit of using built in scalar types, but the option needs to be provided.
	  */

#ifndef MAKE_ATRAIT
#define MAKE_ATRAIT( XX ) template< typename T2 > struct A_Trait< XX, T2 >\
      {\
      /** Used as the argument for the operators, with the built in types it is a pass by value.  */\
      typedef XX ArgRef;\
      /** For the built in types, still need to use a SI unit type, but one that is dimension less */\
      using ExprRef = tNoUnit; \
      /** Keep the dimensions at zero */\
      enum { eL = 0, et = 0, eM = 0, eT=0, eQ=0 };\
      typedef typename T2::Length Length;\
      typedef typename T2::Time Time;\
      typedef typename T2::Mass Mass;\
      typedef typename T2::Tempeture Tempeture;\
      typedef typename T2::Charge Charge;\
      };

	  /// creates struct A_Trait<double, typename T2>
      MAKE_ATRAIT( double );        

	  /// creates struct A_Trait<float, typename T2>
      MAKE_ATRAIT( float );         

	  /// creates struct A_Trait<int, typename T2>
      MAKE_ATRAIT( int );           

	  /// creates struct A_Trait<unsigned, typename T2>
      MAKE_ATRAIT( unsigned );      

	  /// creates struct A_Trait<long, typename T2>
      MAKE_ATRAIT( long );

	  /// creates struct A_Trait<unsigned long, typename T2>
      MAKE_ATRAIT( unsigned long );

      /// creates struct A_Trait<short, typename T2>
      MAKE_ATRAIT( short );

      /// creates struct A_Trait<unsigned short, typename T2>
      MAKE_ATRAIT( unsigned short ); 
	  MAKE_ATRAIT(long long);
	  MAKE_ATRAIT(unsigned long long);
#endif 
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
            static double toBase() 
            { 
               return A1::toBase() * A2::toBase() * A1::fromBase() * A1::fromBase(); 
            }
         };

      protected:
         //typename typedef A_Trait<T1,T2> R1; /// the type of the left side of the arg
         //typename typedef A_Trait<T2,T1> R2; /// the type of the right side of the arg
      public:
		  using R1 = A_Trait<T1, T2>; /// the type of the left side of the arg
		  using R2 = A_Trait<T2, T1>; /// the type of the right side of the arg
											   /// public enum is used to let users know that the types did not match
         /// ie so feet and meters are not mixed up but both are base units
		  enum class ALLTYPES_THE_SAME : bool {
			  val =
			  (is_same<R1::Length::Base, R2::Length::Base>::value
				  && is_same<R1::Time::Base, R2::Time::Base >::value
				  && is_same<R1::Mass::Base, R2::Mass::Base >::value
				  && is_same<R1::Tempeture::Base, R2::Tempeture::Base >::value
				  && is_same<R1::Charge::Base, R2::Charge::Base >::value
				  )
			  || (R1::eL == 0 && R1::et == 0 && R1::eM == 0 && R1::eT == 0 && R1::eQ == 0)
			  || (R2::eL == 0 && R2::et == 0 && R2::eM == 0 && R2::eT == 0 && R2::eQ == 0)
			  , T = true
         };

		  friend constexpr bool operator==(const ALLTYPES_THE_SAME lf, const bool rt) { return lf == rt;  }

         // if the length as same type ie meter to meter, not meter to kilometer
		 // enum value will be true if the two types are the same.
         enum{ IsLengthSame = is_same< typename R1::Length, typename R2::Length >::value };
         enum{ IsTimeSame   = is_same< typename R1::Time,   typename R2::Time   >::value };
         enum{ IsMassSame   = is_same< typename R1::Mass,   typename R2::Mass   >::value };
         enum{ IsTempSame   = is_same< typename R1::Tempeture, typename R2::Tempeture >::value };
         enum{ IsChargeSame = is_same< typename R1::Charge, typename R2::Charge >::value };

         /// need to know if BOTH the dimensions in the two operands are base
         enum{ AreLengthsBase = R1::Length::IsBase && R2::Length::IsBase };
         /// need to know if BOTH the dimensions in the two operands are base
         enum{ AreTimeBase    = R1::Time::IsBase   && R2::Time::IsBase };
         /// need to know if BOTH the dimensions in the two operands are base
         enum{ AreMassBase    = R1::Mass::IsBase   && R2::Mass::IsBase };
         /// need to know if BOTH the dimensions in the two operands are base
         enum{ AreTempBase    = R1::Tempeture::IsBase && R2::Tempeture::IsBase };
         /// need to know if BOTH the dimensions in the two operands are base
         enum{ AreChargeBase  = R1::Charge::IsBase && R2::Charge::IsBase };

		 /* what are the 4 proposed traits going to be used for */
         /// the proposed length type of the result
         typename typedef IF //boost::mpl::if_c
            < R1::eL == 0 || R2::eL == 0
            , NoDim
            , typename IF //boost::mpl::if_c
            < IsLengthSame
            , NoDim
            , typename IF //boost::mpl::if_c
            < !R1::Length::IsBase && !R2::Length::IsBase
            , CombineBaseTypes<typename R1::Length, typename R2::Length>
            , typename IF<R2::Length::IsBase, typename SOU::MakeFrom<typename R1::Length>, typename R2::Length >::RET
            >::RET
            >::RET
            >::RET LenType;

         /// the proposed time type of the result
         typename typedef IF //boost::mpl::if_c
            < R1::et == 0 || R2::et == 0
            , NoDim
            , typename IF //boost::mpl::if_c
            < IsTimeSame
            , NoDim
            , typename IF //boost::mpl::if_c
            < !R1::Time::IsBase && !R2::Time::IsBase
            , CombineBaseTypes<typename R1::Time, typename R2::Time>
            , typename IF<R2::Time::IsBase, SOU::MakeFrom<typename R1::Time>, typename R2::Time >::RET
            >::RET 
            >::RET
            >::RET TimeType;

         /// the proposed mass type of the result
         typename typedef IF //boost::mpl::if_c
            < R1::eM == 0 || R2::eM == 0
            , NoDim
            , typename IF //boost::mpl::if_c
               < IsMassSame
               , NoDim
               , typename IF //boost::mpl::if_c
                  < !R1::Mass::IsBase && !R2::Mass::IsBase
                  , CombineBaseTypes<typename R1::Mass, typename R2::Mass>
                  , typename IF<R2::Mass::IsBase, SOU::MakeFrom<typename R1::Mass>, typename R2::Mass >::RET
                  >::RET 
               >::RET
            >::RET MassType;

         /// the proposed temperature type of the result
         typename typedef IF //boost::mpl::if_c
            < R1::eT == 0 || R2::eT == 0
            , NoDim
            , typename IF //boost::mpl::if_c
            < IsTempSame
            , NoDim
            , typename IF //boost::mpl::if_c
            < !R1::Tempeture::IsBase && !R2::Tempeture::IsBase
            , CombineBaseTypes<typename R1::Tempeture, typename R2::Tempeture>
            , typename IF<R2::Tempeture::IsBase, SOU::MakeFrom<typename R1::Tempeture>, typename R2::Tempeture >::RET
            >::RET 
            >::RET
            >::RET TempetureType;

      };

      /// a class for objects that represents the multiplication of two operands
      template< typename T1, typename T2 >
      class Mul_Result : public operators::base< T1, T2 >
      {
		  using t_base = base< T1, T2 >;
		  //using R1 = A_Trait<T1, T2>;
         typename t_base::R1::ExprRef m_r1;    /// first operand reference
         typename t_base::R2::ExprRef m_r2;    /// second operand reference
      public:
		  using R1 = t_base::R1;
		  using R2 = t_base::R2;
         /// multiplication is addition of the powers 
         enum class Dim : int { Z = 0
				, eL = R1::eL + R2::eL   /// Length Dimension 
              , et = R1::et + R2::et   /// Time Dimension 
              , eM = R1::eM + R2::eM   /// Mass Dimension 
              , eT = R1::eT + R2::eT   /// Tempeture Dimension 
              , eQ = R1::eQ + R2::eQ };/// Charge Dimension 

		 friend constexpr bool operator==(const Dim lf, const int rt) { return lf == rt;  }
		 
         /// informs us during the compile process that the result has no dimensions.
		 //enum { bbb = (Dim::eL == 0) };
         enum class isNoDim : bool { val = (Dim::eL==Dim::Z) && (Dim::et== Dim::Z) && (Dim::eM== Dim::Z) && (Dim::eQ== Dim::Z) && (Dim::eT== Dim::Z) };

         typename typedef IF< Dim::eL== Dim::Z, typename R1::Length,   typename IF<R1::eL!=0, typename R1::Length, typename R2::Length>::RET >::RET Length;
         typename typedef IF< Dim::et== Dim::Z, typename R1::Time  ,    typename IF<R1::et!=0, typename R1::Time  , typename R2::Time  >::RET >::RET Time;
         typename typedef IF< Dim::eM== Dim::Z, typename R1::Mass,      typename IF<R1::eM!=0, typename R1::Mass  , typename R2::Mass  >::RET >::RET Mass;
         typename typedef IF< Dim::eT== Dim::Z, typename R1::Tempeture, typename IF<R1::eT!=0, typename R1::Tempeture, typename R2::Tempeture>::RET >::RET Tempeture;
         typename typedef IF< Dim::eQ== Dim::Z, typename R1::Charge   , typename IF<R1::eQ!=0, typename R1::Charge, typename R2::Charge>::RET >::RET Charge;

         /// all results are based on the first operands type, if NoDim then base on the second.
         typedef SOU::unitType
            < Length, (int)Dim::eL
            , Time, (int)Dim::et
            , Mass, (int)Dim::eM
            , Tempeture, (int)Dim::eT
            , Charge, (int)Dim::eQ
            > TBeforeResult;

      public:
         /// if not dimensions then the return type is double
         typename typedef  IF< (bool)isNoDim::val, double, typename TBeforeResult >::RET TResult;

         /// constructor initializes references to the operands.
         /// @param R1::ArgRef r1 is the right hand side.
         /// @param R2::ArgRef r2 is the left hand side.
         Mul_Result( typename R1::ArgRef r1, typename R2::ArgRef r2 ) : m_r1(r1), m_r2(r2){}

         /// computes when requested
         /// @return TResult which is found at compile time
         typename TResult result() const
         {
            using namespace SOU;

            // line will crash if not the same compatible types
            STATIC_ASSERTION_FAILURE< static_cast<bool>(t_base::ALLTYPES_THE_SAME::val) >;
            // temperature is not supported in more than 1 dimension
            STATIC_ASSERTION_FAILURE< static_cast<bool>( (int)Dim::eT == 0 || (int)Dim::eT == 1 || (int)Dim::eT == -1) >;

            return TResult
               ( m_r1.amount() 
               * t_base::LenType::toBase()
               * t_base::TimeType::toBase()
               * t_base::MassType::toBase()
               * m_r2.amount()
               );
         }
      };

      /// a class for objects that represents the division of two operands
      template< typename T1, typename T2 >
      class Div_Result : public operators::base< T1, T2 >
      {
		  //using R1 = A_Trait<T1, T2>;
         typename base::R1::ExprRef m_r1;    /// first operand reference
         typename base::R2::ExprRef m_r2;    /// second operand reference

      public:
		  using R1 = base::R1;
		  using R2 = base::R2;
         /// division is based on subtracting the two dimensions of the operands
         enum class Dim{ eL = R1::eL - R2::eL   /// Length Dimension 
              , et = R1::et - R2::et   /// Time Dimension 
              , eM = R1::eM - R2::eM   /// Mass Dimension 
              , eT = R1::eT - R2::eT   /// Tempeture Dimension 
              , eQ = R1::eQ - R2::eQ };/// Charge Dimension 

         /// informs us during the compile process that the result has no dimensions.
         enum { isNonDim = Dim::eL==0 && Dim::et==0 && Dim::eM==0 && Dim::eT==0 && Dim::eQ==0 };

		 typename typedef IF< Dim::eL==0, typename R1::Length,    typename IF<R1::eL!=0, typename R1::Length, typename R2::Length>::RET >::RET  Length;
         typename typedef IF< Dim::et==0, typename R1::Time  ,    typename IF<R1::et!=0, typename R1::Time  , typename R2::Time  >::RET >::RET Time;
         typename typedef IF< Dim::eM==0, typename R1::Mass,      typename IF<R1::eM!=0, typename R1::Mass  , typename R2::Mass  >::RET >::RET Mass;
         typename typedef IF< Dim::eT==0, typename R1::Tempeture, typename IF<R1::eT!=0, typename R1::Tempeture, typename R2::Tempeture>::RET >::RET Tempeture;
         typename typedef IF< Dim::eQ==0, typename R1::Charge   , typename IF<R1::eQ!=0, typename R1::Charge, typename R2::Charge>::RET >::RET Charge;

         /// the type it will be if the dims are not 0
         using TBeforeResult  = SOU::unitType
            < Length, Dim::eL
            , Time, Dim::et
            , Mass, Dim::eM
            , Tempeture, Dim::eT
            , Charge, Dim::eQ
            > ;
         /// enum is used so let user know that the types did not match
         /// all results are based on the first operands type, if NoDim then base on the second.
		 typename typedef IF<isNonDim, double, typename TBeforeResult >::RET TResult;
		 // TResult = IF<isNonDim, double, typename TBeforeResult >::RET;

         /// constructor.
         /// @param R1::ArgRef r1 is the right hand side.
         /// @param R2::ArgRef r2 is the left hand side.
         Div_Result( typename R1::ArgRef r1, typename R2::ArgRef r2 ) : m_r1(r1), m_r2(r2){}

         /// computes when requested
         /// @return TResult which is found at compile time
         typename TResult result() const
         {
            // line will crash if not the same compatible types
            STATIC_ASSERTION_FAILURE< eALLTYPES_THE_SAME >;
            STATIC_ASSERTION_FAILURE< eT == 0 || eT == 1 || eT == -1 >;

            return TResult
               ( 
               m_r1.amount() 
               / LenType::toBase()
               / TimeType::toBase()
               / MassType::toBase()
               / m_r2.amount() 
               );
         }
      };

   }  // end of namespace operators
}  // end of namespace SystemOfUnits


/// template function which is multiplication operator of two different operands
template < typename R1, typename R2 >
inline typename SOU::operators::Mul_Result<R1,R2>::TResult operator*( R1 const &r1, R2 const &r2 )
{
   return SOU::operators::Mul_Result<R1,R2>(r1,r2).result();
}

/// template function which is divisional operator of two different operands
template< typename R1, typename R2 >
inline typename SOU::operators::Div_Result<R1,R2>::TResult operator/( R1 const &r1, R2 const &r2 )
{
   return SOU::operators::Div_Result<R1,R2>(r1,r2).result();
}

// Copyright © 2005-2015 "Curt" Leslie L. Martin, All rights reserved.
// curt.leslie.lewis.martin@gmail.com
//
// Permission to use, copy, modify, and distribute this software for any
// purpose is hereby granted without fee, provided that this copyright and
// permissions notice appear in all copies and derivatives.
//
// This software is provided "as is" without express or implied warranty.

/**

*/
#endif