#include <cppunit/extensions/HelperMacros.h>
#include "SI.h"
#include "MetricTypes.h"
#include "TimeAtomicUnits.h"  // contains the time atomic units
#include "operators.h"
#include "WhatAmI.h"

namespace
{
   namespace AT = SOU::Time::AtomicUnit;
// basic test on the multiplication operator
class DivisionFirst : public CppUnit::TestFixture
{
   //using namespace Metric;
   typedef Metric::AtomicUnit::Meter Meter;
   typedef AT::second second;
   typedef Metric::AtomicUnit::gram gram;
   typedef Metric::AtomicUnit::coulomb coul;
   typedef Metric::AtomicUnit::kelvin kelvin;
   typedef SOU::MakeType<Meter,second,gram,kelvin,coul> tMake;
   typedef tMake::MakeDim<1,0,0,0,0>::type t_Meter;
   typedef tMake::MakeDim<2,0,0,0,0>::type t_MeterSq;
   typedef tMake::MakeDim<3,0,0,0,0>::type t_MeterCubed;
   
public:
   void setUp() { }
   void tearDown() {}
private: 
   /// Test division during assignement
   void TestDiv_Result()
   {   
      // division during intialization
      t_Meter m( t_MeterSq(1.0) / t_Meter(1.0));
      CPPUNIT_ASSERT( m == 1.0 );
      
      t_Meter m2 = t_MeterSq(1.0) / t_Meter(2.0);
      CPPUNIT_ASSERT( m2 == 0.5 );
   }

   /// Test with cube
   void TestWithCube()
   {
      t_MeterSq sq1 = t_MeterCubed(9.0) / t_Meter(2.0);
      CPPUNIT_ASSERT( sq1 == 4.5 ); 
   
      t_Meter m1 = t_MeterCubed(15.0) / t_MeterSq(5.0);
      CPPUNIT_ASSERT( m1 == 3.0 );
   
      t_Meter m2 = t_MeterSq( 4.0 ) / t_Meter( 2.0 );
      CPPUNIT_ASSERT( m2 == 2.0 );
   }
   
   /// @code The SystemOfUnits::operators::Div_Result<T1,T2> @endcode must be able to handle chaining
   /// of division.
   void TestChaining()
   {
      t_Meter m1 = t_Meter(2.0) * t_Meter(2.0) / t_Meter(2.0);
      CPPUNIT_ASSERT( m1 == 2.0 );
      
      t_Meter m2 = t_MeterCubed( 27.0 ) / t_Meter(3.0) / t_Meter(3.0);
      CPPUNIT_ASSERT( m2 == 3.0 );
      
      m2 = t_MeterCubed( 27.0 ) / t_Meter(3.0) / t_Meter(3.0) / 2;
      CPPUNIT_ASSERT_EQUAL( 1.5, m2.amount() );

      t_Meter m3 = (t_Meter(2.0) * t_Meter(9.0) ) / t_Meter(3.0);
      CPPUNIT_ASSERT( m3 == 6.0 );

      t_Meter const m4 = 2 * (t_Meter(2.0) * t_Meter(9.0) ) / t_Meter(3.0);
      CPPUNIT_ASSERT_EQUAL( 12.0, m4.amount() );

      t_Meter const m5 = ( 2 * t_Meter(2.0) * t_Meter(9.0) ) / t_Meter(3.0);
      CPPUNIT_ASSERT_EQUAL( 12.0, m5.amount() );
   }

   /// Test that the result can be diminsionless such as Mach or dB.
   void TestDimisionLess()
   {
      // see how well a diminsonless unit is handled
      double d1 = t_MeterSq(12.0) / t_MeterSq(4.0);
      CPPUNIT_ASSERT( d1 == 3.0 );

      double const d2 = t_Meter(11.0) / t_Meter(11.0);
      CPPUNIT_ASSERT_EQUAL( 1.0, d2 );
   }

   /** Test with non-atomic values.  When dividing meters by centimeters. */
   void TestWithNonAtomicUnitUnitsLength()
   {
      using namespace Metric;
      const t_centimeter cent(200.0);
      t_Meter meter = 7.0;
      t_MeterSq meterSq(14.0);

      typedef SOU::operators::Div_Result<t_MeterSq, t_centimeter> t_result;
      CPPUNIT_ASSERT( static_cast<bool>(t_result::ALLTYPES_THE_SAME::val) == true );
      
      meter = meterSq / cent;
      CPPUNIT_ASSERT_EQUAL( 7.0, meter.amount() );

      typedef SOU::MakeSQ< Metric::t_centimeter >::type t_centSq;
      t_centSq centSq = t_centimeter(600) * meter;
      t_centimeter cent2 = centSq / meter;
      CPPUNIT_ASSERT_EQUAL( 600.0, cent2.amount() );

      typedef SOU::MakeSQ< Metric::t_kilometer >::type t_kiloSQ;
      Metric::t_kilometer kilo = t_kiloSQ( 12.0 ) / cent2;
      CPPUNIT_ASSERT_EQUAL( 2000.0, kilo.amount() );
   }

  CPPUNIT_TEST_SUITE( DivisionFirst );
  CPPUNIT_TEST( TestDiv_Result );
  CPPUNIT_TEST( TestWithCube );
  CPPUNIT_TEST( TestChaining );
  CPPUNIT_TEST( TestDimisionLess );
  CPPUNIT_TEST( TestWithNonAtomicUnitUnitsLength );
  CPPUNIT_TEST_SUITE_END();
};

CPPUNIT_TEST_SUITE_REGISTRATION( DivisionFirst );

// template used to make many division tests
template< int RESULT, int DIV1, int DIV2 >
class SOU_Division : public CppUnit::TestFixture
{
   // define the basic types that will be used here.
   typedef Metric::AtomicUnit::Meter Meter;
   typedef SOU::Time::AtomicUnit::second second;
   typedef Metric::AtomicUnit::gram gram;
   typedef Metric::AtomicUnit::coulomb coul;
   typedef Metric::AtomicUnit::kelvin kelvin;

   // build a type from the basics
   typedef SOU::MakeType<Meter,second, gram, kelvin, coul> tMake;

   // Produce the actual Unit.
   typename typedef tMake::MakeDim< RESULT, 0,0,0,0 >::type t_1;
   typename typedef tMake::MakeDim< DIV1,   0,0,0,0 >::type t_2;
   typename typedef tMake::MakeDim< DIV2,   0,0,0,0 >::type t_3;
   typename typedef tMake::MakeDim<-RESULT, 0,0,0,0 >::type t_inv;
   
   // attributes used in the class
   t_1 const * m_1;
   t_2 const * m_2;
   t_3 * m_3;

public:
   void setUp()
   {
      m_1 = new t_1( 12.0 );
      m_2 = new t_2( 4.0 );
      m_3 = new t_3( 3.0);
   }
   void tearDown()
   {
      delete m_1;
      delete m_2;
      delete m_3;
   }
private:
   /** Early test to show how @code SOU::operators::Div_Result< T1, T2 > @endcode worked

      */
   void TestDiv_Result()
   {  
      SOU::operators::Div_Result< t_1, t_2 > res(*m_1, *m_2);
      CPPUNIT_ASSERT( res.result() == *m_3 );
   }

   /// early test show that a simple division could work.
   void Test2()
   {
      t_3 res = *m_1 / *m_2;
      CPPUNIT_ASSERT( res == *m_3 );
      CPPUNIT_ASSERT( *m_3 == *m_1 / *m_2 );

      t_2 res2 = *m_1 / *m_3;
      CPPUNIT_ASSERT( res2 == *m_2 );
   }
   
   /// Did operator/() work with scalar values?
   void TestWithScaler()
   {
      t_1 const res = *m_1 / 4.0;
	  CPPUNIT_ASSERT_EQUAL_MESSAGE( SOU::WhatAmI(res), 3.0, res.amount() );

      t_inv res1 = 36.0 / *m_1;
	  CPPUNIT_ASSERT_EQUAL_MESSAGE( SOU::WhatAmI(res1), 3.0, res1.amount() );
   }

   void TestDivideAssign()
   {
		*m_3 /= 2.0;
		CPPUNIT_ASSERT_EQUAL( 1.5, m_3->amount() );

		*m_3 /= 0.1;
		CPPUNIT_ASSERT_EQUAL( 15.0, m_3->amount() );
   }

  CPPUNIT_TEST_SUITE( SOU_Division );
  CPPUNIT_TEST( TestDiv_Result );
  CPPUNIT_TEST( Test2 );
  CPPUNIT_TEST( TestWithScaler );
  CPPUNIT_TEST( TestDivideAssign );
  CPPUNIT_TEST_SUITE_END();
};

typedef SOU_Division< 2, 1, 1> tDiv1;
CPPUNIT_TEST_SUITE_REGISTRATION( tDiv1 );

typedef SOU_Division<3,2,1> tDiv2;
CPPUNIT_TEST_SUITE_REGISTRATION( tDiv2 );

typedef SOU_Division<5,2,3> tDiv3;
CPPUNIT_TEST_SUITE_REGISTRATION( tDiv3 );

typedef SOU_Division<2,2,0> tDiv4;
CPPUNIT_TEST_SUITE_REGISTRATION( tDiv4 );

typedef SOU_Division<2,0,2> tDiv5;
CPPUNIT_TEST_SUITE_REGISTRATION( tDiv5 );

typedef SOU_Division<2,4,-2> tDiv6;
CPPUNIT_TEST_SUITE_REGISTRATION( tDiv6 );
}
// Copyright © 2005-2015 "Curt" Leslie L. Martin, All rights reserved.
// curt.leslie.lewis.martin@gmail.com
//
// Permission to use, copy, modify, and distribute this software for any
// purpose is hereby granted without fee, provided that this copyright and
// permissions notice appear in all copies and derivatives.
//
// This software is provided "as is" without express or implied warranty.
