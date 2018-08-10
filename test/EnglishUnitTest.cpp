#include <gtest\gtest.h>
//#include <cppunit/extensions/HelperMacros.h>
#include "EnglishTypes.h"
#include "MetricTypes.h"
#include "operators.h"
#include "conversion_cast.h"

namespace
{
   constexpr double delta = 0.000001;
}

// basic test on the multiplication operator
//class EnglishUnitTest : public ::testing::Test //: public CppUnit::TestFixture
//{
//public:
//	void SetUp() {}
//	void TearDown() {}
//private:
//}
   /// Test converting Feet per second from Feet / Second.
   TEST(EnglishUnitTest, TestFPS )
   {
      English::t_foot Feet = 144;
      English::t_second Second = 4;

      English::t_FPS fps = Feet / Second;

      EXPECT_DOUBLE_EQ( 36.0, fps.amount() );

      English::t_FPSS fpss = fps/English::t_second(2.0);
	  EXPECT_DOUBLE_EQ( 18.0, fpss.amount() );
   }
   /// Tests converting different types of length.
   TEST(EnglishUnitTest, TestLength )
   {
      using namespace SOU;

      English::t_mile mile = 1.0;
      English::t_foot feet = SOU::conversion_cast< English::t_foot >( mile );
	  EXPECT_DOUBLE_EQ( 5280.0, feet.amount() );

      feet = 15;
      English::t_yard yard = conversion_cast< English::t_yard >( feet );
	  EXPECT_DOUBLE_EQ( 5.0, yard.amount() );

      English::t_mph mph = 65.0;
      English::t_FPS fps = SOU::conversion_cast< English::t_FPS >( mph );
	  EXPECT_NEAR( 95.333333333, fps.amount(), delta );
   }

//   CPPUNIT_TEST_SUITE( EnglishUnitTest );
//   CPPUNIT_TEST( TestFPS );
//   CPPUNIT_TEST( TestLength);
//   //CPPUNIT_TEST( JustTest );
//   //CPPUNIT_TEST( TestWithlog );
//   CPPUNIT_TEST_SUITE_END();
//
//};
//
//
//CPPUNIT_TEST_SUITE_REGISTRATION( EnglishUnitTest );

// Copyright © 2005-2015 "Curt" Leslie L. Martin, All rights reserved.
// curt.leslie.lewis.martin@gmail.com
//
// Permission to use, copy, modify, and distribute this software for any
// purpose is hereby granted without fee, provided that this copyright and
// permissions notice appear in all copies and derivatives.
//
// This software is provided "as is" without express or implied warranty.
