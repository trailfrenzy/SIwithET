/*
   Provides an implimentation of comparing UnitType to the built in type or to another UnitType.
   Made as a compliment to gtest since prior to this the comparing of UnitTypes required conversion to double in the test.
   Now the conversion to double is hidden in the class and not explicit by the user.
*/
#ifndef SYSTEM_OF_UNITS_EXPECT_UNIT_EQ
#define SYSTEM_OF_UNITS_EXPECT_UNIT_EQ
#include "SI.h"
#include <gtest/gtest.h>
#include <string_view>

template<typename T> concept Arithmetic = std::is_arithmetic<T>::value;

// Class exists only so the inheriting class does not have to define its intiliziation three times for each of the constructors.
class BaseExpect
{
   const ::testing::AssertionResult gtest_ar;
   ::testing::internal::AssertHelper assHelp;
protected:
   /// used by operatora<<() to store the message for display if error.
   ::testing::Message message;

   /// The same constructor is used by the three conctructors below.
   BaseExpect(double t, double u, char const* file, int line, char const* charT, char const* charU)
      : gtest_ar(::testing::internal::CmpHelperFloatingPointEQ<double>(charT, charU, t, u))
      , assHelp(gtest_ar ? ::testing::TestPartResult::kSuccess : ::testing::TestPartResult::kNonFatalFailure, file, line, (gtest_ar ? "" : gtest_ar.message()) )
   {}

   /// The destructor actually writes the message out to std::cout. Note it is not virtual.
   ~BaseExpect()
   {
      assHelp = message;
   }
};

/// Class is only inteded to be used by the Macro at the bottom.
class ExpectUnitEq : private BaseExpect
{
public:
   /// Three different constructors are used since the macro below can generate three different calls.
   template< SOU::UnitSpecies SPEC >
   ExpectUnitEq( SPEC t, double u, char const* file, int line, char const * charT, char const *charU)
      : BaseExpect( t.amount(), u, file, line, charT, charU )
   {}

   template< SOU::UnitSpecies SPEC >
   ExpectUnitEq(double t, SPEC u, char const* file, int line, char const* charT, char const* charU)
      : BaseExpect(t, u.amount(), file, line, charT, charU)
   {}

   template< SOU::UnitSpecies T, SOU::UnitSpecies U >
   ExpectUnitEq(T t, U u, char const* file, int line, char const* charT, char const* charU)
      : BaseExpect(t.amount(), u.amount(), file, line, charT, charU)
   {}

   /// Most of the time it is a char const * string we are passing
   ExpectUnitEq& operator<<(std::string_view val)
   {
      message << val;
      return *this;
   }

   // Used with built in types. Not expected to have a lot of them.
   template< Arithmetic A > ExpectUnitEq& operator<<(A val) { message << val; return *this; }

   // Special operator<<() for all UnitTypes, pass by value.
   template< SOU::UnitSpecies SPEC > ExpectUnitEq& operator<<(SPEC val)
   {
      message << val;
      return *this;
   }

   /// Used by any type which does not has its own operator<<();
   template< typename T > ExpectUnitEq& operator<<(const T& val)
   {
      message << val;
      return *this;
   }
};

/// Yes, we still must use a macro since the file name, line number and two varibles must be generated at compile time.
/// Not sure how else to do it.
#define EXPECT_UNIT_EQ( t,  u) ExpectUnitEq(t, u, __FILE__, __LINE__, #t, #u )

/*
The above macro is used like any other Google Unit test.

TEST(reinterpit_cast, failedTest)
{
   typedef SOU::MakeSQ< Metric::t_gram >::type t_gramSq;
   t_gramSq kiloSq{ 1.0 };

   EXPECT_UNIT_EQ(2.0, kiloSq) << "Unhappy message goes here " << kiloSq << " and continue with more";

}

*/

#endif

// Copyright © 2005-2020 "Curt" Leslie L. Martin, All rights reserved.
// curt.leslie.lewis.martin@gmail.com
//
// Permission to use, copy, modify, and distribute this software for any
// purpose is hereby granted without fee, provided that this copyright and
// permissions notice appear in all copies and derivatives.
//
// This software is provided "as is" without express or implied warranty.
