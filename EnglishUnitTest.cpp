#include <cppunit/extensions/HelperMacros.h>
#include "EnglishTypes.h"
#include "MetricTypes.h"
#include "operators.h"
#include "conversion_cast.h"

namespace
{
   double const delta = 0.000001;
}

// basic test on the multiplication operator
class EnglishUnitTest : public CppUnit::TestFixture
{
public:
   void setUp(){}
   void tearDown(){}
private:

   /// Test converting Feet per second from Feet / Second.
   void TestFPS()
   {
      English::t_foot Feet = 144;
      English::t_second Second = 4;

      English::t_FPS fps = Feet / Second;

      CPPUNIT_ASSERT_DOUBLES_EQUAL( 36.0, fps.amount(), delta );

      English::t_FPSS fpss = fps/English::t_second(2.0);
      CPPUNIT_ASSERT_DOUBLES_EQUAL( 18.0, fpss.amount(), delta );
   }
   /// Tests converting different types of length.
   void TestLength()
   {
      using namespace SOU;

      English::t_mile mile = 1.0;
      English::t_foot feet = SOU::conversion_cast< English::t_foot >( mile );
      CPPUNIT_ASSERT_DOUBLES_EQUAL( 5280.0, feet.amount(), delta );

      feet = 15;
      English::t_yard yard = conversion_cast< English::t_yard >( feet );
      CPPUNIT_ASSERT_DOUBLES_EQUAL( 5.0, yard.amount(), delta );

      English::t_mph mph = 65.0;
      English::t_FPS fps = SOU::conversion_cast< English::t_FPS >( mph );
      CPPUNIT_ASSERT_DOUBLES_EQUAL( 95.333333333, fps.amount(), delta );
   }
/*
   void JustTest()
   {
      CPPUNIT_ASSERT( 2 == 2 );
   }
*/

   CPPUNIT_TEST_SUITE( EnglishUnitTest );
   CPPUNIT_TEST( TestFPS );
   CPPUNIT_TEST( TestLength);
   //CPPUNIT_TEST( JustTest );
   //CPPUNIT_TEST( TestWithlog );
   CPPUNIT_TEST_SUITE_END();

};


CPPUNIT_TEST_SUITE_REGISTRATION( EnglishUnitTest );

// Copyright © 2005-2015 "Curt" Leslie L. Martin, All rights reserved.
// curt.leslie.lewis.martin@gmail.com
//
// Permission to use, copy, modify, and distribute this software for any
// purpose is hereby granted without fee, provided that this copyright and
// permissions notice appear in all copies and derivatives.
//
// This software is provided "as is" without express or implied warranty.
