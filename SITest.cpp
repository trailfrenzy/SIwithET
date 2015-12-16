

#include <cppunit/extensions/HelperMacros.h> // the macros and headers needed by CPPUnit
#include "SI.h"
#include "MetricTypes.h"
//#include "boost/type_traits/is_same.hpp"  // used by SITestSQ
#include "template_help.h"

template< class UNIT_TYPE >
class SITest : public CppUnit::TestFixture
{
   CPPUNIT_TEST_SUITE( SITest );
   CPPUNIT_TEST( Assignment );
   CPPUNIT_TEST( NotEqual );
   CPPUNIT_TEST( LessThan );
   CPPUNIT_TEST( GreaterThan );
   CPPUNIT_TEST( Comparison );
   CPPUNIT_TEST( Addition );
   CPPUNIT_TEST( AdditionAssignment );
   CPPUNIT_TEST( Subtraction );
   CPPUNIT_TEST( SubtractionAssignment );
   CPPUNIT_TEST( Chaining );
   //CPPUNIT_TEST( Squaring );
   CPPUNIT_TEST_SUITE_END();

protected:
   UNIT_TYPE * m_1;
   UNIT_TYPE * m_2;
   UNIT_TYPE const * m_3;
   UNIT_TYPE const * m_4;


public:
   void setUp()
   {
      m_1 = new UNIT_TYPE(8.0);
      m_2 = new UNIT_TYPE(5.0);
      m_3 = new UNIT_TYPE(3.0);
      m_4 = new UNIT_TYPE(4.0);
   }

   void tearDown()
   {
      delete m_1;
      delete m_2;
      delete m_3;
      delete m_4;
   }         
private:
   /// All types should be the same as a double
   void SizeOf()
   {
      CPPUNIT_ASSERT_MESSAGE("was not 64 bit", sizeof( double ) == sizeof( UNIT_TYPE ) );
   }

   void Comparison()
   {
      //using namespace SI;
      *m_1 = 4.5;
      *m_2 = 4.5;

      CPPUNIT_ASSERT( *m_1 == *m_2 );
      CPPUNIT_ASSERT( m_1->amount() == 4.5 );

	  // testing with one side double the other side unitType
      CPPUNIT_ASSERT( *m_1 == 4.5 );
      CPPUNIT_ASSERT( 4.5 == *m_1 );
   }

   void NotEqual()
   {
      CPPUNIT_ASSERT( *m_1 != *m_2 );
	  CPPUNIT_ASSERT( 4.5 != *m_2 );
	  CPPUNIT_ASSERT( *m_2 != 4.5 );
   }

   void LessThan()
   {
      *m_1 = 4.55555;
      *m_2 = 4.55556;
      CPPUNIT_ASSERT( *m_1 < *m_2 );
      CPPUNIT_ASSERT( *m_3 < *m_4 );
   }

   void GreaterThan()
   {
      CPPUNIT_ASSERT( *m_4 > *m_3 );
   }

   void Assignment()
   {
      *m_1 = 68.9;
      CPPUNIT_ASSERT_MESSAGE( "check that m_1 was assigned correctly", *m_1 == 68.9 );

      *m_2 = *m_1;
      CPPUNIT_ASSERT( *m_2 == 68.9 );

	  *m_2 = UNIT_TYPE( 4.5 );
	  CPPUNIT_ASSERT( *m_2 == 4.5 );
   }

   void Addition()
   {
      CPPUNIT_ASSERT( *m_1 == *m_2 + *m_3);
	  CPPUNIT_ASSERT( *m_1 == *m_3 + *m_2 );
      CPPUNIT_ASSERT( *m_1 == *m_4 + *m_4);
      //CPPUNIT_ASSERT_DOUBLES_EQUAL( *m_1, *m_4 + *m_4, 0.00000001 ); 
   }
   void AdditionAssignment()
   {
      *m_2 += *m_3;
      CPPUNIT_ASSERT( *m_1 == *m_2 );
   }
   void Subtraction()
   {
      CPPUNIT_ASSERT( *m_1 - *m_2 == *m_3 );
      CPPUNIT_ASSERT( *m_3 == *m_1 - *m_2 );
   }
   void SubtractionAssignment()
   {
      *m_1 -= *m_2;
      CPPUNIT_ASSERT( *m_1 == *m_3 );
   }
   void Chaining()
   {
      CPPUNIT_ASSERT( *m_4 + *m_4 - *m_2 == *m_3 );

      UNIT_TYPE u1(12.0);
      UNIT_TYPE u2( 6.0);
      CPPUNIT_ASSERT( u2 + u2 + u2 + u2 - u1 == u1 );
      CPPUNIT_ASSERT( u2 + u2 + u2 + u2 - u1 - u2 == u1 - u2 );
	  CPPUNIT_ASSERT( UNIT_TYPE(2.0) + UNIT_TYPE(3.0) == UNIT_TYPE(5.0) );
   }

};

class SITestSQ : public CppUnit::TestFixture
{
   void Squaring()
   {
      namespace AT = SOU::Time::AtomicUnit;
      using namespace Metric::AtomicUnit;
      typedef SOU::unitType< Meter, 0, AT::second,-1, gram, 1, SOU::NoDim,0,SOU::NoDim > t_gramPsec;
      typedef SOU::unitType< Meter, 0, AT::second,-2, gram, 2, SOU::NoDim,0,SOU::NoDim > t_gramPsecSQ;

      typedef SOU::MakeSQ<t_gramPsec>::type gramSQ;

	  enum { b = SystemOfUnits::is_same< gramSQ, typename t_gramPsecSQ >::value };
      CPPUNIT_ASSERT( b );
      
   }

   /// Size is needed to show that unitType<> is the same size as a double
   void TestSize()
   {
      CPPUNIT_ASSERT( sizeof(double) == sizeof( Metric::t_meter ) );
   }

   CPPUNIT_TEST_SUITE( SITestSQ );
   CPPUNIT_TEST( Squaring );
   CPPUNIT_TEST( TestSize );
   CPPUNIT_TEST_SUITE_END();
};

CPPUNIT_TEST_SUITE_REGISTRATION( SITest<Metric::t_meter> );
CPPUNIT_TEST_SUITE_REGISTRATION( SITest<Metric::t_metersecond> );
CPPUNIT_TEST_SUITE_REGISTRATION( SITest<Metric::t_second> );
CPPUNIT_TEST_SUITE_REGISTRATION( SITest<Metric::t_velocity> );
CPPUNIT_TEST_SUITE_REGISTRATION( SITest<Metric::t_gramPsec> );
CPPUNIT_TEST_SUITE_REGISTRATION( SITestSQ );

typedef Metric::AtomicUnit::Meter Meter;
typedef SOU::Time::AtomicUnit::second second;
typedef Metric::AtomicUnit::gram gram;
typedef SOU::MakeType< Meter, second, Metric::AtomicUnit::kilogram, Metric::AtomicUnit::kelvin, Metric::AtomicUnit::coulomb > t_Base;
//typedef SI::unitType< Meter, 1, second, 0, gram, 0 > t_Meter;
//typedef t_Base::MakeDim<1,0,0,0,0>::type t_Meter;

typedef t_Base::MakeDim<2,0,0,0,0>::type t_MeterSq;
typedef t_Base::MakeDim<3,0,0,0,0>::type t_MeterCubed;

CPPUNIT_TEST_SUITE_REGISTRATION( SITest<t_MeterSq> );
CPPUNIT_TEST_SUITE_REGISTRATION( SITest<t_MeterCubed>);

// Copyright © 2005-2015 "Curt" Leslie L. Martin, All rights reserved.
// curt.leslie.lewis.martin@gmail.com
//
// Permission to use, copy, modify, and distribute this software for any
// purpose is hereby granted without fee, provided that this copyright and
// permissions notice appear in all copies and derivatives.
//
// This software is provided "as is" without express or implied warranty.
