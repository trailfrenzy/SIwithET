#include <cppunit/extensions/HelperMacros.h>
//#include "EnglishTypes.h"
#include "MetricTypes.h"
#include "operators.h"
#include "conversion_cast.h"


class MetricUnitTest : public CppUnit::TestFixture
{
public:
   void setUp(){}
   void tearDown(){}
private:


   void BasicTest()
   {
	   typedef Metric::AtomicUnit::Meter m;
	   CPPUNIT_ASSERT_EQUAL( std::string("meter"), std::string( m::str() ) );
	   CPPUNIT_ASSERT( m::IsBase == true );
	   CPPUNIT_ASSERT( m::toBase() == 1.0 );
	   CPPUNIT_ASSERT( m::fromBase() == 1.0 );
   }
   void BasicTestLength()
   {
		typedef Metric::AtomicUnit::Meter m;
		typedef Metric::AtomicUnit::Kilometer km;
		CPPUNIT_ASSERT_EQUAL( 1000.0, km::toBase() );
   }

   CPPUNIT_TEST_SUITE( MetricUnitTest );
   CPPUNIT_TEST( BasicTest );
   CPPUNIT_TEST( BasicTestLength );
   CPPUNIT_TEST_SUITE_END();

};

CPPUNIT_TEST_SUITE_REGISTRATION( MetricUnitTest );

// Copyright © 2005-2015 "Curt" Leslie L. Martin, All rights reserved.
// curt.leslie.lewis.martin@gmail.com
//
// Permission to use, copy, modify, and distribute this software for any
// purpose is hereby granted without fee, provided that this copyright and
// permissions notice appear in all copies and derivatives.
//
// This software is provided "as is" without express or implied warranty.

