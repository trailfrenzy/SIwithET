/* NOTE:
	The purpose of this file is to test and validate that the conversion_cast inside of
	file conversion_cast.h works correctly.

	Do to the way that CPPUnit can be used, the the hole class is inside the cpp file and
	no header is needed for the tester.  A header could be used but to keep the class simpler
	the whole test is placed inside the cpp.

	Think of the this file as a contract for what file confersion_cast.h has.
*/
#include <cppunit/extensions/HelperMacros.h>
//#include "boost/static_assert.hpp"
#include "SI.h"
#include "MetricTypes.h"
#include "conversion_cast.h"
#include "pow.h"

class conversion_castTest : public CppUnit::TestFixture
{
	Metric::t_centimeter m_cent;
public:
   void setUp() { m_cent = 0.0; }
   void tearDown() {}
private: 

	/// Test how well compile time exponential power template works.
	/// @see SI::helpers::P::thePower
	/// @see Metric::AtomicUnit
	void TestPow()
	{
      using namespace SOU::helpers;

		CPPUNIT_ASSERT_DOUBLES_EQUAL( 1.0e+010  , P< Metric::AtomicUnit::Centimeter >::thePower<-5>::toBase(), 0.0001 );
		CPPUNIT_ASSERT_DOUBLES_EQUAL( 1.0e+008  , P< Metric::AtomicUnit::Centimeter >::thePower<-4>::toBase(), 0.0001 );
		CPPUNIT_ASSERT_DOUBLES_EQUAL( 1.0e+006  , P< Metric::AtomicUnit::Centimeter >::thePower<-3>::toBase(), 0.0001 );
		CPPUNIT_ASSERT_EQUAL( 1.0e+004  , P< Metric::AtomicUnit::Centimeter >::thePower<-2>::toBase() );
		CPPUNIT_ASSERT_EQUAL( 100.0  , P< Metric::AtomicUnit::Centimeter >::thePower<-1>::toBase() );
		CPPUNIT_ASSERT_EQUAL( 1.0  , P< Metric::AtomicUnit::Centimeter >::thePower<0>::toBase() );
		CPPUNIT_ASSERT_EQUAL( 0.01  , P< Metric::AtomicUnit::Centimeter >::thePower<1>::toBase() );
		CPPUNIT_ASSERT_EQUAL( 0.0001  , P< Metric::AtomicUnit::Centimeter >::thePower<2>::toBase() );
		CPPUNIT_ASSERT_DOUBLES_EQUAL( 1.0e-006, P< Metric::AtomicUnit::Centimeter >::thePower<3>::toBase(), 0.000001 );
		CPPUNIT_ASSERT_DOUBLES_EQUAL( 1.0e-008, P< Metric::AtomicUnit::Centimeter >::thePower<4>::toBase(), 0.000001 );
		CPPUNIT_ASSERT_DOUBLES_EQUAL( 1.0e-010, P< Metric::AtomicUnit::Centimeter >::thePower<5>::toBase(), 0.000001 );
		CPPUNIT_ASSERT_DOUBLES_EQUAL( 1.0e-012, P< Metric::AtomicUnit::Centimeter >::thePower<6>::toBase(), 0.000001 );

		CPPUNIT_ASSERT_EQUAL( 10000.0, P< SOU::MakeFrom<Metric::AtomicUnit::Centimeter> >::thePower<2>::toBase() );
	}

	/// Test basic length conversions
	void TestLength()
	{
		Metric::t_centimeter cent(20.0);
		Metric::t_meter meter = SOU::conversion_cast<Metric::t_meter>( cent );
		CPPUNIT_ASSERT_EQUAL( 0.20, meter.amount() );

		m_cent = 200.0;
		Metric::t_kilometer kilo = SOU::conversion_cast<Metric::t_kilometer>( m_cent );
		CPPUNIT_ASSERT_EQUAL( 0.002, kilo.amount() );

		m_cent = SOU::conversion_cast<Metric::t_centimeter>(meter);
	}

	/// Test Lengths when squared
	void TestLengthSquared()
	{
		typedef SOU::MakeSQ< Metric::t_meter >::type t_meterSq;
		typedef SOU::MakeSQ< Metric::t_centimeter >::type t_centSq;
		t_centSq cent2 = 10000.0;

		t_meterSq m2 = SOU::conversion_cast< t_meterSq >( cent2 );

		CPPUNIT_ASSERT_EQUAL( 1.0, m2.amount() );
	}

	/// Test time conversions
	void TestTime()
	{
		Metric::t_hour hr(2.0);
		Metric::t_minute min = SOU::conversion_cast<Metric::t_minute>(hr);
		CPPUNIT_ASSERT_EQUAL( 120.0, min.amount() );

      // hour to sec
      Metric::t_second sec = SOU::conversion_cast<Metric::t_second>(hr);
      CPPUNIT_ASSERT_EQUAL( 2.0*60.0*60.0, sec.amount() );

      // sec to hour
      sec = 22.0 * 60.0 * 60.0;
      hr = SOU::conversion_cast<Metric::t_hour>(sec);
      CPPUNIT_ASSERT_EQUAL( 22.0, hr.amount() );
	}

   /// Test Time squared.  Also to see how well conversion_cast<> works with squared diminsions.
	void TestTimeSq()
	{
		typedef SOU::MakeSQ<Metric::t_second>::type t_secSq;
		typedef SOU::MakeSQ<Metric::t_minute>::type t_minSq;

		t_minSq minSq = 2.0;
		t_secSq secSq = SOU::conversion_cast<t_secSq>(minSq);
		CPPUNIT_ASSERT_EQUAL( 7200.0, secSq.amount() );
	}

   /// Test the inverse time.
	void TestInverseTimeSq()
	{
		typedef Metric::AUMetric::MakeDim<1, -2, 0,0,0>::type ACCinM;
		typedef SOU::unitType
			< Metric::AtomicUnit::Kilometer, 1
			, SOU::Time::AtomicUnit::second, -2
			, Metric::AtomicUnit::gram, 0
			, Metric::AtomicUnit::kelvin,0
			, Metric::AtomicUnit::coulomb,0
			> ACCinKM;
		
		ACCinKM accKM1 = 2.0;
		ACCinM  accM1 = SOU::conversion_cast<ACCinM>(accKM1);
		CPPUNIT_ASSERT_DOUBLES_EQUAL( 2000.0, accM1.amount(), 0.00001 );

	}

	/// Test the Mass
	void TestMass()
	{
		Metric::t_gram g( 400.0 );
		Metric::t_kilogram kg = SOU::conversion_cast< Metric::t_kilogram>( g );
		CPPUNIT_ASSERT_EQUAL( 0.4, kg.amount() );
	}

	/// Test Mass Squared
	void TestMassSq()
	{
		typedef SOU::MakeSQ< Metric::t_gram >::type t_gramSq;
		typedef SOU::MakeSQ< Metric::t_kilogram >::type t_kiloSq;
		t_kiloSq kiloSq = 1.0;
		t_gramSq gramSq = SOU::conversion_cast< t_gramSq >( kiloSq );
		CPPUNIT_ASSERT_EQUAL( 1e6, gramSq.amount() );
	}

   /// Test where the dimensions are the wrong size for a conversion.  Test should be a failure.
   void TestWrongDim()
   {
      using namespace SOU;
      namespace AU = Metric::AtomicUnit;

      typedef SOU::unitType< AU::Meter, 1, AT::minute, 1, AU::gram, 0,AU::kelvin,0, AU::coulomb,0 > t_ms;
      typedef SOU::unitType< AU::Meter, 1, AT::minute, 0, AU::gram, 0,AU::kelvin,0, AU::coulomb,0 > t_m;

      typedef t_m IN;
      typedef t_ms OUT;
		enum { eALLDIMS_THE_SAME = IN::eL==OUT::eL && IN::et==OUT::et && IN::eM==OUT::eM};
      CPPUNIT_ASSERT( !eALLDIMS_THE_SAME );
      //BOOST_STATIC_ASSERT< true >;

      //t_m m = 9.0;
      //t_ms ms = conversion_cast< t_ms >( m );

   }

	/// The test suite
   CPPUNIT_TEST_SUITE( conversion_castTest );
   CPPUNIT_TEST( TestPow );
   CPPUNIT_TEST( TestLength );
   CPPUNIT_TEST( TestLengthSquared );
   CPPUNIT_TEST( TestTime );
   CPPUNIT_TEST( TestTimeSq );
   CPPUNIT_TEST( TestInverseTimeSq );
   CPPUNIT_TEST( TestMass );
   CPPUNIT_TEST( TestMassSq );
   CPPUNIT_TEST( TestWrongDim );
   CPPUNIT_TEST_SUITE_END();

};

CPPUNIT_TEST_SUITE_REGISTRATION( conversion_castTest );

// Copyright © 2005-2015 "Curt" Leslie L. Martin, All rights reserved.
// curt.leslie.lewis.martin@gmail.com
//
// Permission to use, copy, modify, and distribute this software for any
// purpose is hereby granted without fee, provided that this copyright and
// permissions notice appear in all copies and derivatives.
//
// This software is provided "as is" without express or implied warranty.
